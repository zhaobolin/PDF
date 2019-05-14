#ifndef IGEO_AFFINETRANSFORM2D_H_HEADER_INCLUDED_B9D3677E
#define IGEO_AFFINETRANSFORM2D_H_HEADER_INCLUDED_B9D3677E
#include "IGeo_Transformation.h"
class IGeo_Point;
class IGeo_Line;
class IGeo_Envelope;

/// \brief 仿射变换
//##ModelId=442B79B60251
class IGeo_AffineTransform2D : public IGeo_Transformation
{
  public:
    //brief
    //     是否定义反射
    //return
    //     如果定义了返回true
    //##ModelId=456A5CB80251
    virtual bool IsReflective() = 0;

    //brief
    //     得到旋转角度
    //##ModelId=456A5D040157
    virtual double GetRotation() = 0;

    //brief
    //     移动初始点
    //param
    //     rPoint:新的初始点
    //##ModelId=456A5D2701B5
    virtual bool MoveOrigin(IGeo_Point& rPoint) = 0;

    //brief
    //     得到空间参考系
    //##ModelId=456A5D8E02AF
    virtual IGeo_SpatialReference GetSpatialReference() = 0;

    //brief
    //     设置空间参考系
    //param
    //     rSpatialRef:新空间参考系
    //return
    //     设置成功返回true
    //##ModelId=456A5DCC005D
    virtual bool SetSpatialReference(IGeo_SpatialReference &rSpatialRef) = 0;

    //brief
    //     得到x向缩放系数
    //##ModelId=456A5E310177
    virtual double GetXScale() = 0;

    //brief
    //      得到y方向缩放系数
    //##ModelId=456A5E5C02EE
    virtual double GetYScale() = 0;

    //brief
    //     得到x方向平移值
    //##ModelId=456A5E810109
    virtual double GetXTranslation() = 0;

    //brief
    //     得到y方向平移值
    //##ModelId=456A5EAC037A
    virtual double GetYTranlation() = 0;

    //brief
    //     由控制点影射定义变换
    //param  
    //     iPoints:控制点个数
    //     pFromPoints:输入控制点
    //     pToPoints:转换后控制点
    //return
    //     定义成功返回true
    //##ModelId=456A7F4F02FD
    virtual bool DefineFromControlPoints(int iPoints, IGeo_Point* pFromPoints, IGeo_Point* pToPoints) = 0;

    //brief
    //     由封套影射定义变换
    //param
    //     pFromEnvelope:输入封套
    //     pToEnvelope:输出封套
    //return
    //     定义变换成功返回true
    //##ModelId=456A8046006D
    virtual bool DefineFromEnvelope(IGeo_Envelope* pFromEnvelope, IGeo_Envelope* pToEnvelope) = 0;

    //brief
    //     由反射定义变换
    //param
    //     rLine:反射轴线
    //return
    //     定义变换成功返回true
    //##ModelId=456A80F700BB
    virtual bool DefineReflection(IGeo_Line &rLine) = 0;

    //brief
    //     得到控制点误差
    //param
    //     iIndex:序数
    //     pdFromError:对应序数起始点误差
    //     pdToError:  对应序数影射点误差
    //return
    //     取值成功返回true
    //##ModelId=456A81680186
    virtual bool GetControlPointError(int iIndex, doube *pdFromError, double *pdToError) = 0;

    //brief
    //     在变换中加入移动因子
    //param
    //     dx\dy:x、y方向偏移量
    //return
    //     设置成功返回true
    //##ModelId=456A827200AB
    virtual bool Move(double dx, double dy) = 0;

    //brief
    //     在变换中加入旋转因子
    //param
    //     dAngle:旋转角度
    //return
    //     设置成功返回true
    //##ModelId=456A82ED0251
    virtual bool Rotate(double dAngle) = 0;

    //brief
    //     在变换中设置缩放因子
    //param
    //     dx\dy:x、y方向缩放因子
    //##ModelId=456A83480177
    virtual bool Scale(double dx, double dy) = 0;

    //brief
    //     在本变换之前先应用另一变换
    //param
    //     rOtherTransform:另一变换
    //return
    //     设置成功返回true
    //##ModelId=456A83CE02FD
    virtual Boolean PreMultiply(IGeo_AffineTransform2D& rOtherTransform) = 0;

    //brief
    //     在本变换之后先应用另一变换
    //param
    //     rOtherTransform:另一变换
    //return
    //     设置成功返回true
    //##ModelId=456A84730109
    virtual bool PostMultiply(IGeo_AffineTransform2D &rOtherTransform) = 0;

    //brief
    //     在变换中设置坐标系变换
    //param
    //     rOtherSpatialRef:影射坐标系
    //return
    //     影射成功返回true
    //##ModelId=456A84A60000
    virtual bool Project(IGeo_SpatialReference &rOtherSpatialRef) = 0;

    //brief
    //     重设变换
    //param
    //     无
    //return
    //     重设成功返回true
    //##ModelId=456A852900FA
    virtual bool Reset() = 0;

};



#endif /* IGEO_AFFINETRANSFORM2D_H_HEADER_INCLUDED_B9D3677E */
