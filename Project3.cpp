/*Joseph Grzywinski
  12/11/2022       
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

//this function is one we've used a couple times. It formats characters to a specific length. For this project is it used for 
//the stars in the histogram and for each output to separate the tital from the products.
string CharOutput(size_t n, char c) {
	int i;
	string Format;
	for (i = 0; i < n; ++i) {
		Format = Format + c;
	}
	return Format;
}

/*the userMenu function is called through main after the menu options are presented to the user. While 4 is to exit the program the user has a choice
between options 1, 2, and 3. 1 calls the python function to basically list all the items puruchased in a day and how many times they were purchased.
user choice 2 will prompt the user to select a specific item to see how many times it was bought that day once an item is selected it will use the python
function to search for that item and display how many times it was purchased. the final option, number 3, will call the python function to created
the frequency.dat file. Once that is created, C++ will open that file and output the histogram based on how many times each item was purchased.*/
void userMenu() {
	int menuChoice;
	cin >> menuChoice;
	cout << endl;
	while (menuChoice != 4) {
		if (menuChoice == 1) {
			string multNum;
			cout << "Total products Purchased" << endl;
			cout << CharOutput(25, '=') << endl;
			CallProcedure("totalInventory");
			break;
		}
		if (menuChoice == 2) {
			string productChoice;
			cout << "What product are you looking for?" << endl;
			cin >> productChoice;
			cout << endl;
			cout << "Item Count" << endl;
			cout << CharOutput(15, '=');
			cout << endl;
			cout << callIntFunc("findItem", productChoice) << endl;
			break;
		}
		if (menuChoice == 3) {
			ifstream inFS;
			string product;
			int freq;
			CallProcedure("writeFile");
			inFS.open("frequency.dat");
			if (!inFS.is_open()) {
				cout << "Could not open file." << endl;
			}
			cout << "Items Purchased today" << endl;
			cout << CharOutput(20, '=') << endl;
			while (!inFS.fail()) {
				inFS >> product;
				inFS >> freq;
				cout << product << " " << CharOutput(freq, '*') << endl;
			}
			break;
		}
		else {
			cout << "Please enter either 1, 2, 3, or 4" << endl;
			break;

		}
	}
}


//this function is called i9n main to display the main menu options for the user
void displayMenu() {
	cout << "1: Display frequency of products purchased" << endl;
	cout << "2: Search a specific item" << endl;
	cout << "3: Display histogram of products purchased" << endl;
	cout << "4: Exit" << endl;
	cout << "Enter your selection as a number 1, 2, or 3." << endl;
}
//Main is small and simple. Calling two separate functions where all my functional code is. 
void main()
{
	int userInput;
	displayMenu();
	userMenu();
}
