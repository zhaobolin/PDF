#include "Ipe_PdfElement.h"
#include "Ipe_LinkList.h"
#include "Ipe_PdfStack.h"
#include "MuInclude.h"

void recursion(Ipe_LinkList<Ipe_PdfElement>* list,struct zblstack* cs,float* cm,struct  routepoint* clipheadler)
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
	if(clipheadler!=NULL)//外层存在裁剪路径
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
			cs->clipheadler=clipheadler;
		}
	}
	Ipe_PdfStack* stack=new Ipe_PdfStack(cs);
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
			recursion(list,k,cs->matrix,cs->clipheadler);//嵌套调用
		}
	}
}