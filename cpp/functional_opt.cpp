#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <map>
#include <set>
#include <regex>
#include <ranges>
#include <functional>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <execution>
#include <thread>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
namespace fs = std::filesystem;

// get all Files in Directory and all Subdirectories
vector<fs::path> getAllFiles(fs::path path, string extension)
{
    vector<fs::path> files;
    for (const auto &entry : fs::recursive_directory_iterator(path))
    {
        if (entry.is_regular_file() && entry.path().extension() == extension)
        {
            files.push_back(entry.path());
        }
    }
    return files;
}

//get all alphanumeric strings from all files using shared memory
vector<string> getStrings(vector<fs::path> files)
{
    vector<string> strings;
    for (const auto &file : files)
    {
        boost::interprocess::file_mapping fileMapping(file.c_str(), boost::interprocess::read_only);
        boost::interprocess::mapped_region mappedRegion(fileMapping, boost::interprocess::read_only);
        string fileContent(static_cast<char *>(mappedRegion.get_address()), mappedRegion.get_size());
        regex reg("[^a-zA-Z0-9 \n]");
        fileContent = regex_replace(fileContent, reg, "");
        transform(fileContent.begin(), fileContent.end(), fileContent.begin(), ::tolower);
        istringstream iss(fileContent);
        string word;
        while (iss >> word)
        {
            strings.push_back(word);
        }
    }
    return strings;
}

//count the number of occurrences of each string
map<string, int> countStrings(vector<string> strings)
{
    map<string, int> stringCounts;
    for (const auto &string : strings)
    {
        stringCounts[string]++;
    }
    return stringCounts;
}

// write the Frequency and Strings sorted reverse alphabetically to a File
void writeToFile(map<string, int> stringCount)
{
    multiset<pair<int, string>, greater<pair<int, string>>> stringFrequency;
    ranges::for_each(stringCount, [&stringFrequency](const auto &string)
                     { stringFrequency.insert(make_pair(string.second, string.first)); });
    ofstream file("output.txt");
    ranges::for_each(stringFrequency, [&file](const auto &string)
                     { file << string.first << " " << string.second << endl; });
}
// get path from command line argument
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
        cout << "Usage: " << argv[0] << " path extension" << endl;
        return 1;
    }

    // start the timer
    auto start = chrono::high_resolution_clock::now();

    // Function Calls
    vector<fs::path> files = getAllFiles(path, extension);
    vector<string> strings = getStrings(files);
    map<string, int> stringCount = countStrings(strings);
    writeToFile(stringCount);

    // end the timer
    auto end = chrono::high_resolution_clock::now();
    // calculate the time
    auto durationmic = chrono::duration_cast<chrono::microseconds>(end - start);
    auto durationmil = chrono::duration_cast<chrono::milliseconds>(end - start);
    auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    // print the time
    cout << "Time: " << durationmic.count() << " microseconds" << endl;
    cout << "Time: " << durationmil.count() << " milliseconds" << endl;
    cout << "Time: " << duration.count() << " seconds" << endl;

    return 0;
}