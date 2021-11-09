#include <iostream>
using namespace std;

// 입력 명령어 define
#define INSERT 'I'
#define FIND 'F'
#define UPDATE 'R'
#define DISCOUNT 'D'

// 입력 변수 선언
int inputCommandCnt; // 입력받을 명령어 수
char commandType; // 명령어 종류
int input_id; // 애플리케이션 ID
string input_name; // 이름
int input_capacity; // 용량
int input_price; // 가격
int input_discount; // 할인율
int input_start; // 범위 시작
int input_end; // 범위 끝

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
	// 생성자
	Node(int id, int capacity, int price, string name) : id(id), capacity(capacity), price(price), name(name) {
		color = RED; // 추가하는 node는 무조건 빨강(root제외)
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
		// 존재하면 애플리케이션의 정보를 출력, 존재하지 않으면 NULL출력
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
		return { nullptr,false };// node가 하나도 없을 때
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
		Node* great_grandparent = grandparent->parent; // 조부모의 부모
		Node* uncle = nullptr;
		Color uncleColor = BLACK;
		Direction direction;
		
		// parent의 sibling node가 RED인지 BLACK인지 확인해야 함
		if (grandparent->left == parent)
			uncle = grandparent->right;
		else if (grandparent->right == parent)
			uncle = grandparent->left;
		if (uncle != nullptr)
			uncleColor = uncle->color;

		if (uncleColor == BLACK)
		{
			
			// curNode, parent, grandparent끼리 restruct => 부모는 BLACK, 자식은 RED로 칠해야 함
			if ((grandparent->left == parent && parent->left == curNode) || (grandparent->right == parent && parent->right == curNode))
			{
				// 무조건 parent가 새로운 sub트리의 parent
				direction = (parent->left == curNode ? LEFT : RIGHT); // 3개 노드(curNode, parent, grandparent)가 어느 쪽으로 뻗어있는 지
				if (direction == LEFT)
				{
					// parent의 딸린 자식 grandparent에 추가
					if (parent->right != nullptr)
						parent->right->parent = grandparent;
					grandparent->left = parent->right;

					// parent와 grandparent의 부모관계 바꿈
					grandparent->parent = parent;
					parent->right = grandparent;
				}
				else if (direction == RIGHT)
				{
					// parent의 딸린 자식 grandparent에 추가
					if (parent->left != nullptr)
						parent->left->parent = grandparent;
					grandparent->right = parent->left;

					// parent와 grandparent의 부모관계 바꿈
					grandparent->parent = parent;
					parent->left = grandparent;
				}
				// parent의 새로운 부모 갱신
				parent->parent = great_grandparent;
				if (great_grandparent != nullptr)
				{
					if (great_grandparent->left == grandparent)
						great_grandparent->left = parent;
					else
						great_grandparent->right = parent;
				}
				// 색 바꿈
				parent->color = BLACK;
				grandparent->color = RED;
				curNode->color = RED;
			}
			else {
				// 무조건 curNode가 새로운 sub트리의 parent
				direction = (parent->left == curNode ? LEFT : RIGHT); // parent의 어느쪽 자식이 curNode인지
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
				// curNode의 새로운 부모 갱신
				curNode->parent = great_grandparent;
				if (great_grandparent != nullptr)
				{
					if (great_grandparent->left == grandparent)
						great_grandparent->left = curNode;
					else
						great_grandparent->right = curNode;
				}
				// 색 바꿈
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
		
		if (nodeInfo.second == true) // 해당 id 이미 존재함
			return;
		
		Node* parent = nodeInfo.first;
		Node* newNode = new Node(id, capacity, price, name);
		if (parent == nullptr)
		{
			// node가 하나도 없을 때 => root 추가해야함
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
			// 애플리케이션 정보(id, 이름, 용량, 가격)를 입력받아 레드블랙트리에 노드를 삽입하고, 그 노드의 깊이를 출력
			// 만약 해당 애플리케이션이 이미 등록되어 있다면, 그 노드의 깊이를 출력하고 등록은 거절
			cin >> input_id >> input_name >> input_capacity >> input_price;
			rdTree->insertNode(input_id, input_name, input_capacity, input_price);
			break;
		case FIND:
			// 입력으로 주어진 애플리케이션 ID를 탐색
			// 존재하면 애플리케이션의 정보를 출력, 존재하지 않으면 NULL출력
			cin >> input_id;
			rdTree->findNode(input_id, FIND);
			break;
		case UPDATE:
			//입력으로 주어진 애플리케이션 ID를 탐색하여 존재
			//존재하면 정보 업데이트, 존재하지 않으면 NULL출력
			cin >> input_id >> input_name >> input_capacity >> input_price;
			rdTree->updateNode(input_id, input_name, input_capacity, input_price);
			break;
		case DISCOUNT:
			// 범위를 입력받아 범위 내 ID를 가진 애플리케이션의 가격 할인
			cin >> input_start >> input_end >> input_discount;
			break;
		}
	}
}
