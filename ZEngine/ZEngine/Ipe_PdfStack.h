#pragma once
#include "ipe_pdfelement.h"
#include "Ipe_LinkList.h"
//此层处理一个图形状态栈的信息
class EX_PORT Ipe_PdfStack :
	public Ipe_PdfElement
{
	int existstack;//是否在图形状态栈中
	int countpath;//记录一个图形状态栈中有多少个路径

	int existcm;//是否存在转置矩阵,默认为0-不存在 1-存在
	float* matrix;//存放转置矩阵,默认为NULL

	int existclip;//是否存在裁剪路径 以及剪辑方式 1-W 2-W*
	int countclip;//剪辑路径点数
	int clipcellcount;//剪辑路径有多少段
	
	int shadowtype;//是否存在阴影(为了提取渐变色)0-不存在 之后每个数字都有各自对应的类型
	float *bcolor;//记录起始颜色
	float *ecolor;//记录结束颜色
	float ca;//透明度,默认为1

	int grade;//栈的层次,用来对裁剪路径以及转置矩阵进行处理,默认为零

	Ipe_LinkList<class Ipe_PdfPath>* pathlist;//存放一个图形状态栈的路径的链表
	Ipe_LinkList<class Ipe_GraphicCell>* cliplist;//存放裁剪路径的链表

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

