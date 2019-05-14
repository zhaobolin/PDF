#ifndef IGEO_LINESTRING_H_HEADER_INCLUDED_B9D37EEB
#define IGEO_LINESTRING_H_HEADER_INCLUDED_B9D37EEB
#include "IGeo_PolyCurve.h"
class IPo_SpatialReference;
class IGeo_Geometry;


//brief
//     线串对象接口
// 
// 由线段、圆弧线、椭圆线、Bazier线组成的线串，等同于ArcInfo的Path与折线的区别是，组成成分可以是园弧、椭圆弧和Bazier弧，可视为折线的超类。
// 如果约束线串的始点与末点相同，则为ArcInfo中的环。
//##ModelId=442B2F4E0128
class IGeo_LineString : public IGeo_PolyCurve
{
  public:
    //brief
    //     创建并添加几何对象。
    // 
    //     根据给定的类型创建一个几何对象并为线串增加该几何对象。
    // 
    //return
    //     返回增加的几何对象的指针。
    // 
    //param
    //     nElementType: 增加的几何对象的类型。
    // 备注 : 用户应根据几何对象类型，将返回值强制转换为相应的GeoXXX指针。
    //##ModelId=456258D203C8
    virtual IGeo_Geometry* CreateElement(poenumGeoType nElementType) = 0;

    //brief
    //     获取线串中几何对象的个数。
    // 
    //return
    //     几何对象的个数。
    //##ModelId=456258D30000
    virtual int GetElementCount() = 0;

    //brief
    //     获取几何对象。
    //     根据下标获取几何对象的指针。
    // 
    //return
    //     指定下标对应的几何对象的指针。
    // 
    //param
    //     nIndex: 所需获取的几何对象的下标。
    //     备注 : 用户应根据几何对象类型，将返回值强制转换为相应的GeoXXX指针。
    //##ModelId=456258D30010
    virtual IGeo_Geometry* GetElementPtr(int nIndex) = 0;

    //brief
    //     获取几何对象。
    //     根据给定点获取几何对象的指针。
    // 
    //return
    //     获取几何对象的指针。
    // 
    //param
    //     sPoint: 输入点。
    //     dTolerance: 点选取阈值。
    //     pSpatialReference: 给定点对应的空间参考系。缺省为NULL，表示使用几何对象本身的空间参考系。
    //     备注 : 用户应根据几何对象类型，将返回值强制转换为相应的GeoXXX指针。
    //##ModelId=456258D3002E
    virtual IGeo_Geometry* GetElementPtr(SPo_DPoint sPoint, double dTolerance = 0.0, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     获取几何对象。
    //     根据给定点获取几何对象的指针。
    // 
    //return
    //     指定下标对应的几何对象的指针。
    // 
    //param
    //     pPoint: 输入点对象。
    //     dTolerance: 点选取阈值。
    //     备注 : 用户应根据几何对象类型，将返回值强制转换为相应的GeoXXX指针。
    //##ModelId=456258D3007D
    virtual IGeo_Geometry* GetElementPtr(const IGeo_Geometry* pPoint, double dTolerance = 0.0) = 0;

    //brief
    //     删除几何对象。
    //     根据下标位置删除几何对象。
    // 
    //return
    //     删除成功，则返回true，否则返回false。
    // 
    //param
    //     nIndex: 需被删除的几何对象的下标位置。
    //     备注 : 0<=nIndex<几何对象个数；后续几何对象的下标将发生变动，几何对象个数减1。
    //##ModelId=456258D300BB
    virtual bool DeleteElement(int nIndex) = 0;

    //brief
    //     用给定的几何对象替换给定索引的几何对象
    // 
    //return
    //     成功返回true， 否则返回false
    // 
    //param
    //     pGeo 用来替换给定索引的几何对象
    //     nIndex 需要被替换的几何对象的索引
    //##ModelId=456258D300EA
    virtual bool ReplaceElement(IGeo_Geometry* pElement, int nIndex) = 0;

    //brief
    //     添加几何对象。
    //     多线增加一个几何对象。
    // 
    //return
    //     成功返回true， 否则返回false
    // 
    //param
    //     pGeo : 增加的几何对象。
    //##ModelId=456258D30119
    virtual IGeo_Geometry* AddElement(IGeo_Geometry* pGeo) = 0;

};

typedef IGeo_LineString IGeo_PathString;//为避免于Line接口意义混淆并将其区分

#endif /* IGEO_LINESTRING_H_HEADER_INCLUDED_B9D37EEB */
