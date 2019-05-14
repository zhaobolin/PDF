#pragma once
#include "Ipe_Lines.h"
#include "Ipe_Bazeir.h"
#include "Ipe_LinkList.h"
#include "Ipe_GraphicCell.h"
#define LEFT_EDGE 1//���ñ߽�
#define RIGHT_EDGE 2
#define BOTTOM_EDGE 4
#define TOP_EDGE 8

struct cliprect
{
	float x0;
	float y0;
	float x1;
	float y1;
};

class Ipe_Lines* cliplines(Ipe_Lines* lines,cliprect* rect);//�ü�ֱ�߼��ĺ���,��󷵻�һ���µĽڵ�
int compcode(Ipe_Point2D *p0,cliprect* rect);//����ü������ɱ���ĺ���
void chopline(Ipe_Point2D* p0,int code,cliprect* rect,float delx,float dely);//�����ƽ��ֱ�ߵĺ���

class Ipe_Bazeir* clipbazeir (Ipe_Bazeir* bazeir,cliprect* rect);//�ü����������ߵĺ���,��󷵻�һ���µı��������߼�
int rtinside(Ipe_Point2D* start,Ipe_Point2D* end,Ipe_Point2D* p);//����ֱ�ߵķ���
Ipe_LinkList<Ipe_GraphicCell>* clipplane(Ipe_LinkList<Ipe_GraphicCell>* list,cliprect* rect);//�ü���ĺ���,����һ��ֱ�߼������߼�������