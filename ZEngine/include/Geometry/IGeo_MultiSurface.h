#ifndef IGEO_MULTISURFACE_H_HEADER_INCLUDED_B9D31943
#define IGEO_MULTISURFACE_H_HEADER_INCLUDED_B9D31943
#include "IGeo_Geometry.h"
class IGeo_Surface;

//brief
//     几何多面对象
//##ModelId=442B4BAC036B
class IGeo_MultiSurface : public IGeo_Geometry
{
  public:
    //brief
    //     得到面的个数
    //param
    //     无
    //return
    //     面个数
    //##ModelId=45654F1D00DA
    virtual int GetSurfaceCount() = 0;

    //brief
    //     得到面对象指针
    //param
    //     iIndex:序数
    //return
    //     面对象指针
    //##ModelId=45654F1D00EA
    virtual IGeo_Surface* GetSurfacePtr(int nIndex) = 0;

    //brief
    //     删除指定位置的面
    //param
    //     iIndex:序数
    //return
    //     删除成功返回true
    //##ModelId=45654F1D00FA
    virtual bool DeleteSurface(int nIndex) = 0;

    //brief
    //     替换指定位置的面
    //param
    //     pGeo:用来替换的面
    //     iIndex:被替换面序数
    //return
    //     替换成功返回true
    //##ModelId=45654F1D0109
    virtual bool ReplaceSurface(IGeo_Surface* pGeo, int nIndex) = 0;

    //brief
    //     添加面对象。
    //param
    //     pGeo:添加面
    //return
    //     添加成功返回true
    //##ModelId=45654F1D0119
    virtual IGeo_Surface* AddSurface(IGeo_Surface* pGeo) = 0;

    //brief
    //     插入一个面
    //param
    //     iIndex:插入位置
    //     pGeo:插入面对象
    //return
    //     插入成功返回true
    //##ModelId=45654F1D0128
    virtual bool InsertSurface(int iIndex, IGeo_Surface* pGeo) = 0;

};



#endif /* IGEO_MULTISURFACE_H_HEADER_INCLUDED_B9D31943 */
