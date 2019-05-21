#pragma once
class Ipe_Color
{
	int r,g,b;
	float v,G;
public:
	Ipe_Color();
	Ipe_Color(float r,float g,float b,float v,float G);
	void setColor(float r,float g,float b,float v,float G);
	void setCmykColor(float r,float g,float b,float v,float G);
	bool operator==(Ipe_Color& c);
	int getr();
	int getg();
	int getb();
	int getG();
	~Ipe_Color(void);
};

