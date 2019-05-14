#ifndef IGEO_ELLIPSE_H_HEADER_INCLUDED_B9D37C3F
#define IGEO_ELLIPSE_H_HEADER_INCLUDED_B9D37C3F
//brief
//     ��Բ�漸�ζ���
//##ModelId=442B4BF70399
class IGeo_Ellipse : public IGeo_Geometry
{
  public:
    //brief
    //     ������Բ�ĳ���
    //param
    //     dAxis:����
    //return
    //     ��
    //##ModelId=45625C12006D
    virtual void SetPrimaryAxis(double dAxis) = 0;

    //brief
    //     ��ȡ��Բ�ĳ���뾶
    //param
    //     ��
    //return
    //     ����뾶
    //##ModelId=45625C12008C
    virtual double GetPrimaryAxis() = 0;

    //brief
    //     ������Բ�Ķ���
    //param
    //     dAxis:����뾶
    //return
    //     ��
    //##ModelId=45625C12009D
    virtual void SetSecondaryAxis(double dAxis) = 0;

    //brief
    //     ��ȡ��Բ�Ķ���뾶
    //param
    //     ��
    //return
    //     ����뾶
    //##ModelId=45625C1200BB
    virtual double GetSecondaryAxis() = 0;

    //brief
    //     ����Բ����ת�����߶���
    //     ���ո�����������Բ�ȷ�Ϊ�߶ζ���
    //param
    //     pGeo: ������߶���
    //     nSegment: �ȷ�Բ�Ķ���
    //return
    //     ת���ɹ�����true
    //##ModelId=45625C1200BD
    virtual bool ConvertToLine(IGeo_PolyLine * pGeo, int nSegment) = 0;

};



#endif /* IGEO_ELLIPSE_H_HEADER_INCLUDED_B9D37C3F */
