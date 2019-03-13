#pragma once
#include "Ipe_Lines.h"
#include "Ipe_Bazeir.h"
#include "Ipe_LinkList.h"
#include "Ipe_GraphicCell.h"
#define LEFT_EDGE 1//设置边界
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

class Ipe_Lines* cliplines(Ipe_Lines* lines,cliprect* rect);//裁剪直线集的函数,最后返回一个新的节点
int compcode(Ipe_Point2D *p0,cliprect* rect);//编码裁剪法生成编码的函数
void chopline(Ipe_Point2D* p0,int code,cliprect* rect,float delx,float dely);//处理非平凡直线的函数

class Ipe_Bazeir* clipbazeir (Ipe_Bazeir* bazeir,cliprect* rect);//裁剪贝赛尔曲线的函数,最后返回一个新的贝赛尔曲线集
int rtinside(Ipe_Point2D* start,Ipe_Point2D* end,Ipe_Point2D* p);//计算直线的方向
Ipe_LinkList<Ipe_GraphicCell>* clipplane(Ipe_LinkList<Ipe_GraphicCell>* list,cliprect* rect);//裁剪面的函数,返回一个直线集与曲线集的链表