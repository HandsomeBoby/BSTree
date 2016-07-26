#pragma once

#include <iostream>

using namespace std;

//节点结构
template <typename K,typename V>
struct BSTNode
{
	K _key;//关键字
	V _value;//数值

	BSTNode <K, V> * _left;
	BSTNode <K, V> * _right;

	BSTNode()
		:_left(NULL)
		, _right(NULL)
	{}

	BSTNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <typename K, typename V>
class BSTree
{
	typedef BSTNode <K, V> Node;

public:
	
	//构造函数
	BSTree()
		:_root(NULL)
	{}

	//析构函数
	~BSTree()
	{
		_Destory(_root);
		_root = NULL;
	}

	//插入（非递归）
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;

		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				// key重复
				return false;
			}
		}

		if (key < parent->_key)
		{
			parent->_left = new Node(key, value);
		}
		else
		{
			parent->_right = new Node(key, value);
		}

		return true;
	}

	//插入（递归）
	bool Insert_R(const K& key, const V& value)
	{
		return _InsertR(_root, key, value);
	}

	//查找（非递归）
	Node * Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}

		return false;
	}

	//查找（递归）
	Node * Find_R(const K& key)
	{
		return _FindR(_root, key);
	}

	//删除（非递归）
	bool Remove(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;

		// 查找要删除的节点
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}

			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			
			// 找到
			else
			{
				
				break;
			}
		}

		if (cur == NULL)
		{
			return false;
		}

		Node* del = NULL;

		if (cur->_left == NULL) // cur左边为空的情况
		{
			del = cur;

			// parent 是NULL表明删除的节点是根节点
			if (parent == NULL)
			{
				_root = cur->_right;
			}
			else
			{
				// 判断结点在左边还是右边
				if (cur->_key < parent->_key)
				{
					parent->_left = cur->_right; 
				}
				else
				{
					parent->_right = cur->_right; 
				}
			}
		}
		else if (cur->_right == NULL) // cur右边为空的情况
		{
			del = cur;
			// 删除根结点的情况
			if (parent == NULL)
			{
				_root = cur->_left;
			}
			else
			{
				if (cur->_key < parent->_key)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
			}
		}
		else // cur 左右都不为空
		{
			// 找右树的最左结点/左树的最右结点
			// 然后和cur交换值 最后将删除cur转换成删除firstLeft

			Node* firstLeft = cur->_right;
			parent = cur;

			while (firstLeft->_left) 
			{
				parent = firstLeft;
				firstLeft = firstLeft->_left;
			}

			del = firstLeft;

			// 交换 cur与 firstLeft

			cur->_key = firstLeft->_key;
			cur->_value = firstLeft->_value;

			if (firstLeft == parent->_left)
			{
				parent->_left = firstLeft->_right; 
			}
			else 
			{
				parent->_right = firstLeft->_right;
			}
		}

		delete del;
		return true;
	}

	//删除（递归）
	bool Remove_R(const K& key)
	{
		return _RemoveR(_root, key);
	}

	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

protected:

	void _Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_Destroy(root->_left);
		_Destroy(root->_right);

		delete root;
	}

	void _InOrder(const Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << "   ";
		_InOrder(root->_right);
	}

	bool _InsertR(Node*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}

		if (key > root->_key)
		{
			return _InsertR(root->_right, key, value);
		}
		else if (key < root->_key)
		{
			return _InsertR(root->_left, key, value);
		}
		else
		{
			return false;
		}
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (key < root->_key)
		{
			return _FindR(root->_left, key);
		}
		else if (key > root->_key)
		{
			return _FindR(root->_right, key);
		}
		else
		{
			return root;
		}
	}

	bool _RemoveR(Node*& root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}

		if (key < root->_key)
		{
			return _RemoveR(root->_left, key);
		}
		else if (key > root->_key)
		{
			return _RemoveR(root->_right, key);
		}
		else 
		{
			Node* del = root;

			if (root->_left == NULL)
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node* firstLeft = root->_right;
				while (firstLeft->_left)
				{
					firstLeft = firstLeft->_left;
				}

				swap(firstLeft->_key, root->_key);
				swap(firstLeft->_value, root->_value);

				// 变成前两种情况 转成递归
				return _RemoveR(root->_right, key);
			}

			delete del;
		}

		return true;
	}

private:
	Node * _root;
};
