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
	else//��㲻����
	{
		/*
		if(cs->existcm)//�ڲ����ת�þ���
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
	if(cliptype!=0)//�����ڲü�·��
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
			cs->existclip=cliptype;//�ڲ�ü�·�����͵����������
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
			grade++;
			recursion(list,k,cs->matrix,cs->clipheadler,cs->existclip);//Ƕ�׵���
			grade--;
		}
	}
}



/*
void recursion(Ipe_LinkList<Ipe_PdfElement>* list,struct zblstack* cs,float* cm,struct  routepoint* clipheadler)
		{
			//�ж��Ƿ���cm,clip,�ֱ���ǰջ��Ƕ��ջ
			if(cs->existcm)
			{
				//�ϲ�cm
				if(cm!=NULL)//������ת�þ���,����������Ҫ����
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
					//�ü�·���ĺϲ�
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
			else//������Ƕ��ջ
			{
				cs->currentstack=cs->stackheadler;
				while(cs->currentstack->nextstack!=NULL)
				{
					cs->currentstack=cs->currentstack->nextstack;
					recursion(list,cs->currentstack,cs->matrix,cs->clipheadler);//Ƕ�׵���
				}
			}

		}
*/
/*recursion(Ipe_LinkList<Ipe_PdfElement>* list,struct zblstack* cs,double* cm,struct  routepoint* clipheadler)
		{
			�ж��Ƿ���cm,clip,�ֱ���ǰջ��Ƕ��ջ

			��ǰջ
				���жϵ�ǰջ�Ƿ���cm,clip
					����ǰջû��cm��clip 00
					�������ͨ��new stack����
					Ipe_PdfStack* stack=new Ipe_PdfStack(routeset->currentstack);
					list->add(stack);

					��01 10 11
					���кϲ�(ֱ�Ӷ�stackָ����в���)
					Ipe_PdfStack* stack=new Ipe_PdfStack(routeset->currentstack);
					list->add(stack);
			

			Ƕ��ջ
				������Ƕ��ջ��:
					����Ƕ��ջ����
					���õݹ麯��(ע���޸�cm,clip����)
				����������
					return
					
		}
		*/