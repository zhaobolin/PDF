#pragma once
#include "Ipe_PdfPage.h"
#include "Ipe_LinkList.h"
#include "Ipe_PdfPage.h"
//#include "FreeImage.h"

class EX_PORT Ipe_PdfDocument
{
	fz_rect rect;
	int PageCount;
	Ipe_LinkList<Ipe_PdfPage>* list;
	struct zimages* getimages;//存放图片数据结构体指针
public:
	Ipe_PdfDocument(void);
	Ipe_PdfDocument(const char* path);//根据文件路径初始化
	~Ipe_PdfDocument(void);
	void printfdocument();
	void writeSVG(char* path);
	Ipe_LinkList<Ipe_PdfPage>* getlist();
	fz_rect getrect();
	void generatepictures(char* path);
	void testfreeimage();
	//void release();
	//int getPageCount();
	//Ipe_PdfPage* getPage(int num);
	//void writeSVG(char* path);
};

