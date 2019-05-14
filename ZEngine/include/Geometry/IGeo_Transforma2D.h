#ifndef IGEO_TRANSFORMA2D_H_HEADER_INCLUDED_B9D36B3F
#define IGEO_TRANSFORMA2D_H_HEADER_INCLUDED_B9D36B3F
#include "SPo_DRect.h"
class IGeo_Point;

/// \brief ��ά�任��ƽ�ơ���ת������
//##ModelId=442B796D03B9
class IGeo_Transforma2D
{
  public:
    //brief
    //     ʹ���ζ����λ�����������ϰ�ָ����ƫ������    ��ƫ�ơ�
    //return
    //     �ɹ�����true�����򷵻�false��
    //param
    //     dx: ˮƽ�����ƫ����
    //     dy: ��ֱ�����ƫ����
    //##ModelId=4562A7FE000F
    virtual bool Move(double dx, double dy) = 0;

    //brief
    //     ���ż��ζ���ʹ֮����ָ���ķ�Χ�ڡ�
    //return
    //     �ɹ�����true�����򷵻�false��
    //param
    //     rect: ������С�����ķ�Χ
    //     
    //##ModelId=4562A8150232
    virtual bool Resize(SPo_DRect rect) = 0;

    //brief
    //     ���ζ�����ת����ʱ�뷽��
    //return
    //     �ɹ�����true�����򷵻�false��
    //param
    //     rPoint: ��ת�Ļ���
    //     dAngle: ��ת�ĽǶȣ���λΪ��
    //     ��ע : dAngleΪ��ʱ����ʱ����ת��dAngleΪ��    ʱ��˳ʱ����ת��
    //##ModelId=4562A827004E
    virtual bool Rotate(IGeo_Point& rPoint, double dAngle) = 0;

    //brief
    //     ��ָ���������з������ζ���
    //param
    //     dRatioX: ˮƽ������
    //     dRatioY: ��ֱ������
    //##ModelId=4562A845037A
    virtual bool Scale(double dRatioX, double dRatioY) = 0;

    //brief
    //     �Լ��ζ�����ж���任
    //param
    //     enumDirection:����������任
    //     rTransformation:����ı任
    //return
    //     �ɹ�����true
    //##ModelId=456A57B303D8
    virtual bool Trandform(poenumTrandformDirection enumDirection, IGeo_Transform &rTransform) = 0;

};



#endif /* IGEO_TRANSFORMA2D_H_HEADER_INCLUDED_B9D36B3F */
