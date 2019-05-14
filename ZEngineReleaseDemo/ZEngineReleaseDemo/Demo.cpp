#include <stdio.h>
#include "Extract.h"
#include "Ipe_Lines.h"
#include "MuInclude.h"
#include "Ipe_PdfPath.h"
#include "Ipe_PdfPage.h"
#include "Ipe_PdfDocument.h"

using namespace std;
void main ()
{
	char* input="C:\\Users\\赵博霖\\Desktop\\两张图片.pdf";//设置要处理的PDF文件路径
	cliprect rect;
	rect.x0=100;
	rect.y0=300;
	rect.x1=500;
	rect.y1=200;
	Ipe_PdfDocument * document=new Ipe_PdfDocument(input);//打开指定的PDF文件并解析,在内存中产生一个Document
	//矢量数据测试部分
	//Ipe_node<Ipe_PdfPage>* page=document->getlist()->headler;//一个Document对应一个PDF文件,此时使用一个page结构读取Document的页链表开头
	//page=page->next;//此时指针指向这个PDF文件的第一页
	//page->t->clipwithrect(&rect);//裁减函数
	//page->t->pagetoSVG("C:\\Users\\赵博霖\\Desktop\\生成1.svg");//此函数将PDF的指定页内容转为SVG存储,路径自己设定
	//page->t->printpage();
	//图片提取测试部分
	char* output="C:\\Users\\赵博霖\\Desktop\\";//此处为生成图片的路径,目前多张图片命名格式为1.png 2.png...
	document->generatepictures(output);//此函数将document对应的PDF中的所有图片以png格式输出到对应路径中
	system("pause");
}