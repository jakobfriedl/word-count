#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <map>
#include <set>
#include <cctype>
#include <locale>
#include <codecvt>
#include <regex>

using namespace std;
namespace fs = std::filesystem;

//get all Files in a Directory
vector<fs::path> getFiles(fs::path path) {
    vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }
    return files;
}

//get all Subdirectories in a Directory
vector<fs::path> getSubdirectories(fs::path path) {
    vector<fs::path> subdirectories;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            subdirectories.push_back(entry.path());
        }
    }
    return subdirectories;
}

//get all Files in a Directory and all Subdirectories
vector<fs::path> getAllFiles(fs::path path) {
    vector<fs::path> files;
    vector<fs::path> subdirectories = getSubdirectories(path);
    for (fs::path subdirectory : subdirectories) {
        vector<fs::path> subdirectoryFiles = getAllFiles(subdirectory);
        files.insert(files.end(), subdirectoryFiles.begin(), subdirectoryFiles.end());
    }
    vector<fs::path> directoryFiles = getFiles(path);
    files.insert(files.end(), directoryFiles.begin(), directoryFiles.end());
    return files;
}

//get all Strings in a File
vector<string> getStrings(fs::path path) {
    vector<string> strings;
    wifstream file(path);
    wstring line;
    while (getline(file, line)) {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        string utf8line = converter.to_bytes(line);
        regex reg("[^a-zA-Z0-9 ]");
        utf8line = regex_replace(utf8line, reg, "");
        transform(utf8line.begin(), utf8line.end(), utf8line.begin(), ::tolower);
        istringstream iss(utf8line);
        string word;
        while (iss >> word) {
            strings.push_back(word);
        }
    }
    return strings;
}

//get all Strings in a File and all Files in a Directory and all Subdirectories
vector<string> getAllStrings(fs::path path) {
    vector<string> strings;
    vector<fs::path> files = getAllFiles(path);
    for (fs::path file : files) {
        vector<string> fileStrings = getStrings(file);
        strings.insert(strings.end(), fileStrings.begin(), fileStrings.end());
    }
    return strings;
}

//count all Strings in a File and all Files in a Directory and all Subdirectories
map<string, int> countStrings(fs::path path) {
    map<string, int> stringCount;
    vector<string> strings = getAllStrings(path);
    for (string string : strings) {
        if (stringCount.find(string) == stringCount.end()) {
            stringCount[string] = 1;
        }
        else {
            stringCount[string]++;
        }
    }
    return stringCount;
}

//print the Frequency and Strings sorted reverse alphabetically
void printStrings(fs::path path) {
    map<string, int> stringCount = countStrings(path);
    multiset<pair<int, string>, greater<pair<int, string>>> stringFrequency;
    for (auto string : stringCount) {
        stringFrequency.insert(make_pair(string.second, string.first));
    }
    for (auto string : stringFrequency) {
        cout << string.first << " " << string.second << endl;
    }
}

// write the Frequency and Strings sorted reverse alphabetically to a File
void writeStrings(fs::path path) {
    map<string, int> stringCount = countStrings(path);
    multiset<pair<int, string>, greater<pair<int, string>>> stringFrequency;
    for (auto string : stringCount) {
        stringFrequency.insert(make_pair(string.second, string.first));
    }
    ofstream file("output.txt");
    for (auto string : stringFrequency) {
        file << string.first << " " << string.second << endl;
    }
}

int main() {
    string path;
    cout << "Enter path to directory: ";
    cin >> path;



    // //Print the Output to the Console
    // start the timer
    // auto start = chrono::high_resolution_clock::now();
    // printStrings(path);
    // //end the timer
    // auto end = chrono::high_resolution_clock::now();
    // //calculate the time
    // auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // //print the time
    // cout << "Time: " << duration.count() << "ms" << endl;



    //Write the Output to a File
    //start the timer
    auto start = chrono::high_resolution_clock::now();
    writeStrings(path);
    //end the timer
    auto end = chrono::high_resolution_clock::now();
    //calculate the time
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    //print the time
    cout << "Time: " << duration.count() << "ms" << endl;

    return 0;
}


