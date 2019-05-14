#ifndef IGEO_POLYGON_H_HEADER_INCLUDED_B9D3434F
#define IGEO_POLYGON_H_HEADER_INCLUDED_B9D3434F
#include "IGeo_Geometry.h"
#include "..\common\SPo_DPoint.h"
class IPo_SpatialReference;
class IGeo_PolyLine;

	//任意形状单环
#define PLNSTYLE_SGLANY 1
		//任意形状多环
#define PLNSTYLE_MLTANY 2
		//正多边形
#define PLNSTYLE_SPZDBX 3
		//平行四边形
#define PLNSTYLE_SPXSBX 4

#define NM_PLNSTYLE_SGLANY "单环多边形"
#define NM_PLNSTYLE_MLTANY "多环多边形"
#define NM_PLNSTYLE_SPZDBX "正多边形"
#define NM_PLNSTYLE_SPXSBX "平行四边形"
//brief
//     多边形，是面的特例，边线是折线
//##ModelId=442B2F260128
class IGeo_Polygon : public IGeo_Geometry
{
  public:
	//获取的iIndex个环的类型(内环外环？)
	//##ModelId=46F8B0990167
    virtual PO_GEORING_TYPE GetRingTypeOf(int iIndex) = 0;
	//获取环的总个数
	//##ModelId=46AF55160251
    virtual int GetRingsCount() = 0;
	//获取第index个环的节点个数
	//##ModelId=46AF55160253
    virtual int GetRingPointsCountOfIndex(int iIndex) = 0;

    //brief
    //     设置多边形内点。
    //     根据给定的空间参考系和内点坐标设置多边形内点。
    //return
    //     内点设置成功，则返回true，否则返回false。
    //param
    //      sPoint: 所设置的内点坐标。
    //      pSpatialReference: 所设置的内点坐标对应的     空间参考系。缺省为NULL，表示使用多边形本身
    // 的空间参考系。
    //##ModelId=45625BBE000F
    virtual bool SetCentralPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     获取多边形的内点。
    //return
    //     多边形内点；若需要重新计算内点，且计算不成功，则返回SPo_Point (0,0)。
    //param
    //      nMode : 获取方式。可能的取值为：
    //      PO_COMPUTE_OFF：不计算，直接返回当前值（缺省参数设置）；
    //      PO_COMPUTE_ON：重新计算；
    //      PO_COMPUTE_ONCE：如果没有计算过，则计算；     否则直接返回当前值。
    //      pSpatialReference：希望获取的内点所对应的     空间参考系。缺省为NULL，表示使用多边形本身
    // 的空间参考系。
    //##ModelId=45625BBE004E
    virtual SPo_DPoint GetCentralPoint(int nMode = GIS_COMPUTE_OFF, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     创建多边形内点。
    //return
    //     创建成功，则返回多边形内点，否则返回    SPo_Point (0,0)。
    //##ModelId=45625BBE007D
    virtual bool CreateCentralPoint() = 0;

    //brief
    //      将面的所有折线串封闭。
    //param
    //      无
    //return
    //      封闭成功返回true
    //何列松认为要进行的步骤如下
    // 1.将重复点号的个数记录到封闭环的链表中如果单环，最后多出一个重复点和起点重合。
    // 2.调整岛与洞的坐标次序，岛变现前进方向向右为内，洞与岛的表示刚好相反。
    //##ModelId=45625BBE00FA
    virtual bool CloseAll() = 0;

    //brief
    //     获取外环数目
    //param
    //     无
    //return
    //     外环数目 
    //##ModelId=45654C0503D8
    virtual int GetExteriorRingCount() = 0;

    //brief
    //     获取指定折线串包含的内环数目
    //param
    //     rRing:指定折线串
    //return
    //     内环数目
    //##ModelId=45654C4F006D
    virtual int GetInteriorRingCount(IGeo_PolyLine* rRing) = 0;

    //brief
    //     查找指定内环的外环
    //param
    //     rInterRing:指定内环
    //return
    //     外环折线串
    //##ModelId=45654CC60148
    virtual IGeo_PolyLine* FindExteriorRing(IGeo_PolyLine* rInterRing) = 0;

    //brief
    //     获取所有外环
    //param
    //     无
    //return
    //     所有外环对象
    //##ModelId=45654D2D0109
    virtual bool GetExteriorRings(IGeo_PolyLine* pExteriorRing) = 0;

    //brief
    //      查找指定外环的所有内环
    //param
    //      rExteriorRing:指定外环
    //      pInteriorRings:所有内环
    //return
    //      成功true
    //##ModelId=45654D7A036B
    virtual bool GetInteriorRings(IGeo_PolyLine* rExteriorRing, IGeo_PolyLine* pInteriorRings) = 0;

    //brief
    //     简化图形保留始末点
    //param
    //     无
    //return
    //     简化成功返回true
    //##ModelId=45654DC80177
    virtual bool SimplifyPreserveFromTo() = 0;
    //##ModelId=465558DC0157
    virtual bool AddPoint(SPo_DPoint sPoint, IPo_SpatialReference *pSpatialReference) = 0;
	//获取内部面串信息，以便在外部操控
	virtual vector<int> *GetRingsFramePtr() = 0;
};



#endif /* IGEO_POLYGON_H_HEADER_INCLUDED_B9D3434F */
