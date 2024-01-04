#pragma once
#include <iostream>


template <typename Type>
class tnode {
public:
	std::string key;
	Type data;
	tnode<Type>* left;
	tnode<Type>* right;
	tnode<Type>* parent;
	bool color;
	tnode() {};
	tnode(std::string k, Type d) {
		key = k;
		data = d;
		color = true;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	};
	static void rightRotate(tnode<Type> *node) {
		tnode<Type> *buffer = node->left->right;
		node->parent->right = node->left;
		node->left->parent = node->parent;
		node->parent = node->left;
		node->parent->right = node;
		node->left = buffer;
	}
	static void leftRotate(tnode<Type> *node) {
		tnode<Type>* buffer = node->right->left;
		node->parent->left = node->right;
		node->right->parent = node->parent;
		node->parent = node->right;
		node->parent->left = node;
		node->right = buffer;
	}
	bool operator > (const std::string& p)
	{
		if (key.compare(p) > 0) return true;
		else return false;
	}
	bool operator < (const std::string& p)
	{
		if (key.compare(p) > 0) return false;
		else return true;
	}
	bool operator == (const std::string& p)
	{
		if (key.compare(p) == 0) return true;
		else return false;
	}
	bool operator != (const std::string& p)
	{
		if (key.compare(p) != 0) return true;
		else return false;
	}
};


template<typename Type>
class Container {
	friend class tnode<Type>;
private:
	tnode<Type>* header;
	tnode<Type>* root;
	int size;
public:
	static tnode<Type>* createEmptyNode() {
		tnode<Type>* node = new tnode<Type>();
		node->key = "";
		node->data = (Type)nullptr;
		node->color = false;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		return node;
	};

	tnode<Type>* nul = createEmptyNode();

	Container() {
		root = nullptr;
		size = 0;
	};
	Container(std::string k, Type d) {
		header = createEmptyNode();
		root = new tnode<Type>(k, d);
		header->left = root;
		header->right = root;
		header->parent = nul;
		root->color = false;
		root->left = nul;
		root->right = nul;
		root->parent = header;
		size = 0;
	};
	~Container() {};
	Type& operator [](std::string key) {
		tnode<Type>* curr = root;
		while (curr != nul && (*curr) != key) {
			if ((*curr) > key)
				curr = curr->left;
			else
				curr = curr->right;
		}
		return curr->data;
	};

	void printTree(tnode<Type>* node) {
		if (node == nul) return;
		printTree(node->left);
		std::cout << node->key;
		printTree(node->right);
	}
	void balanceInsert(tnode<Type>* newNode) {
		tnode<Type> *uncle;
		while (newNode->parent->color) {
			if (newNode->parent == newNode->parent->parent->left) {
				uncle = newNode->parent->parent->right;
				if (uncle->color) {
					newNode->parent->color = false;
					uncle->color = false;
					newNode->parent->parent->color = true;
				}
				else {
					if (newNode == newNode->parent->right) {
						tnode<Type>::leftRotate(newNode->parent);
					}
					newNode->color = false;
					newNode->parent->color = true;
					if (newNode->parent == root) root = newNode;
					tnode<Type>::rightRotate(newNode->parent);
				}
			}
			else {
				uncle = newNode->parent->parent->left;
				if (uncle->color) {
					newNode->parent->color = false;
					uncle->color = false;
					newNode->parent->parent->color = true;
				}
				else {
					if (newNode == newNode->parent->left) {
						tnode<Type>::rightRotate(newNode->parent);
					}
					newNode->color = false;
					newNode->parent->color = true;
					if (newNode->parent == root) root = newNode;
					tnode<Type>::leftRotate(newNode->parent);
				}
			}
			if (newNode->parent == nul) break;
			else newNode = newNode->parent;
			root->color = false;
		}		
	};

	bool nodeExist(tnode<Type>* node) {
		return node != nul;
	}

	void Insert(std::string key, Type data) {
		tnode<Type>* curr = root;
		tnode<Type>* parent = nul;
		while (nodeExist(curr)) {
			parent = curr;
			if ((*curr) > key) curr = curr->left;
			else curr = curr->right;
		}
		tnode<Type>* newNode = new tnode<Type>(key, data);
		newNode->left = nul;
		newNode->right = nul;
		newNode->parent = parent;
		if (parent == nul) { 
			root = newNode; 
			newNode->parent->right = newNode;
			newNode->parent->left = newNode;
		}
		else if ((*parent) > key) parent->left = newNode;
		else parent->right = newNode;
		balanceInsert(newNode);
		this->printTree(root);
		std::cout << std::endl;
	};
	void Delete(std::string key) {

	};
};