#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
// �˵�����
typedef struct People {
	int aim;
	int startfloor;
};
// ��������е� ����
typedef struct Callingnode {
	People data;
	Callingnode* next;
};
typedef struct Calling {
	Callingnode* front;
	Callingnode* rear;
};

// ��������
Calling* initCalling();
// ���
void EnCalling(int aim, int start, Calling* calls);
// ����
void OutCalling(Calling* calls);
// ��ӡ����ȫ��
void PrintCalling(Calling* calls);
// ��ú������� ֱ������-1 -1 -1
void getInput();



// ���ݻ�ûд��
typedef struct Elevator {
	int nowfloor;
	int* aimfloor;
	People* passengers;
	int state;//0,1,2
	int num;
};
Elevator initElevator();
void formElevator(Elevator* p, Calling* calls);




