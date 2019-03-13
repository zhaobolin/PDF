#pragma once
#include "MuInclude.h"
#define EX_PORT __declspec(dllexport) 
/*
	zblroute结构的对应类,这里面存放的是一条路径矢量的信息
*/
class EX_PORT Vector
{

	int type;//路径种类 直线-1 贝塞尔曲线-2 矩形-3 剪辑路径矩形-4

	float linewidth;//记录线宽(目前有个问题,如果线宽不改变,多个路径对象可能共同使用同一个线宽)

	int colorspace;//记录是哪一种颜色空间(可扩展) 1-G 2-g 3-RG 4-rg
	float color[4];//记录颜色

	int countpoint;//记录路径点个数
	float points[500][7];//line[x][0],line[x][1],line[x][6]分别存放直线路径点的x,y坐标,以及构造路径的m,l,h,c状态(分别对应0,1,2,3)
	
	int drawingmethord;//绘制方法 1-S 2-f*
public:
	Vector(void);
	Vector(struct zblroute & vector);
	~Vector(void);
	//set get接口
	int getcountpoint();
	int gettype();
	float getlinewidth();
	int getcolorspace();
	float(*getpoints())[7];
	float* getcolor();
	int getdrawingmethord();
	
};
/*
底层Mupdf提取的文档矢量数据结构体
struct zblroute
{
	int type;//路径种类 直线-1 贝塞尔曲线-2 矩形-3 剪辑路径矩形-4

	float linewidth;//记录线宽(目前有个问题,如果线宽不改变,多个路径对象可能共同使用同一个线宽)

	int colorspace;//记录是哪一种颜色空间(可扩展) 1-G 2-g 3-RG 4-rg
	float color[4];//记录颜色

	int countpoint;//记录路径点个数
	float points[500][7];//line[x][0],line[x][1],line[x][6]分别存放直线路径点的x,y坐标,以及构造路径的m,l,h,c状态(分别对应0,1,2,3)//改成结构体链表
	
	int drawingmethord;//绘制方法 1-S 2-f*
};

struct zblrouteset//提取路径集合结构体 zbl
{
	int count;
	struct zblroute set[1000];

};*/
