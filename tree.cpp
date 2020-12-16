// Kobe Norcross, CS 260, tree.cpp
// This is the implementation file of the Binary Search Tree ADT

#include "tree.h"

//-------------------------------------------------------------------------
//			Constructors/Destructor
//-------------------------------------------------------------------------
Tree::Tree() : size(0), root(nullptr), leftHeight(0), rightHeight(0) {}



Tree::Tree(Tree& aTree) : size(0), root(nullptr), leftHeight(0), rightHeight(0)
{
	*this = aTree;
}



// Initialization of the tree from the list
void Tree::initTree(const char * fileName)
{
	char strBuffer[MAX_SIZE];
	int intBuffer;
	ifstream inputFile;
	inputFile.open(fileName);
	if (inputFile.good())
	{
		while (!inputFile.eof())
		{
			Data * data = new Data();
			//name
			inputFile.getline(strBuffer, MAX_SIZE, ';');
			data->setName(strBuffer);
			//key
			inputFile.getline(strBuffer, MAX_SIZE, ';');
			data->setKey(strBuffer);
			//address
			inputFile.getline(strBuffer, MAX_SIZE, ';');
			data->setAddress(strBuffer);
			//summary
			inputFile.getline(strBuffer, MAX_SIZE, ';');
			data->setSummary(strBuffer);
			//review
			inputFile.getline(strBuffer, MAX_SIZE, ';');
			data->setReview(strBuffer);
			//rating
			inputFile >> intBuffer;
			data->setRating(intBuffer);
			inputFile.get();
			add(data);
			size++;
		}
		getLeftHeight();
		getRightHeight();
	}
	else
	{
		cerr << "Could not open file" << endl;
		exit(1);
	}
}



int Tree::getLeftHeight()
{
	int count = 0;
	leftHeight = getLeftHeight(root, count);
}



int Tree::getLeftHeight(Node * curr, int& count)
{
	if (curr)
	{
		count++;
		return getLeftHeight(curr->left, count);
	}
	return count;
}



int Tree::getRightHeight()
{
	int count = 0;
	rightHeight = getRightHeight(root, count);
}



int Tree::getRightHeight(Node * curr, int& count)
{
	if (curr)
	{
		count++;
		return getRightHeight(curr->right, count);
	}
	return count;
}


Tree::~Tree()
{
	destroy(root);
}


void Tree::destroy(Node *& currRoot)
{
	if (currRoot)
	{
		destroy(currRoot->left);
		destroy(currRoot->right);
		delete currRoot;
		currRoot = nullptr;
	}
}



//-------------------------------------------------------------------------
//			Accessors
//-------------------------------------------------------------------------
void Tree::algorithmEfficiency() const
{
	cout << "The size of the tree is -> " << size << endl << endl;
	cout << "The left height of the tree is -> " << leftHeight << endl << endl;
	cout << "The right height of the tree is -> "  << rightHeight << endl << endl;
	cout << "The left side of the tree's efficiency is -> " << (size/leftHeight) << endl << endl;
	cout << "The right side of the tree's efficiency is -> " << (size/rightHeight) << endl << endl;
}



bool Tree::retrieve(const char * key, Data *& data) const
{
	if (root)
	{
		return retrieve(key, root, data); 
	}
	return false;
}



bool Tree::retrieve(const char * key, Node * curr, Data *& data) const
{
	if (curr)
	{
		int cmp = strcmp(key, curr->data->getKey());

		if (cmp == 0)
		{
			*data = *curr->data;
			return true;
		}
		else if (cmp < 0)
		{
			return retrieve(key, curr->left, data);
		}
		else if (cmp > 0)
		{
			return retrieve(key, curr->right, data);
		}
		else
		{
			return false;
		}
	}
	return false;
}	


bool Tree::display(const char * key) 
{
	int idx = 0;
	Data * data = new Data;

	if (retrieve(key, data) == false)
	{
		cout << endl << key << " could not be found." << endl << endl;
		return false;
	}
	else
	{
		cout << endl << endl;
		cout << "\t\tData found from " << key << endl;
		data->display();
		if (data) delete data;
		return true;
	}
}



//-------------------------------------------------------------------------
//		    	Mutators
//-------------------------------------------------------------------------
void Tree::add(Data *& data)
{
	add(root, data);
	size++;
}



void Tree::add(Node *& curr, Data *& data)
{
	if (!curr)
	{
		curr = new Node(data);
	}
	else if (strcmp(data->getKey(), curr->data->getKey()) < 0)
	{
		add(curr->left, data);
	}
	else
	{
		add(curr->right, data);
	}
}



bool Tree::removeKey(const char * key)
{
	return removeKey(this->root, key);
}


bool Tree::removeKey(Node *& currRoot, const char * key)
{
	if (!currRoot) return false;
	
	int found = strcmp(key, currRoot->data->getKey());

	if (found == 0)
	{
		deleteNode(currRoot);
		size--;
		return true;
	}
	else if (found < 0)
	{
		return removeKey(currRoot->left, key);
	}
	else
	{
		return removeKey(currRoot->right, key);
	}
}



void Tree::removeMatches(const char * name)
{
	int count = 0;
	removeMatches(name, root, count);
	if (count > 0)
	{
		cout << endl << count << " items were successfully removed." << endl << endl;
	}
	else
	{
		cout << endl << "Could not find any matches..." << endl << endl;
	}
}



