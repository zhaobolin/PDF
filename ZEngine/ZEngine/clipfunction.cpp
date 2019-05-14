#include "clipfunction.h"

class Ipe_Lines* cliplines(Ipe_Lines* lines,cliprect* rect)//直线集与窗口矩形参数
{
	Ipe_node<Ipe_Point2D>* currentpoint=lines->getlist()->headler;
	Ipe_Point2D *p0,*p1,*cp0,*cp1;
	int count=0;
	bool isfirstpoint=true;
	Ipe_Lines* newlines=new Ipe_Lines();

	while(currentpoint->next!=NULL)
	{
		currentpoint=currentpoint->next;
		if(isfirstpoint)
		{
			isfirstpoint=false;
			cp0=currentpoint->t;
			count++;
			p0=new Ipe_Point2D(currentpoint->t->getx(),currentpoint->t->gety(),currentpoint->t->getstate());
			continue;
		}
		cp1=currentpoint->t;
		count++;
		p1=new Ipe_Point2D(cp1->getx(),cp1->gety(),cp1->getstate());
		//此时p0,p1为直线上的两端点
		int code0,code1;
		bool done=false;
		code0=compcode(p0,rect);
		code1=compcode(p1,rect);//传入两点与窗口坐标,进行编码判断
		//printf("%d,%d\n",code0,code1);
		int endcount=0;
		do
		{
			if(!(code0|code1))//均为0x00
			{
				//全在窗口内
				//全部复制
				newlines->addpoint(p0->getx(),p0->gety(),p0->getstate());
				newlines->addpoint(p1->getx(),p1->gety(),p1->getstate());
				cp0=cp1;
				p0->setx(cp0->getx());
				p0->sety(cp0->gety());
				p0->setstate(cp0->getstate());
				delete p1;
				done=true;
			}
			else if((code0&code1))
			{
				//全不在窗口内
				//不添加
				cp0=cp1;
				p0->setx(cp0->getx());
				p0->sety(cp0->gety());
				p0->setstate(cp0->getstate());
				delete p1;
				done=true;
			}
			else
			{
				//不能确定的状态
				//求出线段与窗口边界的交点，在交点处把线段一分为二，其中必有一段完全在窗口外，可以弃之.
				//再对另一段重复进行上述处理，直到该线段完全被舍弃或者找到位于窗口内的一段线段为止
				float delx,dely;
				if(code0!=0)//p0在外面
				{
					delx=p1->getx()-p0->getx();
					dely=p1->gety()-p0->gety();
					chopline(p0,code0,rect,delx,dely);
					//printf("x0:%f  y0:%f\n",p0->getx(),p0->gety());
					code0=compcode(p0,rect);
					p0->setstate(0);
					//endcount++;
				}
				else//p1在外面
				{
					delx=p1->getx()-p0->getx();
					dely=p1->gety()-p0->gety();
					chopline(p1,code1,rect,delx,dely);
					//printf("x1:%f  y1:%f\n",p1->getx(),p1->gety());
					code1=compcode(p1,rect);
					//endcount++;
				}
				//printf("在循环中\n");
				if(endcount==2)
				{
					done=true;
					//printf("%d,%d",code0,code1);
				}

			}
		}while(!done);
	}
	//lines->setnum(count);
	//printf("新生成路径点数量:%d\n",count);
	return newlines;
}

int compcode(Ipe_Point2D *p0,cliprect* rect)//返回点的位置编码
{
	/*
		struct fz_rect_s//左上角与右下角定义的矩形,PDF坐标在左上角
		{
			float x0, y0;//左上角
			float x1, y1;//右下角
		};
	*/
	int code=0x00;//8421
	if(p0->gety()>rect->y0)
		code=code|8;
	if(p0->gety()<rect->y1)
		code=code|4;
	if(p0->getx()>rect->x1)
		code=code|2;
	if(p0->getx()<rect->x0)
		code=code|1;
	return code;
}

