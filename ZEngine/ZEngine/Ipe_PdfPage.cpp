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

Ipe_PdfPage::Ipe_PdfPage(zblrouteset* routeset)//��ʼ�������ÿҳ������
{
	int i=0;
	this->graphiccellcount=routeset->count;
	this->list=new Ipe_LinkList<Ipe_PdfElement>();
	routeset->currentstack=routeset->stackheadler;
	while(routeset->currentstack->nextstack!=NULL)
	{
		routeset->currentstack=routeset->currentstack->nextstack;//���������ջ
		recursion(this->list,routeset->currentstack,NULL,NULL,0);//����Ƕ�׵���
	}
	//����ҳ������е�,����ת�þ��������
	this->maketransform();
}

void Ipe_PdfPage::maketransform()//�������о���ת�þ���ĵ�,����ת������
{
	Ipe_node<Ipe_PdfElement>* current;
	current=this->list->headler;
	crect.x0=0;
	crect.x1=0;
	crect.y0=0;
	crect.y1=0;
	while(current->next!=NULL)//����ջ
	{
		current=current->next;
		if(current->t->getelementtype()==1)//����Ϊ1,Ϊͼ�β���
		{
			Ipe_PdfStack* stack;
			stack=dynamic_cast<Ipe_PdfStack*>(current->t);//��̬����ת��
			Ipe_node<Ipe_PdfPath>* pathlist=stack->getpathlist()->headler;//��ȡPath
			int existcm=stack->getexistcm();
			if(existcm==1)//����ת�þ���
			{
				float cm[6];
				stack->setexistcm(0);
				while(pathlist->next!=NULL)//����ջ��·��
				{
					pathlist=pathlist->next;
					Ipe_node <Ipe_Plane>* cplane=pathlist->t->getPlane()->headler;//ȡ�õ�ͼҪ������ͷ
					while(cplane->next!=NULL)//������ͼҪ������,��������,��
					{
						cplane=cplane->next;
						Ipe_Plane *plane=cplane->t;
						if(plane->getisplane())//�жϵ�ͼҪ������,�Ƿ��·��
						{
							//�������·����һ������ֱ��/���߼�
							bool firsttime=true;
							double beginx,beginy;
							Ipe_node<class Ipe_GraphicCell>*graphiccell=plane->getlist()->headler;
							for (int j=0;j<plane->getgraphicellcount();j++)
							{
								graphiccell=graphiccell->next;
								if (graphiccell->t->gettype()==1)//0-���� 1-ֱ�߼� 2-���߼�
								{
									Ipe_Lines * lines=dynamic_cast<Ipe_Lines*>(graphiccell->t);//����ת��Ϊlinesֱ�߼�
									//ֱ�߼��ı���
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
									Ipe_Bazeir* bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell->t);//����ת��Ϊ���������߼�
									//���߼��ı���
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
									printf("����,��ʼ������\n");
								}
							}
						}
						else//�����·��
						{
							Ipe_node<class Ipe_GraphicCell>* cgc=plane->getlist()->headler;
							while(cgc->next!=NULL)//����·���е�ֱ�߼������߼�
							{
								cgc=cgc->next;
								Ipe_GraphicCell* graphiccell=cgc->t;
								if(graphiccell->gettype()==1)//1-ֱ�߼� 
								{
									Ipe_Lines * lines=dynamic_cast<Ipe_Lines*>(graphiccell);//����ת��Ϊlinesֱ�߼�
									//ֱ�߼��ı���
									Ipe_node<Ipe_Point2D>* points=lines->getlist()->headler;
									while (points->next!=NULL)
									{
										points=points->next;
										points->t->setx(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4]));
										points->t->sety(transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5]));
									}
								}
								else if(graphiccell->gettype()==2)//2-���߼�
								{
									Ipe_Bazeir* bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell);//����ת��Ϊ���������߼�
									//���߼��ı���
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
								else//0-����
								{
									printf("δ��ʼ����GraphicCell����\n");
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
	printf("Ipe_PdfPage�ͷ�����\n");
}

Ipe_LinkList<Ipe_PdfElement>* Ipe_PdfPage::getelement()
{
	return this->list;
}

void Ipe_PdfPage::printpage()
{
	int count=0;
	printf("������page���������\n");
	Ipe_node<Ipe_PdfElement>* p=list->headler;
	printf("����ѭ��\n");
	while(p->next!=NULL)
	{
		//p->next->t->printfPath();//����ת��
		printf("��ҳ��%d��ͼ��״̬ջ:+++++++++++++++++++++\n",count);
		Ipe_PdfStack* stack=dynamic_cast<Ipe_PdfStack*>(p->next->t);
		printf("���:%d\n",stack->getgrade());
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

void Ipe_PdfPage::pagetoSVG(char* path)//���һҳΪsvg
{
	int i=0,j=0,k=0,l=0,m=0,n=0,o=0,p=0,shadowid=0;
	Ipe_node<Ipe_PdfElement>* pointer=this->list->headler;//PDFԪ�ص�ͷָ��
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
	//fout1.open("C:\\Users\\�Բ���\\Desktop\\�Ա�����.txt");
	//д�ļ�ͷ
	fout<<"<?xml version=\"1.0\" standalone=\"no\"?>\n\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n <svg width=\"100%\" height=\"100%\" version=\"1.1\" viewBox=\" "<<this->rect.x0<<" "<<this->rect.y0<<" "<<this->rect.x1<<" "<<this->rect.y1<<"\"";
	fout<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;
	//for (i=0;i<this->graphiccellcount;i++)//��ÿ��PDFջ
	while(pointer->next!=NULL)
	{
		pointer=pointer->next;//pointer����ָ��stack�����ͷ��
		stack=dynamic_cast<Ipe_PdfStack*>(pointer->t);//��̬ǿ������ת��
		if(pointer->t->getelementtype()==1)//pdfҳ��Ԫ�ص�����Ϊpath PS:���ж�ͼƬ������
		{
			//printf("��һ�βü�·��״̬:%d\n",stack->getexistclip());
			if(stack->getexistclip()>0)//���ڲü�·��
			{
				//��Ӳü�·��
				string clippath="<defs>";
				o++;
				clippath=clippath+"<clipPath id=\"c-star"+toString(o)+"\">"+"\n";
				clippath=clippath+"<path d=\"";
				clipgraphiccell=stack->getcliplist()->headler;
				while(clipgraphiccell->next!=NULL)//����ֱ�������߼���
				{
					clipgraphiccell=clipgraphiccell->next;
					if(clipgraphiccell->t->gettype()==1)//ֱ�߼�
					{
						lines=dynamic_cast <Ipe_Lines*>(clipgraphiccell->t);//ת�ͳ�Ϊֱ�߼���
						Ipe_node<Ipe_Point2D>* points=lines->getlist()->headler;
						//clippath=clippath+"<clipPath id=\"c-star0"+"\">"+"\n";
						//clippath=clippath+"<polygon points=\"";
						for(n=0;n<lines->getnum();n++)//������
						{
							points=points->next;
							if(points->t->getstate()==0)//m,l,h,c״̬(�ֱ��Ӧ0��1��2��3��
							{
								clippath=clippath+"M"+toString(points->t->getx())+" "+toString((this->getrect().y1-this->getrect().y0)-points->t->gety())+" ";//����Ҫ���д���SVG�ļ�����ҳ�����Ͻ���Ϊ����ԭ��ģ�����Ҫ��y�ᷴ��
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
					else //���߼�
					{
						bazeir=dynamic_cast<Ipe_Bazeir*>(clipgraphiccell->t);//ת�ͳ�Ϊ���߼���
						Ipe_node<Ipe_Point2D>* points=bazeir->getlist()->headler;
						//clippath=clippath+"<clipPath id=\"c-star"+toString(m)+"\">"+"\n";
						points=points->next;
						clippath=clippath+"M"+toString(points->t->getx())+" "+toString((this->getrect().y1-this->getrect().y0)-points->t->gety())+" ";//�������������
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
			if(stack->getshadowtype()!=0)//������Ӱ,����ɫ ���ø�ջ��SVG����ɫ����
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
					//������Խ���Ķ���
					//���е�ǰ�������������

				}
			}
			*/
			if(stack->getexistclip()!=0)//ָ���ü�·�����
			{
				fout<<"<g style=\"clip-path: url(#c-star"<<toString(o)<<+");\">\n";
				//printf("+++++++++++++++++++++++++++++++++++++++++++++��ǰ·���ڲü�·����\n");
			}
			currentpdfpath=stack->getpathlist()->headler;//��ȡջ��path���ϵ�ͷ���
#ifdef debug
			printf("ջ����%d��·��\n",stack->getcountpath());
#endif
			//printf("ջ��·������:%d\n",stack->getcountpath());
			for(l=0;l<stack->getcountpath();l++)//����ջ��·��
			{
				currentpdfpath=currentpdfpath->next;
				pdfpath=currentpdfpath->t;//��ȫ������ת��
				//��ȡÿ��path����ɫ,�߿����Ϣ,����Ϊ����ÿ���߼���SVG����,ÿ��path�����ÿ��SVGԪ�ض���һ�������Խ�β
				string attribute="\" style=\"";
				//������ɫ
				Ipe_Color color=pdfpath->getcolor();
				if(pdfpath->getdrawingmethord()<5)//������������ߵ����
				{
					if(pdfpath->getdrawingmethord()==1||pdfpath->getdrawingmethord()==-1||pdfpath->getdrawingmethord()==4)//����ͿĨ·��  ���Ʒ��� 1-S 2-f* 3-f/F 4-s 5-B 6-B* 7-b 8-b*
					{
						attribute=attribute+"fill:none;stroke:";
						if(pdfpath->getcolorspace()==3||pdfpath->getcolorspace()==4)//��ΪRGB�ռ�
						{
							attribute=attribute+"rgb(";
							attribute=attribute+toString(color.getr())+","+toString(color.getg())+","+toString(color.getb())+"); stroke-width:";
							attribute=attribute+toString(pdfpath->getlinewidth());//�߿�
						}
						else//�Ҷȿռ�
						{
							if(color.getG()==0)//0�Ǻ�ɫ 1�ǰ�ɫ
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
					else//���
					{
						attribute=attribute+"fill:";
						if(pdfpath->getcolorspace()==3||pdfpath->getcolorspace()==4)//�����ΪRGB�ռ�
						{
							attribute=attribute+"rgb(";
							attribute=attribute+toString(color.getr())+","+toString(color.getg())+","+toString(color.getb())+"); ";
						}
						else//�����Ϊ�ڰ�
						{
							if(color.getG()==0)//0�Ǻ�ɫ 1�ǰ�ɫ
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
					if(pdfpath->getcolorspace()==3||pdfpath->getcolorspace()==4)//��ΪRGB�ռ�
					{
						attribute=attribute+"rgb(";
						attribute=attribute+toString(color.getr())+","+toString(color.getg())+","+toString(color.getb())+"); stroke-width:";
					}
					else//�Ҷȿռ�
					{
						if(color.getG()==0)//0�Ǻ�ɫ 1�ǰ�ɫ
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
				else//����Ϳɫ��ʽ����
				{
					Ipe_Color scolor=pdfpath->getscolor();//��ȡstroke����ɫ
					attribute=attribute+"fill:";
					if(pdfpath->getcolorspace()==3||pdfpath->getcolorspace()==4)//�����ΪRGB�ռ�
					{
						attribute=attribute+"rgb(";
						attribute=attribute+toString(color.getr())+","+toString(color.getg())+","+toString(color.getb());
					}
					else//�����Ϊ�ڰ�
					{
						if(color.getG()==0)//0�Ǻ�ɫ 1�ǰ�ɫ
						{
							attribute=attribute+"black;";
						}
						else
						{
							attribute=attribute+"white;";
						}
					}
					attribute+="); stroke:";
					if(pdfpath->getscolorspace()==3||pdfpath->getscolorspace()==4)//�����ΪRGB�ռ�
					{
						attribute=attribute+"rgb(";
						attribute=attribute+toString(scolor.getr())+","+toString(scolor.getg())+","+toString(scolor.getb())+");";
					}
					else//�����Ϊ�ڰ�
					{
						if(scolor.getG()==0)//0�Ǻ�ɫ 1�ǰ�ɫ
						{
							attribute=attribute+"black;";
						}
						else
						{
							attribute=attribute+"white;";
						}
					}
					attribute=attribute+" stroke-width:";
					attribute=attribute+toString(pdfpath->getlinewidth());//�߿�
				}
				
				if(stack->getca()!=1)//���͸���Ȳ�Ϊ1,����͸��������
				{
					attribute=attribute+";opacity:"+toString(stack->getca());
				}
				
				attribute=attribute+"\"";
				//�ж��Ƿ����ת�þ���
				/*
				if(stack->getexistcm()>0)
				{
					attribute=attribute+" transform=\"matrix("+toString(stack->getmatrix()[0])+" "+toString(stack->getmatrix()[1])+" "+toString(stack->getmatrix()[2])+" "+toString(stack->getmatrix()[3])+" " +toString(stack->getmatrix()[4])+" "+toString((this->getrect().y1-this->getrect().y0)-stack->getmatrix()[5])+")\"";//(this->getrect().y1-this->getrect().y0)-  //�˴��д���ȶ,�任ԭ��֮������任
				}
				
				if(stack->getexistclip()==2)//��ż�ü�·��
				{
					attribute=attribute+" fill-rule=\"evenodd\" clip-rule=\"evenodd\"";
				}
				*/
				attribute=attribute+"/>\n";
				//cout<<"���Դ�׺:"<<attribute<<endl;
				//graphiccell=pdfpath->getGraphicCell()->headler;
				
				
				//����������path�����б��ж��Ƿ���·��
				plane=pdfpath->getPlane()->headler;
				while(plane->next!=NULL)//�����е�ÿ��Ԫ�ؽ��б���
				{
					plane=plane->next;
					//printf("��������Ԫ��");
					if(plane->t->getisplane()==false)//����Ϊ�պϵ���,����Ϊһϵ��·����
					{
						graphiccell=plane->t->getlist()->headler;
						//printf("plane�ڲ�Graphiccell������:%d\n",plane->t->getgraphicellcount());
						for (j=0;j<plane->t->getgraphicellcount();j++)
						{
							graphiccell=graphiccell->next;
							if (graphiccell->t->gettype()==1)//0-���� 1-ֱ�߼� 2-���߼�
							{
								lines=dynamic_cast <Ipe_Lines*>(graphiccell->t);//ת�ͳ�Ϊֱ�߼���
								Ipe_node<Ipe_Point2D>* points=lines->getlist()->headler;
								fout<<"<path d=\"";//һ��·��
								char order;
								for(k=0;k<lines->getnum();k++)
								{
		//#ifdef debug
									//printf("%f %f\n",this->getrect().y0,this->getrect().y1);
		//#endif
									points=points->next;
									switch (points->t->getstate())//m,l,h,c״̬(�ֱ��Ӧ0��1��2��3��
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
										fout<<order<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";//����Ҫ���д���SVG�ļ�����ҳ�����Ͻ���Ϊ����ԭ��ģ�����Ҫ��y�ᷴ��
										//fout1<<points->t->getx()<<","<<points->t->gety()<<"------"<<points->t->getx()<<","<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" \n";
									//}
									/*
									else //����ת�þ���
									{
										fout<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<","<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" ";
										//fout1<<points->t->getx()<<","<<points->t->gety()<<"------"<<transform(points->t->getx(),points->t->gety(),stack->getmatrix()[0],stack->getmatrix()[2],stack->getmatrix()[4])<<","<<(this->getrect().y1-this->getrect().y0)-transform(points->t->getx(),points->t->gety(),stack->getmatrix()[1],stack->getmatrix()[3],stack->getmatrix()[5])<<" \n";
									}
									*/
								}
								fout<<attribute;
								fout<<endl;
							}
							else//�������߼� �����ڸ������
							{
								bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell->t);//ת�ͳ�Ϊ���߼���
								Ipe_node<Ipe_Point2D>* points=bazeir->getlist()->headler;
								fout<<"<path d=\"";
								//printf("���������ߵ���:%d\n",bazeir->getnum());
								//printf("%s\n",attribute);
								if(bazeir->getnum()!=0)
								{
									points=points->next;
									fout<<"M"<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";//�������������
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
					else//��һ���պϵ���,��ʱ����SVG��ʱ��Ҫ����һ��������е����һ��·�������γ�һ����յ���
					{
						//printf("��һ���պϵ���\n");
						fout<<"<path d=\"";
						graphiccell=plane->t->getlist()->headler;
						bool firsttime=true;
						double beginx,beginy;
						//for (j=0;j<plane->t->getgraphicellcount();j++)
						while(graphiccell->next!=NULL)
						{
							graphiccell=graphiccell->next;
							if (graphiccell->t->gettype()==1)//0-���� 1-ֱ�߼� 2-���߼�
							{
								//printf("ֱ�߼�\n");
								lines=dynamic_cast <Ipe_Lines*>(graphiccell->t);//ת�ͳ�Ϊֱ�߼���
								Ipe_node<Ipe_Point2D>* points=lines->getlist()->headler;
								//printf("ֱ�߼��е�ĸ���:%d\n",lines->getnum());
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
											//printf("�����б�ע\n");
										}
										else
										{
											
										}
										*/
										order="M";
										beginx=points->t->getx();
										beginy=points->t->gety();
									}
									else // if(points->t->getstate()==1)//m,l,h,c״̬(�ֱ��Ӧ0��1��2��3��
									{
										order="L";
									}
									//printf("ջת�þ���״̬:%d\n",stack->getexistcm());
									if(stack->getexistcm()==0)
									{
										//printf("������ת�þ���\n");
										if(points->t->getstate()==2)
										fout<<order<<beginx<<" "<<(this->getrect().y1-this->getrect().y0)-beginy<<" ";
										else
										{
											fout<<order<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";//����Ҫ���д���SVG�ļ�����ҳ�����Ͻ���Ϊ����ԭ��ģ�����Ҫ��y�ᷴ��
											//cout<<order<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<endl;
										//fout1<<points->t->getx()<<","<<points->t->gety()<<"------"<<points->t->getx()<<","<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" \n";
									
										}
									}
									/*
									else //����ת�þ���
									{
										if(points->t->getstate()==2)//�պ�ָ��,�ص����
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
							else//�������߼� �����ڸ������
							{
								bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell->t);//ת�ͳ�Ϊ���߼���
								Ipe_node<Ipe_Point2D>* points=bazeir->getlist()->headler;
								points=points->next;
								if(stack->getexistcm()==0)
								{
									if(firsttime==true)
									{
										firsttime=false;
										fout<<"M"<<points->t->getx()<<" "<<(this->getrect().y1-this->getrect().y0)-points->t->gety()<<" ";//�������������
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

void Ipe_PdfPage::clipwithrect(cliprect *rect)//�ü�����
{
	if(rect->x0>rect->x1||rect->y0<rect->y1)
	{
		printf("���β��������ϱ�׼");
		return;
	}
	crect.x0=rect->x0;
	crect.x1=rect->x1;
	crect.y0=rect->y0;
	crect.y1=rect->y1;
	Ipe_node<Ipe_PdfElement>* current;
	current=this->list->headler;
	while(current->next!=NULL)//����ջ
	{
		current=current->next;
		if(current->t->getelementtype()==1)//����Ϊ1,Ϊͼ�β���
		{
			Ipe_PdfStack* stack;
			stack=dynamic_cast<Ipe_PdfStack*>(current->t);//��̬����ת��
			Ipe_node<Ipe_PdfPath>* pathlist=stack->getpathlist()->headler;//��ȡPath
			while(pathlist->next!=NULL)//����ջ��·��
			{
				pathlist=pathlist->next;
				Ipe_node <Ipe_Plane>* cplane=pathlist->t->getPlane()->headler;//ȡ�õ�ͼҪ������ͷ
				while(cplane->next!=NULL)//������ͼҪ������,��������,��
				{
					cplane=cplane->next;
					Ipe_Plane *plane=cplane->t;
					if(plane->getisplane())//�жϵ�ͼҪ������,�Ƿ��·��
					{
						//printf("������ü�����\n");
						Ipe_node<class Ipe_GraphicCell>* cgc=plane->getlist()->headler;
						//�������·����һ������ֱ��/���߼�,���вü��Լ��벿�ֱߵ���Ӳ���
						Ipe_LinkList<Ipe_GraphicCell>* list=plane->getlist();
						plane->setlist(clipplane(list,rect));//�����µ�ֱ�������߼�list
						//�������
						Ipe_node<class Ipe_GraphicCell> *p=plane->getlist()->headler->next;
						Ipe_Lines *k=dynamic_cast<Ipe_Lines*>(p->t);
						Ipe_node<Ipe_Point2D>*cp=k->getlist()->headler;
						/*printf("�ü����:\n");
						while(cp->next!=NULL)
						{
							cp=cp->next;
							printf("%f %f %d\n",cp->t->getx(),cp->t->gety(),cp->t->getstate());
						}	
						*/
					}
					else//�����·��
					{
						Ipe_node<class Ipe_GraphicCell>* cgc=plane->getlist()->headler;
						while(cgc->next!=NULL)//����·���е�ֱ�߼������߼�
						{
							cgc=cgc->next;
							Ipe_GraphicCell* graphiccell=cgc->t;
							if(graphiccell->gettype()==1)//1-ֱ�߼� 
							{
								Ipe_Lines * lines=dynamic_cast<Ipe_Lines*>(graphiccell);//����ת��Ϊlinesֱ�߼�
								//ֱ�߼��ı����ü�����
								Ipe_Lines* newlines=cliplines(lines,rect);//�����µĽڵ�ָ��
								delete lines;
								cgc->t=newlines;
								//printf("ֱ�߼��е������:%d\n",newlines->getnum());
								//printf("%f %f\n",newlines->getlist()->headler->next->t->getx(),newlines->getlist()->headler->next->t->gety());
							}
							else if(graphiccell->gettype()==2)//2-���߼�
							{
								Ipe_Bazeir* bazeir=dynamic_cast<Ipe_Bazeir*>(graphiccell);//����ת��Ϊ���������߼�
								//���߼��ı����ü�����
								//printf("�������߲ü�����\n");
								Ipe_Bazeir* newbazeir=clipbazeir(bazeir,rect);
								delete bazeir;
								cgc->t=newbazeir;
								//printf("new bazeir size:%d",newbazeir->getnum());
							}
							else//0-����
							{
								printf("δ��ʼ����GraphicCell����\n");
							}
						}
					}
				}
			}
		}
	}
	/*
	1.���ڵ�,�Ƿ����ֻ���Ƿ���������

	2.������:�������:
		ֱ��:
			��������,��ֹ������εĽ���,���ǽ��вü�,����ʹ�ñ���ü���,
			��ֱ�߽��б���,�����ⲿ,ȡ�ڲ�,���㽻��,����ֱ�ߵĲü�,���ڲ���յ�
			ֱ�߼���,ʹ�ñ߽���滻ԭ���Ķ˵�,֮�������ֱ�߼�������(����������)
		����:
			����㿪ʼ���б��� (״̬0)
			���ĸ����Ƶ㶼�ھ����ڲ�,�򲻽����޸�;
			�������˵���ڲ��ھ����ڲ���,��˵���ǿ�Խ����,����������,����ס���״̬(״̬1)
				״̬1��,��һ����������ȫ���ⲿ,��ɾ��������,������ȥ����,��ά��״̬
				ֱ�������ٴν���ü���������,��״̬��Ϊ��
			�����ڿ��Ƶ㲻�ڲü������ڵ��Ƕ˵��ڲü������ڵ�,���빫ʽ���в���(ȡһ
			Щ����в���)֮���Ƿ��ڲü������ڵĴ���ͬ��
	3.������:
		�����/���߲��ֲ���ü����ཻ����:��������,ʹ��Sutherland_Hodgman�㷨,���������߽���,PS:��������:�˻��߽�
		��������ȫ��Ϊֱ�����,���������ü�
		PS:���ܳ��ֵ����:�󲿷ֶ���ζ���ֻ��һС���ֱ��ü�,Ȼ��ʹ�ñ߽����(���ܵ��Ż���)
		
		�������β���Ϊ���߽ṹ:��?
	*/
}

