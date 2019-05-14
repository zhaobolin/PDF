#ifndef IGEO_POLYCURVE_H_HEADER_INCLUDED_B9D3211E
#define IGEO_POLYCURVE_H_HEADER_INCLUDED_B9D3211E
#include "IGeo_Curve.h"
class IGeo_Point;

//brief
//     多点曲线
//##ModelId=4564FBF6005D
class IGeo_PolyCurve : public IGeo_Curve
{
  public:
    //brief
    //     加密线段
    // 
    //param
    //     dMaxSegmentLength:加密后最大段长
    //     dMaxDeviation:最大偏移量
    // 
    //return
    //     加密成功，返回true
    //##ModelId=456513800119
    virtual bool Densify(double dMaxSegmentLength, double dMaxDeviation) = 0;

    //brief
    //     线段综合
    // 
    //param
    //     dMaxOffset:最大偏移量
    // 
    //return
    //     线段综合成功，返回true
    //##ModelId=4565140202BF
    virtual bool Generalize(double dMaxOffset) = 0;

    //brief
    //     线段光滑
    // 
    //param
    //     dMaxOffset:最大偏移量
    // 
    //return
    //     光滑成功，返回true
    //##ModelId=4565144000DA
    virtual bool Smooth(double dMaxOffset) = 0;

    //brief
    //     在指定位置分离几何对象
    // 
    //param
    //     dDistance:距离
    //     asRatio:距离是按比例尺计算，true
    // 
    //return
    //      成功，true
    //##ModelId=4565146C0128
    virtual bool SplitAtDistance(double dDistance, bool bRatio) = 0;

    //brief
    //     在离输入点最近的地方插入一点
    // 
    //param
    //     pPoint:输入点信息
    // 
    //return
    //     成功，true
    //##ModelId=456515280128
    virtual bool SplitAtPoint(IGeo_Point* pPoint) = 0;

    //brief
    //     综合
    // 
    //param
    //     dMaxOffsetFactor:最大允许偏移因子
    // 
    //return
    //     成功，true
    //##ModelId=4565162903B9
    virtual bool Weed(double dMaxOffsetFactor) = 0;

};



#endif /* IGEO_POLYCURVE_H_HEADER_INCLUDED_B9D3211E */
