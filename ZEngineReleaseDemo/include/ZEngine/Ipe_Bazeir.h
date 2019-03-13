#pragma once
#include "ipe_graphiccell.h"
#include "Ipe_LinkList.h"
#include "Ipe_Point2D.h"
class EX_PORT Ipe_Bazeir :
public Ipe_GraphicCell
{
	int num;//贝塞尔曲线的曲线段的数量
	Ipe_LinkList<class Ipe_Point2D>* list;//曲线列表
public:
	Ipe_Bazeir(void);
	~Ipe_Bazeir(void);
	int addpoint(double x1,double y1,double x2,double y2,double x3,double y3,int state);//添加一条贝塞尔曲线路径,一次添加三个点
	int getnum();//获得贝塞尔曲线集中的曲线数量
	Ipe_LinkList<class Ipe_Point2D>* getlist();//返回存放贝塞尔曲线点信息的链表指针
	virtual void printPoint();
	virtual int gettype(){return 2;};//0-父类 1-直线集 2-曲线集
	
};

