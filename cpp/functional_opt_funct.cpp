#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <map>
#include <set>
#include <regex>
#include <ranges>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
namespace fs = std::filesystem;

// get all Files in Directory and all Subdirectories
vector<fs::path> getAllFiles(const fs::path path, const string extension)
{
    vector<fs::path> files;
    ranges::copy_if(fs::recursive_directory_iterator(path), back_inserter(files), [&extension](const auto &entry)
                    { return entry.is_regular_file() && entry.path().extension() == extension; });
    return files;
}

//get all alphanumeric strings from all files using shared memory
vector<string> getStrings(const vector<fs::path> files)
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
map<string, int> countStrings(const vector<string> strings)
{
    map<string, int> stringCounts;
    ranges::for_each(strings, [&stringCounts](const auto &string)
                     { stringCounts[string]++; });
    return stringCounts;
}

// write the Frequency and Strings sorted reverse alphabetically to a File
void writeToFile(const map<string, int> stringCount)
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
    auto getStringsAndCount = [](const auto &path, const auto &extension)
    {
        return countStrings(getStrings(getAllFiles(path, extension)));
    };
    writeToFile(getStringsAndCount(path, extension));

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