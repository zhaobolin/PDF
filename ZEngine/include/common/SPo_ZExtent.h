#ifndef SPO_ZEXTENT_H_HEADER_INCLUDED_BB16469D
#define SPO_ZEXTENT_H_HEADER_INCLUDED_BB16469D

// Z值值域的结构体，包含两个变量，Z值值域的最小值ZMin，Z值值域的最大值ZMax
//##ModelId=44E9F10E0056
struct SPo_ZExtent
{
	SPo_ZExtent(double dvalmin,double dvalmax)
	{
		dZMin = dvalmin;
		dZMax = dvalmax;
	}
	SPo_ZExtent()
	{
		dZMin = 0;
		dZMax = 0;
	}
    // 空间参考的Z值值域最小值
    //##ModelId=44E9F12A0133
    double dZMin;

    // 空间参考的Z值值域最大值
    //##ModelId=44E9F1470333
    double dZMax;

};



#endif /* SPO_ZEXTENT_H_HEADER_INCLUDED_BB16469D */
