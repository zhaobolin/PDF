#ifndef IGEO_ENVELOPE_H_HEADER_INCLUDED_B9D30230
#define IGEO_ENVELOPE_H_HEADER_INCLUDED_B9D30230
#include "IGeo_Geometry.h"
#include "..\common\SPo_DRect.h"
#include "..\common\SPo_DPoint.h"
class IPo_SpatialReference;

// 基本几何对象封套接口
// 封套即为一个矩形框，它定义了最大最小边界值及相关属性值
// 封套为其它的空间几何对象提供一个近似而有用的边界范围
// 对于一个点，其位置只有二种情况，位于矩形内或外
//##ModelId=408C7E1C030D
class IGeo_Envelope : public IGeo_Geometry
{
  public:
    //brief
    //     设置矩形封套最小x，矩形左边
    //param
    //     dMinx:最小x值
    //##ModelId=456255F303D8
    virtual void SetXMin(double dXMin) = 0;

    //brief
    //     设置矩形封套最大x，矩形右边
    //param
    //     dXMax:矩形封套最大x
    //##ModelId=456255F4000F
    virtual void SetXMax(double dXMax) = 0;

    //brief
    //     设置矩形封套最小y，矩形下边
    //param
    //     dYMin:矩形封套最小y
    //##ModelId=456255F4002E
    virtual void SetYMin(double dYMin) = 0;

    //brief
    //     设置矩形封套最大y，矩形上边
    //param
    //     dYMax:矩形封套最大y
    //##ModelId=456255F4004E
    virtual void SetYMax(double dYMax) = 0;

    //brief
    //     设置矩形封套边界矩形
    //param
    //     sDRect:矩形边界值
    // 
    //    
    //##ModelId=456255F4006D
    virtual void SetBoundRect(SPo_DRect sDRect) = 0;

    //brief
    //     获取矩形封套最小x，矩形左边
    //return
    //     矩形封套最小x
    //##ModelId=456255F4008C
    virtual double GetXMin() = 0;

    //brief
    //     获取矩形封套最大x，矩形右边
    //return
    //     矩形封套最大x
    //##ModelId=456255F4008E
    virtual double GetXMax() = 0;

    //brief
    //     获取矩形封套最小y，矩形下边
    //return
    //     矩形封套最小y
    //##ModelId=456255F4009D
    virtual double GetYMin() = 0;

    //brief
    //     获取矩形封套最大y，矩形上边
    //return
    //     矩形封套最大y
    //##ModelId=456255F400AC
    virtual double GetYMax() = 0;

    //brief
    //     获取矩形封套边界矩形
    //return
    //     封套边界矩形
    //##ModelId=456255F400BC
    virtual SPo_DRect GetBoundRect() = 0;

    //brief
    //     获取矩形封套高，YMax-YMin
    //return
    //     矩形封套高
    //##ModelId=456255F400BE
    virtual double GetHeight() = 0;

    //brief
    //     获取矩形封套的宽，XMax-XMin
    //return
    //     矩形封套的宽
    //##ModelId=456255F400CC
    virtual double GetWidth() = 0;