void chopline(Ipe_Point2D* p0,int code,cliprect* rect,float delx,float dely)
{
	float x,y;
	if(code&LEFT_EDGE)
	{
		//y=p0->gety()+(rect->x0-p0->getx())*dely/delx;
		y=p0->gety()+(rect->x0-p0->getx())*dely/delx;
		x=rect->x0;
	}
	else if(code&RIGHT_EDGE)
	{
		y=p0->gety()+(rect->x1-p0->getx())*dely/delx;
		x=rect->x1;
	}
	else if(code&BOTTOM_EDGE)
	{
		x=p0->getx()+(rect->y1-p0->gety())*delx/dely;
		y=rect->y1;
	}
	else if(code&TOP_EDGE)
	{
		x=p0->getx()+(rect->y0-p0->gety())*delx/dely;
		y=rect->y0;
	}
	p0->setx(x);
	p0->sety(y);
}

class Ipe_Bazeir* clipbazeir (Ipe_Bazeir* bazeir,cliprect* rect)//裁剪贝赛尔曲线的函数,最后返回一个新的贝赛尔曲线集
{
	Ipe_node<Ipe_Point2D>* currentpoint=bazeir->getlist()->headler;
	/*
	currentpoint=currentpoint->next;
	while(currentpoint)
	{
		printf("原本点:%f %f %d\n",currentpoint->t->getx(),currentpoint->t->gety(),currentpoint->t->getstate());
		currentpoint=currentpoint->next;
	}
	currentpoint=bazeir->getlist()->headler;
	*/
	Ipe_Bazeir* newbazeir=new Ipe_Bazeir();
	Ipe_Point2D *p0,*p1,*c0,*c1;//两个端点与控制点
	int state=0;//bazeir曲线的裁剪状态
	bool first=true;
	bool origin=true;
	currentpoint=currentpoint->next;
	while(currentpoint)//遍历一条贝塞尔曲线
	{
			//判断四个点是否在裁剪区域内
			//printf("开始裁剪曲线\n");
			if(first)//起点
			{
				p0=currentpoint->t;
				//printf("原本点0:%f %f %d\n",currentpoint->t->getx(),currentpoint->t->gety(),currentpoint->t->getstate());
				first=false;
				currentpoint=currentpoint->next;
				currentpoint=currentpoint->next;
				currentpoint=currentpoint->next;
				c0=currentpoint->t;
				currentpoint=currentpoint->next;
				c1=currentpoint->t;
				currentpoint=currentpoint->next;
				p1=currentpoint->t;
				//printf("原本点1:%f %f %d\n",currentpoint->t->getx(),currentpoint->t->gety(),currentpoint->t->getstate());
				currentpoint=currentpoint->next;
				//printf("起点\n");
				//printf("起点: %f %f \n",p0->getx(),p0->gety());
			}
			else
			{
				p0=p1;//非起点,p0指向p1
				c0=currentpoint->t;
				currentpoint=currentpoint->next;
				c1=currentpoint->t;
				currentpoint=currentpoint->next;
				//printf("原本点1:%f %f %d\n",currentpoint->t->getx(),currentpoint->t->gety(),currentpoint->t->getstate());
				p1=currentpoint->t;
				currentpoint=currentpoint->next;
			}
			//此时p0,p1,c0,c1分别记录着端点与控制点的信息
			int ps0,ps1,cs0,cs1;//存放点的状态
			ps0=compcode(p0, rect);//判断四个点的位置
			ps1=compcode(p1, rect);
			cs0=compcode(c0, rect);
			cs1=compcode(c1, rect);
			
			//所有情况:
				//	两个端点都在 保留
				//  一个端点在 保留
				//  两个端点都不在  此时看两个控制点 ，有一个在 保留
													//都不在  删除
			//总结:两种情况:四个点都不在裁剪区域内(判断点与边界的距离,若是小于某个值,保留,否则删除该曲线);存在点在裁剪区域内(保留)
			if((ps0!=0)&&(ps1!=0)&&(cs0!=0)&&(cs1!=0))//四个点均在裁剪框外
			{
				//先默认舍弃吧,之后可以添加距离测算函数
				if(1)
				{
					//printf("舍弃贝塞尔曲线点\n");
					continue;
				}
			}
			if(origin)
			{
				newbazeir->addpoint(p0->getx(),p0->gety(),-1,-1,-1,-1,0);//起点
				//printf("新起点:%f %f\n",p0->getx(),p0->gety());
				newbazeir->addpoint(c0->getx(),c0->gety(),c1->getx(),c1->gety(),p1->getx(),p1->gety(),3);
				origin=false;
			}
			else//非起点
			{
				newbazeir->addpoint(c0->getx(),c0->gety(),c1->getx(),c1->gety(),p1->getx(),p1->gety(),3);//加入一般点
				//printf("新路径点:%f %f\n",p1->getx(),p1->gety());
			}
	}
	return newbazeir;
}

