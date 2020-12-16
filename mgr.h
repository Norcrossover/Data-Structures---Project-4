// Kobe Norcross, CS 260, mgr.h
// This is the app manager header file

#include "tree.h"

class AppMgr
{
public:
	// constructor and destructor
	AppMgr();
	~AppMgr();

	// Calls to hash table
	void algoEff();
	void displayTree();
	void addData();
	void removeMatches();
	void removeKey();
	void retrieve();
	void editData();

	// Main Functions
	void printOptions();
	void mainFunction(int c);
	void getUserOption(int& choice);

private:
	Tree * tree;	
	void initTree();
};
