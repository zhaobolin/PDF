#include "Vector.h"

Vector::Vector(void)
{
}
Vector::Vector(struct zblroute &vector)
{
	this->type=vector.type;
	this->linewidth=vector.linewidth;
	this->colorspace=vector.colorspace;
	this->color[0]=vector.color[0];
	this->color[1]=vector.color[1];
	this->color[2]=vector.color[2];
	this->color[3]=vector.color[3];
	this->countpoint=vector.countpoint;
	for(int i=0;i<vector.countpoint;i++)
	{
		for(int j=0;j<7;j++)
		{
			this->points[i][j]=vector.points[i][j];
		}	
	}
	this->drawingmethord=vector.drawingmethord;
}
Vector::~Vector(void)
{
}

int Vector:: getcountpoint()
{
	return this->countpoint;
}

int Vector::gettype()
{
	return this->type;
}

float Vector::getlinewidth()
{
	return this->linewidth;
}

int Vector::getcolorspace()
{
	return this->colorspace;
}

float(* Vector::getpoints())[7]
{
	return this->points;
}

float* Vector::getcolor()
{
	return this->color;
}
int Vector::getdrawingmethord()
{
	return this->drawingmethord;
}

