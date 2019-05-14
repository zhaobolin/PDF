#include "VectorSet.h"
int VectorSet::getcount()
{
	return this->count;
}
class Vector** VectorSet::getvectorset()
{
	return this->T;
}
VectorSet::VectorSet(struct zblrouteset * vectorset)
{
	this->count=vectorset->count;
	for (int i=0;i<vectorset->count;i++)
	{
		Vector* vector=new Vector(vectorset->set[i]);
		this->T[i]=vector;
	}
}


VectorSet::~VectorSet(void)
{
}
