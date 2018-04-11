#include <windows.h>
#include <iostream>
#include <sstream>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
    string path = "D:\\Git\\c++\\hw5\\cmake-build-debug\\WARC201709\\";
    string searchPattern = "*.txt";
    string fullSearchPath = path + searchPattern;

    WIN32_FIND_DATA FindData;
    HANDLE hFind;

    hFind = FindFirstFile( fullSearchPath.c_str(), &FindData );

    if( hFind == INVALID_HANDLE_VALUE )
    {
        cout << "Error searching directory\n";
        return -1;
    }

    map<string, int> corpusVocab;
    do {
        string filePath = path + FindData.cFileName;
        ifstream in(filePath.c_str());
        if (in) {
            // do stuff with the file here
            string scoop;
            stringstream doc;
            doc << in.rdbuf();
            while (doc >> scoop) {
                map<string, int>::iterator it = corpusVocab.begin();
                if (corpusVocab.find(scoop) == corpusVocab.end()) {
                    corpusVocab.emplace(scoop);
                } else {
                    (*it).second = (*it).second + 1;
                }
                cout << "Word: " << (*it).first << endl;
                cout << "Count: " << (*it).second << endl << endl;
            }
        }
    }
    while( FindNextFile(hFind, &FindData) > 0 );

    if( GetLastError() != ERROR_NO_MORE_FILES )
    {
        cout << "Something went wrong during searching\n";
    }

    system("pause");
    return 0;
}

// Note that you can use GetLastError() to get better error information for the
// WinAPI calls but I did not want to complicate the example
