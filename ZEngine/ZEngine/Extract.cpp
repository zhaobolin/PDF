#include "Extract.h"

Extract::Extract(void)
{

}


Extract::~Extract(void)
{
}

void Extract::GetStructureFromPDF(char* input)
{
	fz_context *ctx;
	fz_document *doc;
	fz_page *page;
	fz_rect rect;
	fz_matrix ctm;
	fz_device* dev;
	fz_pixmap *pix;
	struct zblrouteset *getline=(struct zblrouteset *)malloc(sizeof(struct zblrouteset));
	
	ctx=fz_new_context(NULL,NULL,FZ_STORE_UNLIMITED);//��ʼ��context
	doc= fz_open_document(ctx,input);//��ȡPDF�ļ�����ȡ��������Ϣ����fz_document��Ľṹ����
	page=fz_load_page(doc,0);//����ҳ������
	rect=fz_bound_page(doc,page);//��ȡҳ���rectangle����
	ctm.a=1;
	ctm.b=0;
	ctm.c=0;
	ctm.d=1;
	ctm.e=0;
	ctm.f=0;
	pix=fz_new_pixmap(ctx,fz_find_device_colorspace(ctx,"DeviceRGB"),rect.x1-rect.x0,rect.y1-rect.y0);
	fz_clear_pixmap_with_value(ctx,pix,0xFF);//����������Ϊ��ɫ
	dev=fz_new_draw_device(ctx,pix);//������ͼ�豸
	fz_run_page(doc,page,dev,ctm,0);//��ҳ����Ƶ�pixmap���ɵĻ�ͼ�豸��
	//��ȡ����
	fz_return_line(getline);
	/*
		��ӡ���ṹ���ȡ������
		printf("\n·��������%d\n",getline->count);
		for (int z=0;z<getline->count;z++)
		{
			printf("��%d��·��,·������%d,����%d\n",z,getline->set[z].type,getline->set[z].countpoint);
			printf("���Ʒ���:%d �߿�:%.2f\n",getline->set[z].drawingmethord,getline->set[z].linewidth);
			printf("ɫ�ʿռ�:%d\n",getline->set[z].colorspace);
			printf("��ɫ:%.3f %.3f %.3f \n",getline->set[z].color[0],getline->set[z].color[1],getline->set[z].color[2]);
			for (int j=0;j<getline->set[z].countpoint;j++)
			{
				printf("%.2f %.2f %.2f %.2f %.2f %.2f %.0f\n",getline->set[z].points[j][0],getline->set[z].points[j][1],getline->set[z].points[j][2],getline->set[z].points[j][3],getline->set[z].points[j][4],getline->set[z].points[j][5],getline->set[z].points[j][6]);
			}
		}
	*/
	this->vectorset=new VectorSet(getline);
}
VectorSet* Extract::getvectorset()
{
	return this->vectorset;
}

void Extract::CreateDocument(char* filepath)
{
	VectorSet* vectorset;
	int vectorcount,i,j,k;
	ofstream fout;
	fout.open(filepath);
	vectorset=this->getvectorset();
	vectorcount=vectorset->getcount();
	//printf("��·������:%d\n",vectorcount);
	fout<<vectorcount<<endl;
	for (i=0;i<vectorcount;i++)
	{
		//printf("��%d��·����ĸ���:%d\n",i,vectorset->getvectorset()[i]->getcountpoint());
		fout<<vectorset->getvectorset()[i]->getcountpoint()<<endl;
		//printf("·������:%d",vectorset->getvectorset()[i]->gettype());
		fout<<vectorset->getvectorset()[i]->gettype()<<endl;
		//printf("�߿�:%f\n",vectorset->getvectorset()[i]->getlinewidth());
		fout<<vectorset->getvectorset()[i]->getlinewidth()<<endl;
		//printf("��ɫ�ռ�:%d\n",vectorset->getvectorset()[i]->getcolorspace());
		fout<<vectorset->getvectorset()[i]->getcolorspace()<<endl;
		//printf("��ɫ:%.2f %.2f %.2f\n",vectorset->getvectorset()[i]->getcolor()[0],vectorset->getvectorset()[i]->getcolor()[1],vectorset->getvectorset()[i]->getcolor()[2]);
		fout<<vectorset->getvectorset()[i]->getcolor()[0]<<" "<<vectorset->getvectorset()[i]->getcolor()[1]<<" "<<vectorset->getvectorset()[i]->getcolor()[2]<<endl;
		//printf("���Ʒ���:%d\n",vectorset->getvectorset()[i]->getdrawingmethord());
		fout<<vectorset->getvectorset()[i]->getdrawingmethord()<<endl;
		for(j=0;j<vectorset->getvectorset()[i]->getcountpoint();j++)
		{
			for(k=0;k<7;k++)
			{
				//printf("%.2f ",vectorset->getvectorset()[i]->getpoints()[j][k]);
				fout<<vectorset->getvectorset()[i]->getpoints()[j][k]<<" ";
			}
			//printf("\n");
			fout<<endl;
		}
	}
	fout.close();
}