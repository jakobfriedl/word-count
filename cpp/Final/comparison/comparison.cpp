// read 2 files line by line till newline
// clean all white spaces and compare
//print differences and line numbers

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cctype>
#include <regex>

using namespace std;

void clean(string &s)
{
    regex reg("[ \t\r\n\v\f]");
    s = regex_replace(s, reg, "");
}

int main(int argc, char *argv[])
{
    string solution, compare;
    if (argc == 3)
    {
        solution = argv[1];
        compare = argv[2];
    }
    else
    {
        cout << "Usage: " << argv[0] << " path extension" << endl;
        return 1;
    }

    ifstream file1(solution);
    ifstream file2(compare);

    //check if files are empty
    if (file1.peek() == ifstream::traits_type::eof() || file2.peek() == ifstream::traits_type::eof())
    {
        cout << "One or more files is/are empty!" << endl;
        return 1;
    }

    string line1, line2;
    int line = 0;
    int diff = 0;
    while (getline(file1, line1) && getline(file2, line2))
    {
        clean(line1);
        clean(line2);
        if (line1 != line2)
        {
            cout << "Line " << line+1 << " is different" << endl;
            cout << "File1: " << line1 << endl;
            cout << "File2: " << line2 << endl;
            diff++;
        }
        line++;
    }
    if(diff == 0)
        cout << "Files are identical" << endl;
    else
        cout << "Files are different" << endl;
    return 0;
}