#pragma once
#include "Ipe_LinkList.h"
#include "Ipe_GraphicCell.h"
class EX_PORT Ipe_Plane//一条可能为面的路径,由一系列直线集与曲线集组成
{
	int graphiccellcount;
	bool isplane;//是否是一个面
	Ipe_LinkList<class Ipe_GraphicCell>* list;
public:
	Ipe_Plane(void);
	~Ipe_Plane(void);
	Ipe_LinkList<class Ipe_GraphicCell>* getlist();
	void setplane();
	void printPoint();
	void addgraphiccellcount();
	bool getisplane();
	int getgraphicellcount();
	void setlist(Ipe_LinkList<Ipe_GraphicCell>* list);
	
};

