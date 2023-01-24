#ifndef BST_H
#define BST_H

//stop this as well
//using namespace std;

//stop doing this.
//template <typename T>
//class Node;

#include <vector>


template <typename T>
class BST {
	public:
		class Node {
			public:
				friend class BST;
				Node(T curData, Node* curleft, Node* curright) : 
				data{curData},
				left{curleft},
				right{curright}{};
				//free it here, so we don't have to free it in another place
				~Node(){delete left; delete right;}
				T getData() {return data;}
				void setData(T data) {this->data = data;}
				Node* getRight() {return right;}
				Node* getLeft() {return left;}
				void setRight(Node* right) {this->right = right;}
				void setLeft(Node* left) {this->left = left;}
			private:
				T data;
				Node *left;
				Node *right;
		};
		BST() : root{nullptr}, size{0}{};
		~BST(){delete root;}
		//idk this might be useful
		T find(T);
		void insert(T);
		bool remove(T);
		T pop();
		int getSize() {return size;};

		std::vector<T> getArray();
	private:
		Node *root;
		int size;

		//some successor stuff
		//3AM when I wrote this code, bare with me and just 
		//follow along with the code, auto works.
		auto find_Succsor(Node*) -> Node*;
		auto delete_recursive(Node*, T) -> Node*;
		//Node* find_Succsor(Node*);
		//Node* delete_recursive(Node*, T);
};

//complexity: O(n)
template <typename T>
std::vector<T> BST<T>::getArray()
{
	std::vector<Node*> node = std::vector<Node*>();
	std::vector<T> ret = std::vector<T>();
	node.push_back(root);
	while(node.size() > 0)
	{
		if(node.at(0) == nullptr) 
		{
			node.erase(node.begin());
			continue;
		}
		//specifically asking for a copy
		ret.push_back(node.at(0)->getData());
		//node.at(0)->getData()->hasVisited = false;
		node.push_back(node.at(0)->left);
		node.push_back(node.at(0)->right);
		node.erase(node.begin());
	}

	return ret;
}

//Complexity: O(logn)
template <typename T>
//typename BST<T>::Node* BST<T>::find_Succsor(Node* head) {
auto BST<T>::find_Succsor(Node* head) -> Node* 
{
	while(head && head->left != nullptr) head = head->left;
	return head;
}

//sorta just removes root
template <typename T>
T BST<T>::pop()
{
	if(root == nullptr) return T();
	T ret = root->getData();
	remove(ret);
	return ret;
}


//Complexity: O(logn)
template <typename T>
T BST<T>::find(T target) {
	//if root is nullptr
	if (root == nullptr) {
		auto ret = T();
		return ret;
	}
	//loop until we find a nullptr place to place our target
	Node* temp = root;
	while (temp != nullptr) {
		if (target > temp->getData()) // if element is greater than cur
		{
			temp = temp->getRight();
		} else if (target < temp->getData()) // if element is smaller than cur
		{
			temp = temp->getLeft();
		} else //if we found the element
		{
			break;
		}
	}
	auto ret = T();
	return temp == nullptr ? ret : temp->getData();
}

//Complexity: O(logn)
template <typename T>
void BST<T>::insert(T element)
{
	//if root is nullptr
	if(root == nullptr)
	{
		Node *newNode = new Node(element, nullptr, nullptr);
		root = newNode;
		size++;
		return;
	}
	//loop until we find a nullptr place to place our element
	Node *temp = root;
	bool storeLeft = false;
	while (temp != nullptr) {
		if (element > temp->getData()) // if element is greater than cur
		{
			if (temp->getRight() == nullptr) // we have found where to place our element
			{
				storeLeft = false;
				break;
			}
			temp = temp->getRight();
		} else {
			if (temp->getLeft() == nullptr) // we have found where to place our element
			{
				storeLeft = true;
				break;
			}
			temp = temp->getLeft();
			storeLeft = true;
		}
	}
	//store our element
	if(storeLeft) 
	{
		temp->setLeft(new Node(element, nullptr, nullptr));
		size++;
	}
	else 
	{
		temp->setRight(new Node(element, nullptr, nullptr));
		size++;
	}
}

template <typename T>
//typename BST<T>::Node* BST<T>::delete_recursive(Node* head, T target)
auto BST<T>::delete_recursive(Node* head, T target) -> Node*
{
	//base case
	if(head == nullptr) return head;

	//go left
	if(target < head->getData())
	{
		head->left = delete_recursive(head->left, target);
	}
	//go right
	else if (target > head->getData())
	{
		head->right = delete_recursive(head->right, target);
	}
	//delete me
	else
	{
		//only 1 child
		if(head->left == nullptr)
		{
			Node* ret = head->right;
			head->left = nullptr;
			head->right = nullptr;
			delete head;
			size--;
			return ret;
		}
		if(head->right == nullptr)
		{
			Node* ret = head->left;
			head->left = nullptr;
			head->right = nullptr;
			delete head;
			size--;
			return ret;
		}
		//have 2 children, find a successor
		Node* temp = find_Succsor(head->right);
		//copy such temp into me
		head->setData(temp->getData());
		//delete that leaf node
		head->right = delete_recursive(head->right, head->getData());
	}
	return head;
}

//Complexity: O(logn)
template <typename T>
bool BST<T>::remove(T target)
{
	root = delete_recursive(root, target);
	return true;
}




#endif














