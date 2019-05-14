#include "Ipe_PdfDocument.h"
#include "Extract.h"
#include "FreeImage.h"

#include <sstream>
using namespace std;

string itstr(int num)
{
	stringstream ss;
    ss<<num; 
	string s1 = ss.str();
	return s1;
}

Ipe_PdfDocument::Ipe_PdfDocument(void)
{
}
Ipe_PdfDocument::Ipe_PdfDocument(const char* path)//��ʼ���ļ�
{
	this->PageCount=0;
	this->list=new Ipe_LinkList<Ipe_PdfPage>();
	float zoom,rotate;
	int page_number=0,page_count;
	fz_context *ctx;
	fz_document *doc;
	fz_pixmap *pix;
	fz_page *page;
	fz_matrix ctm;
	fz_rect rect;
	fz_device* dev;
	int x,y,j;
	
	struct zblrouteset *getline=(struct zblrouteset *)malloc(sizeof(struct zblrouteset));
	getimages=(struct zimages*)malloc(sizeof(zimages));
	ctx=fz_new_context(NULL,NULL,FZ_STORE_UNLIMITED);//��ʼ��context


	doc= fz_open_document(ctx,(char*)path);//��ȡPDF�ļ�����ȡ��������Ϣ����fz_document��Ľṹ����

	page_number=fz_count_pages(doc);

	cout<<"page_number:"<<page_number<<endl;
	
	for (int i=0;i<page_number;i++)
	{
		printf("///////////pagecount:%d\n",this->PageCount);
		page=fz_load_page(doc,i);//����ҳ������
		rect=fz_bound_page(doc,page);//��ȡҳ���rectangle����
		this->rect=rect;
		ctm.a=1;
		ctm.b=0;
		ctm.c=0;
		ctm.d=1;
		ctm.e=0;
		ctm.f=0;
		pix=fz_new_pixmap(ctx,fz_find_device_colorspace(ctx,"DeviceRGB"),rect.x1-rect.x0,rect.y1-rect.y0);
		fz_clear_pixmap_with_value(ctx,pix,0xFF);//����������Ϊ��ɫ
		//fz_clear_pixmap(ctx,pix);
		dev=fz_new_draw_device(ctx,pix);//������ͼ�豸
		fz_run_page(doc,page,dev,ctm,0);//��ҳ����Ƶ�pixmap���ɵĻ�ͼ�豸��
		//��ȡʸ������
		fz_return_line(getline);
		//��ȡimages
		fz_return_images(getimages);
		Ipe_PdfPage* pdfpage=new Ipe_PdfPage(getline);
		pdfpage->setrect(rect);
		this->list->add(pdfpage);
		this->PageCount++;	
	}
}

Ipe_PdfDocument::~Ipe_PdfDocument(void)
{
	delete list;
	printf("Document�ͷ�����");
}
void Ipe_PdfDocument::printfdocument()
{
	int count=0;
	printf("������document���������\n");
	Ipe_node<Ipe_PdfPage>* p=list->headler;
	while(p->next!=NULL)
	{
		printf("��%dҳ___________________\n",count);
		p->next->t->printpage();//����ת��
		p=p->next;
		count++;
	}
}


void Ipe_PdfDocument::writeSVG(char* path)
{
}

Ipe_LinkList<Ipe_PdfPage>* Ipe_PdfDocument::getlist()
{
	return list;
}

fz_rect Ipe_PdfDocument::getrect()
{
	return rect;
}

