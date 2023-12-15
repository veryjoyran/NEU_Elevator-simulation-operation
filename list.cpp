#include<list.h>
#include<stdio.h>
#include<stdlib.h>
// ��������
Calling* initCalling()
{
	Calling* p = (Calling*)malloc(sizeof(Calling));
	p->front = (Callingnode*)malloc(sizeof(Callingnode));
	p->front->data.aim = 0;
	p->front->next = NULL;
	p->rear = p->front;
	return p;
}
// ���
void EnCalling(int aim, int start, Calling* calls)
{
	Callingnode* node = (Callingnode*)malloc(sizeof(Callingnode));
	node->data.aim = aim;
	node->data.startfloor = start;
	node->next = NULL;
	calls->rear->next = node;
	calls->rear = node;
	calls->front->data.aim++;
}
// ����
void OutCalling(Calling* calls)
{
	Callingnode* print = calls->front->next;
	printf("startfloor:%d  aimfloor:%d\n", print->data.startfloor, print->data.aim);
	calls->front->next = print->next;
	free(print);
}
// ��ӡ����ȫ��
void PrintCalling(Calling* calls)
{
	Callingnode* temp = (Callingnode*)malloc(sizeof(Callingnode));
	temp = calls->front->next;
	while (temp)
	{
		printf("startfloor:%d  aimfloor:%d\n", temp->data.startfloor, temp->data.aim);
		temp = temp->next;
	}
}
// ��ú������� ֱ������-1 -1 -1
void getInput()
{
	int num, aim, start;
	scanf("%d %d %d", &num, &start, &aim);
	Calling* calls = initCalling();
	while (num != -1)
	{
		for (int i = 0; i < num; i++)
		{
			EnCalling(aim, start, calls);
		}
		scanf("%d %d %d", &num, &start, &aim);
	}
	PrintCalling(calls);
	printf("init finish\n");
	OutCalling(calls);
	printf("out finish\n");
	PrintCalling(calls);
}



// ���ݻ�ûд��

Elevator initElevator()
{
	Elevator test;
	test.nowfloor = 1;
	test.state = 0;
	test.num = 0;
	return test;
}
void formElevator(Elevator* p, Calling* calls)
{
	int total = calls->front->data.aim;
	Callingnode* temp = calls->front->next;
	for (int i = 0; i < total; i++)
	{
		p->passengers[i] = temp->data;
		temp = temp->next;
	}

}