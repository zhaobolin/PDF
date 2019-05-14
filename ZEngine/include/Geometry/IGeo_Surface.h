#ifndef IGEO_SURFACE_H_HEADER_INCLUDED_B9D32A15
#define IGEO_SURFACE_H_HEADER_INCLUDED_B9D32A15
#include "IGeo_Geometry.h"
#include "IGeo_LineString.h"
class IGeo_PolyLine;

///brief
//      面，面的边线是线串，相当于arcinfo的ring
//##ModelId=442B4ACC000F
class IGeo_Surface : public IGeo_Geometry
{
  public:
    //brief
    //     获取外环数目
    //param
    //     无
    //return
    //     外环个数
    //##ModelId=45654EB40290
    virtual int GetExteriorRingCount() = 0;

    //brief
    //     获取指定折线串包含的内环数目
    //param
    //     rRing:指定折线串
    //return
    //     内环个数
    //##ModelId=45654EB4029F
    virtual int GetInteriorRingCount(IGeo_PolyLine *rRing) = 0;

    //brief
    //     查找包含指定内环的外环
    //param
    //     rInterRing:内环
    //return
    //     外环对象
    //##ModelId=45654EB402A1
    virtual IGeo_LineString * FindExteriorRing(IGeo_LineString * rInterRing) = 0;

    //brief
    //     获取所有外环
    //param
    //     rExteriorRing:用于返回外环
    //return
    //     返回外环成功true
    //##ModelId=45654EB402AF
    virtual bool GetExteriorRings(IGeo_LineString* pExteriorRing) = 0;

    //brief
    //     返回指定外环的内环
    //param
    //     rExteriorRing:指定外环
    //     pInteriorRing:返回内环
    //return
    //     成功true
    //  
    //##ModelId=45654EB402BF
    virtual bool GetInteriorRings(IGeo_LineString * rExteriorRing, IGeo_LineString* pInteriorRings) = 0;

};



#endif /* IGEO_SURFACE_H_HEADER_INCLUDED_B9D32A15 */
