#pragma once
#include "Ipe_LinkList.h"
#include "Ipe_GraphicCell.h"
class EX_PORT Ipe_Plane//һ������Ϊ���·��,��һϵ��ֱ�߼������߼����
{
	int graphiccellcount;
	bool isplane;//�Ƿ���һ����
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

