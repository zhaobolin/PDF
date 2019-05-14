#include "Ipe_Plane.h"


Ipe_Plane::Ipe_Plane(void)
{
	this->graphiccellcount=0;
	this->isplane=false;
	this->list=new Ipe_LinkList<Ipe_GraphicCell>();
}


Ipe_Plane::~Ipe_Plane(void)
{
	delete list;
}

Ipe_LinkList<class Ipe_GraphicCell>* Ipe_Plane::getlist()
{
	return this->list;
}
void Ipe_Plane::setplane()
{
	this->isplane=true;
}

void Ipe_Plane::printPoint()
{
	printf("������plane���������\n");
	//printf("��·������ɫ�ռ�Ϊ:%d",this->getcolorspace());
	Ipe_node<Ipe_GraphicCell>* p=list->headler;
	//p->t->printPoint();
	printf("����ѭ��\n");
	while(p->next!=NULL)
	{
		p->next->t->printPoint();//����ת��
		p=p->next;
	}
}

void Ipe_Plane::addgraphiccellcount()
{
	this->graphiccellcount++;
}

bool Ipe_Plane::getisplane()
{
	return this->isplane;
}
int Ipe_Plane::getgraphicellcount()
{
	return this->graphiccellcount;
}
void Ipe_Plane::setlist(Ipe_LinkList<Ipe_GraphicCell>* list)
{
	this->list=list;
}