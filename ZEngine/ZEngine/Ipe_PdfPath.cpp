#include "Ipe_PdfPath.h"


Ipe_PdfPath::Ipe_PdfPath(void)
{
}

Ipe_PdfPath::Ipe_PdfPath(zblroute* route)//初始化Path，从zblroute结构体获取数据
{
	int i=0,state=0,first=0;//当前状态
	double currentx,currenty,originx,originy;
	drawingmethord=route->drawingmethord;//绘制方法 1-S 2-f* 3-f/F 4-s 5-B 6-B* 7-b 8-b*
	//printf("drawingmethord::%d\n",drawingmethord);
	GraphicsCellCount=0;
	pathtype=route->type;
	linewidth=route->linewidth;
	if(this->drawingmethord<5)//仅做填充或涂抹
	{
		colorspace=route->colorspace;
		this->scolor=NULL;
		this->scolorspace=0;
		//printf("this->existcm=%d\n\n",route->existcm);
		if(colorspace==1||colorspace==2)//灰度空间
		{
			color.setColor(-1,-1,-1,-1,route->color[0]);
		}
		else if(colorspace==3||colorspace==4)//RGB颜色空间
		{
			color.setColor(route->color[0],route->color[1],route->color[2],-1,-1);
			//printf("颜色:%d %d %d\n",color.getr(),color.getg(),color.getb());
		}
		else if(colorspace==5||colorspace==6)//处理cmyk颜色空间
		{
			colorspace=3;
			color.setCmykColor(255*(100-route->color[0]*100)*(100-route->color[3]*100)/10000,255*(100-route->color[1]*100)*(100-route->color[3]*100)/10000,255*(100-route->color[2]*100)*(100-route->color[3]*100)/10000,-1,-1);
			//printf("CMYK:%f %f %f %f转换成为RGB:%d %d %d",route->color[0],route->color[1],route->color[2],route->color[3],color.getr(),color.getg(),color.getb());
		}
	}
	else//既填充又涂抹,存在两个颜色,填充与涂抹
	{
		//printf("两种颜色\n");
		colorspace=route->colorspace;//填充
		scolorspace=route->scolorspace;//描边
		this->scolor=new Ipe_Color();
		if(colorspace==1||colorspace==2)//灰度空间
		{
			color.setColor(-1,-1,-1,-1,route->color[0]);
		}
		else if(colorspace==3||colorspace==4)//RGB颜色空间
		{
			color.setColor(route->color[0],route->color[1],route->color[2],-1,-1);
			//printf("填充颜色:%d %d %d\n",color.getr(),color.getg(),color.getb());
		}
		else if(colorspace==5||colorspace==6)//处理cmyk颜色空间
		{
			colorspace=3;
			color.setCmykColor(255*(100-route->color[0]*100)*(100-route->color[3]*100)/10000,255*(100-route->color[1]*100)*(100-route->color[3]*100)/10000,255*(100-route->color[2]*100)*(100-route->color[3]*100)/10000,-1,-1);
			//printf("CMYK:%f %f %f %f转换成为RGB:%d %d %d",route->color[0],route->color[1],route->color[2],route->color[3],color.getr(),color.getg(),color.getb());
		}
		//printf("scolorspace=%d\n",scolorspace);
		if(scolorspace==1||scolorspace==2)//灰度空间
		{
			scolor->setColor(-1,-1,-1,-1,route->color[0]);
		}
		else if(scolorspace==3||scolorspace==4)//RGB颜色空间
		{
			scolor->setColor(route->scolor[0],route->scolor[1],route->scolor[2],-1,-1);
			//printf("描边颜色:%d %d %d\n",color.getr(),color.getg(),color.getb());
		}
		else if(scolorspace==5||scolorspace==6)//处理cmyk颜色空间
		{
			scolorspace=3;
			scolor->setCmykColor(255*(100-route->scolor[0]*100)*(100-route->scolor[3]*100)/10000,255*(100-route->scolor[1]*100)*(100-route->scolor[3]*100)/10000,255*(100-route->scolor[2]*100)*(100-route->scolor[3]*100)/10000,-1,-1);
			//printf("CMYK:%f %f %f %f转换成为RGB:%d %d %d",route->color[0],route->color[1],route->color[2],route->color[3],color.getr(),color.getg(),color.getb());
		}
	}
	/*
	将zblroute结构体中的值转化为地图要素对象并存储在list中
	*/
	this->list=new Ipe_LinkList<Ipe_Plane>();
	Ipe_Lines* lines=new Ipe_Lines();//直线集对象
	Ipe_Bazeir* bazeir=new Ipe_Bazeir();//贝塞尔曲线对象
	route->currentpoint=route->pointheadler;
	//Ipe_Point2D* origin=new Ipe_Point2D(0,0);//建立起点
	Ipe_Plane* plane=new Ipe_Plane();//新建面的实例
	while(route->currentpoint->nextpoint!=NULL)//从起点开始，初始state=0，表示不确定接下来是直线集合还是贝塞尔曲线集合
	{
		route->currentpoint=route->currentpoint->nextpoint;

		if(state==0)//初始状态为0
		{
			if(route->currentpoint->state==0)
			{
				originx=route->currentpoint->p0;
				originy=route->currentpoint->p1;
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==1)//m,l,h,c状态(分别对应0，1，2，3）
			{
				
				state=1;
				lines->addpoint(originx,originy,0);//添加起点
				//printf("\n测试路径起点:%d,%d\n",originx,originy);
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1,1);//添加当前点

				//printf("确定第一个直线集的状态\n");
				//printf("添加路径起点与第一个点\n");
				//printf("起点:%f %f\n第一个点:%f %f ",originx,originy,route->currentpoint->p0,route->currentpoint->p1);

				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==3)//遇到贝塞尔曲线
			{
				//printf("确定第一个曲线集的状态\n");
				state=2;
				bazeir->addpoint(originx,originy,-1,-1,-1,-1,0);
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5,3);
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
		}

		if(state==1)//处理直线集
		{
			if(route->currentpoint->state==1)//命令为lint to
			{
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1,1);//将该直线点添加进去

				//printf("插入直线路径点%f %f\n",route->currentpoint->p0,route->currentpoint->p1);

				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==3)//命令为c 此时,将完结的直线添加进list中,然后释放并重新分配lines集合,为下次做好准备
			{
				plane->getlist()->add(lines);
				plane->addgraphiccellcount();
				GraphicsCellCount++;
				//delete lines;
				lines=new Ipe_Lines();//新分配直线集对象,为下次做准备
				bazeir->addpoint(currentx,currenty,-1,-1,-1,-1,0);//添加曲线集的起点
				originx=currentx;
				originy=currenty;
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5,3);
				//添加当前点
				state=2;//改变状态为曲线处理
				continue;
			}
			else if(route->currentpoint->state==2)//命令为h
			{
				lines->addpoint(originx,originy,2);//添加起点(路径闭合)
#ifdef debug
				printf("直线遇到h命令,添加终点%f  %f \n",originx,originy);
#endif
				plane->getlist()->add(lines);//将一个完整直线路径集合加入其中
				plane->addgraphiccellcount();
				plane->setplane();
				lines=new Ipe_Lines();
				if(route->currentpoint->nextpoint->state!=0)//如果h点的下一个点不是起点
				{
					list->add(plane);
					plane=new Ipe_Plane();
					GraphicsCellCount++;
				}
				state=3;
				continue;
			}
		}

		if(state==2)//处理曲线集
		{
			if(route->currentpoint->state==1)//命令为lint to
			{
				plane->getlist()->add(bazeir);
				plane->addgraphiccellcount();
				GraphicsCellCount++;
				//delete bazeir;
				bazeir=new Ipe_Bazeir();
				lines->addpoint(currentx,currenty,0);
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1,1);
				originx=currentx;
				originy=currenty;
				state=1;
				continue;
			}
			else if(route->currentpoint->state==3)//命令为c
			{
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5,3);
				currentx=route->currentpoint->p4;
				currenty=route->currentpoint->p5;
			}
			else if(route->currentpoint->state==2)//命令为h
			{
				bazeir->addpoint(originx,originy,-1,-1,-1,-1,2);
#ifdef debug
				printf("曲线h指令,添加起点%f %f \n",originx,originy);
#endif
				plane->getlist()->add(bazeir);
				plane->addgraphiccellcount();
				bazeir=new Ipe_Bazeir();
				if(route->currentpoint->nextpoint->state!=0)
				{
					list->add(plane);
					plane=new Ipe_Plane();
					GraphicsCellCount++;
				}
				state=3;
				continue;
			}
		}

		if(state==3)//重新开始路径
		{
			originx=route->currentpoint->p0;
			originy=route->currentpoint->p1;
			state=0;
			continue;
		}
		
	}
	if(state==1)
	{
		plane->getlist()->add(lines);
		plane->addgraphiccellcount();
		list->add(plane);
		GraphicsCellCount++;
	}
	if(state==2)
	{
		plane->getlist()->add(bazeir);
		plane->addgraphiccellcount();
		list->add(plane);
		GraphicsCellCount++;
	}

	
}
/*
		route->currentpoint=route->currentpoint->nextpoint;
		if(state==0)//第一次确定状态是line to
		{
			if(route->currentpoint->state==1)
			{
				printf("确定第一个直线集的状态\n");
				state=1;
				lines->addpoint(originx,originy);//添加起点
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1);//添加当前点
				printf("添加路径起点与第一个点\n");
				printf("起点:%f %f\n第一个点:%f %f ",originx,originy,route->currentpoint->p0,route->currentpoint->p1);
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==3)
			{
				printf("确定第一个曲线集的状态\n");
				state=2;
				bazeir->addpoint(originx,originy,-1,-1,-1,-1);
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5);
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==0)
			{
				Ipe_Point2D* origin=new Ipe_Point2D(route->currentpoint->p0,route->currentpoint->p1);//存储起点
				currentx
			}
			
		}
		if (state==1)//当前处理的是直线路径集
		{
			if(route->currentpoint->state==1)//命令为lint to
			{
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1);//将该直线点添加进去
				printf("插入直线路径点%f %f\n",route->currentpoint->p0,route->currentpoint->p1);
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
			}
			else if(route->currentpoint->state==3)//命令为c 此时,将完结的直线添加进list中,然后释放并重新分配lines集合,为下次做好准备
			{
				list->add(lines);
				GraphicsCellCount++;
				//delete lines;
				lines=new Ipe_Lines();//新分配直线集对象,为下次做准备
				bazeir->addpoint(currentx,currenty,-1,-1,-1,-1);//添加曲线集的起点
				originx=currentx;
				originy=currenty;
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5);
				//添加当前点
				state=2;//改变状态为曲线处理
				continue;
			}
			else//命令为h
			{
				lines->addpoint(originx,originy);//添加起点(路径闭合)
				list->add(lines);//将一个完整直线路径集合加入其中
				GraphicsCellCount++;
				state=3;
				continue;
			}
		}
		if (state==2)//当前处理的是曲线路径集
		{
			if(route->currentpoint->state==1)//命令为lint to
			{
				list->add(bazeir);
				GraphicsCellCount++;
				//delete bazeir;
				bazeir=new Ipe_Bazeir();
				lines->addpoint(currentx,currenty);
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1);
				originx=currentx;
				originy=currenty;
				state=1;
			}
			else if(route->currentpoint->state==3)//命令为 c
			{
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5);
				currentx=route->currentpoint->p4;
				currenty=route->currentpoint->p5;
			}
			else//命令为h
			{
				bazeir->addpoint(originx,originy,-1,-1,-1,-1);
				list->add(bazeir);
				GraphicsCellCount++;
				state=3;
				continue;
			}
		}
		if(state==3)//之前命令为h
		{
			
		}
	}
	*/
