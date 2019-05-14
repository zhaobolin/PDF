#ifndef IGEO_RECT_H_HEADER_INCLUDED_B9D30EE9
#define IGEO_RECT_H_HEADER_INCLUDED_B9D30EE9
#include "IGeo_Geometry.h"
class IPo_SpatialReference;
//struct SPo_DPoint;
//brief
//     �����漸�ζ���ӿ�
//##ModelId=442B4BE00261
class IGeo_Rect : public IGeo_Geometry
{
  public:
	
    //brief
    //     ���þ��ζ���ľ��η�Χ��
    //     ���ݸ����Ŀռ�ο�ϵ���þ��ζ���ľ��η�Χ
    //return
    //     ���óɹ����򷵻�true����pSpatialReference��    Ϊ�գ�������ת�����ɹ����򷵻�false��
    // 
    // param
    //     rect: �����õľ���
    //     pSpatialReference: ���õľ��ζ�Ӧ�Ŀռ�ο�    ϵ��ȱʡΪNULL����ʾʹ�þ��α���Ŀռ�ο�    ϵ��
    //##ModelId=45625C35009C
    virtual bool SetRect(SPo_DRect rect, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡ���ζ���ľ��η�Χ��
    //     ���ݸ����Ŀռ�ο�ϵ��ȡ���ζ���ľ��η�Χ
    //return
    //     ���ؾ��ζ���ľ��η�Χ��
    //param
    //     pSpatialReference��ϣ����ȡ�ľ��η�Χ����Ӧ    �Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�þ��α���    �Ŀռ�ο�ϵ��
    //##ModelId=45625C3500CB
    virtual SPo_DRect GetRect(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡ���θߣ�YMax-YMin
    //param
    //     ��
    //return
    //     ���θ�
    //##ModelId=45625C3500EA
    virtual double GetHeight() = 0;

    //brief
    //     ��ȡ���εĿ�XMax-XMin
    //param
    //     ��
    //return
    //     ���εĿ�
    //##ModelId=45625C3500FB
    virtual double GetWidth() = 0;

    //brief
    //      �������ƶ�����ָ���ĵ�Ϊ���ĵ�λ��
    //param
    //     sPoint ָ����
    //     pSpatialReference: ָ�����Ӧ�Ŀռ�ο�ϵ��    ȱʡΪNULL����ʾʹ�ü��ζ�����Ŀռ�ο�   ϵ��
    //return
    //      ���óɹ�����true
    //##ModelId=45625C35010A
    virtual bool CenterAt(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     �������ƶ�����ָ���ĵ�Ϊ���ĵ�λ��
    //param
    //      pPoint ָ����
    //return
    //      ���óɹ�����true
    //##ModelId=45625C350138
    virtual bool CenterAt(const IGeo_Geometry* pPoint) = 0;

    //brief
    //     ʹ������������
    //param
    //     dx : x����ֱ�����dx  XMin-=dx; XMax+=dx;
    //     dy : y����ֱ�����dy  YMin-=dy; YMax+=dy;
    //     bRatio : �����Ƿ�ɱ���Ĭ��Ϊfalse���ӷ���    ��
    //     ��ע : �ɱ�Ϊ XMin-=dx*Width/2;                   XMax+=dx*Width/2;
    // YMin-=dy*Height/2;
    //                   YMax+=dy*Height/2;
    //##ModelId=45625C350157
    virtual void Expand(double dx, double dy, bool bRatio = false) = 0;

    //brief
    //     �����������ľ��εĽ���
    //param
    //     pRect : �����ľ��ζ���
    //return
    //     �ཻ����
    //##ModelId=45625C3501A5
    virtual SPo_DRect Intersect(const IGeo_Geometry* pRect) = 0;

    //brief
    //      �жϾ������Ƿ������������
    //param
    //      ��
    //return
    //      �ǿշ���true
    //##ModelId=45625C3501C5
    virtual bool IsEmpty() = 0;

    //brief
    //      ɾ�����ζ����е����е����
    //param
    //      ��
    //return
    //      �ɹ�����true
    //##ModelId=45625C3501D4
    virtual bool SetEmpty() = 0;

};



#endif /* IGEO_RECT_H_HEADER_INCLUDED_B9D30EE9 */
