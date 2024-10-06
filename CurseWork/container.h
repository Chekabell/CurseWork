#pragma once
#include <iostream>

template<class Type>
class tnode;

template <class Type>
tnode<Type>* nul = new tnode<Type>();

template <class Type>
class Container;

template <typename Type>
class tnode {
	typedef tnode<Type>* Node;
public:
	std::string key;
	Type data;
	Node left;
	Node right;
	Node parent;
	bool color;
	tnode() {
		key = "";
		color = false;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	};
	tnode(std::string k, Type d) {
		key = k;
		data = d;
		color = true;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	};
	~tnode() {
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		key = "";
		color = false;
	};
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
	static Node getMin(Node node) {
		if (node == nul<Type>) return nul<Type>;
		if (node->left == nul<Type>) return node;
		return getMin(node->left);
	};
	static Node getMax(Node node) {
		if (node == nul<Type>) return nul<Type>;
		if (node->right == nul<Type>) return node;
		return getMax(node->right);
	}
	static bool nodeExist(Node node) {
		return (node != nul<Type>) ? true : false;
	};
};

template <class Type>
class Iterator {
	friend class Container<Type>;
private:
	typedef Iterator<Type> Self;
	typedef tnode<Type> Node;
	Node* _pNode;
public:
	Iterator(Node* pNode) :_pNode(pNode) {};
	Type& operator*() {
		return _pNode->data;
	};
	Type* operator->() {
		return &(_pNode->data);
	};
	bool operator != (const Self& it) {
		return _pNode != it._pNode;
	};
	bool operator == (const Self& it) {
		return _pNode == it._pNode;
	};
	Self& operator++ () {
		Increment();
		return *this;
	};
	Self operator++ (int) {
		Self temp(*this);
		Increment();
		return temp;
	};
	Self& operator-- () {
		Decrement();
		return *this;
	};
	Self operator-- (int) {
		Self temp(*this);
		Decrement();
		return temp;
	};
protected:
	void Increment() {
		if (tnode<Type>::nodeExist(_pNode->right)) {
			_pNode = tnode<Type>::getMin(_pNode->right);
		}
		else {
			Node* par = _pNode->parent;
			while (_pNode == par->right) {
				_pNode = par;
				par = par->parent;
			}
			if (_pNode->right != par) _pNode = par;
			if (par == nul<Type> && _pNode->right == nul<Type>) _pNode = nul<Type>;
		}
	};
	void Decrement() {
		if (tnode<Type>::nodeExist(_pNode->left)) {
			_pNode = tnode<Type>::getMax(_pNode->left);
		}
		else {
			Node* par = _pNode->parent;
			while (_pNode == par->left) {
				_pNode = par;
				par = par->parent;
			}
			if (_pNode->left != par) _pNode = par;
			if (par == nul<Type> && _pNode->left == nul<Type>) _pNode = nul<Type>;
		}
	};
};

template<typename Type>
class Container {
	friend class tnode<Type>;
	typedef tnode<Type>* Node;
private:
	Node root;
	int size;
public:
	typedef Iterator<Type> Iter;
	Container() {
		root = nul<Type>;
		size = 0;
	};
	~Container() {
		ClearTree(root);
	};
	Type& operator [](std::string key) {
		return Search(key)->data;
	};

	int GetSize() {
		return size;
	};
	bool Insert(std::string key, Type data) {
		Node curr = root;
		Node parent = nul<Type>;
		while (tnode<Type>::nodeExist(curr)) {
			if (curr->key == key) {
				return false;
			}
			parent = curr;
			if ((*curr) > key) curr = curr->left;
			else curr = curr->right;
		}
		Node newNode = new tnode<Type>(key, data);
		newNode->left = nul<Type>;
		newNode->right = nul<Type>;
		newNode->parent = parent;
		if (parent == nul<Type>) {
			root = newNode; 
		}
		else if ((*parent) > key) parent->left = newNode;
		else parent->right = newNode;
		balanceInsert(newNode);
		size++;
		return true;
	};
	void Remove(std::string key) {
		Node nodeToDelete = Search(key);
		Node child;
		bool removedNodeColor = nodeToDelete->color;
		if (getChildrenCount(nodeToDelete) < 2) {
			child = getChildOrMock(nodeToDelete);
			this->transplantNode(nodeToDelete, child);
			delete nodeToDelete;
		}
		else {
			Node minNode = tnode<Type>::getMin(nodeToDelete->right);
			nodeToDelete->key = minNode->key;
			nodeToDelete->data = minNode->data;
			removedNodeColor = minNode->color;
			child = getChildOrMock(minNode);
			this->transplantNode(minNode, child);
			delete minNode;
		}
		if (removedNodeColor == false) fixAfterRemoval(child);
		nul<Type>->parent = nullptr;
		size--;
	};
	bool Clear() {
		ClearTree(root);
		root = nul<Type>;
		size = 0;
		return ChekTree();
	};
	void printTree() {
		if (root == nul<Type>) return;
		_printTree(root->left);
		std::cout << root->key << std::endl;
		_printTree(root->right);
	}
	