void Ipe_PdfDocument::generatepictures(char* path)
{
	cout<<"��PDF�ļ���"<<getimages->count<<"��ͼƬ"<<endl;
	getimages->currentimage=getimages->head;
	
	//ʹ��freeimage
	FreeImage_Initialise(TRUE);//freeimage��ʼ��
	string spath=path;
	for(int i=0;i<getimages->count;i++)
	{
		getimages->currentimage=getimages->currentimage->next;
		cout<<"w:"<<getimages->currentimage->w<<" "<<"h:"<<getimages->currentimage->h<<" "<<"n:"<<getimages->currentimage->n<<endl;
		int w=getimages->currentimage->w;
		int h=getimages->currentimage->h;
		int n=getimages->currentimage->n;
		unsigned char* data=getimages->currentimage->data;
		
		
		string filename=itstr(i+1)+".png";//ͼƬ��
		cout<<"ͼƬ��"<<filename<<endl;
		
		char* title=(char*)filename.c_str();
		
		string filepath=spath+filename;//����·��+ͼƬ��
		cout<<"·��:"<<filepath<<endl;
		const char* fpath=filepath.c_str();
		
		FREE_IMAGE_FORMAT fif = FIF_PNG;//ָ��ͼƬ��ʽ,�˴�����ΪBMP��ʽ
		
		//FIBITMAP *bitmap=FreeImage_Allocate(w,h,n*8,0x000000FF,0x0000FF00,0x00FF0000);
		FIBITMAP *bitmap=FreeImage_Allocate(w,h,n*8);//����һ���µ��ڴ�,ָ����,��,�������
		unsigned char *bits = FreeImage_GetBits(bitmap);//��ȡָ��
		/*
		int width = FreeImage_GetWidth(bitmap);
		int height = FreeImage_GetHeight(bitmap);
		unsigned int byte_per_pixel = FreeImage_GetLine(bitmap) / width;
		cout<<width<<" "<<height<<" "<<byte_per_pixel<<endl;
		*/
		int cur=0;
		for (int x = 0; x <w*h; ++x)//��������������صĸ��� ��bgra��˳��
		{
        // �����Ӧ��������ÿ�����ص��ֽ���
			int r=0,rp=0;
			for(int j=0;j<n;j++)
			{
				if(j==0)
				{
					r=data[cur];
					rp=cur;
					bits[cur]=data[cur];
				}
				else if(j==2)
				{
					bits[cur]=r;
					bits[rp]=data[cur];
				}
				else
				{
					bits[cur]=data[cur];
				}	
				cur++;
			}
			//cout<<endl;
		}
		//bitmap = FreeImage_RotateEx(bitmap, 180.0, 0, 0,w/2 ,h/2 , TRUE);//��ת
		FreeImage_FlipVertical(bitmap);//��ˮƽ�Ὣ���봹ֱ��ת
		/*
		cur=0;
		for (int x = 0; x <w*h; ++x)//��������������صĸ��� ��bgra��˳��
		{
        // �����Ӧ��������ÿ�����ص��ֽ���
			for(int j=0;j<n;j++)
			{
				cout<<(int)bits[cur]<<" ";
				cur++;
			}
			cout<<endl;
		}
		*/
		FreeImage_Save(fif, bitmap, fpath, PNG_DEFAULT);//����ļ�
		
	}
	 FreeImage_DeInitialise();//freeimage������ʼ��
	 
}

//ʧ�ܵ�ʹ��libpng
/*
string spath=path;
	for(int i=0;i<getimages->count;i++)
	{
		getimages->currentimage=getimages->currentimage->next;
		cout<<"w:"<<getimages->currentimage->w<<" "<<"h:"<<getimages->currentimage->h<<" "<<"n:"<<getimages->currentimage->n<<endl;
		int w=getimages->currentimage->w;
		int h=getimages->currentimage->h;
		int n=getimages->currentimage->n;
		unsigned char* data=getimages->currentimage->data;

		string filename=itstr(i)+".png";//ͼƬ��
		char* title=(char*)filename.data();
		string filepath=spath+filepath;//����·��+�ļ���
		const char* fpath=filepath.c_str();
		FILE *fp = NULL;//���ļ�
		fp = fopen(fpath, "wb");
		//����libpng
		png_structp png_ptr = NULL;
		png_infop info_ptr = NULL;
	    png_bytep row = NULL;
		

		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);//��ʼ��д�ṹ
		info_ptr = png_create_info_struct(png_ptr);//��ʼ����Ϣ�ṹ

		png_init_io(png_ptr, fp);//��ʼ��IO
		//�����ļ��Ļ�����Ϣ
		png_set_IHDR(png_ptr, info_ptr,w,h,n*8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
		

		if (title != NULL) 
		{
         png_text title_text;
         title_text.compression = PNG_TEXT_COMPRESSION_NONE;
         title_text.key = "Title";
         title_text.text = title;
         png_set_text(png_ptr, info_ptr, &title_text, 1);
        }

		png_write_info(png_ptr, info_ptr);
		row = (png_bytep)malloc(4 * w * sizeof(png_byte));
		int cur=0;
		for (int x = 0; x <h; ++x)//��������������صĸ���
		{
        // �����Ӧ��������ÿ�����ص��ֽ���
			for(int y=0;y<w;y++)
			{
				for(int z=0;z<4;z++)
				{
					row[cur]=data[cur];
					cur++;
				}
			}
			png_write_row(png_ptr, row);//д��һ��
			//cout<<endl;
		}
		png_write_end(png_ptr, NULL);//д�����
	}
*/

void Ipe_PdfDocument::testfreeimage()
{
	const char* imageFile = "C:\\Users\\�Բ���\\Desktop\\��ɫ.png";
	// ͼƬ��ʽ
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	// ��ȡͼƬ��ʽ
	fif = FreeImage_GetFileType(imageFile);

	FIBITMAP *bitmap = NULL;
	bitmap = FreeImage_Load(fif, imageFile, PNG_DEFAULT);

	int width = FreeImage_GetWidth(bitmap);
	int height = FreeImage_GetHeight(bitmap);
	unsigned int byte_per_pixel = FreeImage_GetLine(bitmap) / width;
	cout<<width<<" "<<height<<" "<<byte_per_pixel<<endl;

	unsigned char *bits = FreeImage_GetBits(bitmap);

	int cur=0;
	for (int x = 0; x < width*height; ++x){
        // �����Ӧ��������ÿ�����ص��ֽ���:4
		for(int y=0;y<4;y++)
		{
			cout<<(int)bits[cur]<<" ";
			cur++;
		}
		cout<<endl;
    }
	FreeImage_Unload(bitmap);
	FreeImage_DeInitialise();
}