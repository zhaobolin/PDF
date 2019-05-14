#pragma once
#include "MuInclude.h"
#define EX_PORT __declspec(dllexport) 
/*
	zblroute�ṹ�Ķ�Ӧ��,�������ŵ���һ��·��ʸ������Ϣ
*/
class EX_PORT Vector
{

	int type;//·������ ֱ��-1 ����������-2 ����-3 ����·������-4

	float linewidth;//��¼�߿�(Ŀǰ�и�����,����߿��ı�,���·��������ܹ�ͬʹ��ͬһ���߿�)

	int colorspace;//��¼����һ����ɫ�ռ�(����չ) 1-G 2-g 3-RG 4-rg
	float color[4];//��¼��ɫ

	int countpoint;//��¼·�������
	float points[500][7];//line[x][0],line[x][1],line[x][6]�ֱ���ֱ��·�����x,y����,�Լ�����·����m,l,h,c״̬(�ֱ��Ӧ0,1,2,3)
	
	int drawingmethord;//���Ʒ��� 1-S 2-f*
public:
	Vector(void);
	Vector(struct zblroute & vector);
	~Vector(void);
	//set get�ӿ�
	int getcountpoint();
	int gettype();
	float getlinewidth();
	int getcolorspace();
	float(*getpoints())[7];
	float* getcolor();
	int getdrawingmethord();
	
};
/*
�ײ�Mupdf��ȡ���ĵ�ʸ�����ݽṹ��
struct zblroute
{
	int type;//·������ ֱ��-1 ����������-2 ����-3 ����·������-4

	float linewidth;//��¼�߿�(Ŀǰ�и�����,����߿��ı�,���·��������ܹ�ͬʹ��ͬһ���߿�)

	int colorspace;//��¼����һ����ɫ�ռ�(����չ) 1-G 2-g 3-RG 4-rg
	float color[4];//��¼��ɫ

	int countpoint;//��¼·�������
	float points[500][7];//line[x][0],line[x][1],line[x][6]�ֱ���ֱ��·�����x,y����,�Լ�����·����m,l,h,c״̬(�ֱ��Ӧ0,1,2,3)//�ĳɽṹ������
	
	int drawingmethord;//���Ʒ��� 1-S 2-f*
};

struct zblrouteset//��ȡ·�����Ͻṹ�� zbl
{
	int count;
	struct zblroute set[1000];

};*/
