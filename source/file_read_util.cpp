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
        ifs >> data;
    }
    catch (ifstream::failure e) {
        // first check for end of file (sets failbit)
        if (ifs.eof())
            return false;

        // file read error
        if (ifs.bad()) {
            errorID = ERROR_FILE_IO;
        }
        // exit app on logical read error like data type mismatch
        else if (ifs.fail()) {
            errorID = ERROR_DATA_TYPE;
        }

        if (exitApp) {
            errorExit(errorID);
        }

        return false;
    }

    return true;
}

//----------------------------------------------------------------------
// stream file data of passed type into passed vector
// exitApp is optional parameter, by default exits app on error
//----------------------------------------------------------------------
//template <class T>
//bool getFileDataVector(vector<T>& vData, bool exitApp) {
bool getFileDataVector(const string& fName, vector<string>& vData, bool exitApp) {
    ifstream ifs(fName);
    
    if (!ifs.is_open()) {
        if (exitApp) {
            errorExit(ERROR_FILE_OPEN);
        }
        return false;
    }

//    T dataItem{};
    string dataItem{};
    while (ifs >> dataItem)
        vData.push_back(dataItem);

    ifs.close();

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

    cerr << '\n' << errorText << '\n';
    cerr << "Exiting application\n\n";

    exit(errorCode);
}