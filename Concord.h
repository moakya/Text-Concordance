#include <iostream>
#include <string>
#include "BST.h"
#include <queue>
using namespace std;

#ifndef CONCORD_H
#define CONCORD_H

class Concord {
private:
	string str;
	queue<int> lineQ;
public:
	string getStr()const {return str;}
	void concInsert(string, int);
	void concDisplay(ostream &out) const;
	void concQDisplay(queue<int>, ostream &out) const;
	void concQInsert(int);
	bool concQCheck(queue<int> q1, int num);
	int concQFRet()const;
};		//end Concord Class Def

/**************************************************************************
Method: Concord::concQFRet

Description: returns front of the queue of the concord object
**************************************************************************/
int Concord::concQFRet() const{
	return lineQ.front();
}	//end concQFRet

/**************************************************************************
Method: Concord::concQInsert

Description: passes q by value, and the line num to concQCheck,
then enqueues depending on the result, insert for duplicates
**************************************************************************/
void Concord::concQInsert(int num){
	bool flag = concQCheck(lineQ, num);
	if (!flag)	//if duplicate not found (false) enqueue
		lineQ.push(num);
}	//end concQInsert

/**************************************************************************
Method: Concord::concQCheck

Description: checks if element is already in the queue, returns bool value
depending
**************************************************************************/
bool Concord::concQCheck(queue<int> q1, int num) {
	bool flag = false;	//assume not found
	while (!q1.empty()) {
		if (q1.front() == num)	//compare
			flag = true;	//duplicate found
		q1.pop();	//dequeue
	}	//end if
	return flag;
}	//end concQCheck

/**************************************************************************
Function:  operator<

Description: overloaded < operator for concord objects
**************************************************************************/
bool operator<(const Concord &lhs, const Concord &rhs) {
	return (lhs.getStr() < rhs.getStr());
}	//end operator <

/**************************************************************************
Function:  operator>

Description: overloaded > operator for concord objects
**************************************************************************/
bool operator>(const Concord &lhs, const Concord &rhs) {
	return (lhs.getStr() > rhs.getStr());
}	//end operator >

/**************************************************************************
Method: Concord::concInsert()

Description: default setter for the concord class, not considering 
duplicates
**************************************************************************/
void Concord::concInsert(string word, int num){
	str = word;
	lineQ.push(num);
}	//end concord insert

/**************************************************************************
Method: Concord::concDisplay

Description: display method for the concord class obj
**************************************************************************/
void Concord::concDisplay(ostream &out) const {
	out << "(" << str << ") ";	//display the string
	concQDisplay(lineQ, out);	//display the STL queue obj
}	//end display

/**************************************************************************
Method: Concord::concQDisplay

Description: display method for the queue member of the concord obj
**************************************************************************/
void Concord::concQDisplay(queue<int> q, ostream &out) const{
	while (!q.empty()) {
		out << " -> " << q.front();	//display front of q
		q.pop();	//dequeue
	}	//end while
}	//end queueDisplay

/**************************************************************************
Function: operator <<

Description: overloaded << operator for concord object display
**************************************************************************/
ostream &operator << (ostream &out, const Concord &obj) {
	obj.concDisplay(out);
	return out;
}	//end &operator <<

const int MAX_SIZE = 26;

void add(BST<Concord> Koncord[MAX_SIZE], int &numLine, string &term);
void BSTDisplay(BST<Concord> konk[]);
void validFile(ifstream &);
void performConcord(ifstream &);
string makeCaps(string &str);

#endif // !CONCORD_H