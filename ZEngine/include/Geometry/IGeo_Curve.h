#ifndef IGEO_CURVE_H_HEADER_INCLUDED_B9D3394C
#define IGEO_CURVE_H_HEADER_INCLUDED_B9D3394C

#include "IGeo_Geometry.h"

class IGeo_Point;
class IGeo_Line;


//brief
//     曲线
//##ModelId=4564FBB903B9
class IGeo_Curve : public IGeo_Geometry
{
  public:
    //brief
    //     得到起始点
    // 
    //param  
    //     pPoint:返回起始点
    // 
    //return
    //     成功返回，返回true
    //##ModelId=4565005D0203
    virtual bool GetFromPoint(IGeo_Point * pPoint) = 0;

    //brief
    //     设置起始点
    // 
    //param
    //     rPoint:起始点信息
    // 
    //return
    //     成功，返回true
    //##ModelId=4565092E0196
    virtual bool SetFromPoint(IGeo_Point& rPoint) = 0;

    //brief
    //     得到结束点
    // 
    //param
    //     pPoint:返回结束点
    // 
    //return
    //     成功获取，返回true
    //##ModelId=4565097D030D
    virtual bool GetToPoint(IGeo_Point * pPoint) = 0;

    //brief
    //     设置结束点
    // 
    //param
    //     rPoint:点信息
    // 
    //return
    //     成功，返回true
    //##ModelId=4565097D03B9
    virtual bool SetToPoint(IGeo_Point& rPoint) = 0;

    //brief
    //     是否封闭
    // 
    //return
    //     如果封闭，返回true
    //##ModelId=456509B700FA
    virtual bool IsClosed() = 0;

    //brief
    //     得到曲线长度
    // 
    //return
    //     曲线长度
    //##ModelId=456509CE00EA
    virtual double GetLength() = 0;

    //brief
    //     获取子曲线
    // 
    //param
    //     fromDistance:离起始点距离
    //     toDistance:离结束点距离
    //     asRatio:true,距离以百分比度量
    //     outSubCurve:返回子曲线
    //return
    //     获取成功，返回true
    //##ModelId=45650A17029F
    virtual bool GetSubCurve(double fromDistance, double toDistance, bool asRatio, IGeo_Curve* outSubCurve) = 0;

    //brief
    //     求距离起始点一定距离的曲线的法线
    // 
    //param
    //     cExtent:线段扩展方式
    //     dDistance:求法线离起始点位置
    //     asRatio:距离按百分比度量,true
    //     dLength:法线长度
    //     pLine:返回法线对象
    // 
    //return
    //     成功，返回true
    //##ModelId=45650C55007D
    virtual bool QueryNormal(
        //线段扩展方式
        poenumSegmentExtent cExtension, 
        //distance to from point
        double dDistance, bool bRatio, 
        //法线长度
        double dLength, IGeo_Line *pLine) = 0;

    //brief
    //     求取给定位置曲线的切线
    // 
    //param
    //     cExtent:线段扩展方式
    //     dDistance:求法线离起始点位置
    //     asRatio:距离按百分比度量,true
    //     dLength:法线长度
    //     pLine:返回法线对象
    // 
    //return
    //     成功，返回true
    //##ModelId=45650D28033C
    virtual bool QueryTangent(
        //线段扩展方式
        poenumSegmentExtent cExtension, 
        //distance to from point
        double dDistance, bool bRatio, 
        //法线长度
        double dLength, IGeo_Line *pLine) = 0;

    //brief
    //     求取距离起始点某处的点对象
    // 
    //param
    //     cExtent:线段扩展方式
    //     dDistance:求法线离起始点位置
    //     asRatio:距离按百分比度量,true
    //     dLength:法线长度
    //     pPoint:返回点对象
    // 
    //return
    //     成功，返回true
    //##ModelId=45650D700148
    virtual bool QueryPoint(
        //线段扩展方式
        poenumSegmentExtent cExtension, 
        //distance to from point
        double dDistance, bool bRatio, IGeo_Point *& pPoint) = 0;

    //brief
    //     计算离已知点最近的曲线上的点，计算出的点距起始点的距离，给定点离曲线的距离，是否在曲线右侧
    // 
    //param
    //     cExtent:线段扩展方式
    //     pInPoint:输入点
    //     pOutPoint:返回点
    //     dDisAlongCurve:曲线上离起始点距离
    //     dDisFromCurve:偏离曲线距离
    //     bRight:在曲线右侧，true
    // 
    //return
    //      成功返回，true
    //     
    //##ModelId=45650E75036B
    virtual bool QueryPointAndDistance(
        //线段扩展方式
        poenumSegmentExtent cExtension, IGeo_Point* pInPoint, IGeo_Point* pOutPoint, 
        //求出点离起始点距离
        double dDisAlongCurve, 
        //已知点离曲线距离
        double dDisFromCurve, 
        //已知点在曲线右侧吗
        bool bRight) = 0;

    //brief
    //     切换线段方向
    // 
    //return
    //     成功切换，返回true
    //##ModelId=45650FD001F4
    virtual bool ReverseDirection() = 0;

};



#endif /* IGEO_CURVE_H_HEADER_INCLUDED_B9D3394C */
