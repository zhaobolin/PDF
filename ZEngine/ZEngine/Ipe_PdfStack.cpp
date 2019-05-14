#include "Ipe_PdfStack.h"
#include "Ipe_PdfPath.h"

Ipe_PdfStack::Ipe_PdfStack(void)
{
}

Ipe_PdfStack::Ipe_PdfStack(struct zblstack* stack)//初始化函数
{
	int i=0,j;
	int state=0;
	double originx=0,originy=0,currentx=0,currenty=0;
	this->grade=0;//默认栈的层次为零
	this->existstack=stack->existstack;
	this->ca=stack->ca;
	this->shadowtype=stack->shadowtype;
	if(this->shadowtype==0)//若不存在阴影
	{
		this->bcolor=NULL;
		this->ecolor=NULL;
	}
	else
	{
		//printf("存在阴影,阴影类型:%d\n",this->shadowtype);
		this->bcolor=(float*)malloc(4*sizeof(float));
		this->ecolor=(float*)malloc(4*sizeof(float));
		for(j=0;j<3;j++)
		{
			this->bcolor[j]=stack->bcolor[j]*255;
			this->ecolor[j]=stack->ecolor[j]*255;
			//printf("%f %f\n",this->bcolor[j],this->ecolor[j]);
		}
	}
	if(this->existstack==0)//若不在栈中则默认只有一个路径
	{
		this->countpath=1;
	}
	else
	{
		this->countpath=stack->countroute;
	}
	this->existcm=stack->existcm;
	this->clipcellcount=0;
	if(this->existcm>0)
	{
		
		this->matrix=new float[6];
		this->matrix[0]=stack->matrix[0];
		this->matrix[1]=stack->matrix[1];
		this->matrix[2]=stack->matrix[2];
		this->matrix[3]=stack->matrix[3];
		this->matrix[4]=stack->matrix[4];
		this->matrix[5]=stack->matrix[5];
	}
	else
	{
		this->matrix=NULL;
	}
	this->existclip=stack->existclip;
	this->countclip=stack->countclip;//记录裁剪路径有多少个点

	this->cliplist=new Ipe_LinkList<Ipe_GraphicCell>();
	Ipe_Lines* lines=new Ipe_Lines();//直线集对象
	Ipe_Bazeir* bazeir=new Ipe_Bazeir();//贝塞尔曲线对象
	stack->currentclip=stack->clipheadler;
	//printf("裁剪路径点数量:%d\n",this->countclip);
	for(i=0;i<this->countclip;i++)//提取裁剪路径
	{
		stack->currentclip=stack->currentclip->nextpoint;
		//printf("\n裁剪路径点值%f %f状态:%d\n",stack->currentclip->p0,stack->currentclip->p1,stack->currentclip->state);
		if(state==0)//初始状态为0
		{
			if(stack->currentclip->state==0)
			{
				originx=stack->currentclip->p0;
				originy=stack->currentclip->p1;
				currentx=stack->currentclip->p0;
				currenty=stack->currentclip->p1;
				continue;
			}
			else if(stack->currentclip->state==1)//
			{
#ifdef debug
				printf("确定第一个直线集的状态\n");
#endif
				state=1;
				lines->addpoint(originx,originy,0);//添加起点
				lines->addpoint(stack->currentclip->p0,stack->currentclip->p1,1);//添加当前点
#ifdef debug
				printf("添加路径起点与第一个点\n");
				printf("起点:%f %f\n第一个点:%f %f ",originx,originy,stack->currentclip->p0,stack->currentclip->p1);
#endif
				currentx=stack->currentclip->p0;
				currenty=stack->currentclip->p1;
				continue;
			}
			else if(stack->currentclip->state==3)
			{
#ifdef debug
				printf("确定第一个曲线集的状态\n");
#endif
				state=2;
				bazeir->addpoint(originx,originy,-1,-1,-1,-1,0);
				bazeir->addpoint(stack->currentclip->p0,stack->currentclip->p1,stack->currentclip->p2,stack->currentclip->p3,stack->currentclip->p4,stack->currentclip->p5,3);
				currentx=stack->currentclip->p0;
				currenty=stack->currentclip->p1;
				continue;
			}
		}

		if(state==1)//处理直线集
		{
			if(stack->currentclip->state==1)//命令为lint to
			{
				lines->addpoint(stack->currentclip->p0,stack->currentclip->p1,1);//将该直线点添加进去
#ifdef debug
				printf("插入直线路径点%f %f\n",stack->currentclip->p0,stack->currentclip->p1);
#endif
				currentx=stack->currentclip->p0;
				currenty=stack->currentclip->p1;
				continue;
			}
			else if(stack->currentclip->state==3)//命令为c 此时,将完结的直线添加进list中,然后释放并重新分配lines集合,为下次做好准备
			{
				this->cliplist->add(lines);
				this->clipcellcount++;
				//delete lines;
				lines=new Ipe_Lines();//新分配直线集对象,为下次做准备
				bazeir->addpoint(currentx,currenty,-1,-1,-1,-1,0);//添加曲线集的起点
				originx=currentx;
				originy=currenty;
				bazeir->addpoint(stack->currentclip->p0,stack->currentclip->p1,stack->currentclip->p2,stack->currentclip->p3,stack->currentclip->p4,stack->currentclip->p5,3);
				//添加当前点
				state=2;//改变状态为曲线处理
				continue;
			}
			else if(stack->currentclip->state==2)//命令为h  m,l,h,c状态(分别对应0，1，2，3）
			{
				lines->addpoint(originx,originy,2);//添加起点(路径闭合)
				this->cliplist->add(lines);//将一个完整直线路径集合加入其中
				lines=new Ipe_Lines();
				this->clipcellcount++;
				state=3;
				continue;
			}
		}

		if(state==2)//处理曲线集
		{
			if(stack->currentclip->state==1)//命令为lint to
			{
				this->cliplist->add(bazeir);
				this->clipcellcount++;
				//delete bazeir;
				bazeir=new Ipe_Bazeir();
				lines->addpoint(currentx,currenty,0);
				lines->addpoint(stack->currentclip->p0,stack->currentclip->p1,1);
				originx=currentx;
				originy=currenty;
				state=1;
				continue;
			}
			else if(stack->currentclip->state==3)//命令为 c
			{
				bazeir->addpoint(stack->currentclip->p0,stack->currentclip->p1,stack->currentclip->p2,stack->currentclip->p3,stack->currentclip->p4,stack->currentclip->p5,3);
				currentx=stack->currentclip->p4;
				currenty=stack->currentclip->p5;
			}
			else if(stack->currentclip->state==2)//命令为h
			{
				bazeir->addpoint(originx,originy,-1,-1,-1,-1,2);
				this->cliplist->add(bazeir);
				bazeir=new Ipe_Bazeir();
				this->clipcellcount++;
				state=3;
				continue;
			}
		}

		if(state==3)//重新开始路径
		{
			originx=stack->currentclip->p0;
			originy=stack->currentclip->p1;
			state=0;
			continue;
		}
	}
	if(state==1)
	{
		this->cliplist->add(lines);
		this->clipcellcount++;
	}
	if(state==2)
	{
		this->cliplist->add(bazeir);
		this->clipcellcount++;
	}

	stack->currentroute=stack->routeheadler;
	this->pathlist=new Ipe_LinkList<class Ipe_PdfPath>();
	//printf("当前栈的路径数:%d\n",this->countpath);
	for(i=0;i<this->countpath;i++)//添加路径
	{
		stack->currentroute=stack->currentroute->nextroute;
		Ipe_PdfPath* path=new Ipe_PdfPath(stack->currentroute);
		pathlist->add(path);
	}

}

