#ifndef IGEO_MULTILINESTRING_H_HEADER_INCLUDED_B9D31EC7
#define IGEO_MULTILINESTRING_H_HEADER_INCLUDED_B9D31EC7
#include "IGeo_Geometry.h"
class IGeo_LineString;

//brief
//    �ߴ����϶���ӿڣ����ɸ��ߴ��ļ��ζ���
//##ModelId=442B47F60177
class IGeo_MultiLineString : public IGeo_Geometry
{
  public:
    //brief
    //     ��ȡ���߼��϶����ж��߶���ĸ�����
    //return
    //     ���߶���ĸ�����
    //##ModelId=456258970109
    virtual int GetLineStringCount() = 0;

    //brief
    //     ��ȡ���߼��ζ���
    //     �����±��ȡ���߼��ζ����ָ�롣
    //return
    //     ָ���±��Ӧ�Ķ��߶����ָ�롣
    //param
    //     nIndex: �����ȡ�ļ��ζ�����±ꡣ
    // 
    //     ��ע : �û�Ӧ���ݼ��ζ������ͣ�������ֵǿ��    ת��Ϊ��Ӧ��GeoXXXָ�롣
    //##ModelId=45625897011A
    virtual IGeo_LineString* GetLineStringPtr(int nIndex) = 0;

    //brief
    //     ɾ���ߴ����ζ���
    //     �����±�λ��ɾ���ߴ����ζ���
    //     ɾ���ɹ����򷵻�true�����򷵻�false��
    //param
    //     nIndex: �豻ɾ�����ߴ�������±�λ�á�
    // 
    //     ��ע : 0<=nIndex<���ζ���������������ζ���    ���±꽫�����䶯�����ζ��������1��
    //##ModelId=456258970148
    virtual bool DeleteLineString(int nIndex) = 0;

    //brief
    //     �ø������ߴ������滻�����������ߴ�����
    // 
    //return
    //     �ɹ�����true�� ���򷵻�false
    // 
    //param
    //     pGeo �����滻�����������ߴ�����
    //     nIndex ��Ҫ���滻���ߴ����������
    //##ModelId=456258970167
    virtual bool ReplaceLineString(IGeo_Geometry* pGeo, int nIndex) = 0;

    //brief
    //     ����ߴ�����Ϊ�ߴ���������һ���ߴ����ζ���
    // 
    //return
    //     �ɹ�����true�� ���򷵻�false
    // 
    //param
    //     pGeo : ���ӵ��ߴ�����
    //##ModelId=4562589701A5
    virtual IGeo_LineString* AddLineString(IGeo_Geometry* pGeo) = 0;

    //brief
    //     ����������ߴ�����
    // 
    //return
    //     �������ӵ��ߴ������ָ�롣
    //##ModelId=4562589701D5
    virtual IGeo_LineString* InsertLineString(int iIndex) = 0;

};

typedef IGeo_MultiLineString IGeo_MultiPathString;//Ϊ������Line�ӿ������������������

#endif /* IGEO_MULTILINESTRING_H_HEADER_INCLUDED_B9D31EC7 */
