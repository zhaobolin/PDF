#include "Ipe_Bazeir.h"


Ipe_Bazeir::Ipe_Bazeir(void)
{
	num=0;
	list=new Ipe_LinkList<Ipe_Point2D>;
}


Ipe_Bazeir::~Ipe_Bazeir(void)
{
	delete list;
	//printf("Ipe_Bazeir链表释放\n");
}

int Ipe_Bazeir::addpoint(double x1,double y1,double x2,double y2,double x3,double y3,int state)
{
	Ipe_Point2D* point1=new Ipe_Point2D(x1,y1,state);
	Ipe_Point2D* point2=new Ipe_Point2D(x2,y2,state);
	Ipe_Point2D* point3=new Ipe_Point2D(x3,y3,state);
	list->add(point1);
	list->add(point2);
	list->add(point3);
	num++;
	//printf("添加贝塞尔路径:%d:%f %f  %f %f  %f %f",num,x1,y1,x2,y2,x3,y3);
	return 0;
}
int Ipe_Bazeir::getnum()
{
	return num;
}

Ipe_LinkList<class Ipe_Point2D>* Ipe_Bazeir::getlist()
{
	return list;
}
void Ipe_Bazeir::printPoint()
{
	printf("曲线的点集%d个点\n",this->getnum());
	Ipe_node<Ipe_Point2D>* p=list->headler;
	while(p->next!=NULL)
	{
		printf("%f %f\n",p->next->t->getx(),p->next->t->gety());
		p=p->next;
	}
	//printf("贝塞尔曲线点集输出完毕\n");
}

