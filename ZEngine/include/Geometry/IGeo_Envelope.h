#ifndef IGEO_ENVELOPE_H_HEADER_INCLUDED_B9D30230
#define IGEO_ENVELOPE_H_HEADER_INCLUDED_B9D30230
#include "IGeo_Geometry.h"
#include "..\common\SPo_DRect.h"
#include "..\common\SPo_DPoint.h"
class IPo_SpatialReference;

// �������ζ�����׽ӿ�
// ���׼�Ϊһ�����ο��������������С�߽�ֵ���������ֵ
// ����Ϊ�����Ŀռ伸�ζ����ṩһ�����ƶ����õı߽緶Χ
// ����һ���㣬��λ��ֻ�ж��������λ�ھ����ڻ���
//##ModelId=408C7E1C030D
class IGeo_Envelope : public IGeo_Geometry
{
  public:
    //brief
    //     ���þ��η�����Сx���������
    //param
    //     dMinx:��Сxֵ
    //##ModelId=456255F303D8
    virtual void SetXMin(double dXMin) = 0;

    //brief
    //     ���þ��η������x�������ұ�
    //param
    //     dXMax:���η������x
    //##ModelId=456255F4000F
    virtual void SetXMax(double dXMax) = 0;

    //brief
    //     ���þ��η�����Сy�������±�
    //param
    //     dYMin:���η�����Сy
    //##ModelId=456255F4002E
    virtual void SetYMin(double dYMin) = 0;

    //brief
    //     ���þ��η������y�������ϱ�
    //param
    //     dYMax:���η������y
    //##ModelId=456255F4004E
    virtual void SetYMax(double dYMax) = 0;

    //brief
    //     ���þ��η��ױ߽����
    //param
    //     sDRect:���α߽�ֵ
    // 
    //    
    //##ModelId=456255F4006D
    virtual void SetBoundRect(SPo_DRect sDRect) = 0;

    //brief
    //     ��ȡ���η�����Сx���������
    //return
    //     ���η�����Сx
    //##ModelId=456255F4008C
    virtual double GetXMin() = 0;

    //brief
    //     ��ȡ���η������x�������ұ�
    //return
    //     ���η������x
    //##ModelId=456255F4008E
    virtual double GetXMax() = 0;

    //brief
    //     ��ȡ���η�����Сy�������±�
    //return
    //     ���η�����Сy
    //##ModelId=456255F4009D
    virtual double GetYMin() = 0;

    //brief
    //     ��ȡ���η������y�������ϱ�
    //return
    //     ���η������y
    //##ModelId=456255F400AC
    virtual double GetYMax() = 0;

    //brief
    //     ��ȡ���η��ױ߽����
    //return
    //     ���ױ߽����
    //##ModelId=456255F400BC
    virtual SPo_DRect GetBoundRect() = 0;

    //brief
    //     ��ȡ���η��׸ߣ�YMax-YMin
    //return
    //     ���η��׸�
    //##ModelId=456255F400BE
    virtual double GetHeight() = 0;

    //brief
    //     ��ȡ���η��׵Ŀ�XMax-XMin
    //return
    //     ���η��׵Ŀ�
    //##ModelId=456255F400CC
    virtual double GetWidth() = 0;