int rtinside(Ipe_Point2D* start,Ipe_Point2D* end,Ipe_Point2D* p)
{
	return ((end->getx()-start->getx())*(p->gety()-start->gety())-(p->getx()-start->getx())*(end->gety()-start->gety()))>0?0:1;
}

Ipe_Point2D* intersection (Ipe_Point2D* l1s,Ipe_Point2D* l1e,Ipe_Point2D* l2s,Ipe_Point2D* l2e)//计算两直线的交点 l1s/e为要被裁剪的直线,l2s/e为边界直线
{
	Ipe_Point2D *p=new Ipe_Point2D();
	//求被裁剪直线的点斜式
	//printf("被裁剪直线:%f %f \n %f %f \n边界:%f %f \n %f %f\n ",l1s->getx(),l1s->gety(),l1e->getx(),l1e->gety(),l2s->getx(),l2s->gety(),l2e->getx(),l2e->gety());
	double k1=(l1e->gety()-l1s->gety())/(l1e->getx()-l1s->getx());
	double b1=l1s->gety()-(k1*l1s->getx());
	double x,y;
	if(l2s->getx()==l2e->getx())
	{
		x=l2s->getx();
		y=(k1*x)+b1;
	}
	else
	{
		y=l2s->gety();
		x=(y-b1)/k1;
	}
	//求解
	//printf("交点x y %f %f\n",x,y);
	p->setx(x);
	p->sety(y);
	p->setstate(l1s->getstate());
	//printf("生成%f %f %d\n",p->getx(),p->gety(),p->getstate());
	return p;
}

