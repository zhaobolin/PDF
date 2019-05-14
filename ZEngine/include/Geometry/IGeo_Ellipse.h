#ifndef IGEO_ELLIPSE_H_HEADER_INCLUDED_B9D37C3F
#define IGEO_ELLIPSE_H_HEADER_INCLUDED_B9D37C3F
//brief
//     椭圆面几何对象
//##ModelId=442B4BF70399
class IGeo_Ellipse : public IGeo_Geometry
{
  public:
    //brief
    //     设置椭圆的长轴
    //param
    //     dAxis:长轴
    //return
    //     无
    //##ModelId=45625C12006D
    virtual void SetPrimaryAxis(double dAxis) = 0;

    //brief
    //     获取椭圆的长轴半径
    //param
    //     无
    //return
    //     长轴半径
    //##ModelId=45625C12008C
    virtual double GetPrimaryAxis() = 0;

    //brief
    //     设置椭圆的短轴
    //param
    //     dAxis:短轴半径
    //return
    //     无
    //##ModelId=45625C12009D
    virtual void SetSecondaryAxis(double dAxis) = 0;

    //brief
    //     获取椭圆的短轴半径
    //param
    //     无
    //return
    //     短轴半径
    //##ModelId=45625C1200BB
    virtual double GetSecondaryAxis() = 0;

    //brief
    //     将椭圆对象转换成线对象。
    //     按照给定参数将椭圆等分为线段对象。
    //param
    //     pGeo: 输出的线对象
    //     nSegment: 等分圆的段数
    //return
    //     转换成功返回true
    //##ModelId=45625C1200BD
    virtual bool ConvertToLine(IGeo_PolyLine * pGeo, int nSegment) = 0;

};



#endif /* IGEO_ELLIPSE_H_HEADER_INCLUDED_B9D37C3F */
