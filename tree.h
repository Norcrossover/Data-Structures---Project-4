// Kobe Norcross, CS 260, tree.h
// This is the rooter file of the Tree ADT

#include "data.h"

class Tree
{
public:
	// constructors
	Tree();
	Tree(Tree& aTree);
	
	// init 
	void initTree(const char * fileName);

	// destructors
	~Tree();

	// accessors
	bool retrieve(const char * key, Data *& data) const;
	bool display(const char * key);
	int getSize() const;
	void algorithmEfficiency() const;

	// mutators
	void addData();
	void add(Data *& data);
	void removeMatches(const char * name);
	bool removeKey(const char * key);
	bool editData(const char * key);
	int getLeftHeight();
	int getRightHeight();

	// operator overload
	const Tree& operator=(Tree& aTree);
	friend ostream& operator<<(ostream& out, const Tree& srcTree);

	void saveToFile(const char * fileName) const;

private:
	struct Node
	{
		Node()
		{
			data = nullptr;
			left = right = nullptr;
		}
		Node(Data *& newData)
		{
			data = newData;
			left = right = nullptr;
		}
		~Node()
		{
			if (data) delete data;
		}
		Data * data;
		Node * left;
		Node * right;
	};

	Node *  root;
	int 	size;
	int leftHeight;
	int rightHeight;

	// destructor functions
	void destroy(Node *& currRoot);
	void saveToFile(ostream& out, Node * currRoot) const;

	// Recursive Calls
	int getLeftHeight(Node * curr, int& count);
	int getRightHeight(Node * curr, int& count);
	bool retrieve(const char * key, Node * currRoot, Data *& data) const;
	bool removeKey(Node *& curr, const char * key);
	void removeMatches(const char * name, Node *& curr, int& count);
	void add(Node *& curr, Data *& data);
	void deleteNode(Node *& target);
	void display(ostream& out, Node * currRoot) const;
	void displayPreorder(ostream& out, Node *currRoot) const;
	void displayInorder(ostream& out, Node * currRoot, int& index) const;
	void displayPostorder(ostream& out, Node * currRoot) const;
	void copy(Node * srcRoot, Node * destRoot);

};