Ipe_PdfStack::~Ipe_PdfStack(void)
{
	if(this->existclip>0)//存在裁剪路径
	{
		delete this->cliplist;
	}
	delete this->pathlist;
	printf("释放栈中路径节点与裁剪路径节点");
}

void Ipe_PdfStack::printfPath(void)
{
	printf("调用了stack的输出函数\n");
	printf("栈中有%d个路径",this->countpath);
	printf("栈中是否存在转置矩阵参数:%d\n",this->existcm);
	if(this->existcm>0)
	{
		printf("转置矩阵:%f %f %f %f %f %f\n",this->matrix[0],this->matrix[1],this->matrix[2],this->matrix[3],this->matrix[4],this->matrix[5]);
	}
	Ipe_node<Ipe_PdfPath>* p=this->pathlist->headler;
	//p->t->printPoint();
	printf("进入循环\n");
	while(p->next!=NULL)
	{
		printf("在循环中\n");
		p->next->t->printfPath();//向下转型
		p=p->next;
	}
}

int Ipe_PdfStack::getelementtype()
{
	return 1;
}

int Ipe_PdfStack::getcountpath()
{
	return this->countpath;
}
int Ipe_PdfStack::getexistclip()
{
	return this->existclip;
}

int Ipe_PdfStack::getexistcm()
{
	return this->existcm;
}

float* Ipe_PdfStack::getmatrix()
{
	return this->matrix;
}

int Ipe_PdfStack::getclipcellcount()
{
	return this->clipcellcount;
}
Ipe_LinkList<class Ipe_PdfPath>* Ipe_PdfStack::getpathlist()
{
	return this->pathlist;
}

Ipe_LinkList<class Ipe_GraphicCell>* Ipe_PdfStack::getcliplist()
{
	return this->cliplist;
}
int Ipe_PdfStack::getshadowtype()
{
	return this->shadowtype;
}
float* Ipe_PdfStack::getbcolor()
{
	return this->bcolor;
}
float* Ipe_PdfStack::getecolor()
{
	return this->ecolor;
}

float Ipe_PdfStack::getca()
{
	return this->ca;
}

void Ipe_PdfStack::setgrade(int grade)
{
	this->grade;
}

int Ipe_PdfStack::getgrade()
{
	return this->grade;
}

void Ipe_PdfStack::setexistcm(int cm)
{
	this->existcm=cm;
}