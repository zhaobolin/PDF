#pragma once
#include "Ipe_GraphicCell.h"
#include"Ipe_Color.h"
#include "Ipe_LinkList.h"
#include "MuInclude.h"
#include "Ipe_Point2D.h"
#include "Ipe_Lines.h"
#include "Ipe_Bazeir.h"
#include "Ipe_PdfElement.h"
#include "Ipe_Plane.h"
//�˲㴦��һ��·��������·�������ԣ�����·����Ϣ��ֱ�߼��뱴�������߼����л���
class EX_PORT Ipe_PdfPath
{
	int pathtype;//path���ͣ��Ƿ��Ǽ���·������ ����-3 ����·������-4

	float linewidth;//��¼�߿�
	int colorspace;//��¼����һ����ɫ�ռ�(����չ) 1-G 2-g 3-RG 4-rg 5-cmyk(k) 6-cmyk(K)
	Ipe_Color color;//��¼��ɫ

	int scolorspace;//������������µ���ɫ�ռ�
	Ipe_Color *scolor;//һ��ָ��,�ȴ�����������ɫ�ռ�
	//��֮�������:һ������ͨ���,ֻ��һ����ɫ
	//��һ�������,��Ҫ���ҲҪ��ɫ,��ʱĬ��scolor���,color��ɫ

	int drawingmethord;//���Ʒ��� 1-S 2-f* 3-f/F 4-s 5-B 6-B* 7-b 8-b*
	int GraphicsCellCount;//��¼ֱ�߼������߼�����
	Ipe_LinkList<class Ipe_Plane>* list;//��ŵ�ͼҪ�ص�����


public:
	Ipe_PdfPath(void);
	Ipe_PdfPath(zblroute* route);//��ʼ��·������
	~Ipe_PdfPath(void);
	void printfPath();
	int isclosedfeature();//�б��Ƿ��Ǳպ�·��
	int getcolorspace();//��ȡ��ɫ�ռ�
	int getGraphicCellCount();//ȡ�õ�ͼҪ������
	int getdrawingmethord();//ȡ�û��Ʒ��� 1-S 2-f*
	Ipe_LinkList<class Ipe_Plane>* getPlane();//ȡ�õ�ͼҪ������
	Ipe_Color getcolor();//ȡ����ɫ
	int getelementtype(){return 1;};//�жϱ������� 0-���� 1-Ipe_PdfPath 2-? 3-? 
	float getlinewidth();
	int getpathtype();
	Ipe_Color getscolor();//ȡ�õڶ�����ɫ
	int getscolorspace();
};

