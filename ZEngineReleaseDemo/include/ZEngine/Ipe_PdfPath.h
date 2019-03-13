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
//此层处理一条路径，保存路径的属性，并将路径信息按直线集与贝塞尔曲线集进行划分
class EX_PORT Ipe_PdfPath
{
	int pathtype;//path类型，是否是剪辑路径矩形 矩形-3 剪辑路径矩形-4

	float linewidth;//记录线宽
	int colorspace;//记录是哪一种颜色空间(可扩展) 1-G 2-g 3-RG 4-rg 5-cmyk(k) 6-cmyk(K)
	Ipe_Color color;//记录颜色

	int scolorspace;//处理特殊情况下的颜色空间
	Ipe_Color *scolor;//一个指针,等待分配额外的颜色空间
	//总之两种情况:一种是普通情况,只有一个颜色
	//另一种情况是,既要描边也要填色,此时默认scolor描边,color填色

	int drawingmethord;//绘制方法 1-S 2-f* 3-f/F 4-s 5-B 6-B* 7-b 8-b*
	int GraphicsCellCount;//记录直线集与曲线集数量
	Ipe_LinkList<class Ipe_Plane>* list;//存放地图要素的链表


public:
	Ipe_PdfPath(void);
	Ipe_PdfPath(zblroute* route);//初始化路径对象
	~Ipe_PdfPath(void);
	void printfPath();
	int isclosedfeature();//判别是否是闭合路径
	int getcolorspace();//获取颜色空间
	int getGraphicCellCount();//取得地图要素数量
	int getdrawingmethord();//取得绘制方法 1-S 2-f*
	Ipe_LinkList<class Ipe_Plane>* getPlane();//取得地图要素链表
	Ipe_Color getcolor();//取得颜色
	int getelementtype(){return 1;};//判断本类类型 0-父类 1-Ipe_PdfPath 2-? 3-? 
	float getlinewidth();
	int getpathtype();
	Ipe_Color getscolor();//取得第二种颜色
	int getscolorspace();
};

