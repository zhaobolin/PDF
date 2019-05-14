#include "Ipe_PdfPage.h"
#include "Ipe_PdfStack.h"
#include <fstream>
#include <string>
#include <sstream>
#include"calculate.h"
#include "recursion.h"

cliprect crect;

Ipe_PdfPage::Ipe_PdfPage(void)
{
}

Ipe_PdfPage::Ipe_PdfPage(zblrouteset* routeset)//初始化，存放每页的内容
{
	int i=0;
	this->graphiccellcount=routeset->count;
	this->list=new Ipe_LinkList<Ipe_PdfElement>();
	routeset->currentstack=routeset->stackheadler;
	while(routeset->currentstack->nextstack!=NULL)
	{
		routeset->currentstack=routeset->currentstack->nextstack;//遍历最外层栈
		recursion(this->list,routeset->currentstack,NULL,NULL,0);//进行嵌套调用
	}
	//遍历页面的所有点,进行转置矩阵的运算
	this->maketransform();
}

void Ipe_PdfPage::maketransform()//遍历所有具有转置矩阵的点,进行转置运算
{
	Ipe_node<Ipe_PdfElement>* current;
	current=this->list->headler;
	crect.x0=0;
	crect.x1=0;
	crect.y0=0;
	crect.y1=0;
	while(current->next!=NULL)//遍历栈
	{
		current=current->next;
		if(current->t->getelementtype()==1)//类型为1,为图形参数
		{
			Ipe_PdfStack* stack;
			stack=dynamic_cast<Ipe_PdfStack*>(current->t);//动态类型转换
			Ipe_node<Ipe_PdfPath>* pathlist=stack->getpathlist()->headler;//获取Path
			int existcm=stack->getexistcm();
			if(existcm==1)//存在转置矩阵
			{
				float cm[6];
				stack->setexistcm(0);
				while(pathlist->next!=NULL)//遍历栈中路径
				{
					pathlist=pathlist->next;
					Ipe_node <Ipe_Plane>* cplane=pathlist->t->getPlane()->headler;//取得地图要素链表头
					while(cplane->next!=NULL)//遍历地图要素链表,可能是线,面
					{
						cplane=cplane->next;
						Ipe_Plane *plane=cplane->t;
						if(plane->getisplane())//判断地图要素类型,是封闭路径
						{
							//遍历封闭路径的一个或多个直线/曲线集
							bool firsttime=true;
							double beginx,beginy;
							Ipe_node<class Ipe_GraphicCell>*graphiccell=plane->getlist()->headler;
							for (int j=0;j<plane->getgraphicellcount();j++)
							{
								graphiccell=graphiccell->next;
								if (graphiccell->t->gettype()==1)//0-父类 1-直线集 2-曲线集
								{
									Ipe_Lines * lines=dynamic_cast<Ipe_Lines*>(graphiccell->t);//向下转型为lines直线集
									//直线集的遍历
									Ipe_node<Ipe_Point2D>* points=lines->getlist()->headler;
									while (points->next!=NULL)
									{
										points=points->next;
										points->t->setx(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4]));
										points->t->sety(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5]));
									}
								}
								else if(graphiccell->t->gettype()==2)
								{
									Ipe_Bazeir* bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell->t);//向下转型为贝塞尔曲线集
									//曲线集的遍历
									Ipe_node<Ipe_Point2D>* points=bazeir->getlist()->headler;
									while (points->next!=NULL)
									{
										points=points->next;
										points->t->setx(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4]));
										points->t->sety(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5]));
									}
								}
								else
								{
									printf("父类,初始化错误\n");
								}
							}
						}
						else//不封闭路径
						{
							Ipe_node<class Ipe_GraphicCell>* cgc=plane->getlist()->headler;
							while(cgc->next!=NULL)//遍历路径中的直线集与曲线集
							{
								cgc=cgc->next;
								Ipe_GraphicCell* graphiccell=cgc->t;
								if(graphiccell->gettype()==1)//1-直线集 
								{
									Ipe_Lines * lines=dynamic_cast<Ipe_Lines*>(graphiccell);//向下转型为lines直线集
									//直线集的遍历
									Ipe_node<Ipe_Point2D>* points=lines->getlist()->headler;
									while (points->next!=NULL)
									{
										points=points->next;
										points->t->setx(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4]));
										points->t->sety(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5]));
									}
								}
								else if(graphiccell->gettype()==2)//2-曲线集
								{
									Ipe_Bazeir* bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell);//向下转型为贝塞尔曲线集
									//曲线集的遍历
									Ipe_node<Ipe_Point2D>* points=bazeir->getlist()->headler;
									points=points->next;
									points->t->setx(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4]));
									points->t->sety(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5]));
									points=points->next;
									points=points->next;
									while (points->next!=NULL)
									{
										points=points->next;
										points->t->setx(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4]));
										points->t->sety(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5]));
									}
								}
								else//0-父类
								{
									printf("未初始化的GraphicCell对象\n");
								}
							}
						}
					}
				}
			}
		}
	}
}