void Tree::removeMatches(const char * name, Node *& curr, int& count)
{
	if (curr)
	{
		int cmp = strcmp(name, curr->data->getName());
		removeMatches(name, curr->left, count);
		removeMatches(name, curr->right, count);

		if (cmp == 0)
		{
			//cout << endl;
			//curr->data->display();
			//cout << "... successfully removed." << endl << endl;
			deleteNode(curr);
			count++;
		}
	}
}




// case 1: leaf node deletion (no children)
// case 2: only child on right
// case 3: only child on left
// case 4: two children
void Tree::deleteNode(Node *& target)
{
	// case 1
	if (!target->left && !target->right)
	{
		delete target;
		target = nullptr;
	}
	// case 2
	else if (!target->right)
	{
		Node * temp = target;
		target = target->left;
		delete temp;
	}
	// case 3
	else if (!target->left)
	{
		Node * temp = target;
		target = target->right;
		delete temp;
	}
	// case 4
	else
	{
		Node * prev = nullptr;
		Node * curr = target->right;
		if (!curr->left)
		{
			target->right = curr->right;
		}
		else
		{
			while (curr->left)
			{
				prev = curr;
				curr = curr->left;
			}
			prev->left = curr->right;
		}
		delete target->data;
		target->data = curr->data;
		delete curr;
	}
}


void Tree::addData()
{
	//cin.ignore(MAX_SIZE, '\n');
	char buffer[MAX_SIZE];
	int rating;
	Data * data = new Data;

	// get topic name
	cout << "Enter the name of the topic" << endl << "-> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	data->setName(buffer);

	// get key word
	cout << "Enter the keyword to be searched for this topic" << endl << "-> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	data->setKey(buffer);

	// get web address
	cout << "Enter the address of the website" << endl << " -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	data->setAddress(buffer);
	
	// get summary of data
	cout << "Enter a brief summary of what the topic is about" << endl << " -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	data->setSummary(buffer);

	// get review of data
	cout << "Enter a review on the topic" << endl << " -> ";
	cin.getline(buffer, MAX_SIZE, '\n');
	data->setReview(buffer);
		
	// get rating int
	cout << "Enter a rating (1-5)" << endl << " -> ";
	cin >> rating;
	while (!cin || rating < 1 || rating > 5)
	{
		cout << endl;
		cin.clear();
		cin.ignore(MAX_SIZE, '\n');
		cout << "Invalid input, please enter a valid rating [1-5] -> ";
		cin >> rating;
	}
	data->setRating(rating);

	// add data to the tree
	add(data);
}



//-------------------------------------------------------------------------
//			Table copy functions
//-------------------------------------------------------------------------
const Tree& Tree::operator=(Tree& treeSrc)
{
	if (this == &treeSrc) return *this;
	if (this->root) destroy(this->root);
	size = treeSrc.size;
	copy(treeSrc.root, this->root);
	return *this;
}




void Tree::copy(Node * srcRoot, Node * destRoot)
{
	if (srcRoot)
	{
		destRoot = new Node(srcRoot->data);
		copy(srcRoot->left, destRoot->left);
		copy(srcRoot->right, destRoot->right);
	}
	else
	{
		destRoot = nullptr;
	}
}




//-------------------------------------------------------------------------
//			Display functions
//-------------------------------------------------------------------------
ostream& operator<<(ostream& out, const Tree& srcTree)
{
	out << endl << "\t\tDisplaying the tree ... " << endl;
	srcTree.display(out, srcTree.root);
	return out;
}



void Tree::display(ostream& out, Node * currRoot) const
{
	/*
	out << endl << "Pre-order showing the tree ..." << endl;
	displayPreorder(out, currRoot);
	out << endl << "In-order showing the tree ... " << endl;
	*/
	int index = 0;
	displayInorder(out, currRoot, index);
	/*
	out << endl << "Post-order showing the tree ..." << endl;
	displayPostorder(out, currRoot);
	*/
}



/*
void Tree::displayPreorder(ostream& out, Node * currRoot) const
{
	if (currRoot)
	{
		currRoot->data->display(out);
		displayPreorder(out, currRoot->left);
		displayPreorder(out, currRoot->right);
	}
}
*/



void Tree::displayInorder(ostream& out, Node * currRoot, int& index) const
{
	if (currRoot)
	{
		displayInorder(out, currRoot->left, index);
		out << index << "." << endl;
		currRoot->data->display(out);
		out << endl;
		index++;
		displayInorder(out, currRoot->right, index);
	}
}



/*
void Tree::displayPostorder(ostream& out, Node * currRoot) const
{
	if (currRoot)
	{
		displayPostorder(out, currRoot->left);
		displayPostorder(out, currRoot->right);
		currRoot->data->display(out);
	}
}
*/


void Tree::saveToFile(const char * fileName) const
{
	ofstream out;
	out.open(fileName);
	if (out.good())
	{
		saveToFile(out, this->root);
		out.close();
	}
	else
	{
		cerr << "Failed to open " << fileName << "to write to!" << endl;
		exit(1);
	}
}



void Tree::saveToFile(ostream& out, Node * currRoot) const
{
	// writes to the file in pre-order
	if (currRoot)
	{
		currRoot->data->writeToFile(out);
		saveToFile(out, currRoot->left);
		saveToFile(out, currRoot->right);
	}
}

















