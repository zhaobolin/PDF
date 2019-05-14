#include "Ipe_Engine.h"


Ipe_Engine::Ipe_Engine(void)
{
}


Ipe_Engine::~Ipe_Engine(void)
{
}

Ipe_PdfDocument* Ipe_Engine::OpenPDFDocument(const char* path)
{
	Ipe_PdfDocument* document=new Ipe_PdfDocument(path);
	return document;
}
