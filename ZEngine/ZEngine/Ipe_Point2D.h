#pragma once
class Ipe_Point2D
{
	double x,y;
	int state;
public:
	Ipe_Point2D(void);
	Ipe_Point2D(double x,double y,int state);
	~Ipe_Point2D(void);
	double getx();
	double gety();
	void setx(double x);
	void sety(double y);
	int getstate();
	void setstate(int state);

};

