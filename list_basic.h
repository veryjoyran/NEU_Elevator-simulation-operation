#ifndef LIST_BASIC_H
#define LIST_BASIC_H

#include <iostream>
#include <cstdlib>

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
private:
    class Node {
    public:
        DataType data = {};
        Node *next = nullptr;
        Node() = default;
    };
    
    Node* head;                      
};

#endif // LIST_H
