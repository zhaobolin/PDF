#include "Ipe_PdfPath.h"


Ipe_PdfPath::Ipe_PdfPath(void)
{
}

Ipe_PdfPath::Ipe_PdfPath(zblroute* route)//��ʼ��Path����zblroute�ṹ���ȡ����
{
	int i=0,state=0,first=0;//��ǰ״̬
	double currentx,currenty,originx,originy;
	drawingmethord=route->drawingmethord;//���Ʒ��� 1-S 2-f* 3-f/F 4-s 5-B 6-B* 7-b 8-b*
	//printf("drawingmethord::%d\n",drawingmethord);
	GraphicsCellCount=0;
	pathtype=route->type;
	linewidth=route->linewidth;
	if(this->drawingmethord<5)//��������ͿĨ
	{
		colorspace=route->colorspace;
		this->scolor=NULL;
		this->scolorspace=0;
		//printf("this->existcm=%d\n\n",route->existcm);
		if(colorspace==1||colorspace==2)//�Ҷȿռ�
		{
			color.setColor(-1,-1,-1,-1,route->color[0]);
		}
		else if(colorspace==3||colorspace==4)//RGB��ɫ�ռ�
		{
			color.setColor(route->color[0],route->color[1],route->color[2],-1,-1);
			//printf("��ɫ:%d %d %d\n",color.getr(),color.getg(),color.getb());
		}
		else if(colorspace==5||colorspace==6)//����cmyk��ɫ�ռ�
		{
			colorspace=3;
			color.setCmykColor(255*(100-route->color[0]*100)*(100-route->color[3]*100)/10000,255*(100-route->color[1]*100)*(100-route->color[3]*100)/10000,255*(100-route->color[2]*100)*(100-route->color[3]*100)/10000,-1,-1);
			//printf("CMYK:%f %f %f %fת����ΪRGB:%d %d %d",route->color[0],route->color[1],route->color[2],route->color[3],color.getr(),color.getg(),color.getb());
		}
	}
	else//�������ͿĨ,����������ɫ,�����ͿĨ
	{
		//printf("������ɫ\n");
		colorspace=route->colorspace;//���
		scolorspace=route->scolorspace;//���
		this->scolor=new Ipe_Color();
		if(colorspace==1||colorspace==2)//�Ҷȿռ�
		{
			color.setColor(-1,-1,-1,-1,route->color[0]);
		}
		else if(colorspace==3||colorspace==4)//RGB��ɫ�ռ�
		{
			color.setColor(route->color[0],route->color[1],route->color[2],-1,-1);
			//printf("�����ɫ:%d %d %d\n",color.getr(),color.getg(),color.getb());
		}
		else if(colorspace==5||colorspace==6)//����cmyk��ɫ�ռ�
		{
			colorspace=3;
			color.setCmykColor(255*(100-route->color[0]*100)*(100-route->color[3]*100)/10000,255*(100-route->color[1]*100)*(100-route->color[3]*100)/10000,255*(100-route->color[2]*100)*(100-route->color[3]*100)/10000,-1,-1);
			//printf("CMYK:%f %f %f %fת����ΪRGB:%d %d %d",route->color[0],route->color[1],route->color[2],route->color[3],color.getr(),color.getg(),color.getb());
		}
		//printf("scolorspace=%d\n",scolorspace);
		if(scolorspace==1||scolorspace==2)//�Ҷȿռ�
		{
			scolor->setColor(-1,-1,-1,-1,route->color[0]);
		}
		else if(scolorspace==3||scolorspace==4)//RGB��ɫ�ռ�
		{
			scolor->setColor(route->scolor[0],route->scolor[1],route->scolor[2],-1,-1);
			//printf("�����ɫ:%d %d %d\n",color.getr(),color.getg(),color.getb());
		}
		else if(scolorspace==5||scolorspace==6)//����cmyk��ɫ�ռ�
		{
			scolorspace=3;
			scolor->setCmykColor(255*(100-route->scolor[0]*100)*(100-route->scolor[3]*100)/10000,255*(100-route->scolor[1]*100)*(100-route->scolor[3]*100)/10000,255*(100-route->scolor[2]*100)*(100-route->scolor[3]*100)/10000,-1,-1);
			//printf("CMYK:%f %f %f %fת����ΪRGB:%d %d %d",route->color[0],route->color[1],route->color[2],route->color[3],color.getr(),color.getg(),color.getb());
		}
	}
	/*
	��zblroute�ṹ���е�ֵת��Ϊ��ͼҪ�ض��󲢴洢��list��
	*/
	this->list=new Ipe_LinkList<Ipe_Plane>();
	Ipe_Lines* lines=new Ipe_Lines();//ֱ�߼�����
	Ipe_Bazeir* bazeir=new Ipe_Bazeir();//���������߶���
	route->currentpoint=route->pointheadler;
	//Ipe_Point2D* origin=new Ipe_Point2D(0,0);//�������
	Ipe_Plane* plane=new Ipe_Plane();//�½����ʵ��
	while(route->currentpoint->nextpoint!=NULL)//����㿪ʼ����ʼstate=0����ʾ��ȷ����������ֱ�߼��ϻ��Ǳ��������߼���
	{
		route->currentpoint=route->currentpoint->nextpoint;

		if(state==0)//��ʼ״̬Ϊ0
		{
			if(route->currentpoint->state==0)
			{
				originx=route->currentpoint->p0;
				originy=route->currentpoint->p1;
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==1)//m,l,h,c״̬(�ֱ��Ӧ0��1��2��3��
			{
				
				state=1;
				lines->addpoint(originx,originy,0);//������
				//printf("\n����·�����:%d,%d\n",originx,originy);
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1,1);//��ӵ�ǰ��

				//printf("ȷ����һ��ֱ�߼���״̬\n");
				//printf("���·��������һ����\n");
				//printf("���:%f %f\n��һ����:%f %f ",originx,originy,route->currentpoint->p0,route->currentpoint->p1);

				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==3)//��������������
			{
				//printf("ȷ����һ�����߼���״̬\n");
				state=2;
				bazeir->addpoint(originx,originy,-1,-1,-1,-1,0);
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5,3);
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
		}

		if(state==1)//����ֱ�߼�
		{
			if(route->currentpoint->state==1)//����Ϊlint to
			{
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1,1);//����ֱ�ߵ���ӽ�ȥ

				//printf("����ֱ��·����%f %f\n",route->currentpoint->p0,route->currentpoint->p1);

				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==3)//����Ϊc ��ʱ,������ֱ����ӽ�list��,Ȼ���ͷŲ����·���lines����,Ϊ�´�����׼��
			{
				plane->getlist()->add(lines);
				plane->addgraphiccellcount();
				GraphicsCellCount++;
				//delete lines;
				lines=new Ipe_Lines();//�·���ֱ�߼�����,Ϊ�´���׼��
				bazeir->addpoint(currentx,currenty,-1,-1,-1,-1,0);//������߼������
				originx=currentx;
				originy=currenty;
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5,3);
				//��ӵ�ǰ��
				state=2;//�ı�״̬Ϊ���ߴ���
				continue;
			}
			else if(route->currentpoint->state==2)//����Ϊh
			{
				lines->addpoint(originx,originy,2);//������(·���պ�)
#ifdef debug
				printf("ֱ������h����,����յ�%f  %f \n",originx,originy);
#endif
				plane->getlist()->add(lines);//��һ������ֱ��·�����ϼ�������
				plane->addgraphiccellcount();
				plane->setplane();
				lines=new Ipe_Lines();
				if(route->currentpoint->nextpoint->state!=0)//���h�����һ���㲻�����
				{
					list->add(plane);
					plane=new Ipe_Plane();
					GraphicsCellCount++;
				}
				state=3;
				continue;
			}
		}

		if(state==2)//�������߼�
		{
			if(route->currentpoint->state==1)//����Ϊlint to
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
			else if(route->currentpoint->state==3)//����Ϊc
			{
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5,3);
				currentx=route->currentpoint->p4;
				currenty=route->currentpoint->p5;
			}
			else if(route->currentpoint->state==2)//����Ϊh
			{
				bazeir->addpoint(originx,originy,-1,-1,-1,-1,2);
#ifdef debug
				printf("����hָ��,������%f %f \n",originx,originy);
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

		if(state==3)//���¿�ʼ·��
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
		if(state==0)//��һ��ȷ��״̬��line to
		{
			if(route->currentpoint->state==1)
			{
				printf("ȷ����һ��ֱ�߼���״̬\n");
				state=1;
				lines->addpoint(originx,originy);//������
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1);//��ӵ�ǰ��
				printf("���·��������һ����\n");
				printf("���:%f %f\n��һ����:%f %f ",originx,originy,route->currentpoint->p0,route->currentpoint->p1);
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==3)
			{
				printf("ȷ����һ�����߼���״̬\n");
				state=2;
				bazeir->addpoint(originx,originy,-1,-1,-1,-1);
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5);
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
				continue;
			}
			else if(route->currentpoint->state==0)
			{
				Ipe_Point2D* origin=new Ipe_Point2D(route->currentpoint->p0,route->currentpoint->p1);//�洢���
				currentx
			}
			
		}
		if (state==1)//��ǰ�������ֱ��·����
		{
			if(route->currentpoint->state==1)//����Ϊlint to
			{
				lines->addpoint(route->currentpoint->p0,route->currentpoint->p1);//����ֱ�ߵ���ӽ�ȥ
				printf("����ֱ��·����%f %f\n",route->currentpoint->p0,route->currentpoint->p1);
				currentx=route->currentpoint->p0;
				currenty=route->currentpoint->p1;
			}
			else if(route->currentpoint->state==3)//����Ϊc ��ʱ,������ֱ����ӽ�list��,Ȼ���ͷŲ����·���lines����,Ϊ�´�����׼��
			{
				list->add(lines);
				GraphicsCellCount++;
				//delete lines;
				lines=new Ipe_Lines();//�·���ֱ�߼�����,Ϊ�´���׼��
				bazeir->addpoint(currentx,currenty,-1,-1,-1,-1);//������߼������
				originx=currentx;
				originy=currenty;
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5);
				//��ӵ�ǰ��
				state=2;//�ı�״̬Ϊ���ߴ���
				continue;
			}
			else//����Ϊh
			{
				lines->addpoint(originx,originy);//������(·���պ�)
				list->add(lines);//��һ������ֱ��·�����ϼ�������
				GraphicsCellCount++;
				state=3;
				continue;
			}
		}
		if (state==2)//��ǰ�����������·����
		{
			if(route->currentpoint->state==1)//����Ϊlint to
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
			else if(route->currentpoint->state==3)//����Ϊ c
			{
				bazeir->addpoint(route->currentpoint->p0,route->currentpoint->p1,route->currentpoint->p2,route->currentpoint->p3,route->currentpoint->p4,route->currentpoint->p5);
				currentx=route->currentpoint->p4;
				currenty=route->currentpoint->p5;
			}
			else//����Ϊh
			{
				bazeir->addpoint(originx,originy,-1,-1,-1,-1);
				list->add(bazeir);
				GraphicsCellCount++;
				state=3;
				continue;
			}
		}
		if(state==3)//֮ǰ����Ϊh
		{
			
		}
	}
	*/
Ipe_PdfPath::~Ipe_PdfPath(void)
{
	delete list;
	printf("Ipe_PdfPath�����ͷ�\n");
}

void Ipe_PdfPath::printfPath()
{
	printf("������path���������\n");
	printf("��·������ɫ�ռ�Ϊ:%d",this->getcolorspace());
	Ipe_node<Ipe_Plane>* p=list->headler;
	//p->t->printPoint();
	printf("����ѭ��\n");
	while(p->next!=NULL)
	{
		p->next->t->printPoint();//����ת��
		p=p->next;
	}
	/*
	if(this->existclip!=0)
	{
		printf("���ڲü�·��:%d\n",this->existclip);
		Ipe_node<Ipe_GraphicCell>* q=cliplist->headler;
		while(q->next!=NULL)
		{
			printf("�������·���ĵ�\n");
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

int Ipe_PdfPath::getcolorspace()//��ȡ��ɫ�ռ�
{
	return this->colorspace;//��¼����һ����ɫ�ռ�(����չ) 1-G 2-g 3-RG 4-rg
}

Ipe_Color Ipe_PdfPath::getcolor()//ȡ����ɫ
{
	return this->color;
}

int Ipe_PdfPath::getdrawingmethord()//ȡ�û��Ʒ���
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