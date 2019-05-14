#ifndef IGEO_PROXIMITYOPERATOR_H_HEADER_INCLUDED_B9D30653
#define IGEO_PROXIMITYOPERATOR_H_HEADER_INCLUDED_B9D30653
class IGeo_Point;
class IGeo_Geometry;

//brief
//     邻近判定
//##ModelId=456A453B00DA
class IGeo_ProximityOperator
{
  public:
    //brief
    //     查询离输入点最近的点对象
    //parameter
    //     rPoint:输入点对象
    //     enumExtent:线段扩展方式
    //     pPoint:返回点对象
    //return
    //     计算成功，返回true
    //##ModelId=456A45B5032C
    virtual bool QueryNearestPoint(IGeo_Point& rPoint, poenumSegmentExtent enumExtent, IGe_Point *pPoint) = 0;

    //brief
    //     求两几何对象之间的距离
    //##ModelId=456A4C5B030D
    virtual double Distance(IGeo_Geometry& rGeometry) = 0;

    //brief
    //     创建并返回最近的点对象
    //param
    //     rPoint:输入点对象
    //     enumExtent:线段扩展方式
    //     pPoint:返回点对象
    //##ModelId=456A4CB30167
    virtual bool ReturnNearestPoint(IGeo_Point& rPoint, poenumSegmentExtent enumExtent, IGeo_Point* pPoint) = 0;

};



#endif /* IGEO_PROXIMITYOPERATOR_H_HEADER_INCLUDED_B9D30653 */
