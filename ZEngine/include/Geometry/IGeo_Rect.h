#ifndef IGEO_RECT_H_HEADER_INCLUDED_B9D30EE9
#define IGEO_RECT_H_HEADER_INCLUDED_B9D30EE9
#include "IGeo_Geometry.h"
class IPo_SpatialReference;
//struct SPo_DPoint;
//brief
//     矩形面几何对象接口
//##ModelId=442B4BE00261
class IGeo_Rect : public IGeo_Geometry
{
  public:
	
    //brief
    //     设置矩形对象的矩形范围。
    //     根据给定的空间参考系设置矩形对象的矩形范围
    //return
    //     设置成功，则返回true；若pSpatialReference不    为空，且坐标转换不成功，则返回false。
    // 
    // param
    //     rect: 需设置的矩形
    //     pSpatialReference: 设置的矩形对应的空间参考    系。缺省为NULL，表示使用矩形本身的空间参考    系。
    //##ModelId=45625C35009C
    virtual bool SetRect(SPo_DRect rect, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     获取矩形对象的矩形范围。
    //     根据给定的空间参考系获取矩形对象的矩形范围
    //return
    //     返回矩形对象的矩形范围。
    //param
    //     pSpatialReference：希望获取的矩形范围所对应    的空间参考系。缺省为NULL，表示使用矩形本身    的空间参考系。
    //##ModelId=45625C3500CB
    virtual SPo_DRect GetRect(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     获取矩形高，YMax-YMin
    //param
    //     无
    //return
    //     矩形高
    //##ModelId=45625C3500EA
    virtual double GetHeight() = 0;

    //brief
    //     获取矩形的宽，XMax-XMin
    //param
    //     无
    //return
    //     矩形的宽
    //##ModelId=45625C3500FB
    virtual double GetWidth() = 0;

    //brief
    //      将矩形移动到以指定的点为中心的位置
    //param
    //     sPoint 指定点
    //     pSpatialReference: 指定点对应的空间参考系。    缺省为NULL，表示使用几何对象本身的空间参考   系。
    //return
    //      设置成功返回true
    //##ModelId=45625C35010A
    virtual bool CenterAt(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     将矩形移动到以指定的点为中心的位置
    //param
    //      pPoint 指定点
    //return
    //      设置成功返回true
    //##ModelId=45625C350138
    virtual bool CenterAt(const IGeo_Geometry* pPoint) = 0;

    //brief
    //     使矩形向外扩张
    //param
    //     dx : x方向分别外扩dx  XMin-=dx; XMax+=dx;
    //     dy : y方向分别外扩dy  YMin-=dy; YMax+=dy;
    //     bRatio : 外扩是否成倍，默认为false，加法外    扩
    //     备注 : 成倍为 XMin-=dx*Width/2;                   XMax+=dx*Width/2;
    // YMin-=dy*Height/2;
    //                   YMax+=dy*Height/2;
    //##ModelId=45625C350157
    virtual void Expand(double dx, double dy, bool bRatio = false) = 0;

    //brief
    //     求矩形与给定的矩形的交集
    //param
    //     pRect : 给定的矩形对象
    //return
    //     相交矩形
    //##ModelId=45625C3501A5
    virtual SPo_DRect Intersect(const IGeo_Geometry* pRect) = 0;

    //brief
    //      判断矩形中是否含有其它点对象
    //param
    //      无
    //return
    //      是空返回true
    //##ModelId=45625C3501C5
    virtual bool IsEmpty() = 0;

    //brief
    //      删除矩形对象中的所有点对象
    //param
    //      无
    //return
    //      成功返回true
    //##ModelId=45625C3501D4
    virtual bool SetEmpty() = 0;

};



#endif /* IGEO_RECT_H_HEADER_INCLUDED_B9D30EE9 */
