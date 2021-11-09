#include <iostream>
using namespace std;

// �Է� ��ɾ� define
#define INSERT 'I'
#define FIND 'F'
#define UPDATE 'R'
#define DISCOUNT 'D'

// �Է� ���� ����
int inputCommandCnt; // �Է¹��� ��ɾ� ��
char commandType; // ��ɾ� ����
int input_id; // ���ø����̼� ID
string input_name; // �̸�
int input_capacity; // �뷮
int input_price; // ����
int input_discount; // ������
int input_start; // ���� ����
int input_end; // ���� ��

enum Color 
{
	RED,
	BLACK
};

enum Direction
{
	LEFT,
	RIGHT
};

struct Node
{
	// ������
	Node(int id, int capacity, int price, string name) : id(id), capacity(capacity), price(price), name(name) {
		color = RED; // �߰��ϴ� node�� ������ ����(root����)
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

int id;
int capacity;
int price;
string name;
Color color;
Node* left;
Node* right;
Node* parent;
};

class RedBlackTree {
private:
	Node* root;

public:
	RedBlackTree() {
		root = nullptr;
	}

	bool isLeafNode(Node* node)
	{
		return (node->left == nullptr && node->right == nullptr);
	}

	pair<Node*, bool> findNode(int find_id, char commandType)
	{
		// �����ϸ� ���ø����̼��� ������ ���, �������� ������ NULL���
		Node* curNode = this->root;
		int depth = 0;
		while (curNode != nullptr)
		{
			if (curNode->id == find_id)
			{
				if (commandType == FIND)
					cout << depth << ' ' << curNode->name << ' ' << curNode->capacity << ' ' << curNode->price << "\n";
				else if (commandType == UPDATE || commandType == INSERT)
					cout << depth << "\n";
				return { curNode, true };
			}
			else if (curNode->id > find_id)
			{
				if (curNode->left != nullptr)
					curNode = curNode->left;
				else {
					if (commandType != INSERT)
						cout << "NULL\n";
					return { curNode, false };
				}
			}
			else
			{
				if (curNode->right != nullptr)
					curNode = curNode->right;
				else {
					if (commandType != INSERT)
						cout << "NULL\n";
					return { curNode, false };
				}
			}
			depth++;
		}
		if (commandType != INSERT)
			cout << "NULL\n";
		return { nullptr,false };// node�� �ϳ��� ���� ��
	}

	void updateNode(int id, string name, int capacity, int price)
	{
		pair<Node*, bool> nodeInfo = findNode(id, UPDATE);
		if (nodeInfo.second == true)
		{
			nodeInfo.first->name = name;
			nodeInfo.first->capacity = capacity;
			nodeInfo.first->price = price;
		}
	}

