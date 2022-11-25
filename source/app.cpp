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
#include "file_read_util.h"		// #includes needed system header files
using std::cin;

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
// this file goes in your VS project folder
const string g_fName = "test.txt";

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
inline void displayVectorItems(vector<string>& vData, const string& msg);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {
	// file data buffer
	string data;

	ifstream ifs;
	// ignore return value, instead exit app on file open error
	openDataFile(ifs, g_fName);
	cout << '\n' + g_fName << '\n';

	// read lines from file
	int lineNum = 0;
	int errorCode;

	// display file lines
	while (getFileLine(ifs, data, errorCode)) {

		cout << "Line " << ++lineNum << ": " << data << "\n";
	}
	cout << '\n' << lineNum << " lines read from file " + g_fName + '\n';

	// we opened the file so we must close it
	ifs.close();
	cout << "\nClosed " + g_fName + '\n';

	// vector for file words
	vector<string> vWordData;

	// fill word vector with file data, error exits app
	getFileWordVector(g_fName, vWordData);
	displayVectorItems(vWordData, "word vector");

	// vector for file lines
	vector<string> vLineData;

	// fill line vector with file data, error exits app
	getFileLineVector(g_fName, vLineData);
	displayVectorItems(vLineData, "line vector");

	// wait for user input
	cin.get();
	cout << "Goodbye!\n";

	return 0;
}

//------------------------------------------------------------------------------
// loop to display vector elements
//------------------------------------------------------------------------------
inline void displayVectorItems(vector<string>& vData, const string& msg) {
	cout << msg << "\n\n";
	for (auto item : vData) {
		cout << item << '\n';
	}
	cout << '\n';
}
