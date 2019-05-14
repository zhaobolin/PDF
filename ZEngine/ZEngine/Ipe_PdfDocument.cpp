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
Ipe_PdfDocument::Ipe_PdfDocument(const char* path)//初始化文件
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
	ctx=fz_new_context(NULL,NULL,FZ_STORE_UNLIMITED);//初始化context


	doc= fz_open_document(ctx,(char*)path);//读取PDF文件并提取出其中信息放入fz_document类的结构体中

	page_number=fz_count_pages(doc);

	cout<<"page_number:"<<page_number<<endl;
	
	for (int i=0;i<page_number;i++)
	{
		printf("///////////pagecount:%d\n",this->PageCount);
		page=fz_load_page(doc,i);//加载页面内容
		rect=fz_bound_page(doc,page);//获取页面的rectangle对象
		this->rect=rect;
		ctm.a=1;
		ctm.b=0;
		ctm.c=0;
		ctm.d=1;
		ctm.e=0;
		ctm.f=0;
		pix=fz_new_pixmap(ctx,fz_find_device_colorspace(ctx,"DeviceRGB"),rect.x1-rect.x0,rect.y1-rect.y0);
		fz_clear_pixmap_with_value(ctx,pix,0xFF);//将背景设置为白色
		//fz_clear_pixmap(ctx,pix);
		dev=fz_new_draw_device(ctx,pix);//创建绘图设备
		fz_run_page(doc,page,dev,ctm,0);//将页面绘制到pixmap生成的绘图设备上
		//提取矢量数据
		fz_return_line(getline);
		//提取images
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
	printf("Document释放链表");
}
void Ipe_PdfDocument::printfdocument()
{
	int count=0;
	printf("调用了document的输出函数\n");
	Ipe_node<Ipe_PdfPage>* p=list->headler;
	while(p->next!=NULL)
	{
		printf("第%d页___________________\n",count);
		p->next->t->printpage();//向下转型
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
	cout<<"该PDF文件有"<<getimages->count<<"幅图片"<<endl;
	getimages->currentimage=getimages->head;
	
	//使用freeimage
	FreeImage_Initialise(TRUE);//freeimage初始化
	string spath=path;
	for(int i=0;i<getimages->count;i++)
	{
		getimages->currentimage=getimages->currentimage->next;
		cout<<"w:"<<getimages->currentimage->w<<" "<<"h:"<<getimages->currentimage->h<<" "<<"n:"<<getimages->currentimage->n<<endl;
		int w=getimages->currentimage->w;
		int h=getimages->currentimage->h;
		int n=getimages->currentimage->n;
		unsigned char* data=getimages->currentimage->data;
		
		
		string filename=itstr(i+1)+".png";//图片名
		cout<<"图片名"<<filename<<endl;
		
		char* title=(char*)filename.c_str();
		
		string filepath=spath+filename;//生成路径+图片名
		cout<<"路径:"<<filepath<<endl;
		const char* fpath=filepath.c_str();
		
		FREE_IMAGE_FORMAT fif = FIF_PNG;//指定图片格式,此处设置为BMP格式
		
		//FIBITMAP *bitmap=FreeImage_Allocate(w,h,n*8,0x000000FF,0x0000FF00,0x00FF0000);
		FIBITMAP *bitmap=FreeImage_Allocate(w,h,n*8);//分配一块新的内存,指定宽,高,像素深度
		unsigned char *bits = FreeImage_GetBits(bitmap);//获取指针
		/*
		int width = FreeImage_GetWidth(bitmap);
		int height = FreeImage_GetHeight(bitmap);
		unsigned int byte_per_pixel = FreeImage_GetLine(bitmap) / width;
		cout<<width<<" "<<height<<" "<<byte_per_pixel<<endl;
		*/
		int cur=0;
		for (int x = 0; x <w*h; ++x)//遍历数组进行像素的复制 以bgra的顺序
		{
        // 这里对应于上述的每个像素的字节数
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
		//bitmap = FreeImage_RotateEx(bitmap, 180.0, 0, 0,w/2 ,h/2 , TRUE);//旋转
		FreeImage_FlipVertical(bitmap);//沿水平轴将输入垂直反转
		/*
		cur=0;
		for (int x = 0; x <w*h; ++x)//遍历数组进行像素的复制 以bgra的顺序
		{
        // 这里对应于上述的每个像素的字节数
			for(int j=0;j<n;j++)
			{
				cout<<(int)bits[cur]<<" ";
				cur++;
			}
			cout<<endl;
		}
		*/
		FreeImage_Save(fif, bitmap, fpath, PNG_DEFAULT);//输出文件
		
	}
	 FreeImage_DeInitialise();//freeimage撤销初始化
	 
}

//失败的使用libpng
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

		string filename=itstr(i)+".png";//图片名
		char* title=(char*)filename.data();
		string filepath=spath+filepath;//生成路径+文件名
		const char* fpath=filepath.c_str();
		FILE *fp = NULL;//打开文件
		fp = fopen(fpath, "wb");
		//调用libpng
		png_structp png_ptr = NULL;
		png_infop info_ptr = NULL;
	    png_bytep row = NULL;
		

		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);//初始化写结构
		info_ptr = png_create_info_struct(png_ptr);//初始化信息结构

		png_init_io(png_ptr, fp);//初始化IO
		//设置文件的基本信息
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
		for (int x = 0; x <h; ++x)//遍历数组进行像素的复制
		{
        // 这里对应于上述的每个像素的字节数
			for(int y=0;y<w;y++)
			{
				for(int z=0;z<4;z++)
				{
					row[cur]=data[cur];
					cur++;
				}
			}
			png_write_row(png_ptr, row);//写入一行
			//cout<<endl;
		}
		png_write_end(png_ptr, NULL);//写入结束
	}
*/

void Ipe_PdfDocument::testfreeimage()
{
	const char* imageFile = "C:\\Users\\赵博霖\\Desktop\\红色.png";
	// 图片格式
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	// 获取图片格式
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
        // 这里对应于上述的每个像素的字节数:4
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