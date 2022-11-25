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

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
int getErrorCode(ifstream& ifs);

//------------------------------------------------------------------------------
// returns false on file open error 
// exitApp is optional parameter, by default exits app on error
//------------------------------------------------------------------------------
bool openDataFile(ifstream& ifs, const string& fName, bool exitApp) {

    // register exceptions to handle in catch blocks
    ifs.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        ifs.open(fName.c_str());
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
bool getFileLine(ifstream& ifs, string& data, int& errorID, bool exitApp) {
    try {
        getline(ifs, data);
    }
    catch (ifstream::failure e) {
        errorID = getErrorCode(ifs);

        if (errorID != ERROR_FILE_OK && exitApp) {
            errorExit(errorID);
        }
        return false;
    }
    return true;
}

//----------------------------------------------------------------------
// stream file lines into passed vector
// exitApp is optional parameter, by default exits app on error
// returns true on success, false on failure
//----------------------------------------------------------------------
bool getFileLineVector(const string& fName, vector<string>& vData, 
                        bool exitApp) {
    ifstream ifs(fName);

    if (!ifs.is_open()) {
        if (exitApp) {
            errorExit(ERROR_FILE_OPEN);
        }
        return false;
    }

    // stop on eof or any error
    while (ifs.good()) {
        string line;
        getline(ifs, line);

        vData.push_back(line);
    }

    // grab eof bit before trying to close file
    bool retVal = ifs.eof();

    // try closing the file regardless of error
    ifs.close();

    return retVal;
}

//----------------------------------------------------------------------
// stream file data of passed type into passed vector
// exitApp is optional parameter, by default exits app on error
//----------------------------------------------------------------------
bool getFileWordVector(const string& fName, vector<string>& vData,
                        bool exitApp) {
    ifstream ifs(fName);
    
    if (!ifs.is_open()) {
        if (exitApp) {
            errorExit(ERROR_FILE_OPEN);
        }
        return false;
    }

    string dataItem{};
    while (ifs >> dataItem)
        vData.push_back(dataItem);

    ifs.close();

    return true;
}

//------------------------------------------------------------------------------
// common catch block code
//------------------------------------------------------------------------------
int getErrorCode(ifstream& ifs) {

    // first check for end of file (sets failbit)
    if (ifs.eof())
        return ERROR_FILE_OK;

    // file read error
    if (ifs.bad()) {
        return ERROR_FILE_IO;
    }
    // exit app on logical read error like data type mismatch
    if (ifs.fail()) {
        return ERROR_DATA_TYPE;
    }

    return ERROR_UNKNOWN;
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

    cerr << '\n' << errorText << '\n';
    cerr << "Exiting application\n\n";

    exit(errorCode);
}