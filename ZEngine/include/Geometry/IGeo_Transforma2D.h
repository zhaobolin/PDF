#ifndef IGEO_TRANSFORMA2D_H_HEADER_INCLUDED_B9D36B3F
#define IGEO_TRANSFORMA2D_H_HEADER_INCLUDED_B9D36B3F
#include "SPo_DRect.h"
class IGeo_Point;

/// \brief 二维变换，平移、旋转、伸缩
//##ModelId=442B796D03B9
class IGeo_Transforma2D
{
  public:
    //brief
    //     使几何对象的位置在坐标轴上按指定的偏移量发    生偏移。
    //return
    //     成功返回true，否则返回false。
    //param
    //     dx: 水平方向的偏移量
    //     dy: 垂直方向的偏移量
    //##ModelId=4562A7FE000F
    virtual bool Move(double dx, double dy) = 0;

    //brief
    //     缩放几何对象，使之充满指定的范围内。
    //return
    //     成功返回true，否则返回false。
    //param
    //     rect: 调整大小后对象的范围
    //     
    //##ModelId=4562A8150232
    virtual bool Resize(SPo_DRect rect) = 0;

    //brief
    //     几何对象旋转，逆时针方向。
    //return
    //     成功返回true，否则返回false。
    //param
    //     rPoint: 旋转的基点
    //     dAngle: 旋转的角度，单位为度
    //     备注 : dAngle为正时，逆时针旋转；dAngle为负    时，顺时针旋转。
    //##ModelId=4562A827004E
    virtual bool Rotate(IGeo_Point& rPoint, double dAngle) = 0;

    //brief
    //     按指定比例进行放缩几何对象。
    //param
    //     dRatioX: 水平缩放率
    //     dRatioY: 垂直缩放率
    //##ModelId=4562A845037A
    virtual bool Scale(double dRatioX, double dRatioY) = 0;

    //brief
    //     对几何对象进行定义变换
    //param
    //     enumDirection:正向还是逆向变换
    //     rTransformation:定义的变换
    //return
    //     成功返回true
    //##ModelId=456A57B303D8
    virtual bool Trandform(poenumTrandformDirection enumDirection, IGeo_Transform &rTransform) = 0;

};



#endif /* IGEO_TRANSFORMA2D_H_HEADER_INCLUDED_B9D36B3F */
