#pragma once
#include "Ipe_Point2D.h"
#include "MuInclude.h"
#include <iostream>
using namespace std;
class Ipe_PdfMapEdge
{
	Ipe_Point2D lu,ld,ru,rd;
public:
	Ipe_PdfMapEdge(fz_rect& rect);
	void updatePoints(float x,float y);//���º���
	void printdata();
	void changecoor(float y);
	~Ipe_PdfMapEdge(void);
};

