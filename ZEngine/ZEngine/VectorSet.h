#pragma once
/*
	ʸ�����ݼ�,��ӦMupdf�е�zblrouteset
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
	VectorSet(struct zblrouteset * vectorset);//��ʼ��ʸ�����ݼ�
	~VectorSet(void);
};

