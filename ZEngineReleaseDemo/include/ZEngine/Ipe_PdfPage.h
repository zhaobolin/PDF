#pragma once
#include "Ipe_LinkList.h"
#include "Ipe_PdfElement.h"
#include "Ipe_PdfPath.h"
#include "MuInclude.h"
#include "clipfunction.h"
#include "Ipe_Point2D.h"
#include "Ipe_PdfMapEdge.h"
#include <vector>
#include <map>
#include <algorithm>

struct simplepoint
{
	float x;
	float y;
};
struct simpleline
{
	float x1,y1;
	float x2,y2;
};


class EX_PORT Ipe_PdfPage
{
	fz_rect rect;//页面范围 此处存疑待修改
	Ipe_LinkList<Ipe_PdfElement>* list;//存放页面元素 路径，xobject等
	int graphiccellcount;//记录页面元素数量
	//Ipe_PdfMapEdge* edge;//检测地图边界
public:
	Ipe_PdfPage(void);
	Ipe_PdfPage(zblrouteset* routeset);//初始化页面
	~Ipe_PdfPage(void);
	int getgraphiccellcount();
	Ipe_LinkList<Ipe_PdfElement>* getelement();//获取页面元素列表
	void printpage();
	inline float transform(float x,float y,float a,float b,float c){
		//printf("\n转置矩阵运算:x=%f y=%f a=%f b=%f c=%f\n",x,y,a,b,c);
		return a*x+b*y+c;};//内联函数,用于进行矩阵运算
	void pagetoSVG(char* path);//生成SVG的函数
	fz_rect getrect();
	void setrect(fz_rect rect);
	void maketransform(); //遍历页内部内容,进行转置矩阵运算
	void clipwithrect(cliprect *myrect);//使用给定大小的矩形对模型进行裁剪
	void searchedge();
	struct simpleline screen(vector<simpleline>& xeqal,bool state);
};

