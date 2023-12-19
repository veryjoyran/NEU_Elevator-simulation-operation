#ifndef LIST_BASIC_H
#define LIST_BASIC_H

#include <iostream>
#include <cstdlib>
using namespace std;
// 定义链表类
template <typename DataType>
class LinkList {
public:
    LinkList();                      
    ~LinkList();                       
    void CreateLinkList(int n);      
    void TravalLinkList();           
    int GetLength();                 
    bool IsEmpty();                  
    int FindNodePosition(DataType data);   
    void InsertElemAtEnd(DataType data);            
    void InsertElemAtIndex(DataType data, int n);   
    void InsertElemAtHead(DataType data);           
    void DeleteElemAtEnd();          
    void DeleteAll();                
    void DeleteElemAtPoint(DataType data);          
    void DeleteElemAtHead();         
    DataType GetElemAtIndex(int n);
    void SetElemAtIndex(int n, DataType data);
private:
    class Node {
    public:
        DataType data = {};
        Node *next = nullptr;
        Node() = default;
    };
    
    Node* head;                      
};

//初始化单链表
template <typename DataType>
LinkList<DataType>::LinkList()                  
{
    head = new Node;            
    head->data = 0;               //将头结点的数据域定义为0
    head->next = nullptr;            //头结点的下一个定义为NULL
}     
 
// 析构函数
template <typename DataType>
LinkList<DataType>::~LinkList() {
    DeleteAll(); // 删除所有节点
    delete head; // 最后删除头结点
}

 
//创建一个单链表
template <typename DataType>
void LinkList<DataType>::CreateLinkList(int n)
{
    Node *pnew, *ptemp;
    ptemp = head;
    head->data = n;         //将头结点的数据域定义为n
    if (n < 0) {       //当输入的值有误时，处理异常
        cout << "输入的节点个数有误" << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n;i++) {        //将值一个一个插入单链表中
        pnew = new Node;
        cout << "请输入第" << i + 1 << "个值: " ;
        cin >> pnew->data;
        pnew->next = NULL;          //新节点的下一个地址为NULL
        ptemp->next = pnew;         //当前结点的下一个地址设为新节点
        ptemp = pnew;               //将当前结点设为新节点
    }
}
 
//遍历单链表
template <typename DataType>
void LinkList<DataType>::TravalLinkList()
{
    if (head == NULL || head->next ==NULL) {
        cout << "链表为空表" << endl;
    }
    Node *p = head;                 //另指针指向头结点
    while (p->next != NULL)        //当指针的下一个地址不为空时，循环输出p的数据域
    {
        p = p->next;               //p指向p的下一个地址
        cout << p->data << " ";
    }
}
 
//获取单链表的长度
template <typename DataType>
int LinkList<DataType>::GetLength()
{
   return head->data;
}
 
//判断单链表是否为空
template <typename DataType>
bool LinkList<DataType>::IsEmpty()
{
    if (head->next == NULL) {                 
        return true;
    }
    return false;
}
 
//查找节点
template <typename DataType>
int LinkList<DataType>::FindNodePosition(DataType data)
{
    Node * p = head;
    if (p == NULL) {                           //当为空表时，报异常
        cout << "此链表为空链表" << endl;
        return -1;
    }
    else{
        int count = 0;
        while (p->next != NULL)                //当指针的下一个地址不为空时，循环输出p的数据域
        {
            p = p->next;                       //p指向p的下一个地址
            count++;
            if (p->data == data) {             //当p的数据域等于data时，返回count
                return count;
            }
        }
        return -1;
    }

}
 

//在尾部插入指定的元素
template <typename DataType>
void LinkList<DataType>::InsertElemAtEnd(DataType data)
{
    Node * newNode = new Node;    //定义一个Node结点指针newNode
    newNode->next = NULL;         //定义newNode的数据域和指针域
    newNode->data = data;
    Node * p = head;              //定义指针p指向头结点
    if (head == NULL) {           //当头结点为空时，设置newNode为头结点
        head = newNode;
    }
    else                          //循环知道最后一个节点，将newNode放置在最后
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = newNode;
    }
    head->data++;                 //头结点的数据域加1
}
 
//在指定位置插入指定元素
template <typename DataType>
void LinkList<DataType>::InsertElemAtIndex(DataType data,int n)
{
    if (n<1 || n>GetLength())                   //输入有误报异常
        cout << "输入的值错误" << endl;
    else
    {
        Node * ptemp = new Node;        //创建一个新的节点
        ptemp->data = data;                     //定义数据域
        Node * p = head;                    //创建一个指针指向头结点
        int i = 1;
        while (n > i)                           //遍历到指定的位置
        {
            p = p->next;
            i++;
        }
        ptemp->next = p->next;                 //将新节点插入到指定位置
        p->next = ptemp;
    }
    head->data++;                              //头结点的数据域加1
}
 