    //brief
    //     将矩形封套移动到以指定的点为中心的位置
    //param
    //     sPoint 指定点
    //     pSpatialReference: 指定点对应的空间参考系。     缺省为NULL，表示使用几何对象本身的空间参考      系。
    //##ModelId=456255F400CE
    virtual bool CenterAt(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     将矩形封套移动到以指定的点为中心的位置
    //param
    //     pPoint 指定点
    //##ModelId=456255F40109
    virtual bool CenterAt(const IGeo_Geometry* pPoint) = 0;

    //brief
    //     设置矩形封套最小z，矩形最小深度
    //param
    //     dZMin:矩形封套最小z
    //##ModelId=456255F40128
    virtual void SetZMin(double dZMin) = 0;

    //brief
    //     获取矩形封套最小z，矩形最小深度
    //return
    //     矩形封套最小z
    //##ModelId=456255F40148
    virtual double GetZMin() = 0;

    //brief
    //     设置矩形封套最大z，矩形最大高程
    //param
    //     dZMax:矩形封套最大z
    //##ModelId=456255F40158
    virtual void SetZMax(double dZMax) = 0;

    //brief
    //     获取矩形封套最大z，矩形最大高程
    //return
    //     矩形封套最大z
    //##ModelId=456255F40177
    virtual double GetZMax() = 0;

    //brief
    //     获取矩形封套深度，ZMax-ZMin
    //return
    //     矩形封套深度
    //##ModelId=456255F40187
    virtual double GetDepth() = 0;

    //brief
    //     使矩形封套向外扩张
    //param
    //     dx : x方向分别外扩dx  XMin-=dx; XMax+=dx;
    //     dy : y方向分别外扩dy  YMin-=dy; YMax+=dy;
    //     bRatio : 外扩是否成倍，默认为false，加法外    扩
    //     备注 : 成倍为 XMin-=dx*Width/2;     XMax+=dx*Width/2; YMin-=dy*Height/2;
    //     YMax+=dy*Height/2;
    //##ModelId=456255F40197
    virtual void Expand(double dx, double dy, bool bRatio = false) = 0;

    //brief
    //     扩大M值
    //param
    //     dm:M扩大dm
    //     asRatio:是否成倍扩大
    //##ModelId=4562C16802BF
    virtual void ExpandM(double dm, bool asRatio) = 0;

    //brief
    //     沿Z方向向外扩张矩形封套
    //param
    //     dz : 外扩值
    //     bRatio : 是否成倍扩张，默认为false，相加扩    张
    //     备注 : 成倍扩张为 ZMin-=dz*Depth/2;     ZMax+=dz*Depth/2;
    //     相加扩张为 ZMin-=dz; ZMax+=dz;
    //##ModelId=456255F401E4
    virtual void ExpandZ(double dz, bool bRatio = false) = 0;

    //brief
    //     求矩形封套与给定的矩形封套的交集
    //param
    //     pEnvelope : 给定的矩形封套对象
    //return
    //     相交矩形
    //##ModelId=456255F40222
    virtual SPo_DRect Intersect(const IGeo_Geometry* pEnvelope) = 0;

    //brief
    //     判断矩形中是否含有其它点对象
    //return
    //     如不包含返回true
    // 
    //##ModelId=456255F40242
    virtual bool IsEmpty() = 0;

    //brief
    //     删除封套对象中的所有点对象
    // /return
    //     成功返回true
    //##ModelId=456255F40252
    virtual bool SetEmpty() = 0;

    // 返回几何对象的中心点。
    // 参数说明 : pSpatialReference: 几何对象中心对应的空间参考系。缺省为NULL，表示使用几何对象本身的空间参考系。
    //##ModelId=4562AD0701F4
    virtual SPo_DPoint GetCentroidPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //设置左下角点坐标
    //##ModelId=4562BFA501B5
    virtual void SetLowerLeft(const SPo_DPoint csPoint) = 0;

    //得到左下角点坐标
    //##ModelId=4562BFFB004E
    virtual SPo_DPoint GetLowerLeft() = 0;

    //设置右下角点坐标
    //##ModelId=4562C02F01D4
    virtual void SetLowerRight(const SPo_DPoint csPoint) = 0;

    //得到右下角点坐标
    //##ModelId=4562C02F01D6
    virtual SPo_DPoint GetLowerRight() = 0;

    //设置左上角点坐标
    //##ModelId=4562C047005D
    virtual void SetUpperLeft(const SPo_DPoint csPoint) = 0;

    //得到左上角点坐标
    //##ModelId=4562C047005F
    virtual SPo_DPoint GetUpperLeft() = 0;

    //设置右上角点坐标
    //##ModelId=4562C06F02DE
    virtual void SetUpperRight(const SPo_DPoint csPoint) = 0;

    //得到右上角点坐标
    //##ModelId=4562C06F02FD
    virtual SPo_DPoint GetUpperRight() = 0;

    //偏移坐标
    //##ModelId=4562C1CD02BF
    virtual void Offset(double dx, double dy) = 0;

    //偏移M值
    //##ModelId=4562C2250148
    virtual void OffsetM(double dz) = 0;

    //偏移Z值
    //##ModelId=4562C248007D
    virtual void OffsetZ(double dz) = 0;

    //设置封套的角点坐标
    //##ModelId=4562C2DB01E4
    virtual void PutCoords(const double XMin, const double XMax, const double YMin, const double YMax) = 0;

    //查询坐标角点
    //##ModelId=4562C4B60261
    virtual void QueryCoords(double &XMin, double &XMax, double &YMin, double &YMax) = 0;

    //将封套范围设置为原有范围与输入封套的交
    //##ModelId=4562C34D0128
    virtual void Intersect(IGeo_Envelope& inEnvelope) = 0;

    //将封套设置为原有范围与输入封套的并
    //##ModelId=4562C3B00222
    virtual void Union(IGeo_Envelope& inEnvelope) = 0;

};



#endif /* IGEO_ENVELOPE_H_HEADER_INCLUDED_B9D30230 */
