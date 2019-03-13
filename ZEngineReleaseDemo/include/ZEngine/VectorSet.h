#pragma once
/*
	矢量数据集,对应Mupdf中的zblrouteset
*/
#include "Vector.h"
#include "MuInclude.h"


class EX_PORT VectorSet
{
	int count;
	class Vector* T[1000];
public:
	int getcount();
	class Vector ** getvectorset();
	VectorSet(struct zblrouteset * vectorset);//初始化矢量数据集
	~VectorSet(void);
};

