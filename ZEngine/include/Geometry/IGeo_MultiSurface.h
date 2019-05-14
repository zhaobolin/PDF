#ifndef IGEO_MULTISURFACE_H_HEADER_INCLUDED_B9D31943
#define IGEO_MULTISURFACE_H_HEADER_INCLUDED_B9D31943
#include "IGeo_Geometry.h"
class IGeo_Surface;

//brief
//     ���ζ������
//##ModelId=442B4BAC036B
class IGeo_MultiSurface : public IGeo_Geometry
{
  public:
    //brief
    //     �õ���ĸ���
    //param
    //     ��
    //return
    //     �����
    //##ModelId=45654F1D00DA
    virtual int GetSurfaceCount() = 0;

    //brief
    //     �õ������ָ��
    //param
    //     iIndex:����
    //return
    //     �����ָ��
    //##ModelId=45654F1D00EA
    virtual IGeo_Surface* GetSurfacePtr(int nIndex) = 0;

    //brief
    //     ɾ��ָ��λ�õ���
    //param
    //     iIndex:����
    //return
    //     ɾ���ɹ�����true
    //##ModelId=45654F1D00FA
    virtual bool DeleteSurface(int nIndex) = 0;

    //brief
    //     �滻ָ��λ�õ���
    //param
    //     pGeo:�����滻����
    //     iIndex:���滻������
    //return
    //     �滻�ɹ�����true
    //##ModelId=45654F1D0109
    virtual bool ReplaceSurface(IGeo_Surface* pGeo, int nIndex) = 0;

    //brief
    //     ��������
    //param
    //     pGeo:�����
    //return
    //     ��ӳɹ�����true
    //##ModelId=45654F1D0119
    virtual IGeo_Surface* AddSurface(IGeo_Surface* pGeo) = 0;

    //brief
    //     ����һ����
    //param
    //     iIndex:����λ��
    //     pGeo:���������
    //return
    //     ����ɹ�����true
    //##ModelId=45654F1D0128
    virtual bool InsertSurface(int iIndex, IGeo_Surface* pGeo) = 0;

};



#endif /* IGEO_MULTISURFACE_H_HEADER_INCLUDED_B9D31943 */
