#include "Ipe_LinkList.h"

//¡¥±Ìƒ£∞Â¿‡
template <class T>
Ipe_LinkList<T>::Ipe_LinkList(void)
{
	headler=new Ipe_node<T>;
	headler->next=null;
	current=headler;
	this->length=0;
}

template <class T>
Ipe_LinkList<T>::~Ipe_LinkList(void)
{
	 Ipe_node<T> *tmp = NULL;  
    while (header) {  
        tmp = header->next;  
        delete header;  
        header = tmp;  
    }  
}

template <class T>
int Ipe_LinkList<T>::add(T t)
{
	Ipe_node<T> *node = new Ipe_node <T>;  
	node->t=t;
	length++;
	current->next=node;
	node->next=null;
	current=node;
	return 0;
}
