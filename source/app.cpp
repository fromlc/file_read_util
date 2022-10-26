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
// entry point
//------------------------------------------------------------------------------
int main() {

    // exits app on file open error
    openDataFile();
    cout << "\nOpened " + g_fName + "\n\n";

    // read lines from file
    int lineNum = 0;
    int errorCode;

    while (getFileData(errorCode)) {

        cout << "Line " << ++lineNum << ": " << g_data << "\n";
    } 

    cout << '\n' << lineNum << " lines read from file\n";

    g_file.close();
    cout << "\nClosed " + g_fName + "\n\n";

    system("pause");

    return 0;
}
