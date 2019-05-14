#include "Ipe_PdfStack.h"
#include "Ipe_PdfPath.h"

Ipe_PdfStack::Ipe_PdfStack(void)
{
}

Ipe_PdfStack::Ipe_PdfStack(struct zblstack* stack)//��ʼ������
{
	int i=0,j;
	int state=0;
	double originx=0,originy=0,currentx=0,currenty=0;
	this->grade=0;//Ĭ��ջ�Ĳ��Ϊ��
	this->existstack=stack->existstack;
	this->ca=stack->ca;
	this->shadowtype=stack->shadowtype;
	if(this->shadowtype==0)//����������Ӱ
	{
		this->bcolor=NULL;
		this->ecolor=NULL;
	}
	else
	{
		//printf("������Ӱ,��Ӱ����:%d\n",this->shadowtype);
		this->bcolor=(float*)malloc(4*sizeof(float));
		this->ecolor=(float*)malloc(4*sizeof(float));
		for(j=0;j<3;j++)
		{
			this->bcolor[j]=stack->bcolor[j]*255;
			this->ecolor[j]=stack->ecolor[j]*255;
			//printf("%f %f\n",this->bcolor[j],this->ecolor[j]);
		}
	}
	if(this->existstack==0)//������ջ����Ĭ��ֻ��һ��·��
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
	this->countclip=stack->countclip;//��¼�ü�·���ж��ٸ���

	this->cliplist=new Ipe_LinkList<Ipe_GraphicCell>();
	Ipe_Lines* lines=new Ipe_Lines();//ֱ�߼�����
	Ipe_Bazeir* bazeir=new Ipe_Bazeir();//���������߶���
	stack->currentclip=stack->clipheadler;
	//printf("�ü�·��������:%d\n",this->countclip);
	for(i=0;i<this->countclip;i++)//��ȡ�ü�·��
	{
		stack->currentclip=stack->currentclip->nextpoint;
		//printf("\n�ü�·����ֵ%f %f״̬:%d\n",stack->currentclip->p0,stack->currentclip->p1,stack->currentclip->state);
		if(state==0)//��ʼ״̬Ϊ0
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
				printf("ȷ����һ��ֱ�߼���״̬\n");
#endif
				state=1;
				lines->addpoint(originx,originy,0);//������
				lines->addpoint(stack->currentclip->p0,stack->currentclip->p1,1);//��ӵ�ǰ��
#ifdef debug
				printf("���·��������һ����\n");
				printf("���:%f %f\n��һ����:%f %f ",originx,originy,stack->currentclip->p0,stack->currentclip->p1);
#endif
				currentx=stack->currentclip->p0;
				currenty=stack->currentclip->p1;
				continue;
			}
			else if(stack->currentclip->state==3)
			{
#ifdef debug
				printf("ȷ����һ�����߼���״̬\n");
#endif
				state=2;
				bazeir->addpoint(originx,originy,-1,-1,-1,-1,0);
				bazeir->addpoint(stack->currentclip->p0,stack->currentclip->p1,stack->currentclip->p2,stack->currentclip->p3,stack->currentclip->p4,stack->currentclip->p5,3);
				currentx=stack->currentclip->p0;
				currenty=stack->currentclip->p1;
				continue;
			}
		}

		if(state==1)//����ֱ�߼�
		{
			if(stack->currentclip->state==1)//����Ϊlint to
			{
				lines->addpoint(stack->currentclip->p0,stack->currentclip->p1,1);//����ֱ�ߵ���ӽ�ȥ
#ifdef debug
				printf("����ֱ��·����%f %f\n",stack->currentclip->p0,stack->currentclip->p1);
#endif
				currentx=stack->currentclip->p0;
				currenty=stack->currentclip->p1;
				continue;
			}
			else if(stack->currentclip->state==3)//����Ϊc ��ʱ,������ֱ����ӽ�list��,Ȼ���ͷŲ����·���lines����,Ϊ�´�����׼��
			{
				this->cliplist->add(lines);
				this->clipcellcount++;
				//delete lines;
				lines=new Ipe_Lines();//�·���ֱ�߼�����,Ϊ�´���׼��
				bazeir->addpoint(currentx,currenty,-1,-1,-1,-1,0);//������߼������
				originx=currentx;
				originy=currenty;
				bazeir->addpoint(stack->currentclip->p0,stack->currentclip->p1,stack->currentclip->p2,stack->currentclip->p3,stack->currentclip->p4,stack->currentclip->p5,3);
				//��ӵ�ǰ��
				state=2;//�ı�״̬Ϊ���ߴ���
				continue;
			}
			else if(stack->currentclip->state==2)//����Ϊh  m,l,h,c״̬(�ֱ��Ӧ0��1��2��3��
			{
				lines->addpoint(originx,originy,2);//������(·���պ�)
				this->cliplist->add(lines);//��һ������ֱ��·�����ϼ�������
				lines=new Ipe_Lines();
				this->clipcellcount++;
				state=3;
				continue;
			}
		}

		if(state==2)//�������߼�
		{
			if(stack->currentclip->state==1)//����Ϊlint to
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
			else if(stack->currentclip->state==3)//����Ϊ c
			{
				bazeir->addpoint(stack->currentclip->p0,stack->currentclip->p1,stack->currentclip->p2,stack->currentclip->p3,stack->currentclip->p4,stack->currentclip->p5,3);
				currentx=stack->currentclip->p4;
				currenty=stack->currentclip->p5;
			}
			else if(stack->currentclip->state==2)//����Ϊh
			{
				bazeir->addpoint(originx,originy,-1,-1,-1,-1,2);
				this->cliplist->add(bazeir);
				bazeir=new Ipe_Bazeir();
				this->clipcellcount++;
				state=3;
				continue;
			}
		}

		if(state==3)//���¿�ʼ·��
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
	//printf("��ǰջ��·����:%d\n",this->countpath);
	for(i=0;i<this->countpath;i++)//���·��
	{
		stack->currentroute=stack->currentroute->nextroute;
		Ipe_PdfPath* path=new Ipe_PdfPath(stack->currentroute);
		pathlist->add(path);
	}

}

Ipe_PdfStack::~Ipe_PdfStack(void)
{
	if(this->existclip>0)//���ڲü�·��
	{
		delete this->cliplist;
	}
	delete this->pathlist;
	printf("�ͷ�ջ��·���ڵ���ü�·���ڵ�");
}

void Ipe_PdfStack::printfPath(void)
{
	printf("������stack���������\n");
	printf("ջ����%d��·��",this->countpath);
	printf("ջ���Ƿ����ת�þ������:%d\n",this->existcm);
	if(this->existcm>0)
	{
		printf("ת�þ���:%f %f %f %f %f %f\n",this->matrix[0],this->matrix[1],this->matrix[2],this->matrix[3],this->matrix[4],this->matrix[5]);
	}
	Ipe_node<Ipe_PdfPath>* p=this->pathlist->headler;
	//p->t->printPoint();
	printf("����ѭ��\n");
	while(p->next!=NULL)
	{
		printf("��ѭ����\n");
		p->next->t->printfPath();//����ת��
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