	void fixDoubleRed(Node* curNode)
	{
		Node* parent = curNode->parent;
		Node* grandparent = parent->parent;
		Node* great_grandparent = grandparent->parent; // ���θ��� �θ�
		Node* uncle = nullptr;
		Color uncleColor = BLACK;
		Direction direction;
		
		// parent�� sibling node�� RED���� BLACK���� Ȯ���ؾ� ��
		if (grandparent->left == parent)
			uncle = grandparent->right;
		else if (grandparent->right == parent)
			uncle = grandparent->left;
		if (uncle != nullptr)
			uncleColor = uncle->color;

		if (uncleColor == BLACK)
		{
			
			// curNode, parent, grandparent���� restruct => �θ�� BLACK, �ڽ��� RED�� ĥ�ؾ� ��
			if ((grandparent->left == parent && parent->left == curNode) || (grandparent->right == parent && parent->right == curNode))
			{
				// ������ parent�� ���ο� subƮ���� parent
				direction = (parent->left == curNode ? LEFT : RIGHT); // 3�� ���(curNode, parent, grandparent)�� ��� ������ �����ִ� ��
				if (direction == LEFT)
				{
					// parent�� ���� �ڽ� grandparent�� �߰�
					if (parent->right != nullptr)
						parent->right->parent = grandparent;
					grandparent->left = parent->right;

					// parent�� grandparent�� �θ���� �ٲ�
					grandparent->parent = parent;
					parent->right = grandparent;
				}
				else if (direction == RIGHT)
				{
					// parent�� ���� �ڽ� grandparent�� �߰�
					if (parent->left != nullptr)
						parent->left->parent = grandparent;
					grandparent->right = parent->left;

					// parent�� grandparent�� �θ���� �ٲ�
					grandparent->parent = parent;
					parent->left = grandparent;
				}
				// parent�� ���ο� �θ� ����
				parent->parent = great_grandparent;
				if (great_grandparent != nullptr)
				{
					if (great_grandparent->left == grandparent)
						great_grandparent->left = parent;
					else
						great_grandparent->right = parent;
				}
				// �� �ٲ�
				parent->color = BLACK;
				grandparent->color = RED;
				curNode->color = RED;
			}
			else {
				// ������ curNode�� ���ο� subƮ���� parent
				direction = (parent->left == curNode ? LEFT : RIGHT); // parent�� ����� �ڽ��� curNode����
				if (direction == LEFT)
				{
					if (curNode->left != nullptr)
						curNode->left->parent = grandparent;
					grandparent->right = curNode->left;

					if (curNode->right != nullptr)
						curNode->right->parent = parent;
					parent->left = curNode->right;

					curNode->left = grandparent;
					grandparent->parent = curNode;

					curNode->right = parent;
					parent->parent = curNode;
				}
				else if (direction == RIGHT)
				{
					if (curNode->left != nullptr)
						curNode->left->parent = parent;
					parent->right = curNode->left;

					if (curNode->right != nullptr)
						curNode->right->parent = grandparent;
					grandparent->left = curNode->right;

					curNode->left = parent;
					parent->parent = curNode;
					
					curNode->right = grandparent;
					grandparent->parent = curNode;
				}
				// curNode�� ���ο� �θ� ����
				curNode->parent = great_grandparent;
				if (great_grandparent != nullptr)
				{
					if (great_grandparent->left == grandparent)
						great_grandparent->left = curNode;
					else
						great_grandparent->right = curNode;
				}
				// �� �ٲ�
				parent->color = RED;
				grandparent->color = RED;
				curNode->color = BLACK;
			}

		}
		else if (uncleColor == RED) {
			//recoloring 
			uncle->color = BLACK;
			parent->color = BLACK;
			if (grandparent != this->root)
				grandparent->color = RED;
			if (grandparent->parent != nullptr && grandparent->parent->color == RED)
				fixDoubleRed(grandparent);
		}
	}

	void insertNode(int id, string name, int capacity, int price)
	{
		pair<Node*, bool> nodeInfo = findNode(id, INSERT);
		
		if (nodeInfo.second == true) // �ش� id �̹� ������
			return;
		
		Node* parent = nodeInfo.first;
		Node* newNode = new Node(id, capacity, price, name);
		if (parent == nullptr)
		{
			// node�� �ϳ��� ���� �� => root �߰��ؾ���
			newNode->color = BLACK;
			this->root = newNode;
			cout << "0\n";
			return;
		}
		newNode->parent = parent;
		if (parent->id > id)
			parent->left = newNode;
		else
			parent->right = newNode;
		if (parent->color == RED && parent->parent != nullptr)
			fixDoubleRed(newNode);
		findNode(id, INSERT);
	}
};

int main() 
{
	RedBlackTree* rdTree = new RedBlackTree();
	cin >> inputCommandCnt;
	while (inputCommandCnt--)
	{
		cin >> commandType;
		switch (commandType)
		{
		case INSERT:
			// ���ø����̼� ����(id, �̸�, �뷮, ����)�� �Է¹޾� �����Ʈ���� ��带 �����ϰ�, �� ����� ���̸� ���
			// ���� �ش� ���ø����̼��� �̹� ��ϵǾ� �ִٸ�, �� ����� ���̸� ����ϰ� ����� ����
			cin >> input_id >> input_name >> input_capacity >> input_price;
			rdTree->insertNode(input_id, input_name, input_capacity, input_price);
			break;
		case FIND:
			// �Է����� �־��� ���ø����̼� ID�� Ž��
			// �����ϸ� ���ø����̼��� ������ ���, �������� ������ NULL���
			cin >> input_id;
			rdTree->findNode(input_id, FIND);
			break;
		case UPDATE:
			//�Է����� �־��� ���ø����̼� ID�� Ž���Ͽ� ����
			//�����ϸ� ���� ������Ʈ, �������� ������ NULL���
			cin >> input_id >> input_name >> input_capacity >> input_price;
			rdTree->updateNode(input_id, input_name, input_capacity, input_price);
			break;
		case DISCOUNT:
			// ������ �Է¹޾� ���� �� ID�� ���� ���ø����̼��� ���� ����
			cin >> input_start >> input_end >> input_discount;
			break;
		}
	}
}
