#pragma once
#include "ipe_pdfelement.h"
#include "Ipe_LinkList.h"
//�˲㴦��һ��ͼ��״̬ջ����Ϣ
class EX_PORT Ipe_PdfStack :
	public Ipe_PdfElement
{
	int existstack;//�Ƿ���ͼ��״̬ջ��
	int countpath;//��¼һ��ͼ��״̬ջ���ж��ٸ�·��

	int existcm;//�Ƿ����ת�þ���,Ĭ��Ϊ0-������ 1-����
	float* matrix;//���ת�þ���,Ĭ��ΪNULL

	int existclip;//�Ƿ���ڲü�·�� �Լ�������ʽ 1-W 2-W*
	int countclip;//����·������
	int clipcellcount;//����·���ж��ٶ�
	
	int shadowtype;//�Ƿ������Ӱ(Ϊ����ȡ����ɫ)0-������ ֮��ÿ�����ֶ��и��Զ�Ӧ������
	float *bcolor;//��¼��ʼ��ɫ
	float *ecolor;//��¼������ɫ
	float ca;//͸����,Ĭ��Ϊ1

	int grade;//ջ�Ĳ��,�����Բü�·���Լ�ת�þ�����д���,Ĭ��Ϊ��

	Ipe_LinkList<class Ipe_PdfPath>* pathlist;//���һ��ͼ��״̬ջ��·��������
	Ipe_LinkList<class Ipe_GraphicCell>* cliplist;//��Ųü�·��������

public:
	Ipe_PdfStack(void);
	Ipe_PdfStack(struct zblstack*);
	void printfPath();
	virtual int getelementtype();
	~Ipe_PdfStack(void);
	int getcountpath();
	int getexistclip();
	int getexistcm();
	int getclipcellcount();
	float *getmatrix();
	Ipe_LinkList<class Ipe_GraphicCell>* getcliplist();
	Ipe_LinkList<class Ipe_PdfPath>* getpathlist();
	int getshadowtype();
	float* getbcolor();
	float* getecolor();
	float getca();
	void setgrade(int grade);
	int getgrade();
	void setexistcm(int cm);
};

