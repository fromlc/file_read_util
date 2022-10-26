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

#include <iostream>     // cerr, cout, string
#include <fstream>      // ifstream

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cerr;
using std::cout;
using std::ifstream;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int ERROR_FILE_OPEN   = -1;
constexpr int ERROR_FILE_IO     = -2;
constexpr int ERROR_BAD_FORMAT  = -3;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
void openDataFile();
bool getFileData();
void errorExit(const string& str, int errorCode);

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
const string g_fName = "test.txt";
ifstream g_file;
string g_data;

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

    openDataFile();

    // read a line from file
    int lineNum = 0;

    while (getFileData()) {

        cout << "Line " << ++lineNum << ": " << g_data << "\n";
    } 

    cout << '\n' << lineNum << " lines read from file\n";

    g_file.close();
    cout << "\nClosed " + g_fName + "\n\n";

    system("pause");

    return 0;
}

//------------------------------------------------------------------------------
// exits on file open error
//------------------------------------------------------------------------------
void openDataFile() {

    // register the exceptions we want to handle
    g_file.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        g_file.open(g_fName.c_str());
    }
    // File may not exist, or another problem 
    catch (ifstream::failure e) {
        errorExit("could not open file", ERROR_FILE_OPEN);
    }

    cout << "Opened " << g_fName << "\n\n";
}

//------------------------------------------------------------------------------
// read one line from file into string parameter
//------------------------------------------------------------------------------
bool getFileData() {
    
    try {
        g_file >> g_data;
    }
    catch (ifstream::failure e) {
        // first check for end of file (sets failbit)
        if (g_file.eof())
            return false;

        // exit app on i/o err 
        if (g_file.bad())
            errorExit("I/O error", ERROR_FILE_IO);

        // exit app on logical read error like data type mismatch
        else if (g_file.fail())
            errorExit("Data type mismatch reading from file", ERROR_BAD_FORMAT);
    }

    return true;
}

//------------------------------------------------------------------------------
// display error message and exit application
//------------------------------------------------------------------------------
void errorExit(const string& str, int errorCode) {
    cerr << '\n' << g_fName << ": " << str << '\n';
    cerr << "Exiting application\n\n";

    system("pause");

    exit(errorCode);
}