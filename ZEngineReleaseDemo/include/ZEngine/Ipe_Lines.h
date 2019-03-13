#pragma once
#include "ipe_graphiccell.h"
#include "Ipe_Point2D.h"
#include "Ipe_LinkList.h"
#include "MuInclude.h"
//完全由直线组成的路径
class EX_PORT Ipe_Lines :
	public Ipe_GraphicCell
{
	int num;//直线集的路径点数量
	Ipe_LinkList<class Ipe_Point2D>* list;
public:
	Ipe_Lines(void);
	~Ipe_Lines(void);
	int addpoint(double x,double y,int state);//添加点,使用参数
	int addpoint(Ipe_Point2D* point);//添加点
	virtual void printPoint();//打印函数
	int getnum();//返回直线的路径点数量
	void setnum(int num);//设置直线的路径点数量
	Ipe_LinkList<class Ipe_Point2D>* getlist();//返回存放直线点信息的链表指针
	virtual int gettype(){return 1;};//0-父类 1-直线集 2-曲线集
};

