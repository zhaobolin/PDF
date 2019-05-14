#ifndef IGEO_POLYLINE_H_HEADER_INCLUDED_B9D32CC6
#define IGEO_POLYLINE_H_HEADER_INCLUDED_B9D32CC6
#include "IGeo_PolyCurve.h"
class IPo_SpatialReference;
class IGeo_Geometry;

//brief
//     折线几何对象接口
//     折线由一系列点连接而成，如果折线首尾封闭就构成面对象Polygon的边界
//##ModelId=442B4B58006D
class IGeo_PolyLine : public IGeo_PolyCurve
{
  public:
    //brief
    //     添加顶点。
    //     根据给定的空间参考系添加顶点。
    // 
    //return
    //     添加成功，则返回true，否则返回false。
    // 
    //param
    //     sPoint: 所添加的顶点坐标。
    //     pSpatialReference: 所添加的顶点坐标对应的空间参考系。缺省为NULL，表示使用折线本身的空间参考系。
    //##ModelId=456259700213
    virtual bool AddPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     添加顶点。
    //     根据给定的空间参考系添加顶点。
    // 
    //return
    //     添加成功，则返回true，否则返回false。
    // 
    //param
    //     pPoint: 所添加的顶点－点对象。
    //##ModelId=456259700251
    virtual bool AddPoint(const IGeo_Geometry* pPoint) = 0;

    //brief
    //     设置折线的顶点坐标。
    //     根据给定的空间参考系设置指定下标的顶点坐标。
    // 
    //return
    //     设置成功，则返回true，否则返回false。
    // 
    //param
    //     nIndex: 需设置坐标的顶点的下标。
    //     sPoint: 所设置的顶点坐标。
    //     pSpatialReference: 所设置的顶点坐标对应的空间参考系。缺省为NULL，表示使用折线本身的空间参考系。
    //##ModelId=456259700271
    virtual bool SetPoint(int nIndex, SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     设置折线的顶点坐标。
    //     根据给定的空间参考系设置指定下标的顶点坐标。
    // 
    //return
    //     设置成功，则返回true，否则返回false。
    // 
    //param
    //     nIndex: 需设置坐标的顶点的下标。
    //     pPoint: 所设置的顶点－点对象。
    //##ModelId=4562597002BF
    virtual bool SetPoint(int nIndex, const IGeo_Geometry* pPoint) = 0;

    //brief
    //     替换折线中若干个顶点。
    //     用给定的折线的所有顶点替换本折线中指定下标范围的顶点。
    // 
    //return
    //     替换成功，则返回true，否则返回false。
    // 
    //param
    //     nBeginIndex: 被替换顶点的起始下标位置。
    //     nEndIndex: 被替换顶点的终止下标位置。
    //     pPolyLine: 用来替换顶点的折线。
    //     备注 :
    // 0<=nBeginIndex,nEndIndex<顶点个数;替换顶点时重新分配内存;替换顶点后，后续顶点的下标将发生变动，顶点个数也将改变。
    //##ModelId=4562597002EE
    virtual bool ReplacePointsByIndex(int nBeginIndex, int nEndIndex, const IGeo_Geometry* pPolyLine) = 0;

    //brief
    //     删除顶点。
    //     根据下标位置删除顶点。
    // 
    //return
    //     删除成功，则返回true，否则返回false。
    // 
    //param
    //     nIndex: 需被删除的顶点的下标位置。
    //##ModelId=45625970033C
    virtual bool DeletePoint(int nIndex) = 0;

    //brief
    //     删除顶点。
    //     根据给定的点坐标和空间坐标系删除顶点。
    // 
    //return
    //     删除成功，则返回true，否则返回false。
    // 
    //param
    //     sPoint: 需被删除的顶点位置。
    //     pSpatialReference: 给定点对应的空间参考系。缺省为NULL，表示使用多边形本身的空间参考系。
    //            dTolerance: 阈值，以点为圆心，阈值为半径的圆内的顶点则被删除。
    //##ModelId=45625970035B
    virtual bool DeletePoint(SPo_DPoint * sPoint, IPo_SpatialReference* pSpatialReference = NULL, double dTolerance = 0.0) = 0;

    //brief
    //     将折线封闭。
    //     将折线的封闭，使得首尾顶点相等
    // 
    //return
    //     折线封闭成功，则返回true，否则返回false。
    //##ModelId=4562597003BA
    virtual bool Close() = 0;

    //brief
    //     添加顶点。
    //     根据给定的空间参考系和下标位置，在下标位置后添加顶点。
    // 
    // 
    //return
    //     添加成功，则返回true，否则返回false。
    // 
    //param
    //     nIndex: 需添加顶点的下标位置。
    //     sPoint: 所添加的顶点坐标。
    //     pSpatialReference: 所添加的顶点坐标对应的空间参考系。缺省为NULL，表示使用折线对象本身的空间参考系。
    //     备注 : 0<iIndex<顶点个数；添加顶点时重新分配内存；后续顶点的下标将发生变动，顶点个数加1，不改变首末结点
    //##ModelId=45625971009C
    virtual bool InsertPoint(int nIndex, SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     添加顶点。
    //     根据给定的点几何对象和下标位置，在下标位置后添加顶点。
    // 
    // 
    //return
    //     添加成功，则返回true，否则返回false。
    // 
    //param
    //     nIndex: 需添加顶点的下标位置。
    //     pPoint: 所添加的顶点的点对象。
    // 
    //     备注 : 0<iIndex<顶点个数；添加顶点时重新分配内存；后续顶点的下标将发生变动，顶点个数加1，不改变首末结点
    //##ModelId=4562597100EA
    virtual bool InsertPoint(int nIndex, const IGeo_Geometry* pPoint) = 0;

};



#endif /* IGEO_POLYLINE_H_HEADER_INCLUDED_B9D32CC6 */
