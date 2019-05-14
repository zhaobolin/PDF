#include "Ipe_PdfElement.h"
#include "Ipe_LinkList.h"
#include "Ipe_PdfStack.h"
//#include "MuInclude.h"
int grade=0;
int getlength(routepoint* clipheadler)
{
	int count=0;
	routepoint* p=clipheadler;
	if(clipheadler==NULL/*||clipheadler->nextpoint==NULL*/)
	{
		return 0;
	}
	p=clipheadler;
	while(p->nextpoint!=NULL)
	{
		p=p->nextpoint;
		count++;
	}
	return count;
}


void recursion(Ipe_LinkList<Ipe_PdfElement>* list,struct zblstack* cs,float* cm,struct  routepoint* clipheadler,int cliptype)
{
	//判断是否有cm,clip,分别处理当前栈和嵌套栈
	if(cm!=NULL)//外层存在转置矩阵
	{
		if(cs->existcm)//内层也存在转置矩阵
		{
			cs->matrix[0]=cs->matrix[0]*cm[0]+cs->matrix[1]*cm[2];
			cs->matrix[1]=cs->matrix[0]*cm[1]+cs->matrix[1]*cm[3];
			cs->matrix[2]=cs->matrix[2]*cm[0]+cs->matrix[3]*cm[2];
			cs->matrix[3]=cs->matrix[2]*cm[1]+cs->matrix[3]*cm[3];
			cs->matrix[4]=cs->matrix[4]*cm[0]+cs->matrix[5]*cm[2]+cs->matrix[4];
			cs->matrix[5]=cs->matrix[4]*cm[1]+cs->matrix[5]*cm[3]+cs->matrix[5];
		}
		else//内层不存在转置矩阵,则将外层与内层进行复制
		{
			cs->matrix[0]=cm[0];
			cs->matrix[1]=cm[1];
			cs->matrix[2]=cm[2];
			cs->matrix[3]=cm[3];
			cs->matrix[4]=cm[4];
			cs->matrix[5]=cm[5];
			cs->existcm=1;
		}
	}
	//都不存在的情况?
	else//外层不存在
	{
		/*
		if(cs->existcm)//内层存在转置矩阵
		{
			cs->matrix[0]=cs->matrix[0]*cm[0]+cs->matrix[1]*cm[2];
			cs->matrix[1]=cs->matrix[0]*cm[1]+cs->matrix[1]*cm[3];
			cs->matrix[2]=cs->matrix[2]*cm[0]+cs->matrix[3]*cm[2];
			cs->matrix[3]=cs->matrix[2]*cm[1]+cs->matrix[3]*cm[3];
			cs->matrix[4]=cs->matrix[4]*cm[0]+cs->matrix[5]*cm[2]+cs->matrix[4];
			cs->matrix[5]=cs->matrix[4]*cm[1]+cs->matrix[5]*cm[3]+cs->matrix[5];
		}
		*/
	}
	if(cliptype!=0)//外层存在裁剪路径
	{
		if(cs->existclip)//内层也存在
		{
			//进行裁剪路径的合并
			struct routepoint* p=clipheadler;
			while(p->nextpoint!=NULL)
			{
				p=p->nextpoint;
			}
			p->nextpoint=cs->clipheadler->nextpoint;
		}
		else//外层存在内层不存在 将外层裁剪路径复制到内层裁剪路径
		{
			cs->existclip=cliptype;//内层裁剪路径类型等于外层类型
			cs->clipheadler=(struct routepoint*)malloc(sizeof(struct routepoint));
			cs->currentclip=cs->clipheadler;
			cs->currentclip->nextpoint=NULL;
			cs->countclip=getlength(clipheadler);
			struct routepoint* cc=clipheadler;
			while(cc->nextpoint!=NULL)
			{
				cc=cc->nextpoint;
				struct routepoint* p=(struct routepoint*)malloc(sizeof(struct routepoint));
				p->nextpoint=NULL;
				p->p0=cc->p0;
				p->p1=cc->p1;
				p->p2=cc->p2;
				p->p3=cc->p3;
				p->p4=cc->p4;
				p->p5=cc->p5;
				p->state=cc->state;
				cs->currentclip->nextpoint=p;
				cs->currentclip=cs->currentclip->nextpoint;
			}
		}
	}
	Ipe_PdfStack* stack=new Ipe_PdfStack(cs);
	stack->setgrade(grade);
	list->add(stack);
	if(cs->existnest==0)//不存在嵌套栈
	{
		return;
	}
	else//若存在嵌套栈
	{
		zblstack* k=cs->stackheadler;
		while(k->nextstack!=NULL)
		{
			k=k->nextstack;
			grade++;
			recursion(list,k,cs->matrix,cs->clipheadler,cs->existclip);//嵌套调用
			grade--;
		}
	}
}



/*
void recursion(Ipe_LinkList<Ipe_PdfElement>* list,struct zblstack* cs,float* cm,struct  routepoint* clipheadler)
		{
			//判断是否有cm,clip,分别处理当前栈和嵌套栈
			if(cs->existcm)
			{
				//合并cm
				if(cm!=NULL)//外层存在转置矩阵,不存在则不需要操作
				{
					cs->matrix[0]=cs->matrix[0]*cm[0]+cs->matrix[1]*cm[2];
					cs->matrix[1]=cs->matrix[0]*cm[1]+cs->matrix[1]*cm[3];
					cs->matrix[2]=cs->matrix[2]*cm[0]+cs->matrix[3]*cm[2];
					cs->matrix[3]=cs->matrix[2]*cm[1]+cs->matrix[3]*cm[3];
					cs->matrix[4]=cs->matrix[4]*cm[0]+cs->matrix[5]*cm[2]+cs->matrix[4];
					cs->matrix[5]=cs->matrix[4]*cm[1]+cs->matrix[5]*cm[3]+cs->matrix[5];
				
				}
			}
			if(cs->existclip)
			{
				if(clipheadler!=NULL)
				{
					//裁剪路径的合并
					struct routepoint* p=clipheadler;
					while(p->nextpoint!=NULL)
					{
						p=p->nextpoint;
					}
					p->nextpoint=cs->clipheadler->nextpoint;
				}
			}
			Ipe_PdfStack* stack=new Ipe_PdfStack(cs);
			list->add(stack);
			
			if(cs->existnest==0)
			{
				return;
			}
			else//若存在嵌套栈
			{
				cs->currentstack=cs->stackheadler;
				while(cs->currentstack->nextstack!=NULL)
				{
					cs->currentstack=cs->currentstack->nextstack;
					recursion(list,cs->currentstack,cs->matrix,cs->clipheadler);//嵌套调用
				}
			}

		}
*/
/*recursion(Ipe_LinkList<Ipe_PdfElement>* list,struct zblstack* cs,double* cm,struct  routepoint* clipheadler)
		{
			判断是否有cm,clip,分别处理当前栈和嵌套栈

			当前栈
				先判断当前栈是否有cm,clip
					若当前栈没有cm与clip 00
					则进行普通的new stack操作
					Ipe_PdfStack* stack=new Ipe_PdfStack(routeset->currentstack);
					list->add(stack);

					若01 10 11
					进行合并(直接对stack指针进行操作)
					Ipe_PdfStack* stack=new Ipe_PdfStack(routeset->currentstack);
					list->add(stack);
			

			嵌套栈
				若存在嵌套栈则:
					遍历嵌套栈链表
					调用递归函数(注意修改cm,clip参数)
				若不存在则
					return
					
		}
		*/