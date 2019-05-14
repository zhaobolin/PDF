#ifndef IGEO_SURFACE_H_HEADER_INCLUDED_B9D32A15
#define IGEO_SURFACE_H_HEADER_INCLUDED_B9D32A15
#include "IGeo_Geometry.h"
#include "IGeo_LineString.h"
class IGeo_PolyLine;

///brief
//      �棬��ı������ߴ����൱��arcinfo��ring
//##ModelId=442B4ACC000F
class IGeo_Surface : public IGeo_Geometry
{
  public:
    //brief
    //     ��ȡ�⻷��Ŀ
    //param
    //     ��
    //return
    //     �⻷����
    //##ModelId=45654EB40290
    virtual int GetExteriorRingCount() = 0;

    //brief
    //     ��ȡָ�����ߴ��������ڻ���Ŀ
    //param
    //     rRing:ָ�����ߴ�
    //return
    //     �ڻ�����
    //##ModelId=45654EB4029F
    virtual int GetInteriorRingCount(IGeo_PolyLine *rRing) = 0;

    //brief
    //     ���Ұ���ָ���ڻ����⻷
    //param
    //     rInterRing:�ڻ�
    //return
    //     �⻷����
    //##ModelId=45654EB402A1
    virtual IGeo_LineString * FindExteriorRing(IGeo_LineString * rInterRing) = 0;

    //brief
    //     ��ȡ�����⻷
    //param
    //     rExteriorRing:���ڷ����⻷
    //return
    //     �����⻷�ɹ�true
    //##ModelId=45654EB402AF
    virtual bool GetExteriorRings(IGeo_LineString* pExteriorRing) = 0;

    //brief
    //     ����ָ���⻷���ڻ�
    //param
    //     rExteriorRing:ָ���⻷
    //     pInteriorRing:�����ڻ�
    //return
    //     �ɹ�true
    //  
    //##ModelId=45654EB402BF
    virtual bool GetInteriorRings(IGeo_LineString * rExteriorRing, IGeo_LineString* pInteriorRings) = 0;

};



#endif /* IGEO_SURFACE_H_HEADER_INCLUDED_B9D32A15 */
