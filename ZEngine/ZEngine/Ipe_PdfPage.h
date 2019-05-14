#pragma once
#include "Ipe_LinkList.h"
#include "Ipe_PdfElement.h"
#include "Ipe_PdfPath.h"
#include "MuInclude.h"
#include "clipfunction.h"
class EX_PORT Ipe_PdfPage
{
	fz_rect rect;//ҳ�淶Χ �˴����ɴ��޸�
	Ipe_LinkList<Ipe_PdfElement>* list;//���ҳ��Ԫ�� ·����xobject��
	int graphiccellcount;//��¼ҳ��Ԫ������
public:
	Ipe_PdfPage(void);
	Ipe_PdfPage(zblrouteset* routeset);//��ʼ��ҳ��
	~Ipe_PdfPage(void);
	int getgraphiccellcount();
	Ipe_LinkList<Ipe_PdfElement>* getelement();//��ȡҳ��Ԫ���б�
	void printpage();
	inline float transform(float x,float y,float a,float b,float c){
		//printf("\nת�þ�������:x=%f y=%f a=%f b=%f c=%f\n",x,y,a,b,c);
		return a*x+b*y+c;};//��������,���ڽ��о�������
	void pagetoSVG(char* path);//����SVG�ĺ���
	fz_rect getrect();
	void setrect(fz_rect rect);
	void maketransform(); //����ҳ�ڲ�����,����ת�þ�������
	void clipwithrect(cliprect *myrect);//ʹ�ø�����С�ľ��ζ�ģ�ͽ��вü�
};

