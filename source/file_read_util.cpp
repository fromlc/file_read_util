//------------------------------------------------------------------------------
// file_read_util.cpp
//
// Read file data as lines and as one string
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
ifstream g_file;
string g_data;

//------------------------------------------------------------------------------
// returns false on file open error 
// exitApp is optional parameter, by default exits app on error
//------------------------------------------------------------------------------
bool openDataFile(bool exitApp) {

    // register exceptions to handle in catch blocks
    g_file.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        g_file.open(g_fName.c_str());
    }
    // File may not exist, or another problem 
    catch (ifstream::failure e) {
        if (exitApp) {
            errorExit(ERROR_FILE_OPEN);
        }
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
// read one line from file into string parameter
// exitApp is optional parameter, by default exits app on error
//------------------------------------------------------------------------------
bool getFileData(int& errorID, bool exitApp) {

    errorID = ERROR_FILE_OK;

    try {
        g_file >> g_data;
    }
    catch (ifstream::failure e) {
        // first check for end of file (sets failbit)
        if (g_file.eof())
            return false;

        // file read error
        if (g_file.bad()) {
            errorID = ERROR_FILE_IO;
        }
        // exit app on logical read error like data type mismatch
        else if (g_file.fail()) {
            errorID = ERROR_DATA_TYPE;
        }

        if (exitApp) {
            errorExit(errorID);
        }

        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
// display error message and exit application
//------------------------------------------------------------------------------
void errorExit(int errorCode) {

    string errorText;

    switch (errorCode) {
    case ERROR_FILE_OK:
        errorText = g_errorFileOK;
        break;
    case ERROR_FILE_OPEN:
        errorText = g_errorFileOpen;
        break;
    case ERROR_FILE_IO:
        errorText = g_errorFileIO;
        break;
    case ERROR_DATA_TYPE:
        errorText = g_errorFileData;
        break;
    default:
        errorText = g_errorFileUnk;
    }

    cerr << '\n' << g_fName << ": " << errorText << '\n';
    cerr << "Exiting application\n\n";

    exit(errorCode);
}