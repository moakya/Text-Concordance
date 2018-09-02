#include "Concord.h"
#include <cctype>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
	ifstream infile;
	infile.open("concord.txt");
	validFile(infile);
	infile.close();
	return 0;
}	//end main

/**************************************************************************
Function: validFile

Description: Checks if file opened correctly

Pre: istream object

Post: -
**************************************************************************/
void validFile(ifstream &infile) {
	if (!infile) {
		cout << "Error opening the file. Exitting........\n";
		exit(1107);
	}	//end if
	else
		performConcord(infile);		//begin object operations
}	//end validFile

/**************************************************************************
Function: performConcord

Description: does all the processes on the file input, creates objects
calls to other functions/methods

Pre: istream object

Post: -
**************************************************************************/
void performConcord(ifstream &infile) {
	int numLine = 1;	//default for line num
	string term;	//to contain word from line
	string str;		//to contain main line
	BST<Concord> konk[MAX_SIZE];	//create Concord BST array

	while (getline(infile, str)) {		//grab entire line
		istringstream koncStr(str);		//istringstream koncStr
		while (koncStr >> term && infile)	//get the word
			add(konk, numLine, term);	//fn to process word and linenum
		numLine++;						//increment line num
	}	//end for
	BSTDisplay(konk);					//display the entire thing
}	//end performConcord

/**************************************************************************
Function: add

Description: get modified string, creates Concord object, changes its
members, and then inserts it into the BST

Pre: BST array of Concords, num of line, word from the string

Post: -
**************************************************************************/
void add(BST<Concord> Koncord[MAX_SIZE], int &numLine, string &term) {
	string nstr = makeCaps(term);	//get the modified string
	int val = nstr[0] - 'A';	//get index

	Concord konk;	//create concord obj
	konk.concInsert(nstr, numLine);	//insert members into obj
	Koncord[val].BSTKonkInsert(konk);	//insert obj into BST
}	//end insert

/**************************************************************************
Function: makeCaps

Description: converts string toupper and then only adds alpha chars to new
string and returns it

Pre: string object

Post: string object
**************************************************************************/
string makeCaps(string &str) {
	//create a new string and add all Alpha chars to it
	string nstr = "";
	for (int i = 0; i < str.length(); i++)
		if (isalpha(str[i]))
			nstr += str[i];

	//convert the new string to upper case
	for (int i = 0; i < nstr.length(); i++)
		nstr[i] = toupper(nstr[i]);

	return nstr;
}	//end makeCaps

/**************************************************************************
Function: BSTDisplay

Description: traverses the array of Concord BSTs and displays the BST

Pre: BST array of Concords

Post: -
**************************************************************************/
void BSTDisplay(BST<Concord> konk[]) {
	cout << "\n";
	for (int i = 0; i < MAX_SIZE; i++) {
		if (!konk[i].empty()) {
			cout << "Concord [" << i << "] i.e. character: "
				<< char('A' + i) << endl << endl;
			konk[i].graph(cout);
			cout << endl;
		}	//end if
	} //end for
	cout << "\n\n";
}	//end BSTDisplay