#pragma once
#include "Ipe_LinkList.h"
#include "Ipe_PdfDocument.h"
class EX_PORT Ipe_Engine
{
	Ipe_LinkList<Ipe_PdfDocument>* list;
public:
	Ipe_Engine(void);
	~Ipe_Engine(void);
	Ipe_PdfDocument* OpenPDFDocument(const char*); 
	//Ipe_Render * createRender();

};

