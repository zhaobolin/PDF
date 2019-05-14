#include "Ipe_Lines.h"
#include<stdio.h>

Ipe_Lines::Ipe_Lines(void)
{
	num=0;
	list=new Ipe_LinkList<Ipe_Point2D>;
}


Ipe_Lines::~Ipe_Lines(void)
{
	delete list;
	//printf("Ipe_Lines链表释放\n");
}

int Ipe_Lines::addpoint(double x,double y,int state)
{
	Ipe_Point2D* point=new Ipe_Point2D(x,y,state);
	list->add(point);
	num++;
	//printf("%d:%f %f\n",num,x,y);
	return 0;
}

int Ipe_Lines::addpoint(Ipe_Point2D* point)
{
	list->add(point);
	num++;
	//printf("%d:%f %f\n",num,point->getx(),point->gety());
	return 0;
}

void Ipe_Lines::printPoint()
{
	int i=0;
	printf("直线点集\n");
	Ipe_node<Ipe_Point2D>* p=list->headler;
	while(p->next!=NULL)
	{
		i++;
		printf("第%d个点\n",i);
		printf("%f %f\n",p->next->t->getx(),p->next->t->gety());
		p=p->next;
	}
	//printf("直线点集输出完毕\n");
}

int Ipe_Lines::getnum()
{
	return num;
}

void Ipe_Lines::setnum(int num)
{
	this->num=num;
}

Ipe_LinkList<class Ipe_Point2D>* Ipe_Lines::getlist()
{
	return list;
}
