#pragma once
#include <iostream>


template <typename Type>
class tnode {
public:
	std::string key;
	Type data;
	tnode* left;
	tnode* right;
	tnode* parent;
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
	static void swap(tnode <Type> *a, tnode<Type> *b) {
		std::string a_key = a->key;
		a->key = b->key;
		b->key = a_key;
		Type a_data = a->data;
		a->data = b->data;
		b->data = a_data;
	};
	static void rightRotate(tnode<Type> *node) {
		swap(node, node->left);
		tnode *buffer = node->right;
		node->right = node->left;
		node->left = node->right->left;
		node->right->left = node->right->right;
		node->right->right = buffer;
	}
	static void leftRotate(tnode<Type> *node) {
		swap(node,node->right);
		tnode* buffer = node->left;
		node->left = node->right;
		node->right = node->left->right;
		node->left->right = node->left->left;
		node->left->left = buffer;
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
	friend class Contain;
private:
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
		root = new tnode<Type>(k, d);
		root->color = false;
		root->left = nul;
		root->right = nul;
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

	static void printTree(tnode<Type>* node) {
		if (!node->left || !node->right) return;
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
					newNode = newNode->parent->parent;
				}
				else {
					if (newNode == newNode->parent->right) {
						newNode = newNode->parent;
						tnode<Type>::leftRotate(newNode->parent->parent);
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					tnode<Type>::rightRotate(newNode->parent->parent);
				}
			}
			else {
				uncle = newNode->parent->parent->left;
				if (uncle->color) {
					newNode->parent->color = false;
					uncle->color = false;
					newNode->parent->parent->color = true;
					newNode = newNode->parent->parent;
				}
				else {
					if (newNode == newNode->parent->left) {
						newNode = newNode->parent;
						tnode<Type>::rightRotate(newNode->parent->parent);
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					tnode<Type>::leftRotate(newNode->parent->parent);
				}
			}
		}
		root->color = false;
	};
	void Insert(std::string key, Type data) {
		tnode<Type>* curr = root;
		if (root == nullptr) {
			root = new tnode<Type>(key, data);
			return;
		}
		else {
			while (curr && (*curr) != key) {
				if ((*curr) > key && curr->left == nul) {
					curr->left = new tnode<Type>(key, data);
					curr->left->parent = curr;
					curr->left->left = nul;
					curr->left->right = nul;
					this->balanceInsert(curr->left);
					size++;
					printTree(root);
					return;
				}
				if ((*curr) < key && curr->right == nul) {
					curr->right = new tnode<Type>(key, data);
					curr->right->parent = curr;
					curr->right->left = nul;
					curr->right->right = nul;
					this->balanceInsert(curr->right);
					size++;
					printTree(root);
					return;
				}
				if ((*curr) > key)
					curr = curr->left;
				else
					curr = curr->right;
			}
		}
	};
	void Delete(std::string key) {

	};
};