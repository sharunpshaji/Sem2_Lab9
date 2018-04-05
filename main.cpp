#include <iostream>
using namespace std;

struct node{
	int data;
	node *parent;
	node *leftChild;
	node *rightChild;
	//Constructor
	node() {
		parent = leftChild = rightChild = NULL;
	}
};

class binaryTree{
public:
	node *root;
	binaryTree() {
		root = NULL;
	}
	void insert(int value);
	void remove(int value);
	void display(node *temp);
	int count(node* temp);
	node* leftMostNode(node *temp);
	node* rightMostNode(node *temp);
	node* search(int value, node *temp);
	int rangeSearch(int lowerLimit, int upperLimit, node* temp);
};

node* binaryTree::leftMostNode(node *temp) {
	if (temp->leftChild == NULL)
		return temp;
	else
		return leftMostNode(temp->leftChild);
}

node* binaryTree::rightMostNode(node *temp) {
	if (temp->rightChild == NULL)
		return temp;
	else
		return rightMostNode(temp->rightChild);
}

//insert() function
void binaryTree::insert(int value) {
	node *temp = new node;
	temp->data = value;
	if (root == NULL) {
		root = temp;
	}
	else {
		node *pointer = root;
		while (temp->parent == NULL) {
			if (value <= pointer->data) {
				if (pointer->leftChild != NULL) {
					pointer = pointer->leftChild;
				}
				else {
					pointer->leftChild = temp;
					temp->parent = pointer;
				}
			}
			else {
				if (pointer->rightChild != NULL) {
					pointer = pointer->rightChild;
				}
				else {
					pointer->rightChild = temp;
					temp->parent = pointer;
				}
			}
		}
	}
}

//display() function
void binaryTree::display(node *temp) {
	if (temp != NULL) {
		display(temp->leftChild);
		cout << temp->data << " ";
		display(temp->rightChild);
	}
}

//Search function
node* binaryTree::search(int value, node *temp) {
	if (temp != NULL) {
		if (temp->data == value) {
			cout << "Found" << endl;
			return temp;
		}
		else {
			if (temp->data > value) {
				return search(value, temp->leftChild);
			}
			else {
				return search(value, temp->rightChild);
			}
		}
	}
	else {
		cout << "Not found" << endl;
		return NULL;
	}
}

//remove() or delete() function
void binaryTree::remove(int value) {
	node* temp = search(value, root);
	//If 'value' is not present in the tree, do nothing
	if (temp == NULL) {
		return;
	}
	//If 'value' is present, we delete it
	else {
		node* baap = temp->parent;
		//Three cases:
		if (baap != NULL) {
			//When a leaf needs to be removed...
			if (temp->leftChild == NULL && temp->rightChild == NULL) {
				if (value < baap->data)
					baap->leftChild = NULL;
				else
					baap->rightChild = NULL;
			}
			//When an internal node needs to be removed...
			else {
				if (value < baap->data) {
					if (temp->rightChild != NULL && temp->leftChild != NULL) {
						baap->leftChild = temp->leftChild;
						temp->leftChild->parent = baap;
						node* junction = rightMostNode(temp->leftChild);
						temp->rightChild->parent = junction;
						junction->rightChild = temp->rightChild;
					}
					else if (temp->rightChild == NULL && temp->leftChild != NULL) {
						baap->leftChild = temp->leftChild;
						temp->leftChild->parent = baap;
					}
					else {
						baap->leftChild = temp->rightChild;
						temp->rightChild->parent = baap;
					}
				}
				else {
					if (value > baap->data) {
						if (temp->rightChild != NULL && temp->leftChild != NULL) {
							baap->rightChild = temp->leftChild;
							temp->leftChild->parent = baap;
							node* junction = rightMostNode(temp->leftChild);
							temp->rightChild->parent = junction;
							junction->rightChild = temp->rightChild;
						}
						else if (temp->rightChild == NULL && temp->leftChild != NULL) {
							baap->rightChild = temp->leftChild;
							temp->leftChild->parent = baap;
						}
						else {
							baap->rightChild = temp->rightChild;
							temp->rightChild->parent = baap;
						}
					}
				}
			}
		}
		//When the root needs to be removed
		else {
			node* replacement = rightMostNode(temp->leftChild);
			temp->data = replacement->data;
			if (replacement->leftChild != NULL) {
				replacement->parent->rightChild = replacement->leftChild;
				replacement->leftChild->parent = replacement->parent;
			}
			else {
				replacement->parent->rightChild = NULL;
				replacement->parent = NULL;
			}
			delete replacement;
		}
		temp->parent = NULL;
		delete temp;
	}
}

//count() function that gives the number of nodes in the tree
int binaryTree::count(node* temp) {
	if (temp != NULL)
		return count(temp->leftChild) + count(temp->rightChild) + 1;
	else
		return 0;
}

//Function for range search
int binaryTree::rangeSearch(int lowerLimit, int upperLimit, node* temp) {
	static int count = 0;
	if (temp != NULL) {
		rangeSearch(lowerLimit, upperLimit, temp->leftChild);
		if (lowerLimit <= temp->data && temp->data <= upperLimit) {
			cout << temp->data << " ";
			count++;
		}
		rangeSearch(lowerLimit, upperLimit, temp->rightChild);
	}
	return count;
}

int main() {
	binaryTree treeOne;
	treeOne.insert(10);
	treeOne.insert(15);
	treeOne.insert(14);
	treeOne.insert(16);
	treeOne.insert(17);
	treeOne.insert(5);
	treeOne.insert(6);
	treeOne.insert(9);
	treeOne.insert(3);
	treeOne.insert(8);
	treeOne.display(treeOne.root);
	cout << endl;
	cout << "Number of nodes: " << treeOne.count(treeOne.root) << endl;
	treeOne.remove(10);
	treeOne.display(treeOne.root);
	cout << endl;
	cout << "Number of nodes: " << treeOne.count(treeOne.root) << endl;
	int count = treeOne.rangeSearch(10, 12, treeOne.root);
	cout << endl << count;
	cout << endl;
	return 0;
}
