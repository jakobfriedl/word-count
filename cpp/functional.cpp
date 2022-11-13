#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <map>
#include <set>
#include <regex>
#include <ranges>

using namespace std;
namespace fs = std::filesystem;

// get all Files in a Directory
vector<fs::path> getFiles(fs::path path, string extension)
{
    vector<fs::path> files;
    ranges::copy_if(fs::directory_iterator(path), back_inserter(files), [&extension](const auto &entry)
                    { return entry.is_regular_file() && entry.path().extension() == extension; });
    return files;
}

// get all Subdirectories in a Directory
vector<fs::path> getSubdirectories(fs::path path)
{
    vector<fs::path> subdirectories;
    ranges::copy_if(fs::directory_iterator(path), back_inserter(subdirectories), [](const auto &entry)
                    { return entry.is_directory(); });
    return subdirectories;
}

// get all Files in a Directory and all Subdirectories
vector<fs::path> getAllFiles(fs::path path, string extension)
{
    vector<fs::path> files;
    vector<fs::path> subdirectories = getSubdirectories(path);
    ranges::for_each(subdirectories, [&files, &extension](const auto &subdirectory)
                     {
        vector<fs::path> subdirectoryFiles = getAllFiles(subdirectory, extension);
        ranges::copy(subdirectoryFiles, back_inserter(files)); });
    vector<fs::path> directoryFiles = getFiles(path, extension);
    ranges::copy(directoryFiles, back_inserter(files));
    return files;
}

// get all Strings in a File
vector<string> getStrings(fs::path path)
{
    vector<string> strings;
    wifstream file(path);
    wstring line;
    while (getline(file, line))
    {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        string utf8line = converter.to_bytes(line);
        regex reg("[^a-zA-Z0-9 ]");
        utf8line = regex_replace(utf8line, reg, "");
        transform(utf8line.begin(), utf8line.end(), utf8line.begin(), ::tolower);
        istringstream iss(utf8line);
        string word;
        while (iss >> word)
        {
            strings.push_back(word);
        }
    }
    return strings;
}

// get all Strings in a File and all Files in a Directory and all Subdirectories
vector<string> getAllStrings(fs::path path, string extension)
{
    vector<string> strings;
    vector<fs::path> files = getAllFiles(path, extension);
    ranges::for_each(files, [&strings](const auto &file)
                     {
        vector<string> fileStrings = getStrings(file);
        ranges::copy(fileStrings, back_inserter(strings)); });
    return strings;
}

// count all Strings in a File and all Files in a Directory and all Subdirectories
map<string, int> countStrings(fs::path path, string extension)
{
    map<string, int> stringCount;
    vector<string> strings = getAllStrings(path, extension);
    ranges::for_each(strings, [&stringCount](const auto &string)
                     {
        if (stringCount.find(string) == stringCount.end()) {
            stringCount[string] = 1;
        }
        else {
            stringCount[string]++;
        } });
    return stringCount;
}

// write the Frequency and Strings sorted reverse alphabetically to a File
void writeStrings(fs::path path, string extension)
{
    map<string, int> stringCount = countStrings(path, extension);
    multiset<pair<int, string>, greater<pair<int, string>>> stringFrequency;
    ranges::for_each(stringCount, [&stringFrequency](const auto &string)
                     { stringFrequency.insert(make_pair(string.second, string.first)); });
    ofstream file("output.txt");
    ranges::for_each(stringFrequency, [&file](const auto &string)
                     { file << string.first << " " << string.second << endl; });
}

// get path from command line
int main(int argc, char *argv[])
{
    string path;
    string extension;
    if (argc == 3)
    {
        path = argv[1];
        extension = argv[2];
    }
    else
    {
        cout << "Please enter a path: ";
        cin >> path;
        cout << "Please enter a file extension: ";
        cin >> extension;
    }

    // Write the Output to a File
    // start the timer
    auto start = chrono::high_resolution_clock::now();
    writeStrings(path, extension);
    // end the timer
    auto end = chrono::high_resolution_clock::now();
    // calculate the time
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // print the time
    cout << "Time: " << duration.count() << "ms" << endl;

    return 0;
}