#pragma once
#include "ipe_graphiccell.h"
#include "Ipe_LinkList.h"
#include "Ipe_Point2D.h"
class EX_PORT Ipe_Bazeir :
public Ipe_GraphicCell
{
	int num;//���������ߵ����߶ε�����
	Ipe_LinkList<class Ipe_Point2D>* list;//�����б�
public:
	Ipe_Bazeir(void);
	~Ipe_Bazeir(void);
	int addpoint(double x1,double y1,double x2,double y2,double x3,double y3,int state);//���һ������������·��,һ�����������
	int getnum();//��ñ��������߼��е���������
	Ipe_LinkList<class Ipe_Point2D>* getlist();//���ش�ű��������ߵ���Ϣ������ָ��
	virtual void printPoint();
	virtual int gettype(){return 2;};//0-���� 1-ֱ�߼� 2-���߼�
	
};

