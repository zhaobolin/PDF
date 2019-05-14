#include "Ipe_Point2D.h"


Ipe_Point2D::Ipe_Point2D(void)
{
}

Ipe_Point2D::Ipe_Point2D(double x,double y,int state)
{
	this->x=x;
	this->y=y;
	this->state=state;
}
Ipe_Point2D::~Ipe_Point2D(void)
{
}

double Ipe_Point2D::getx()
{
	return x;
}

double Ipe_Point2D::gety()
{
	return y;
}

void Ipe_Point2D::setx(double x)
{
	this->x=x;
}

void Ipe_Point2D::sety(double y)
{
	this->y=y;
}
int Ipe_Point2D::getstate()
{
	return this->state;
}

void Ipe_Point2D::setstate(int state)
{
	this->state=state;
}

