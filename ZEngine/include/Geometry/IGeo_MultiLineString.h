#ifndef IGEO_MULTILINESTRING_H_HEADER_INCLUDED_B9D31EC7
#define IGEO_MULTILINESTRING_H_HEADER_INCLUDED_B9D31EC7
#include "IGeo_Geometry.h"
class IGeo_LineString;

//brief
//    线串集合对象接口，若干个线串的几何对象
//##ModelId=442B47F60177
class IGeo_MultiLineString : public IGeo_Geometry
{
  public:
    //brief
    //     获取多线集合对象中多线对象的个数。
    //return
    //     多线对象的个数。
    //##ModelId=456258970109
    virtual int GetLineStringCount() = 0;

    //brief
    //     获取多线几何对象。
    //     根据下标获取多线几何对象的指针。
    //return
    //     指定下标对应的多线对象的指针。
    //param
    //     nIndex: 所需获取的几何对象的下标。
    // 
    //     备注 : 用户应根据几何对象类型，将返回值强制    转换为相应的GeoXXX指针。
    //##ModelId=45625897011A
    virtual IGeo_LineString* GetLineStringPtr(int nIndex) = 0;

    //brief
    //     删除线串几何对象。
    //     根据下标位置删除线串几何对象。
    //     删除成功，则返回true，否则返回false。
    //param
    //     nIndex: 需被删除的线串对象的下标位置。
    // 
    //     备注 : 0<=nIndex<几何对象个数；后续几何对象    的下标将发生变动，几何对象个数减1。
    //##ModelId=456258970148
    virtual bool DeleteLineString(int nIndex) = 0;

    //brief
    //     用给定的线串对象替换给定索引的线串对象
    // 
    //return
    //     成功返回true， 否则返回false
    // 
    //param
    //     pGeo 用来替换给定索引的线串对象
    //     nIndex 需要被替换的线串对象的索引
    //##ModelId=456258970167
    virtual bool ReplaceLineString(IGeo_Geometry* pGeo, int nIndex) = 0;

    //brief
    //     添加线串对象。为线串集合增加一个线串几何对象。
    // 
    //return
    //     成功返回true， 否则返回false
    // 
    //param
    //     pGeo : 增加的线串对象。
    //##ModelId=4562589701A5
    virtual IGeo_LineString* AddLineString(IGeo_Geometry* pGeo) = 0;

    //brief
    //     创建并添加线串对象。
    // 
    //return
    //     返回增加的线串对象的指针。
    //##ModelId=4562589701D5
    virtual IGeo_LineString* InsertLineString(int iIndex) = 0;

};

typedef IGeo_MultiLineString IGeo_MultiPathString;//为避免于Line接口意义混淆并将其区分

#endif /* IGEO_MULTILINESTRING_H_HEADER_INCLUDED_B9D31EC7 */
