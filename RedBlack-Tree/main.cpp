#include <iostream>
using namespace std;

// �Է� ���ɾ� define
#define INSERT 'I'
#define FIND 'F'
#define UPDATE 'R'
#define DISCOUNT 'D'

// �Է� ���� ����
int inputCommandCnt; // �Է¹��� ���ɾ� ��
char commandType; // ���ɾ� ����
int input_id; // ���ø����̼� ID
string input_name; // �̸�
int input_capacity; // �뷮
int input_price; // ����
int input_discount; // ������
int input_start; // ���� ����
int input_end; // ���� ��

int main() {

	cin >> inputCommandCnt;
	while (inputCommandCnt--)
	{
		cin >> commandType;
		switch (commandType)
		{
		case INSERT:
			// ���ø����̼� ����(id, �̸�, �뷮, ����)�� �Է¹޾� �������Ʈ���� ��带 �����ϰ�, �� ����� ���̸� ���
			// ���� �ش� ���ø����̼��� �̹� ��ϵǾ� �ִٸ�, �� ����� ���̸� ����ϰ� ����� ����
			cin >> input_id >> input_name >> input_capacity >> input_price;
			break;
		case FIND:
			// �Է����� �־��� ���ø����̼� ID�� Ž��
			// �����ϸ� ���ø����̼��� ������ ���, �������� ������ NULL���
			cin >> input_id;
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