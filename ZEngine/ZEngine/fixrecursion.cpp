#include "Ipe_PdfElement.h"
#include "Ipe_LinkList.h"
#include "Ipe_PdfStack.h"
#include "MuInclude.h"

void recursion(Ipe_LinkList<Ipe_PdfElement>* list,struct zblstack* cs,float* cm,struct  routepoint* clipheadler)
{
	//�ж��Ƿ���cm,clip,�ֱ���ǰջ��Ƕ��ջ
	if(cm!=NULL)//������ת�þ���
	{
		if(cs->existcm)//�ڲ�Ҳ����ת�þ���
		{
			cs->matrix[0]=cs->matrix[0]*cm[0]+cs->matrix[1]*cm[2];
			cs->matrix[1]=cs->matrix[0]*cm[1]+cs->matrix[1]*cm[3];
			cs->matrix[2]=cs->matrix[2]*cm[0]+cs->matrix[3]*cm[2];
			cs->matrix[3]=cs->matrix[2]*cm[1]+cs->matrix[3]*cm[3];
			cs->matrix[4]=cs->matrix[4]*cm[0]+cs->matrix[5]*cm[2]+cs->matrix[4];
			cs->matrix[5]=cs->matrix[4]*cm[1]+cs->matrix[5]*cm[3]+cs->matrix[5];
		}
		else//�ڲ㲻����ת�þ���,��������ڲ���и���
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
	//�������ڵ����?
	if(clipheadler!=NULL)//�����ڲü�·��
	{
		if(cs->existclip)//�ڲ�Ҳ����
		{
			//���вü�·���ĺϲ�
			struct routepoint* p=clipheadler;
			while(p->nextpoint!=NULL)
			{
				p=p->nextpoint;
			}
			p->nextpoint=cs->clipheadler->nextpoint;
		}
		else//�������ڲ㲻���� �����ü�·�����Ƶ��ڲ�ü�·��
		{
			cs->clipheadler=clipheadler;
		}
	}
	Ipe_PdfStack* stack=new Ipe_PdfStack(cs);
	list->add(stack);
	if(cs->existnest==0)//������Ƕ��ջ
	{
		return;
	}
	else//������Ƕ��ջ
	{
		zblstack* k=cs->stackheadler;
		while(k->nextstack!=NULL)
		{
			k=k->nextstack;
			recursion(list,k,cs->matrix,cs->clipheadler);//Ƕ�׵���
		}
	}
}