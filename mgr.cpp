// Kobe Norcross, CS 260, mgr.cpp
// implementation file of the app manager

#include "mgr.h"

AppMgr::AppMgr() 
{
	initTree();
}



void AppMgr::initTree()
{
	tree = new Tree();
	tree->initTree("data.txt");
}



AppMgr::~AppMgr()
{
	if (tree) 
	{
		tree->saveToFile("data.txt");
		delete tree;
	}
}



// ==========================================================================================================
// 					Calls to hash tree
// ==========================================================================================================
void AppMgr::algoEff()
{
	tree->algorithmEfficiency();
}



void AppMgr::displayTree()
{
	cout << *tree;
}



void AppMgr::addData()
{
	cin.ignore(MAX_SIZE, '\n');
	tree->addData();
}


void AppMgr::removeMatches()
{
	char buffer[MAX_SIZE];
	cin.ignore(MAX_SIZE, '\n');
	cout << endl << "Please enter the name of the topic you wish to remove -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	char * name = new char[strlen(buffer)+1];
	strcpy(name, buffer);
	tree->removeMatches(name);
	delete [] name;
}



void AppMgr::removeKey()
{
	char buffer[MAX_SIZE];
	cin.ignore(MAX_SIZE, '\n');
	cout << endl << "Please enter the keyword of the website you would like to delete -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	char * key = new char[strlen(buffer)+1];
	strcpy(key, buffer);
	if ((tree->removeKey(key)) == true)
	{
		cout << endl << endl << "Succesfully removed " << key << endl;
	}
	else
	{
		cout << endl << "Could not find any matches..." << endl << endl;
	}
	delete [] key;
}



void AppMgr::retrieve()
{
	char buffer[MAX_SIZE];
	Data * data = new Data();
	cin.ignore(MAX_SIZE, '\n');
	cout << endl << "Please enter the keyword of the website you would like to retrieve -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	char * key = new char[strlen(buffer)+1];
	strcpy(key, buffer);

	if ((tree->retrieve(key, data)) == true)
	{
		cout << endl << endl << "Successfully retrieved data at keyword: " << key << endl << endl;
		cout << "Website address of the data retrieved: " << data->getAddress() << endl << endl;
		data->display();
	}
	else
	{
		cout << endl << endl << "Failed to retrieve data at keyword: " << key << endl;
	}

	delete [] key;
	if (data) delete data;
}



// ==========================================================================================================
// 					Main Function functions
// ==========================================================================================================
void AppMgr::printOptions()
{
	cout << endl;
	cout << "------------------------------------------------------" << endl << endl;
       	cout << "		     Website Database" 			 << endl;
	cout << "		     ----------------"			 << endl << endl;	
//	cout << "0. Algorithm Efficiency information." 			 << endl << endl;
	cout << "1. Display all websites in order by keyword." 		 << endl << endl;
	cout << "2. Add a new website."	 			 	 << endl << endl;
	cout << "3. Remove all websites under a certain topic." 	 << endl << endl;
	cout << "4. Remove a specific website."				 << endl << endl;
	cout << "5. Retrieve information about a particular website."	 << endl << endl;
	cout << "6. Quit program."					 << endl << endl;
	cout << "------------------------------------------------------" << endl << endl;
}



void AppMgr::getUserOption(int & choice)
{
	cin >> choice;
	while (!cin || choice < 1 || choice > 6)
	{
		cout << endl;
		cin.clear();
		cin.ignore(MAX_SIZE, '\n');
		cout << "Invalid option, please try again -> ";
		cin >> choice;
		cout << endl;
	}
}


void AppMgr::mainFunction(int c)
{
	if (c == 1)
	{
		displayTree();
	}
/*
	else if (c == 0)
	{
		algoEff();
	}
*/
	else if (c == 2)
	{
		addData();
	}
	else if (c == 3)
	{
		removeMatches();
	}
	else if (c == 4)
	{
		removeKey();
	}
	else if (c == 5)
	{
		retrieve();
	}
	else
	{
		cout << endl << "Quitting..." << endl << endl;
	}	
}
