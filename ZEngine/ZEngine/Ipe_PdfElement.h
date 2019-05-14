#pragma once
#include <string>
#include "MuInclude.h"
class EX_PORT Ipe_PdfElement
{
public:
	Ipe_PdfElement(void);
	~Ipe_PdfElement(void);
	virtual void printfPath(){printf("父类的输出函数");};
	virtual int getelementtype(){return 0;};//判断类型 0-父类 1-Ipe_PdfStack 2-? 3-? 

};

