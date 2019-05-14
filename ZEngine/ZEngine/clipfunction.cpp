#include "clipfunction.h"

class Ipe_Lines* cliplines(Ipe_Lines* lines,cliprect* rect)//ֱ�߼��봰�ھ��β���
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
		//��ʱp0,p1Ϊֱ���ϵ����˵�
		int code0,code1;
		bool done=false;
		code0=compcode(p0,rect);
		code1=compcode(p1,rect);//���������봰������,���б����ж�
		//printf("%d,%d\n",code0,code1);
		int endcount=0;
		do
		{
			if(!(code0|code1))//��Ϊ0x00
			{
				//ȫ�ڴ�����
				//ȫ������
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
				//ȫ���ڴ�����
				//�����
				cp0=cp1;
				p0->setx(cp0->getx());
				p0->sety(cp0->gety());
				p0->setstate(cp0->getstate());
				delete p1;
				done=true;
			}
			else
			{
				//����ȷ����״̬
				//����߶��봰�ڱ߽�Ľ��㣬�ڽ��㴦���߶�һ��Ϊ�������б���һ����ȫ�ڴ����⣬������֮.
				//�ٶ���һ���ظ�������������ֱ�����߶���ȫ�����������ҵ�λ�ڴ����ڵ�һ���߶�Ϊֹ
				float delx,dely;
				if(code0!=0)//p0������
				{
					delx=p1->getx()-p0->getx();
					dely=p1->gety()-p0->gety();
					chopline(p0,code0,rect,delx,dely);
					//printf("x0:%f  y0:%f\n",p0->getx(),p0->gety());
					code0=compcode(p0,rect);
					p0->setstate(0);
					//endcount++;
				}
				else//p1������
				{
					delx=p1->getx()-p0->getx();
					dely=p1->gety()-p0->gety();
					chopline(p1,code1,rect,delx,dely);
					//printf("x1:%f  y1:%f\n",p1->getx(),p1->gety());
					code1=compcode(p1,rect);
					//endcount++;
				}
				//printf("��ѭ����\n");
				if(endcount==2)
				{
					done=true;
					//printf("%d,%d",code0,code1);
				}

			}
		}while(!done);
	}
	//lines->setnum(count);
	//printf("������·��������:%d\n",count);
	return newlines;
}

