#pragma once
#include "ipe_graphiccell.h"
#include "Ipe_Point2D.h"
#include "Ipe_LinkList.h"
#include "MuInclude.h"
//��ȫ��ֱ����ɵ�·��
class EX_PORT Ipe_Lines :
	public Ipe_GraphicCell
{
	int num;//ֱ�߼���·��������
	Ipe_LinkList<class Ipe_Point2D>* list;
public:
	Ipe_Lines(void);
	~Ipe_Lines(void);
	int addpoint(double x,double y,int state);//��ӵ�,ʹ�ò���
	int addpoint(Ipe_Point2D* point);//��ӵ�
	virtual void printPoint();//��ӡ����
	int getnum();//����ֱ�ߵ�·��������
	void setnum(int num);//����ֱ�ߵ�·��������
	Ipe_LinkList<class Ipe_Point2D>* getlist();//���ش��ֱ�ߵ���Ϣ������ָ��
	virtual int gettype(){return 1;};//0-���� 1-ֱ�߼� 2-���߼�
};

