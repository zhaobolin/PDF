#pragma once
#include <string>
#include "MuInclude.h"
class EX_PORT Ipe_PdfElement
{
public:
	Ipe_PdfElement(void);
	~Ipe_PdfElement(void);
	virtual void printfPath(){printf("������������");};
	virtual int getelementtype(){return 0;};//�ж����� 0-���� 1-Ipe_PdfStack 2-? 3-? 

};