int compcode(Ipe_Point2D *p0,cliprect* rect)//���ص��λ�ñ���
{
	/*
		struct fz_rect_s//���Ͻ������½Ƕ���ľ���,PDF���������Ͻ�
		{
			float x0, y0;//���Ͻ�
			float x1, y1;//���½�
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

class Ipe_Bazeir* clipbazeir (Ipe_Bazeir* bazeir,cliprect* rect)//�ü����������ߵĺ���,��󷵻�һ���µı��������߼�
{
	Ipe_node<Ipe_Point2D>* currentpoint=bazeir->getlist()->headler;
	/*
	currentpoint=currentpoint->next;
	while(currentpoint)
	{
		printf("ԭ����:%f %f %d\n",currentpoint->t->getx(),currentpoint->t->gety(),currentpoint->t->getstate());
		currentpoint=currentpoint->next;
	}
	currentpoint=bazeir->getlist()->headler;
	*/
	Ipe_Bazeir* newbazeir=new Ipe_Bazeir();
	Ipe_Point2D *p0,*p1,*c0,*c1;//�����˵�����Ƶ�
	int state=0;//bazeir���ߵĲü�״̬
	bool first=true;
	bool origin=true;
	currentpoint=currentpoint->next;
	while(currentpoint)//����һ������������
	{
			//�ж��ĸ����Ƿ��ڲü�������
			//printf("��ʼ�ü�����\n");
			if(first)//���
			{
				p0=currentpoint->t;
				//printf("ԭ����0:%f %f %d\n",currentpoint->t->getx(),currentpoint->t->gety(),currentpoint->t->getstate());
				first=false;
				currentpoint=currentpoint->next;
				currentpoint=currentpoint->next;
				currentpoint=currentpoint->next;
				c0=currentpoint->t;
				currentpoint=currentpoint->next;
				c1=currentpoint->t;
				currentpoint=currentpoint->next;
				p1=currentpoint->t;
				//printf("ԭ����1:%f %f %d\n",currentpoint->t->getx(),currentpoint->t->gety(),currentpoint->t->getstate());
				currentpoint=currentpoint->next;
				//printf("���\n");
				//printf("���: %f %f \n",p0->getx(),p0->gety());
			}
			else
			{
				p0=p1;//�����,p0ָ��p1
				c0=currentpoint->t;
				currentpoint=currentpoint->next;
				c1=currentpoint->t;
				currentpoint=currentpoint->next;
				//printf("ԭ����1:%f %f %d\n",currentpoint->t->getx(),currentpoint->t->gety(),currentpoint->t->getstate());
				p1=currentpoint->t;
				currentpoint=currentpoint->next;
			}
			//��ʱp0,p1,c0,c1�ֱ��¼�Ŷ˵�����Ƶ����Ϣ
			int ps0,ps1,cs0,cs1;//��ŵ��״̬
			ps0=compcode(p0, rect);//�ж��ĸ����λ��
			ps1=compcode(p1, rect);
			cs0=compcode(c0, rect);
			cs1=compcode(c1, rect);
			
			//�������:
				//	�����˵㶼�� ����
				//  һ���˵��� ����
				//  �����˵㶼����  ��ʱ���������Ƶ� ����һ���� ����
													//������  ɾ��
			//�ܽ�:�������:�ĸ��㶼���ڲü�������(�жϵ���߽�ľ���,����С��ĳ��ֵ,����,����ɾ��������);���ڵ��ڲü�������(����)
			if((ps0!=0)&&(ps1!=0)&&(cs0!=0)&&(cs1!=0))//�ĸ�����ڲü�����
			{
				//��Ĭ��������,֮�������Ӿ�����㺯��
				if(1)
				{
					//printf("�������������ߵ�\n");
					continue;
				}
			}
			if(origin)
			{
				newbazeir->addpoint(p0->getx(),p0->gety(),-1,-1,-1,-1,0);//���
				//printf("�����:%f %f\n",p0->getx(),p0->gety());
				newbazeir->addpoint(c0->getx(),c0->gety(),c1->getx(),c1->gety(),p1->getx(),p1->gety(),3);
				origin=false;
			}
			else//�����
			{
				newbazeir->addpoint(c0->getx(),c0->gety(),c1->getx(),c1->gety(),p1->getx(),p1->gety(),3);//����һ���
				//printf("��·����:%f %f\n",p1->getx(),p1->gety());
			}
	}
	return newbazeir;
}

int rtinside(Ipe_Point2D* start,Ipe_Point2D* end,Ipe_Point2D* p)
{
	return ((end->getx()-start->getx())*(p->gety()-start->gety())-(p->getx()-start->getx())*(end->gety()-start->gety()))>0?0:1;
}

Ipe_Point2D* intersection (Ipe_Point2D* l1s,Ipe_Point2D* l1e,Ipe_Point2D* l2s,Ipe_Point2D* l2e)//������ֱ�ߵĽ��� l1s/eΪҪ���ü���ֱ��,l2s/eΪ�߽�ֱ��
{
	Ipe_Point2D *p=new Ipe_Point2D();
	//�󱻲ü�ֱ�ߵĵ�бʽ
	//printf("���ü�ֱ��:%f %f \n %f %f \n�߽�:%f %f \n %f %f\n ",l1s->getx(),l1s->gety(),l1e->getx(),l1e->gety(),l2s->getx(),l2s->gety(),l2e->getx(),l2e->gety());
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
	//���
	//printf("����x y %f %f\n",x,y);
	p->setx(x);
	p->sety(y);
	p->setstate(l1s->getstate());
	//printf("����%f %f %d\n",p->getx(),p->gety(),p->getstate());
	return p;
}

