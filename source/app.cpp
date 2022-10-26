//------------------------------------------------------------------------------
// file_read_util.cpp
//
// Handles file open and read errors using exceptions
//
// References: 
//      http://www.cplusplus.com/doc/tutorial/files/
//      http://www.cplusplus.com/reference/istream/istream/get/
//
//------------------------------------------------------------------------------
#include "file_read_util.h"

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
const string g_fName = "test.txt";

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {
    // file data buffer
    string data;

    // exits app on file open error
    ifstream ifs;
    openDataFile(ifs, g_fName);
    //cout << "\nOpened " + g_fName + "\n\n";
    cout << '\n' + g_fName << '\n';

    // read lines from file
    int lineNum = 0;
    int errorCode;

    while (getFileLine(ifs, data, errorCode)) {

        cout << "Line " << ++lineNum << ": " << data << "\n";
    } 

    cout << '\n' << lineNum << " lines read from file " + g_fName + '\n';

    ifs.close();
    //cout << "\nClosed " + g_fName + '\n';

    // reopen for read
    //cout << "\nReading " + g_fName + " into vector\n";

    // data buckets
    vector<string> vData;

    if (getFileDataVector(g_fName, vData, APP_NOEXIT)) {
        cout << "\nRead file data into vector\n\n";

        for (auto item : vData) {
            cout << item << '\n';
        }
    }
    else {
        cout << "\nError reading file data into vector\n";
    }

    cout << '\n';
    system("pause");

    return 0;
}
