#pragma once
#include<stdio.h>
#include<iostream>
#include"MuInclude.h"
//#include "Ipe_Linklist.cpp"
using namespace std;

template <class T>
struct Ipe_node
{
	T* t;
	Ipe_node<T>* next;
};

//链表模板类
template <class T>
class EX_PORT Ipe_LinkList
{
public:
	Ipe_node<T>* headler;
	Ipe_node<T>* current;
	double length;
public:
	Ipe_LinkList(void);
	~Ipe_LinkList(void);
	int add(T* t);//添加链表结构
	void remove(int count);
    int get(int pos, T &t);  
    double getLen(void);  
};



template <class T>
Ipe_LinkList<T>::Ipe_LinkList(void)
{
	headler=new Ipe_node<T>;
	headler->next=NULL;
	current=headler;
	this->length=0;
}

template <class T>
Ipe_LinkList<T>::~Ipe_LinkList(void)
{
	 Ipe_node<T> *tmp = NULL;  
    while (headler) {  
        tmp = headler->next;  
        delete headler;  
        headler = tmp;  
    }
}

template <class T>
int Ipe_LinkList<T>::add(T* t)
{
	Ipe_node<T> *node = new Ipe_node <T>;  
	node->t=t;
	length++;
	current->next=node;
	node->next=NULL;
	current=node;
	return 0;
}

template <class T>
void Ipe_LinkList<T>::remove(int count)
{
	if(count>length)
	{
		printf("error:要删除不存在的元素\n");
	}
	else
	{
		int i;
		Ipe_node<T> *tmp = NULL;
		Ipe_node<T> *de=NULL;
		tmp=headler;
		 for(i=0;i<count-1;i++)
		 {
			 tmp=tmp->next;
		 }
		 de=tmp->next;
		 tmp->next=tmp->next->next;
		 delete de;
		 de=NULL;
		 length--;
	}
}

template <class T>
double Ipe_LinkList<T>::getLen(void)
{
	return length;
}