Ipe_LinkList<Ipe_GraphicCell>* clipplane(Ipe_LinkList<Ipe_GraphicCell>* list,cliprect* rect)//�ü���ĺ���,����һ��ֱ�߼������߼�������
{
	Ipe_LinkList<Ipe_GraphicCell>* newlist=new Ipe_LinkList<Ipe_GraphicCell>();//�½�����
	Ipe_node<Ipe_GraphicCell>* cgc=list->headler;
	bool existbazeir=false;
	while(cgc->next!=NULL)//�ȱ���·���е�ֱ�߼������߼�(���鿴������)
	{
		cgc=cgc->next;
		Ipe_GraphicCell* graphiccell=cgc->t;
		if(graphiccell->gettype()==2)//���߼�
		{
			existbazeir=true;
		}
	}
	cgc=list->headler;
	if(existbazeir)//���Ǵ��ڱ��������߼�,�����·��
	{
		//������ڲü�������,����ȥ
		//�����ڲ����ڲü�������,ȫ������,���Է���ԭ������,�����޸�
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
					if(!compcode(currentpoint->t,rect))//���ڵ��ڲü�������
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
					if(!compcode(currentpoint->t,rect))//���ڵ��ڲü�������
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
				printf("������������graphiccell��Ա\n");
			}
		}
	}
	else//�����߹��ɵ���,ʹ��sutherland-hodgman�㷨��߲ü�
	{
		//printf("ʹ��sutherland-hodgman�㷨��߲ü�\n");
		int flag=0;//flagΪ0��ʾ���ڱ߽��ⲿ,Ϊһ���ʾ�ڱ߽��ڲ�
		Ipe_Lines* rline=new Ipe_Lines();//��ž���·��,���������߽��вü�
		rline->addpoint(rect->x0,rect->y0,0);
		rline->addpoint(rect->x1,rect->y0,0);
		rline->addpoint(rect->x1,rect->y1,0);
		rline->addpoint(rect->x0,rect->y1,0);
		rline->addpoint(rect->x0,rect->y0,0);
		Ipe_node<Ipe_Point2D>* start=rline->getlist()->headler;
		Ipe_node<Ipe_Point2D>* end=start->next;
		
		cgc=cgc->next;
		Ipe_Lines* line=dynamic_cast<Ipe_Lines*>(cgc->t);
		Ipe_Lines* res=new Ipe_Lines();//�����ɵ�����·��
		Ipe_node<Ipe_Point2D>* lp=line->getlist()->headler;//lpΪ����Ҫ�ü�����ĵ��ָ��
		Ipe_Point2D* p=new Ipe_Point2D();//������������

		for(int i=0;i<4;i++)//�����Ĵ�
		{
			start=start->next;
			end=end->next;
			bool first=true;
			bool deletestart=false;
			//printf("��%d��\n",i);
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
					if(flag==1)//���ڲ�
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

				if(rtinside(start->t,end->t,lp->t)==0)//��ǰ���ڱ߽��ⲿ
				{
					if(flag==1)//��������
					{
						flag=0;
						Ipe_Point2D* cp;
						//������߽罻��
						cp=intersection (p,lp->t,start->t,end->t);
						res->addpoint(cp);//�����߽�Ľ���
					}
				}
				else //���ڱ߽��ڲ�
				{
					if(flag==0)//��������
					{
						flag=1;
						Ipe_Point2D* cp;
						//������߽罻��
						cp=intersection (p,lp->t,start->t,end->t);
						res->addpoint(cp);//�����߽�Ľ���
						res->addpoint(lp->t);
					}
					else
					{
						res->addpoint(lp->t);//������ڲü������ڲ�	
					}
				}
				p->setx(lp->t->getx());
				p->sety(lp->t->gety());
				p->setstate(lp->t->getstate());
				//printf("%f %f %d\n",p->getx(),p->gety(),p->getstate());
			}
			//һ��ѭ������
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
			printf("��%d�βü�������\n",i);
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
	printf("�ü����:\n");
	while(cp->next!=NULL)
	{
		cp=cp->next;
		printf("%f %f %d\n",cp->t->getx(),cp->t->gety(),cp->t->getstate());
	}
	*/
	return newlist;
}