#ifndef LIST_BASIC_H
#define LIST_BASIC_H

#include <iostream>
#include <cstdlib>
typedef int DataType;

// 前向声明
class Node;

// 定义链表节点类
class Node {
public:
    DataType data;
    Node *next;
    Node(DataType d = 0, Node* n = NULL);
};

// 定义链表类
class LinkList {
public:
    LinkList();                      
    ~LinkList();                     
    void CreateLinkList(int n);      
    void TravalLinkList();           
    int GetLength();                 
    bool IsEmpty();                  
    Node* FindNode(DataType data);   
    void InsertElemAtEnd(DataType data);            
    void InsertElemAtIndex(DataType data, int n);   
    void InsertElemAtHead(DataType data);           
    void DeleteElemAtEnd();          
    void DeleteAll();                
    void DeleteElemAtPoint(DataType data);          
    void DeleteElemAtHead();         
private:
    Node* head;                      
};

#endif // LIST_H
