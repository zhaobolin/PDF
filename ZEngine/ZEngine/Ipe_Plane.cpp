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
	printf("调用了plane的输出函数\n");
	//printf("本路径的颜色空间为:%d",this->getcolorspace());
	Ipe_node<Ipe_GraphicCell>* p=list->headler;
	//p->t->printPoint();
	printf("进入循环\n");
	while(p->next!=NULL)
	{
		p->next->t->printPoint();//向下转型
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