Ipe_PdfPage::~Ipe_PdfPage(void)
{
	delete list;
	printf("Ipe_PdfPage释放链表\n");
}

Ipe_LinkList<Ipe_PdfElement>* Ipe_PdfPage::getelement()
{
	return this->list;
}

void Ipe_PdfPage::printpage()
{
	int count=0;
	printf("调用了page的输出函数\n");
	Ipe_node<Ipe_PdfElement>* p=list->headler;
	printf("进入循环\n");
	while(p->next!=NULL)
	{
		//p->next->t->printfPath();//向下转型
		printf("本页第%d个图形状态栈:+++++++++++++++++++++\n",count);
		Ipe_PdfStack* stack=dynamic_cast<Ipe_PdfStack*>(p->next->t);
		printf("层号:%d\n",stack->getgrade());
		p=p->next;
		count++;
	}
}

void Ipe_PdfPage::setrect(fz_rect rect)
{
	this->rect=rect;
}

fz_rect Ipe_PdfPage::getrect()
{
	return rect;
}

void Ipe_PdfPage::pagetoSVG(char* path)//输出一页为svg
{
	int i=0,j=0,k=0,l=0,m=0,n=0,o=0,p=0,shadowid=0;
	Ipe_node<Ipe_PdfElement>* pointer=this->list->headler;//PDF元素的头指针
	Ipe_PdfElement* element;
	Ipe_PdfStack* stack;
	Ipe_PdfPath* pdfpath;
	Ipe_node<class Ipe_PdfPath>* currentpdfpath;
	Ipe_node<class Ipe_GraphicCell>* graphiccell;
	Ipe_node<class Ipe_GraphicCell>* clipgraphiccell;
	Ipe_node<class Ipe_Plane>* plane;
	Ipe_Lines* lines;
	Ipe_Bazeir* bazeir;
	ofstream fout;//fout1;
	fout.open(path);
	//fout1.open("C:\\Users\\赵博霖\\Desktop\\对比数据.txt");
	//写文件头
	fout<<"<?xml version=\"1.0\" standalone=\"no\"?>\n\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n <svg width=\"100%\" height=\"100%\" version=\"1.1\" viewBox=\" "<<this->rect.x0<<" "<<this->rect.y0<<" "<<this->rect.x1<<" "<<this->rect.y1<<"\"";
	fout<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;
	//for (i=0;i<this->graphiccellcount;i++)//对每个PDF栈
	while(pointer->next!=NULL)
	{
		pointer=pointer->next;//pointer现在指向stack链表的头部
		stack=dynamic_cast<Ipe_PdfStack*>(pointer->t);//动态强制类型转换
		if(pointer->t->getelementtype()==1)//pdf页面元素的种类为path PS:待判断图片与文字
		{
			//printf("第一次裁剪路径状态:%d\n",stack->getexistclip());
			if(stack->getexistclip()>0)//存在裁剪路径
			{
				//添加裁剪路径
				string clippath="<defs>";
				o++;
				clippath=clippath+"<clipPath id=\"c-star"+toString(o)+"\">"+"\n";
				clippath=clippath+"<path d=\"";
				clipgraphiccell=stack->getcliplist()->headler;
				while(clipgraphiccell->next!=NULL)//遍历直线与曲线集合
				{
					clipgraphiccell=clipgraphiccell->next;
					if(clipgraphiccell->t->gettype()==1)//直线集
					{
						lines=dynamic_cast <Ipe_Lines*>(clipgraphiccell->t);//转型成为直线集合
						Ipe_node<Ipe_Point2D>* points=lines->getlist()->headler;
						//clippath=clippath+"<clipPath id=\"c-star0"+"\">"+"\n";
						//clippath=clippath+"<polygon points=\"";
						for(n=0;n<lines->getnum();n++)//遍历点
						{
							points=points->next;
							if(points->t->getstate()==0)//m,l,h,c状态(分别对应0，1，2，3）
							{
								clippath=clippath+"M"+toString(points->t->getx())+" "+toString((this->getrect().y1-this->getrect().y0)-points->t->gety())+" ";//这里要进行处理，SVG文件是以页面左上角作为坐标原点的，所以要将y轴反置
							}
							else if(points->t->getstate()==1)
							{
								clippath=clippath+"L"+toString(points->t->getx())+" "+toString((this->getrect().y1-this->getrect().y0)-points->t->gety())+" ";
							}
							else if(points->t->getstate()==2)
							{
								clippath=clippath+"L"+toString(points->t->getx())+" "+toString((this->getrect().y1-this->getrect().y0)-points->t->gety())+" Z ";
							}
							
						}
						//clippath=clippath+"\"/>"+"\n";
						//clippath=clippath+"</clipPath>";
					}
					else //曲线集
					{
						bazeir=dynamic_cast<Ipe_Bazeir*>(clipgraphiccell->t);//转型成为曲线集合
						Ipe_node<Ipe_Point2D>* points=bazeir->getlist()->headler;
						//clippath=clippath+"<clipPath id=\"c-star"+toString(m)+"\">"+"\n";
						points=points->next;
						clippath=clippath+"M"+toString(points->t->getx())+" "+toString((this->getrect().y1-this->getrect().y0)-points->t->gety())+" ";//贝赛尔曲线起点
						//fout<<"M"<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";
						points=points->next;
						points=points->next;
						points=points->next;
						for(k=0;k<bazeir->getnum()-1;k++)
						{
							clippath=clippath+"C"+toString(points->t->getx())+" "+toString((this->getrect().y1-this->getrect().y0)-points->t->gety())+" ";
							//fout<<"C"<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";
							points=points->next;
							clippath=clippath+"C"+toString(points->t->getx())+" "+toString((this->getrect().y1-this->getrect().y0)-points->t->gety())+" ";
							points=points->next;
							clippath=clippath+"C"+toString(points->t->getx())+" "+toString((this->getrect().y1-this->getrect().y0)-points->t->gety())+"\n";
							points=points->next;
						}
						clippath=clippath+"\"/>"+"\n";
						
					}
						
				}
				clippath=clippath+"\"/>"+"\n";
				clippath=clippath+"</clipPath>";
				clippath=clippath+"</defs>";
				fout<<clippath<<endl;
			}
			/*
			if(stack->getshadowtype()!=0)//存在阴影,渐变色 设置该栈的SVG渐变色属性
			{
				if(stack->getshadowtype()==1)
				{

					shadowid++;
					fout<<"<defs>\n<linearGradient id=\""<<shadowid<<"\" x1=\""<<x1<<"%\" x2=\""<<x2<<"%\" y1=\""<<y1<<"%\" y2=\""<<y2<<"%\">"<<endl;
					fout<<"<stop offset=\"0%\" style=\"stop-color:rgb("<<stack->getbcolor()[0]<<","<<stack->getbcolor()[1]<<","<<stack->getbcolor()[2]<<");"<<endl;
					fout<<"stop-opacity:1\"/>"<<endl;
					fout<<"<stop offset=\"100%\" style=\"stop-color:rgb("<<stack->getecolor()[0]<<","<<stack->getecolor()[1]<<","<<stack->getecolor()[2]<<");"<<endl;
					fout<<"stop-opacity:1\"/>"<<endl;
					fout<<"</linearGradient>"<<endl<<"</defs>"<<endl;
					//完成线性渐变的定义
					//进行当前渐变区域的描述

				}
			}
			*/
			if(stack->getexistclip()!=0)//指明裁剪路径序号
			{
				fout<<"<g style=\"clip-path: url(#c-star"<<toString(o)<<+");\">\n";
				//printf("+++++++++++++++++++++++++++++++++++++++++++++当前路径在裁剪路径中\n");
			}
			currentpdfpath=stack->getpathlist()->headler;//获取栈中path集合的头结点
#ifdef debug
			printf("栈中有%d条路径\n",stack->getcountpath());
#endif
			//printf("栈中路径数量:%d\n",stack->getcountpath());
			for(l=0;l<stack->getcountpath();l++)//遍历栈中路径
			{
				currentpdfpath=currentpdfpath->next;
				pdfpath=currentpdfpath->t;//安全的向下转型
				//提取每条path的颜色,线宽等信息,导出为下面每个线集的SVG属性,每个path里面的每条SVG元素都是一样的属性结尾
				string attribute="\" style=\"";
				//处理颜色
				Ipe_Color color=pdfpath->getcolor();
				if(pdfpath->getdrawingmethord()<5)//仅仅填充或者描边的情况
				{
					if(pdfpath->getdrawingmethord()==1||pdfpath->getdrawingmethord()==-1||pdfpath->getdrawingmethord()==4)//仅仅涂抹路径  绘制方法 1-S 2-f* 3-f/F 4-s 5-B 6-B* 7-b 8-b*
					{
						attribute=attribute+"fill:none;stroke:";
						if(pdfpath->getcolorspace()==3||pdfpath->getcolorspace()==4)//若为RGB空间
						{
							attribute=attribute+"rgb(";
							attribute=attribute+toString(color.getr())+","+toString(color.getg())+","+toString(color.getb())+"); stroke-width:";
							attribute=attribute+toString(pdfpath->getlinewidth());//线宽
						}
						else//灰度空间
						{
							if(color.getG()==0)//0是黑色 1是白色
							{
								attribute=attribute+"black;";
							}
							else
							{
								attribute=attribute+"white;";
							}
							attribute=attribute+" stroke-width:";
						}
					}
					else//填充
					{
						attribute=attribute+"fill:";
						if(pdfpath->getcolorspace()==3||pdfpath->getcolorspace()==4)//若填充为RGB空间
						{
							attribute=attribute+"rgb(";
							attribute=attribute+toString(color.getr())+","+toString(color.getg())+","+toString(color.getb())+"); ";
						}
						else//若填充为黑白
						{
							if(color.getG()==0)//0是黑色 1是白色
							{
								attribute=attribute+"black;";
							}
							else
							{
								attribute=attribute+"white;";
							}
						}
					}
					/*
					if(pdfpath->getcolorspace()==3||pdfpath->getcolorspace()==4)//若为RGB空间
					{
						attribute=attribute+"rgb(";
						attribute=attribute+toString(color.getr())+","+toString(color.getg())+","+toString(color.getb())+"); stroke-width:";
					}
					else//灰度空间
					{
						if(color.getG()==0)//0是黑色 1是白色
						{
							attribute=attribute+"black;";
						}
						else
						{
							attribute=attribute+"white;";
						}
						attribute=attribute+" stroke-width:";
					}
					*/
					
				}
				else//两种涂色方式都有
				{
					Ipe_Color scolor=pdfpath->getscolor();//获取stroke的颜色
					attribute=attribute+"fill:";
					if(pdfpath->getcolorspace()==3||pdfpath->getcolorspace()==4)//若填充为RGB空间
					{
						attribute=attribute+"rgb(";
						attribute=attribute+toString(color.getr())+","+toString(color.getg())+","+toString(color.getb());
					}
					else//若填充为黑白
					{
						if(color.getG()==0)//0是黑色 1是白色
						{
							attribute=attribute+"black;";
						}
						else
						{
							attribute=attribute+"white;";
						}
					}
					attribute+="); stroke:";
					if(pdfpath->getscolorspace()==3||pdfpath->getscolorspace()==4)//若填充为RGB空间
					{
						attribute=attribute+"rgb(";
						attribute=attribute+toString(scolor.getr())+","+toString(scolor.getg())+","+toString(scolor.getb())+");";
					}
					else//若填充为黑白
					{
						if(scolor.getG()==0)//0是黑色 1是白色
						{
							attribute=attribute+"black;";
						}
						else
						{
							attribute=attribute+"white;";
						}
					}
					attribute=attribute+" stroke-width:";
					attribute=attribute+toString(pdfpath->getlinewidth());//线宽
				}
				
				if(stack->getca()!=1)//如果透明度不为1,设置透明度属性
				{
					attribute=attribute+";opacity:"+toString(stack->getca());
				}
				
				attribute=attribute+"\"";
				//判断是否存在转置矩阵
				/*
				if(stack->getexistcm()>0)
				{
					attribute=attribute+" transform=\"matrix("+toString(stack->getmatrix()[0])+" "+toString(stack->getmatrix()[1])+" "+toString(stack->getmatrix()[2])+" "+toString(stack->getmatrix()[3])+" " +toString(stack->getmatrix()[4])+" "+toString((this->getrect().y1-this->getrect().y0)-stack->getmatrix()[5])+")\"";//(this->getrect().y1-this->getrect().y0)-  //此处有待商榷,变换原点之后坐标变换
				}
				
				if(stack->getexistclip()==2)//奇偶裁剪路径
				{
					attribute=attribute+" fill-rule=\"evenodd\" clip-rule=\"evenodd\"";
				}
				*/
				attribute=attribute+"/>\n";
				//cout<<"属性词缀:"<<attribute<<endl;
				//graphiccell=pdfpath->getGraphicCell()->headler;
				
				
				//接下来遍历path的面列表判断是否是路径
				plane=pdfpath->getPlane()->headler;
				while(plane->next!=NULL)//对面中的每个元素进行遍历
				{
					plane=plane->next;
					//printf("处理面中元素");
					if(plane->t->getisplane()==false)//并非为闭合的面,仅仅为一系列路径点
					{
						graphiccell=plane->t->getlist()->headler;
						//printf("plane内部Graphiccell的数量:%d\n",plane->t->getgraphicellcount());
						for (j=0;j<plane->t->getgraphicellcount();j++)
						{
							graphiccell=graphiccell->next;
							if (graphiccell->t->gettype()==1)//0-父类 1-直线集 2-曲线集
							{
								lines=dynamic_cast <Ipe_Lines*>(graphiccell->t);//转型成为直线集合
								Ipe_node<Ipe_Point2D>* points=lines->getlist()->headler;
								fout<<"<path d=\"";//一条路径
								char order;
								for(k=0;k<lines->getnum();k++)
								{
		//#ifdef debug
									//printf("%f %f\n",this->getrect().y0,this->getrect().y1);
		//#endif
									points=points->next;
									switch (points->t->getstate())//m,l,h,c状态(分别对应0，1，2，3）
									{
										case 0:
											order='M';
											break;
										case 1:
											order='L';
											break;
									}
									//if(stack->getexistcm()==0)
									//{
										fout<<order<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";//这里要进行处理，SVG文件是以页面左上角作为坐标原点的，所以要将y轴反置
										//fout1<<points->t->getx()<<","<<points->t->gety()<<"------"<<points->t->getx()<<","<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" \n";
									//}
									/*
									else //存在转置矩阵
									{
										fout<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<","<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" ";
										//fout1<<points->t->getx()<<","<<points->t->gety()<<"------"<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<","<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" \n";
									}
									*/
								}
								fout<<attribute;
								fout<<endl;
							}
							else//否则曲线集 不存在父类情况
							{
								bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell->t);//转型成为曲线集合
								Ipe_node<Ipe_Point2D>* points=bazeir->getlist()->headler;
								fout<<"<path d=\"";
								//printf("贝塞尔曲线点数:%d\n",bazeir->getnum());
								//printf("%s\n",attribute);
								if(bazeir->getnum()!=0)
								{
									points=points->next;
									fout<<"M"<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";//贝赛尔曲线起点
									points=points->next;
									points=points->next;
									points=points->next;
								}
								for(k=0;k<bazeir->getnum()-1;k++)
								{
									//if(stack->getexistcm()==0)
									//{
										fout<<"C"<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";
										points=points->next;
										fout<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";
										points=points->next;
										fout<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<"\n";
										points=points->next;
									//}
									/*
									else
									{
										fout<<"C"<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<" "<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" ";
										points=points->next;
										fout<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<" "<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" ";
										points=points->next;
										fout<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<" "<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<"\n";
										points=points->next;
									}
									*/
								}
								fout<<attribute;
								fout<<endl;
							}
						}
					}
					else//是一个闭合的面,此时生成SVG的时候要将这一个面的所有点放在一条路径中以形成一个封闭的面
					{
						//printf("是一个闭合的面\n");
						fout<<"<path d=\"";
						graphiccell=plane->t->getlist()->headler;
						bool firsttime=true;
						double beginx,beginy;
						//for (j=0;j<plane->t->getgraphicellcount();j++)
						while(graphiccell->next!=NULL)
						{
							graphiccell=graphiccell->next;
							if (graphiccell->t->gettype()==1)//0-父类 1-直线集 2-曲线集
							{
								//printf("直线集\n");
								lines=dynamic_cast <Ipe_Lines*>(graphiccell->t);//转型成为直线集合
								Ipe_node<Ipe_Point2D>* points=lines->getlist()->headler;
								//printf("直线集中点的个数:%d\n",lines->getnum());
								for(k=0;k<lines->getnum();k++)
								{
									string order;
									points=points->next;
									//printf("%f %f %d\n",points->t->getx(),points->t->gety(),points->t->getstate());
									if(points->t->getstate()==0)
									{
										//printf("%d",firsttime);
										/*if(firsttime==true)
										{
											order="M";
											firsttime=false;
											beginx=points->t->getx();
											beginy=points->t->gety();
											//printf("起点进行标注\n");
										}
										else
										{
											
										}
										*/
										order="M";
										beginx=points->t->getx();
										beginy=points->t->gety();
									}
									else // if(points->t->getstate()==1)//m,l,h,c状态(分别对应0，1，2，3）
									{
										order="L";
									}
									//printf("栈转置矩阵状态:%d\n",stack->getexistcm());
									if(stack->getexistcm()==0)
									{
										//printf("不存在转置矩阵\n");
										if(points->t->getstate()==2)
										fout<<order<<beginx<<" "<<(this->getrect().y1-this->getrect().y0)-beginy<<" ";
										else
										{
											fout<<order<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";//这里要进行处理，SVG文件是以页面左上角作为坐标原点的，所以要将y轴反置
											//cout<<order<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<endl;
										//fout1<<points->t->getx()<<","<<points->t->gety()<<"------"<<points->t->getx()<<","<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" \n";
									
										}
									}
									/*
									else //存在转置矩阵
									{
										if(points->t->getstate()==2)//闭合指令,回到起点
										fout<<order<<transform(beginx,beginy,stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<" "<<(this->getrect().y1-this->getrect().y0)-transform(beginx,beginy,stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" ";
										else
										fout<<order<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<" "<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" ";
										//fout1<<points->t->getx()<<","<<points->t->gety()<<"------"<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<","<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" \n";
									}
									*/
								}
								//fout<<attribute;
								//fout<<endl;
							}
							else//否则曲线集 不存在父类情况
							{
								bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell->t);//转型成为曲线集合
								Ipe_node<Ipe_Point2D>* points=bazeir->getlist()->headler;
								points=points->next;
								if(stack->getexistcm()==0)
								{
									if(firsttime==true)
									{
										firsttime=false;
										fout<<"M"<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";//贝赛尔曲线起点
										beginx=points->t->getx();
										beginy=points->t->gety();
									}
								}
								else
								{
									if(firsttime==true)
									{
										firsttime=false;
										fout<<"M"<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<" "<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" ";
										beginx=points->t->getx();
										beginy=points->t->gety();
									}
								}
								points=points->next;
								points=points->next;
								points=points->next;
								for(k=0;k<bazeir->getnum()-1;k++)
								{
									if(stack->getexistcm()==0)
									{
										fout<<"C"<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";
										points=points->next;
										fout<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";
										points=points->next;
										fout<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<"\n";
										points=points->next;
									}
									else
									{
										fout<<"C"<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<" "<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" ";
										points=points->next;
										fout<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<" "<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" ";
										points=points->next;
										fout<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<" "<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<"\n";
										points=points->next;
									}
								}
								//fout<<attribute;
								//fout<<endl;
							}
						}
						fout<<attribute;
						fout<<endl;
					}
				}
				
			}
			if(stack->getexistclip()>0)
			{
				fout<<"</g>";
			}
		}
		

	}
	if((crect.x0!=0)||(crect.x1!=0)||(crect.y0!=0)||(crect.y1!=0))
	{
		fout<<"<rect x=\""<<crect.x0<<"\" y=\""<<this->rect.y1-crect.y0<<"\" width=\""<<crect.x1-crect.x0<<"\" height=\""<<crect.y0-crect.y1<<"\" style=\"fill:none; stroke:rgb(0,0,255);\"/>"<<endl;
	
	}
	fout<<"</svg>";
	fout.close();
	//fout1.close();
}

