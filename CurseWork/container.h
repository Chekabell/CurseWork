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
	tnode() {
		key = "";
		data = (Type)nullptr;
		color = false;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	};
	tnode(std::string k) {
		key = k;
		data = (Type)nullptr;
		color = true;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
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
		data = (Type)nullptr;
		color = false;
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
		if (this->right->left != nullptr && this->right->right != nullptr) this->right->parent = this;
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

template <class Type>
tnode<Type>* nul = new tnode<Type>();

template <class Type>
class Container;

template <class Type>
class Iterator {
	friend class Container<Type>;
	friend class tnode<Type>;
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
	
private:
	void Increment() {
		if (Container<Type>::nodeExist(_pNode->right)) {
			_pNode = Container<Type>::getMin(_pNode->right);
		}
		else {
			Node* par = _pNode->parent;
			while (_pNode == par->right) {
				_pNode = par;
				par = par->parent;
			}
			if (_pNode->right != par) _pNode = par;
		}
	};
	void Decrement() {
		if (Container<Type>::nodeExist(_pNode->left)) {
			_pNode = Container<Type>::getMax(_pNode->left);
		}
		else {
			Node* par = _pNode->parent;
			while (_pNode == par->left) {
				_pNode = par;
				par = par->parent;
			}
			if (_pNode->left != par) _pNode = par;
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
	int getSize() {
		return size;
	};
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

	Type& operator [](std::string key) {
		return Search(key)->data;
	};

	void printTree(Node node) {
		if (node == nul) return;
		printTree(node->left);
		std::cout << node->key;
		printTree(node->right);
	};
	bool Insert(std::string key, Type data) {
		Node curr = root;
		Node parent = nul<Type>;
		while (nodeExist(curr)) {
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
			Node minNode = getMin(nodeToDelete->right);
			nodeToDelete->key = minNode->key;
			nodeToDelete->data = minNode->data;
			removedNodeColor = minNode->color;
			child = getChildOrMock(minNode);
			this->transplantNode(minNode, child);
			delete minNode;
		}
		if (removedNodeColor == false) this->fixRulesAfterRemoval(child);
		nul<Type>->parent = nullptr;
		size--;
	};
	bool Clear() {
		ClearTree(root);
		root = nul<Type>;
		size = 0;
		return ChekTree();
	};
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
	Iter begin() { return Iterator(getMin(root)); }
	Iter rbegin() { return Iterator(getMax(root)->right); }
	Iter end() { return Iterator(getMax(root)); }
	Iter rend() { return Iterator(getMin(root)->left); }
	static bool nodeExist(Node node) {
		return (node != nul<Type>) ? true : false;
	};
protected:
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
		}
		root->color = false;
	};
	int getChildrenCount(Node node) {
		int count = 0;
		if (nodeExist(node->left))count += 1;
		if (nodeExist(node->right))count += 1;
		return count;
	};
	Node getChildOrMock(Node node) {
		return nodeExist(node->left) ? node->left : node->right;
	};
	void ClearTree(Node node) {
		if (node == nul<Type>) return;
		ClearTree(node->left);
		ClearTree(node->right);
		delete node;
	};
	bool ChekTree() {
		return nodeExist(root) ? true : false;
	};
	void fixRulesAfterRemoval(Node node) {
		while (node != root && !node->color) {
			Node brother;
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
	void transplantNode(Node toNode, Node fromNode) {
		if (toNode == root) root = fromNode;
		if (toNode == toNode->parent->left) toNode->parent->left = fromNode;
		else toNode->parent->right = fromNode;
		fromNode->parent = toNode->parent;
	};
};


