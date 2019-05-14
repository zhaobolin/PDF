#ifndef IGEO_POINT_H_HEADER_INCLUDED_B9D30AB5
#define IGEO_POINT_H_HEADER_INCLUDED_B9D30AB5
#include "IGeo_Geometry.h"
class IPo_SpatialReference;

//brief
//     基本几何对象--点对象接口
//##ModelId=442B2E28008C
class IGeo_Point : public IGeo_Geometry
{
  public:
    //brief
    //     设置定位点。
    //     根据给定的空间参考系设置定位点。
    //return
    //      定位点设置成功，返回true; 若     pSpatialReference不为空，且坐标转换不成功    ，则返回false。
    //param
    //      sPoint: 需设置的定位点。
    //      pSpatialReference: 定位点对应的空间参考系     。缺省为NULL，表示使用点本身的空间参考系。
    //##ModelId=4562578F0148
    virtual bool SetPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL, 
        // 要设置点坐标的索引号,如果是实体点,内部只插入一个点坐标,如果是有向点,0表明插入第一点,1表明插入第二点即方向点坐标.
        int iIndex = 0) = 0;

    /// \brief 设置方向点。
    /// 
    /// 根据给定的空间参考系设置方向点。
    /// 
    /// \return 方向点设置成功，则返回true；若pSpatialReference不为空，且坐标转换不成功，则返回false。
    /// 
    /// \param sPoint: 需设置的方向点。
    /// \param pSpatialReference: 方向点对应的空间参考系。缺省为NULL，表示使用点本身的空间参考系。
    /// 
    //##ModelId=4563EF6F0280
    virtual SPo_DPoint GetPoint(int iIndex = 0, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     设置方向点。
    //     根据给定的空间参考系设置方向点。
    //return
    //     方向点设置成功，则返回true；若    pSpatialReference不为空，且坐标转换不成功，    则返回false。
    //param
    //     sPoint: 需设置的方向点。
    //     pSpatialReference: 方向点对应的空间参考系。    缺省为NULL，表示使用点本身的空间参考系。
    //##ModelId=4562578F0177
    virtual bool SetDirectionPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     获取方向点。
    //     根据给定的空间参考系获取方向点的坐标。
    //return
    //     方向点的坐标。
    //param
    //      pSpatialReference: 希望所获取的方向点对应     的空间参考系。缺省为NULL，表示使用点本身的
    // 空间参考系。
    //      备注 : 若pSpatialReference不为空，且坐标转     换不成功，则返回SGIS_Point(0,0)。
    //##ModelId=4562578F01B5
    virtual SPo_DPoint GetDirectionPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     计算点对象到其他对象的距离，单位与该点对象    的单位相同。
    //return
    //     成功返回点对象到其它对象的距离，否则返回负    值。
    //param
    //     pGeo: 其它对象
    //##ModelId=4562578F01D4
//    virtual double GetDistanceTo(const IGeo_Geometry* pGeo) = 0;

    //brief
    //     获取ID值，用于用户编程
    //return
    //     ID值
    //##ModelId=4563FB7C030D
    virtual unsigned long GetID() = 0;

    //brief
    //     设置ID值，用于用户编程
    //param
    //     lValue:ID值
    //return
    //     设置成功返回true
    //##ModelId=4563FBAB001F
    virtual bool SetID(unsigned long lValue) = 0;

    //brief
    //     获取Measure值，用于诸如动态分段等分析
    //param
    //     无
    //return
    //     Measure值
    //##ModelId=4563FBFC00CB
    virtual double GetM() = 0;

    //brief
    //     设置Measure值，用于诸如动态分段等分析
    //param
    //     dM:Measure值
    //return
    //     设置成功返回true
    //##ModelId=4563FC3A038A
    virtual bool SetM(double dM) = 0;

};



#endif /* IGEO_POINT_H_HEADER_INCLUDED_B9D30AB5 */