Ipe_LinkList<Ipe_GraphicCell>* clipplane(Ipe_LinkList<Ipe_GraphicCell>* list,cliprect* rect)//裁剪面的函数,返回一个直线集与曲线集的链表
{
	Ipe_LinkList<Ipe_GraphicCell>* newlist=new Ipe_LinkList<Ipe_GraphicCell>();//新建链表
	Ipe_node<Ipe_GraphicCell>* cgc=list->headler;
	bool existbazeir=false;
	while(cgc->next!=NULL)//先遍历路径中的直线集与曲线集(仅查看其类型)
	{
		cgc=cgc->next;
		Ipe_GraphicCell* graphiccell=cgc->t;
		if(graphiccell->gettype()==2)//曲线集
		{
			existbazeir=true;
		}
	}
	cgc=list->headler;
	if(existbazeir)//若是存在贝赛尔曲线集,则遍历路径
	{
		//如果都在裁剪区域外,就舍去
		//若存在部分在裁剪区域内,全部保留,可以返回原本的面,不做修改
		while(cgc->next!=NULL)
		{
			cgc=cgc->next;
			if(cgc->t->gettype()==1)
			{
				Ipe_Lines* line=dynamic_cast<Ipe_Lines*>(cgc->t);
				Ipe_node<Ipe_Point2D>* currentpoint=line->getlist()->headler;
				while(currentpoint->next!=0)
				{
					currentpoint=currentpoint->next;
					if(!compcode(currentpoint->t,rect))//存在点在裁剪区域内
					{
						newlist=list;
						break;
					}
				}
			}
			else if(cgc->t->gettype()==2)
			{
				Ipe_Bazeir* bazeir=dynamic_cast<Ipe_Bazeir*>(cgc->t);
				Ipe_node<Ipe_Point2D>* currentpoint=bazeir->getlist()->headler;
				bool first=true;
				while(currentpoint->next!=0)
				{
					currentpoint=currentpoint->next;
					if(!compcode(currentpoint->t,rect))//存在点在裁剪区域内
					{
						newlist=list;
						break;
					}
					if(first)
					{
						currentpoint=currentpoint->next;
						currentpoint=currentpoint->next;
						first=false;
					}
				}
			}
			else
			{
				printf("错误的输出父类graphiccell成员\n");
			}
		}
	}
	else//纯折线构成的面,使用sutherland-hodgman算法逐边裁剪
	{
		//printf("使用sutherland-hodgman算法逐边裁剪\n");
		int flag=0;//flag为0表示点在边界外部,为一则表示在边界内部
		Ipe_Lines* rline=new Ipe_Lines();//存放矩形路径,便于四条边进行裁剪
		rline->addpoint(rect->x0,rect->y0,0);
		rline->addpoint(rect->x1,rect->y0,0);
		rline->addpoint(rect->x1,rect->y1,0);
		rline->addpoint(rect->x0,rect->y1,0);
		rline->addpoint(rect->x0,rect->y0,0);
		Ipe_node<Ipe_Point2D>* start=rline->getlist()->headler;
		Ipe_node<Ipe_Point2D>* end=start->next;
		
		cgc=cgc->next;
		Ipe_Lines* line=dynamic_cast<Ipe_Lines*>(cgc->t);
		Ipe_Lines* res=new Ipe_Lines();//新生成的折线路径
		Ipe_node<Ipe_Point2D>* lp=line->getlist()->headler;//lp为遍历要裁剪的面的点的指针
		Ipe_Point2D* p=new Ipe_Point2D();//处理起点的问题

		for(int i=0;i<4;i++)//遍历四次
		{
			start=start->next;
			end=end->next;
			bool first=true;
			bool deletestart=false;
			//printf("第%d次\n",i);
			while(lp->next!=NULL)
			{
				lp=lp->next;
				//printf("%f %f %d\n",lp->t->getx(),lp->t->gety(),lp->t->getstate());
				if(first)
				{
					p->setx(lp->t->getx());
					p->sety(lp->t->gety());
					p->setstate(lp->t->getstate());
					flag=rtinside(start->t,end->t,p);
					if(flag==1)//在内部
					{
						res->addpoint(p);
					}
					else
					{
						deletestart=true;
					}
					first=false;
					continue;
				}

				if(rtinside(start->t,end->t,lp->t)==0)//当前点在边界外部
				{
					if(flag==1)//由内向外
					{
						flag=0;
						Ipe_Point2D* cp;
						//计算与边界交点
						cp=intersection (p,lp->t,start->t,end->t);
						res->addpoint(cp);//添加与边界的交点
					}
				}
				else //点在边界内部
				{
					if(flag==0)//由外向内
					{
						flag=1;
						Ipe_Point2D* cp;
						//计算与边界交点
						cp=intersection (p,lp->t,start->t,end->t);
						res->addpoint(cp);//添加与边界的交点
						res->addpoint(lp->t);
					}
					else
					{
						res->addpoint(lp->t);//两点均在裁剪区域内部	
					}
				}
				p->setx(lp->t->getx());
				p->sety(lp->t->gety());
				p->setstate(lp->t->getstate());
				//printf("%f %f %d\n",p->getx(),p->gety(),p->getstate());
			}
			//一次循环结束
			if(deletestart==true)
			{
				if(res->getlist()->headler!=NULL&&res->getlist()->headler->next!=NULL)
				{
					Ipe_Point2D* sp=new Ipe_Point2D(res->getlist()->headler->next->t->getx(),res->getlist()->headler->next->t->gety(),res->getlist()->headler->next->t->getstate());
					res->addpoint(sp);
				}
			}
			/*
			lp=res->getlist()->headler;
			printf("第%d次裁剪后内容\n",i);
			while(lp->next!=NULL)
			{
				lp=lp->next;
				printf("%f %f %d\n",lp->t->getx(),lp->t->gety(),lp->t->getstate());
			}
			*/
			lp=res->getlist()->headler;
			if(i!=3)
			{
				res=new Ipe_Lines();
			}
		}
		if(res->getlist()->headler->next!=NULL)
		{
			res->getlist()->headler->next->t->setstate(0);
		}
		newlist->add(res);
	}
	/*
	Ipe_node<class Ipe_GraphicCell> *p=newlist->headler->next;
	Ipe_Lines *k=dynamic_cast<Ipe_Lines*>(p->t);
	Ipe_node<Ipe_Point2D>*cp=k->getlist()->headler;
	printf("裁剪结果:\n");
	while(cp->next!=NULL)
	{
		cp=cp->next;
		printf("%f %f %d\n",cp->t->getx(),cp->t->gety(),cp->t->getstate());
	}
	*/
	return newlist;
}