Ipe_PdfPath::~Ipe_PdfPath(void)
{
	delete list;
	printf("Ipe_PdfPath链表释放\n");
}

void Ipe_PdfPath::printfPath()
{
	printf("调用了path的输出函数\n");
	printf("本路径的颜色空间为:%d",this->getcolorspace());
	Ipe_node<Ipe_Plane>* p=list->headler;
	//p->t->printPoint();
	printf("进入循环\n");
	while(p->next!=NULL)
	{
		p->next->t->printPoint();//向下转型
		p=p->next;
	}
	/*
	if(this->existclip!=0)
	{
		printf("存在裁剪路径:%d\n",this->existclip);
		Ipe_node<Ipe_GraphicCell>* q=cliplist->headler;
		while(q->next!=NULL)
		{
			printf("输出剪辑路径的点\n");
			q->next->t->printPoint();
			q=q->next;
		}
	}
	*/
	
}


int Ipe_PdfPath::getGraphicCellCount()
{
	return GraphicsCellCount;
}
Ipe_LinkList<class Ipe_Plane>* Ipe_PdfPath::getPlane()
{
	return list;
}

int Ipe_PdfPath::getcolorspace()//获取颜色空间
{
	return this->colorspace;//记录是哪一种颜色空间(可扩展) 1-G 2-g 3-RG 4-rg
}

Ipe_Color Ipe_PdfPath::getcolor()//取得颜色
{
	return this->color;
}

int Ipe_PdfPath::getdrawingmethord()//取得绘制方法
{
	return this->drawingmethord;
}


float Ipe_PdfPath::getlinewidth()
{
	return this->linewidth;
}

int Ipe_PdfPath::getpathtype()
{
	return pathtype;
}

Ipe_Color Ipe_PdfPath::getscolor()
{
	return *this->scolor;
}
int Ipe_PdfPath::getscolorspace()
{
	return this->scolorspace;
}