void Ipe_PdfPage::clipwithrect(cliprect *rect)//裁减函数
{
	if(rect->x0>rect->x1||rect->y0<rect->y1)
	{
		printf("矩形参数不符合标准");
		return;
	}
	crect.x0=rect->x0;
	crect.x1=rect->x1;
	crect.y0=rect->y0;
	crect.y1=rect->y1;
	Ipe_node<Ipe_PdfElement>* current;
	current=this->list->headler;
	while(current->next!=NULL)//遍历栈
	{
		current=current->next;
		if(current->t->getelementtype()==1)//类型为1,为图形参数
		{
			Ipe_PdfStack* stack;
			stack=dynamic_cast<Ipe_PdfStack*>(current->t);//动态类型转换
			Ipe_node<Ipe_PdfPath>* pathlist=stack->getpathlist()->headler;//获取Path
			while(pathlist->next!=NULL)//遍历栈中路径
			{
				pathlist=pathlist->next;
				Ipe_node <Ipe_Plane>* cplane=pathlist->t->getPlane()->headler;//取得地图要素链表头
				while(cplane->next!=NULL)//遍历地图要素链表,可能是线,面
				{
					cplane=cplane->next;
					Ipe_Plane *plane=cplane->t;
					if(plane->getisplane())//判断地图要素类型,是封闭路径
					{
						//printf("调用面裁剪函数\n");
						Ipe_node<class Ipe_GraphicCell>* cgc=plane->getlist()->headler;
						//遍历封闭路径的一个或多个直线/曲线集,进行裁剪以及与部分边的添加操作
						Ipe_LinkList<Ipe_GraphicCell>* list=plane->getlist();
						plane->setlist(clipplane(list,rect));//持有新的直线与曲线集list
						//测试输出
						Ipe_node<class Ipe_GraphicCell> *p=plane->getlist()->headler->next;
						Ipe_Lines *k=dynamic_cast<Ipe_Lines*>(p->t);
						Ipe_node<Ipe_Point2D>*cp=k->getlist()->headler;
						/*printf("裁剪结果:\n");
						while(cp->next!=NULL)
						{
							cp=cp->next;
							printf("%f %f %d\n",cp->t->getx(),cp->t->gety(),cp->t->getstate());
						}	
						*/
					}
					else//不封闭路径
					{
						Ipe_node<class Ipe_GraphicCell>* cgc=plane->getlist()->headler;
						while(cgc->next!=NULL)//遍历路径中的直线集与曲线集
						{
							cgc=cgc->next;
							Ipe_GraphicCell* graphiccell=cgc->t;
							if(graphiccell->gettype()==1)//1-直线集 
							{
								Ipe_Lines * lines=dynamic_cast<Ipe_Lines*>(graphiccell);//向下转型为lines直线集
								//直线集的遍历裁剪函数
								Ipe_Lines* newlines=cliplines(lines,rect);//返回新的节点指针
								delete lines;
								cgc->t=newlines;
								//printf("直线集中点的数量:%d\n",newlines->getnum());
								//printf("%f %f\n",newlines->getlist()->headler->next->t->getx(),newlines->getlist()->headler->next->t->gety());
							}
							else if(graphiccell->gettype()==2)//2-曲线集
							{
								Ipe_Bazeir* bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell);//向下转型为贝塞尔曲线集
								//曲线集的遍历裁剪函数
								//printf("进入曲线裁剪函数\n");
								Ipe_Bazeir* newbazeir=clipbazeir(bazeir,rect);
								delete bazeir;
								cgc->t=newbazeir;
								//printf("new bazeir size:%d",newbazeir->getnum());
							}
							else//0-父类
							{
								printf("未初始化的GraphicCell对象\n");
							}
						}
					}
				}
			}
		}
	}
	/*
	1.对于点,是否存在只看是否在区域内

	2.对于线:两种情况:
		直线:
			从起点遍历,终止于与矩形的交点,若是进行裁剪,可以使用编码裁剪法,
			将直线进行编码,弃置外部,取内部,计算交点,进行直线的裁剪,对于不封闭的
			直线集合,使用边界点替换原本的端点,之后可以另开直线继续遍历(反正是链表)
		曲线:
			从起点开始进行遍历 (状态0)
			若四个控制点都在矩形内部,则不进行修改;
			若两个端点存在不在矩形内部的,则说明是跨越的线,保留这条线,并记住这个状态(状态1)
				状态1下,下一部分若是完全在外部,则删除此条线,继续下去遍历,并维持状态
				直到到达再次进入裁剪区域或结束,将状态置为零
			若存在控制点不在裁剪区域内但是端点在裁剪区域内的,代入公式进行测试(取一
			些点进行测试)之后是否在裁剪区域内的处理同上
	3.对于面:
		多边形/曲线部分不与裁剪框相交的面:从起点遍历,使用Sutherland_Hodgman算法,将多边形与边界结合,PS:存在问题:退化边界
		多边形如果全部为直线组成,可以这样裁剪
		PS:可能出现的情况:大部分多边形都是只有一小部分被裁减,然后使用边界替代(可能的优化点)
		
		如果多边形部分为曲线结构:则?
	*/
}

