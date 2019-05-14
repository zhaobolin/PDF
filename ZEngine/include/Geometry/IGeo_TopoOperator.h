#ifndef IGEO_TOPOOPERATOR_H_HEADER_INCLUDED_B9D3074C
#define IGEO_TOPOOPERATOR_H_HEADER_INCLUDED_B9D3074C
class IGeo_Geometry;
class IGeo_Envelope;

/// \brief 拓扑运算器，缓冲区、裁减、并、差、交运算
//##ModelId=442B783C0119
class IGeo_TopoOperator
{
  public:
    //brief
    //     获取几何对象边界，维数降低，如线的边界为点，点的边界为空
    //param
    //     rBoundary:用于返回边界值
    //return
    //     返回成功返回true
    //##ModelId=45666284008C
    virtual Boolean GetBoundary(IGeo_Geometry& rBoundary) = 0;

    //brief
    //     求几何对象的缓冲区
    //param
    //     dDistance:建立缓冲区的距离
    //     pBuffer:返回建立的缓冲区几何对象 
    //return
    //     建立缓冲区成功，返回true
    //##ModelId=456901230138
    virtual bool Buffer(double dDistance, IGeo_Geometry* pBuffer) = 0;

    //brief
    //     用输入的封套裁减几何对象
    //param
    //     rEnvelope:裁减几何对象的封套
    //     pResult:裁减后得到的几何对象
    //return:
    //     如果裁减成功，返回true
    //##ModelId=456901F9034B
    virtual bool Clip(IGeo_Envelope& rEnvelope, IGeo_Geometry* pResult) = 0;

    //brief
    //     计算几何对象的凸壳
    //param
    //     无
    //return
    //     计算成功返回true
    //    
    //##ModelId=456902CE0261
    virtual bool ConvexHull() = 0;

    //brief
    //     用折线串切割几何对象
    //param
    //     rPolyline:用于切割的折线串
    //     pLeftGeom:切割后左半部几何对象
    //     pRightGeom:切割后右半部几何对象
    //return
    //     如果切割成功返回true
    //##ModelId=45690347031C
    virtual bool Cut(IGeo_Polyline &rPolyline, IGeo_Geometry* pLeftGeom, IGeo_Geometry* pRightGeom) = 0;

    //brief
    //     求几何对象之差
    //param
    //     rOtherGeo:输入的几何对象，求当前几何对象与该对象之差
    //     pOutGeom:返回结果几何对象
    //return
    //     如果计算成功，返回true
    //##ModelId=4569042C034B
    virtual bool Difference(IGeo_Geometry& rOtherGeom, IGeo_Geometry* pOutGeom) = 0;

    //brief
    //     计算已知几何对象与输入几何对象的交
    //param
    //     rOtherGeom:输入的几何对象
    //     rGeoDim:结果几何的维度
    //     pOutGeom:返回结果几何对象
    //return
    //     计算成功，返回true
    //##ModelId=456904E60271
    virtual bool Intersect(IGeo_Geometry& rOtherGeom, poenumGeometryDimension& rGeoDim, IGeo_Geometry* pOutGeom) = 0;

    //brief
    //     求并
    //param
    //     rOtherGeom:输入的几何对象
    //     pOutGeom:返回结果几何对象
    //return
    //     如果结算成功返回true
    //##ModelId=456905F6031C
    virtual bool Union(IGeo_Geometry& rOtherGeom, IGeo_Geometry* pOutGeom) = 0;

};



#endif /* IGEO_TOPOOPERATOR_H_HEADER_INCLUDED_B9D3074C */
