#ifndef IGEO_RELATIONOPERATOR_H_HEADER_INCLUDED_B9D36C17
#define IGEO_RELATIONOPERATOR_H_HEADER_INCLUDED_B9D36C17
class IGeo_Geometry;

/// \brief 关系运算器，包含、相触、相交运算器
//##ModelId=442B78A70177
class IGeo_RelationOperator
{
  public:
    //brief
    //    已知几何对象是否包含输入几何对象
    //param
    //    rOtherGeom:被判断几何对象
    //return
    //    rOtherGeom被包容返回true
    //##ModelId=456907110196
    virtual bool Contains(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     判断两几何对象是否相交,交的维度小于包含几何对象
    //param
    //     rOtherGeom:被判断几何对象
    //return
    //     如果成功，返回true
    //##ModelId=45690BC503C8
    virtual bool Crosses(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     判断两几何对象是否相离
    //param
    //     rOtherGeom:被判断几何对象
    //rerurn
    //     如果相离返回true
    //##ModelId=45690D710271
    virtual bool Disjoint(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     判断两几何对象是否严格相等
    //param
    //     rOtherGeom:被判断几何对象
    //return
    //     如果两几何对象相等返回true
    //##ModelId=45690DEF0232
    virtual bool Equals(IGe_Geometry &rOtherGeom) = 0;

    //brief
    //     判断两几何对象的交是否与已知几何对象具有相同维度,是否重叠。
    //param
    //     rOtherGeom:被判断几何对象
    //return
    //     如果重叠，返回true
    //##ModelId=45690EB9000F
    virtual bool Overlaps(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     判断两几何对象有共同边界
    //param
    //     rOtherGeom:被判断几何对象
    //return
    //    如果相触，返回true
    //##ModelId=45690F8901A5
    virtual bool Touches(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     判断几何对象是否被包含
    //return
    //    如果包含，返回true
    //##ModelId=45690FFE03D8
    virtual bool Within(IGeo_Geometry& rOtherGeom) = 0;

};



#endif /* IGEO_RELATIONOPERATOR_H_HEADER_INCLUDED_B9D36C17 */
