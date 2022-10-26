//------------------------------------------------------------------------------
// file_read_util.h
//------------------------------------------------------------------------------
#ifndef FILE_READ_UTIL_H
#define FILE_READ_UTIL_H

#include <iostream>     // cerr, cout, string
#include <fstream>      // ifstream
#include <vector>		// for getFileDataVector()

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cerr;
using std::cout;
using std::ifstream;
using std::string;
using std::vector;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr bool APP_EXIT	  = true;
constexpr bool APP_NOEXIT = false;

// error codes
constexpr int ERROR_FILE_OK	  = 0;
constexpr int ERROR_FILE_OPEN = -1;
constexpr int ERROR_FILE_IO   = -2;
constexpr int ERROR_DATA_TYPE = -3;
constexpr int ERROR_UNKNOWN	  = -4;

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
// corresponding error messages
const string g_errorFileOK = "no error";
const string g_errorFileOpen = "could not open file";
const string g_errorFileIO = "file read error";
const string g_errorFileData = "file data type mismatch";
const string g_errorFileUnk = "unknown error";

//------------------------------------------------------------------------------
// function prototypes
//------------------------------------------------------------------------------
// exits app by default
bool openDataFile(ifstream& ifs, const string& fName, bool exitApp = true);
// exits app by default
bool getFileLine(ifstream& ifs, string& data, int& errorID, bool exitApp = true);
// exits app by default
bool getFileDataVector(const string& fName, vector<string>& vData, bool exitApp = true);
void errorExit(int errorCode);

#endif // !FILE_READ_UTIL_H