//在头部插入指定元素
template <typename DataType>
void LinkList<DataType>::InsertElemAtHead(DataType data)
{
    Node * newNode = new Node;    //定义一个Node结点指针newNode
    newNode->data = data;
    Node * p = head;              //定义指针p指向头结点
    if (head == NULL) {           //当头结点为空时，设置newNode为头结点
        head = newNode;
    }
    newNode->next = p->next;          //将新节点插入到指定位置
    p->next = newNode;
    head->data++;                 //头结点的数据域加1
}
 
//在尾部删除元素
template <typename DataType>
void LinkList<DataType>::DeleteElemAtEnd()
{
    Node * p = head;          //创建一个指针指向头结点
    Node * ptemp = NULL;      //创建一个占位节点
    if (p->next == NULL) {        //判断链表是否为空
        cout << "单链表空" << endl;
    }
    else
    {
        while (p->next != NULL)   //循环到尾部的前一个
        {
            ptemp = p;            //将ptemp指向尾部的前一个节点
            p = p->next;          //p指向最后一个节点
        }
        delete p;                //删除尾部节点
        p = NULL;
        ptemp->next = NULL;
    }
    head->data--;               //头结点的数据域减1
}
 
//删除所有数据
template <typename DataType>
void LinkList<DataType>::DeleteAll()
{
    Node * p = head->next;
    Node * ptemp = new Node;
    while (p != NULL)                    //在头结点的下一个节点逐个删除节点
    {
        ptemp = p;
        p = p->next;
        head->next = p;
        ptemp->next = NULL;
        delete ptemp;
    }
    head->next = NULL;                 //头结点的下一个节点指向NULL
    head->data = 0;                    //头结点的数据域为0
}
 
//删除指定的数据
template <typename DataType>
void LinkList<DataType>::DeleteElemAtPoint(DataType data)
{
    int temp = FindNodePosition(data);    //查找到指定数据的节点位置
    if (temp == -1) {                     //当查找不到时，报异常
        cout << "没有该节点" << endl;
    }
    else
    {
        Node * p = head;              //创建一个指针指向头结点
        Node * ptemp = NULL;          //创建一个占位节点
        for (int i = 0; i < temp; i++)    //循环到指定的位置
        {
            ptemp = p;                    //将ptemp指向指定位置的前一个节点
            p = p->next;                  //p指向指定位置的节点
        }
        ptemp->next = p->next;            //将指定位置的前一个节点指向指定位置的下一个节点
        delete p;                         //删除指定位置的节点
        p = NULL;
    }
    head->data--;                         //头结点的数据域减1
 
}
 
//在头部删除节点
template <typename DataType>
void LinkList<DataType>::DeleteElemAtHead()
{
    Node * p = head;
    if (p == NULL || p->next == NULL) {   //判断是否为空表，报异常
        cout << "该链表为空表" << endl;
    }
    else
    {
        Node * ptemp = NULL;      //创建一个占位节点
        p = p->next;
        ptemp = p->next;              //将头结点的下下个节点指向占位节点
        delete p;                     //删除头结点的下一个节点
        p = NULL;
        head->next = ptemp;           //头结点的指针更换
    }
    head->data--;                     //头结点的数据域减1
}

//获取指定位置的数据
template <typename DataType>
DataType LinkList<DataType>::GetElemAtIndex(int n)
{
    Node * p = head;
    if (p == NULL) {                           //当为空表时，报异常
        cout << "此链表为空链表" << endl;
        return -1;
    }
    else{
        int count = 0;
        while (p->next != NULL)                //当指针的下一个地址不为空时，循环输出p的数据域
        {
            p = p->next;                       //p指向p的下一个地址
            count++;
            if (count == n) {             //当p的数据域等于data时，返回count
                return p->data;
            }
        }
        return -1;
    }
}

//设置指定位置的数据
template <typename DataType>
void LinkList<DataType>::SetElemAtIndex(int n, DataType data)
{
    Node * p = head;
    if (p == NULL) {                           //当为空表时，报异常
        cout << "此链表为空链表" << endl;
    }
    else{
        int count = 0;
        while (p->next != NULL)                //当指针的下一个地址不为空时，循环输出p的数据域
        {
            p = p->next;                       //p指向p的下一个地址
            count++;
            if (count == n) {             //当p的数据域等于data时，返回count
                p->data=data;
            }
        }
    }
}
 
#endif // LIST_H
