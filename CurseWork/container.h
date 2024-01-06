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
	void swap(tnode<Type>* b) {
		std::string a_key = this->key;
		this->key = b->key;
		b->key = a_key;
		bool a_col = this->color;
		this->color = b->color;
		b->color = a_col;
		Type a_data = this->data;
		this->data = b->data;
		b->data = a_data;
	};
	void rightRotate() {
		this->swap(this->left);
		tnode<Type> *buffer = this->right;
		this->right = this->left;
		this->left = this->right->left;
		this->right->left = this->right->right;
		this->right->right = buffer;
		if (this->left->left != nullptr && this->left->right != nullptr) this->left->parent = this;
	}
	void leftRotate() {
		this->swap(this->right);
		tnode<Type>* buffer = this->left;
		this->left = this->right;
		this->right = this->left->right;
		this->left->right = this->left->left;
		this->left->left = buffer;
		if (this->right->right != nullptr && this->right->right != nullptr) this->right->parent = this;
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
	};

	Container(std::string k, Type d) {
		root = new tnode<Type>(k, d);
		root->color = false;
		root->left = nul;
		root->right = nul;
		root->parent = nul;
		size = 0;
	};

	~Container() {};

	tnode<Type>* search(std::string key) {
		tnode<Type>* curr = root;
		while (curr != nul && (*curr) != key) {
			if ((*curr) > key)
				curr = curr->left;
			else
				curr = curr->right;
		}
		return curr;
	};

	Type& operator [](std::string key) {
		return this->search(key)->data;
	};

	bool nodeExist(tnode<Type>* node) {
		return node != nul;
	};

	void printTree(tnode<Type>* node) {
		if (node == nul) return;
		printTree(node->left);
		std::cout << node->key;
		printTree(node->right);
	};

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
						newNode->leftRotate();
						newNode = newNode->left;
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					newNode->parent->parent->rightRotate();
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
						newNode->rightRotate();
						newNode = newNode->right;
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					newNode->parent->parent->leftRotate();
				}
			}
			root->color = false;
		}		
	};

	bool Insert(std::string key, Type data) {
		tnode<Type>* curr = root;
		tnode<Type>* parent = nul;
		while (nodeExist(curr)) {
			if (curr->key == key) {
				return false;
			}
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
		return true;
	};

	int getChildrenCount(tnode<Type>* node) {
		int count = 0;
		if (nodeExist(node->left))count += 1;
		if (nodeExist(node->right))count += 1;
		return count;
	};

	tnode<Type>* getChildOrMock(tnode<Type>* node) {
		return nodeExist(node->left) ? node->left : node->right;
	};

	void transplantNode(tnode<Type>* toNode, tnode<Type>* fromNode) {
		if (toNode == root) root = fromNode;
		if (toNode == toNode->parent->left) toNode->parent->left = fromNode;
		else toNode->parent->right = fromNode;
		if(nodeExist(fromNode)) fromNode->parent = toNode->parent;
	};

	tnode<Type>* getMin(tnode<Type>* node) {
		if (node == nul) return nul;
		if (node->left = nul) return node;
		return getMin(node->left);
	};

	void fixRulesAfterRemoval(tnode<Type>* node) {
		while (node != root && !node->color) {
			tnode<Type>* brother;
			if (node == node->parent->left) {
				brother = node->parent->right;
				if (brother->color) {
					brother->color = false;
					node->parent->color = true;
					node->parent->leftRotate();
					brother = node->parent->right;
				}
				if (!brother->left->color && !brother->right->color) {
					brother->color = true;
					node = node->parent;
				}
				else {
					if (!brother->right->color) {
						brother->left->color = false;
						brother->color = true;
						brother->rightRotate();
						brother = node->parent->right;
					}
					brother->color = node->parent->color;
					node->parent->color = false;
					brother->right->color = false;
					node->parent->leftRotate();
					node = root;
				}
			}
			else {
				brother = node->parent->left;
				if (brother->color) {
					brother->color = false;
					node->parent->color = true;
					node->parent->rightRotate();
					brother = node->parent->left;
				}
				if (!brother->left->color && !brother->right->color) {
					brother->color = true;
					node = node->parent;
				}
				else {
					if (!brother->left->color) {
						brother->right->color = false;
						brother->color = true;
						brother->leftRotate();
						brother = node->parent->left;
					}
					brother->color = node->parent->color;
					node->parent->color = false;
					brother->left->color = false;
					node->parent->rightRotate();
					node = root;
				}
			}
		}
		node->color = false;
	};

	void Remove(std::string key) {
		tnode<Type>* nodeToDelete = this->search(key);
		tnode<Type>* child;
		bool removedNodeColor = nodeToDelete->color;
		if (getChildrenCount(nodeToDelete) < 2) {
			child = getChildOrMock(nodeToDelete);
			this->transplantNode(nodeToDelete, child);
			delete nodeToDelete;
		}
		else {
			tnode<Type>* minNode = getMin(nodeToDelete->right);
			nodeToDelete->key = minNode->key;
			nodeToDelete->data = minNode->data;
			removedNodeColor = minNode->color;
			child = getChildOrMock(minNode);
			this->transplantNode(minNode, child);
			delete minNode;
		}
		if (removedNodeColor == false) this->fixRulesAfterRemoval(child);
		this->printTree(root);
	};
};