    //brief
    //     �����η����ƶ�����ָ���ĵ�Ϊ���ĵ�λ��
    //param
    //     sPoint ָ����
    //     pSpatialReference: ָ�����Ӧ�Ŀռ�ο�ϵ��     ȱʡΪNULL����ʾʹ�ü��ζ�����Ŀռ�ο�      ϵ��
    //##ModelId=456255F400CE
    virtual bool CenterAt(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     �����η����ƶ�����ָ���ĵ�Ϊ���ĵ�λ��
    //param
    //     pPoint ָ����
    //##ModelId=456255F40109
    virtual bool CenterAt(const IGeo_Geometry* pPoint) = 0;

    //brief
    //     ���þ��η�����Сz��������С���
    //param
    //     dZMin:���η�����Сz
    //##ModelId=456255F40128
    virtual void SetZMin(double dZMin) = 0;

    //brief
    //     ��ȡ���η�����Сz��������С���
    //return
    //     ���η�����Сz
    //##ModelId=456255F40148
    virtual double GetZMin() = 0;

    //brief
    //     ���þ��η������z���������߳�
    //param
    //     dZMax:���η������z
    //##ModelId=456255F40158
    virtual void SetZMax(double dZMax) = 0;

    //brief
    //     ��ȡ���η������z���������߳�
    //return
    //     ���η������z
    //##ModelId=456255F40177
    virtual double GetZMax() = 0;

    //brief
    //     ��ȡ���η�����ȣ�ZMax-ZMin
    //return
    //     ���η������
    //##ModelId=456255F40187
    virtual double GetDepth() = 0;

    //brief
    //     ʹ���η�����������
    //param
    //     dx : x����ֱ�����dx  XMin-=dx; XMax+=dx;
    //     dy : y����ֱ�����dy  YMin-=dy; YMax+=dy;
    //     bRatio : �����Ƿ�ɱ���Ĭ��Ϊfalse���ӷ���    ��
    //     ��ע : �ɱ�Ϊ XMin-=dx*Width/2;     XMax+=dx*Width/2; YMin-=dy*Height/2;
    //     YMax+=dy*Height/2;
    //##ModelId=456255F40197
    virtual void Expand(double dx, double dy, bool bRatio = false) = 0;

    //brief
    //     ����Mֵ
    //param
    //     dm:M����dm
    //     asRatio:�Ƿ�ɱ�����
    //##ModelId=4562C16802BF
    virtual void ExpandM(double dm, bool asRatio) = 0;

    //brief
    //     ��Z�����������ž��η���
    //param
    //     dz : ����ֵ
    //     bRatio : �Ƿ�ɱ����ţ�Ĭ��Ϊfalse�������    ��
    //     ��ע : �ɱ�����Ϊ ZMin-=dz*Depth/2;     ZMax+=dz*Depth/2;
    //     �������Ϊ ZMin-=dz; ZMax+=dz;
    //##ModelId=456255F401E4
    virtual void ExpandZ(double dz, bool bRatio = false) = 0;

    //brief
    //     ����η���������ľ��η��׵Ľ���
    //param
    //     pEnvelope : �����ľ��η��׶���
    //return
    //     �ཻ����
    //##ModelId=456255F40222
    virtual SPo_DRect Intersect(const IGeo_Geometry* pEnvelope) = 0;

    //brief
    //     �жϾ������Ƿ������������
    //return
    //     �粻��������true
    // 
    //##ModelId=456255F40242
    virtual bool IsEmpty() = 0;

    //brief
    //     ɾ�����׶����е����е����
    // /return
    //     �ɹ�����true
    //##ModelId=456255F40252
    virtual bool SetEmpty() = 0;

    // ���ؼ��ζ�������ĵ㡣
    // ����˵�� : pSpatialReference: ���ζ������Ķ�Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����Ŀռ�ο�ϵ��
    //##ModelId=4562AD0701F4
    virtual SPo_DPoint GetCentroidPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //�������½ǵ�����
    //##ModelId=4562BFA501B5
    virtual void SetLowerLeft(const SPo_DPoint csPoint) = 0;

    //�õ����½ǵ�����
    //##ModelId=4562BFFB004E
    virtual SPo_DPoint GetLowerLeft() = 0;

    //�������½ǵ�����
    //##ModelId=4562C02F01D4
    virtual void SetLowerRight(const SPo_DPoint csPoint) = 0;

    //�õ����½ǵ�����
    //##ModelId=4562C02F01D6
    virtual SPo_DPoint GetLowerRight() = 0;

    //�������Ͻǵ�����
    //##ModelId=4562C047005D
    virtual void SetUpperLeft(const SPo_DPoint csPoint) = 0;

    //�õ����Ͻǵ�����
    //##ModelId=4562C047005F
    virtual SPo_DPoint GetUpperLeft() = 0;

    //�������Ͻǵ�����
    //##ModelId=4562C06F02DE
    virtual void SetUpperRight(const SPo_DPoint csPoint) = 0;

    //�õ����Ͻǵ�����
    //##ModelId=4562C06F02FD
    virtual SPo_DPoint GetUpperRight() = 0;

    //ƫ������
    //##ModelId=4562C1CD02BF
    virtual void Offset(double dx, double dy) = 0;

    //ƫ��Mֵ
    //##ModelId=4562C2250148
    virtual void OffsetM(double dz) = 0;

    //ƫ��Zֵ
    //##ModelId=4562C248007D
    virtual void OffsetZ(double dz) = 0;

    //���÷��׵Ľǵ�����
    //##ModelId=4562C2DB01E4
    virtual void PutCoords(const double XMin, const double XMax, const double YMin, const double YMax) = 0;

    //��ѯ����ǵ�
    //##ModelId=4562C4B60261
    virtual void QueryCoords(double &XMin, double &XMax, double &YMin, double &YMax) = 0;

    //�����׷�Χ����Ϊԭ�з�Χ��������׵Ľ�
    //##ModelId=4562C34D0128
    virtual void Intersect(IGeo_Envelope& inEnvelope) = 0;

    //����������Ϊԭ�з�Χ��������׵Ĳ�
    //##ModelId=4562C3B00222
    virtual void Union(IGeo_Envelope& inEnvelope) = 0;

};



#endif /* IGEO_ENVELOPE_H_HEADER_INCLUDED_B9D30230 */