	Iter begin() { return Iterator(tnode<Type>::getMin(root)); }
	Iter rbegin() { return Iterator(tnode<Type>::getMax(root)->right); }
	Iter end() { return Iterator(tnode<Type>::getMax(root)); }
	Iter rend() { return Iterator(tnode<Type>::getMin(root)->left); }
protected:
	void _printTree(Node node){
		if (node == nul<Type>) return;
		_printTree(node->left);
		std::cout << node->key << std::endl;
		_printTree(node->right);
	}
	Node Search(std::string key) {
		Node curr = root;
		while (curr != nul<Type> && (*curr) != key) {
			if ((*curr) > key)
				curr = curr->left;
			else
				curr = curr->right;
		}
		return curr;
	};
	void balanceInsert(Node newNode) {
		Node uncle;
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
						leftRotate(newNode);
						newNode = newNode->left;
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					rightRotate(newNode->parent->parent);
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
						rightRotate(newNode);
						newNode = newNode->right;
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					leftRotate(newNode->parent->parent);
				}
			}
		}
		root->color = false;
	};
	int getChildrenCount(Node node) {
		int count = 0;
		if (tnode<Type>::nodeExist(node->left))count += 1;
		if (tnode<Type>::nodeExist(node->right))count += 1;
		return count;
	};
	Node getChildOrMock(Node node) {
		return tnode<Type>::nodeExist(node->left) ? node->left : node->right;
	};
	void ClearTree(Node node) {
		if (node == nul<Type>) return;
		ClearTree(node->left);
		ClearTree(node->right);
		delete node;
	};
	bool ChekTree() {
		return tnode<Type>::nodeExist(root) ? true : false;
	};
	void fixAfterRemoval(Node node) {
		while (node != root && !node->color) {
			Node brother;
			if (node == node->parent->left) {
				brother = node->parent->right;
				if (brother->color) {
					brother->color = false;
					node->parent->color = true;
					leftRotate(node->parent);
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
						rightRotate(brother);
						brother = node->parent->right;
					}
					brother->color = node->parent->color;
					node->parent->color = false;
					brother->right->color = false;
					leftRotate(node->parent);
					node = root;
				}
			}
			else {
				brother = node->parent->left;
				if (brother->color) {
					brother->color = false;
					node->parent->color = true;
					rightRotate(node->parent);
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
						leftRotate(brother);
						brother = node->parent->left;
					}
					brother->color = node->parent->color;
					node->parent->color = false;
					brother->left->color = false;
					rightRotate(node->parent);
					node = root;
				}
			}
		}
		node->color = false;
	};
	void transplantNode(Node toNode, Node fromNode) {
		if (toNode == root) root = fromNode;
		if (toNode == toNode->parent->left) toNode->parent->left = fromNode;
		else toNode->parent->right = fromNode;
		fromNode->parent = toNode->parent;
	};
	void swap(Node a, Node b) {
		std::string a_key = a->key;
		a->key = b->key;
		b->key = a_key;
		bool a_col = a->color;
		a->color = b->color;
		b->color = a_col;
		Type a_data = a->data;
		a->data = b->data;
		b->data = a_data;
	};
	void rightRotate(Node node) {
		swap(node, node->left);
		Node buffer = node->right;
		node->right = node->left;
		node->left = node->right->left;
		node->right->left = node->right->right;
		node->right->right = buffer;
		if (node->left != nul<Type>) node->left->parent = node;
	}
	void leftRotate(Node node) {
		swap(node, node->right);
		Node buffer = node->left;
		node->left = node->right;
		node->right = node->left->right;
		node->left->right = node->left->left;
		node->left->left = buffer;
		if (node->right != nul<Type>) node->right->parent = node;
	}
};