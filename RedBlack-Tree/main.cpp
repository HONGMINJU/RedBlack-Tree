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

	void findNode(int find_id)
	{
		// �����ϸ� ���ø����̼��� ������ ���, �������� ������ NULL���
		Node* curNode = this->root;
		int depth = 0;
		while (curNode != nullptr)
		{
			if (curNode->id == find_id)
			{
				cout << depth << curNode->name << curNode->capacity << curNode->price << "\n";
				return;
			}
			else if (curNode->id > find_id)
				curNode = curNode->left;
			else
				curNode = curNode->right;
			depth++;
		}
		cout << "NULL\n";
		return;
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
			break;
		case FIND:
			// �Է����� �־��� ���ø����̼� ID�� Ž��
			// �����ϸ� ���ø����̼��� ������ ���, �������� ������ NULL���
			cin >> input_id;
			rdTree->findNode(input_id);
			break;
		case UPDATE:
			//�Է����� �־��� ���ø����̼� ID�� Ž���Ͽ� ����
			//�����ϸ� ���� ������Ʈ, �������� ������ NULL���
			cin >> input_id >> input_name >> input_capacity >> input_price;
			break;
		case DISCOUNT:
			// ������ �Է¹޾� ���� �� ID�� ���� ���ø����̼��� ���� ����
			cin >> input_start >> input_end >> input_discount;
			break;
		}
	}
}
