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

struct Node
{
	int id;
	int capacity;
	int price;
	string name;
	Color color = RED;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

class RedBlackTree {
private:
	Node* root;

public : 
	RedBlackTree() {
		root = nullptr;
	}

	bool isLeafNode(Node* node)
	{
		return (node->left == nullptr && node->right == nullptr);
	}

	Node* findNode(int find_id, char commandType)
	{
		// 존재하면 애플리케이션의 정보를 출력, 존재하지 않으면 NULL출력
		Node* curNode = this->root;
		int depth = 0;
		while (curNode != nullptr)
		{
			if (curNode->id == find_id)
			{
				if (commandType == FIND)
					cout << depth << curNode->name << curNode->capacity << curNode->price << "\n";
				else if (commandType == UPDATE)
					cout << depth << "\n";
				return curNode;
			}
			else if (curNode->id > find_id)
				curNode = curNode->left;
			else 
				curNode = curNode->right;
			depth++;
		}
		cout << "NULL\n";
		return nullptr;
	}
	
	void updateNode(int id, string name, int capacity, int price)
	{
		Node* curNode = findNode(id, UPDATE);
		if (curNode != nullptr)
		{
			curNode->name = name;
			curNode->capacity = capacity;
			curNode->price = price;
		}
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
			break;
		case FIND:
			// 입력으로 주어진 애플리케이션 ID를 탐색
			// 존재하면 애플리케이션의 정보를 출력, 존재하지 않으면 NULL출력
			cin >> input_id;
			rdTree->findNode(input_id);
			break;
		case UPDATE:
			//입력으로 주어진 애플리케이션 ID를 탐색하여 존재
			//존재하면 정보 업데이트, 존재하지 않으면 NULL출력
			cin >> input_id >> input_name >> input_capacity >> input_price;
			break;
		case DISCOUNT:
			// 범위를 입력받아 범위 내 ID를 가진 애플리케이션의 가격 할인
			cin >> input_start >> input_end >> input_discount;
			break;
		}
	}
}
