#ifndef IGEO_POLYCURVE_H_HEADER_INCLUDED_B9D3211E
#define IGEO_POLYCURVE_H_HEADER_INCLUDED_B9D3211E
#include "IGeo_Curve.h"
class IGeo_Point;

//brief
//     �������
//##ModelId=4564FBF6005D
class IGeo_PolyCurve : public IGeo_Curve
{
  public:
    //brief
    //     �����߶�
    // 
    //param
    //     dMaxSegmentLength:���ܺ����γ�
    //     dMaxDeviation:���ƫ����
    // 
    //return
    //     ���ܳɹ�������true
    //##ModelId=456513800119
    virtual bool Densify(double dMaxSegmentLength, double dMaxDeviation) = 0;

    //brief
    //     �߶��ۺ�
    // 
    //param
    //     dMaxOffset:���ƫ����
    // 
    //return
    //     �߶��ۺϳɹ�������true
    //##ModelId=4565140202BF
    virtual bool Generalize(double dMaxOffset) = 0;

    //brief
    //     �߶ι⻬
    // 
    //param
    //     dMaxOffset:���ƫ����
    // 
    //return
    //     �⻬�ɹ�������true
    //##ModelId=4565144000DA
    virtual bool Smooth(double dMaxOffset) = 0;

    //brief
    //     ��ָ��λ�÷��뼸�ζ���
    // 
    //param
    //     dDistance:����
    //     asRatio:�����ǰ������߼��㣬true
    // 
    //return
    //      �ɹ���true
    //##ModelId=4565146C0128
    virtual bool SplitAtDistance(double dDistance, bool bRatio) = 0;

    //brief
    //     �������������ĵط�����һ��
    // 
    //param
    //     pPoint:�������Ϣ
    // 
    //return
    //     �ɹ���true
    //##ModelId=456515280128
    virtual bool SplitAtPoint(IGeo_Point* pPoint) = 0;

    //brief
    //     �ۺ�
    // 
    //param
    //     dMaxOffsetFactor:�������ƫ������
    // 
    //return
    //     �ɹ���true
    //##ModelId=4565162903B9
    virtual bool Weed(double dMaxOffsetFactor) = 0;

};



#endif /* IGEO_POLYCURVE_H_HEADER_INCLUDED_B9D3211E */
