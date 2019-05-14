#include "Ipe_Color.h"
Ipe_Color::Ipe_Color()
{}

Ipe_Color::Ipe_Color(float r,float g,float b,float v,float G)
	:r(r),g(g),b(b),v(v),G(G)
{
}
void Ipe_Color::setColor(float r,float g,float b,float v,float G)
{
	this->r=r*255;
	this->g=g*255;
	this->b=b*255;
	this->v=v;
	this->G=G;
}

void Ipe_Color::setCmykColor(float r,float g,float b,float v,float G)
{
	this->r=r;
	this->g=g;
	this->b=b;
	this->v=v;
	this->G=G;
}

Ipe_Color::~Ipe_Color(void)
{
}

int Ipe_Color::getr()
{
	return r;
}

int Ipe_Color::getg()
{
	return g;
}

int Ipe_Color::getb()
{
	return b;
}

int Ipe_Color::getG()
{
	return G;
}