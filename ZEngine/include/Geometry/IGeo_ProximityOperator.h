#ifndef IGEO_PROXIMITYOPERATOR_H_HEADER_INCLUDED_B9D30653
#define IGEO_PROXIMITYOPERATOR_H_HEADER_INCLUDED_B9D30653
class IGeo_Point;
class IGeo_Geometry;

//brief
//     �ڽ��ж�
//##ModelId=456A453B00DA
class IGeo_ProximityOperator
{
  public:
    //brief
    //     ��ѯ�����������ĵ����
    //parameter
    //     rPoint:��������
    //     enumExtent:�߶���չ��ʽ
    //     pPoint:���ص����
    //return
    //     ����ɹ�������true
    //##ModelId=456A45B5032C
    virtual bool QueryNearestPoint(IGeo_Point& rPoint, poenumSegmentExtent enumExtent, IGe_Point *pPoint) = 0;

    //brief
    //     �������ζ���֮��ľ���
    //##ModelId=456A4C5B030D
    virtual double Distance(IGeo_Geometry& rGeometry) = 0;

    //brief
    //     ��������������ĵ����
    //param
    //     rPoint:��������
    //     enumExtent:�߶���չ��ʽ
    //     pPoint:���ص����
    //##ModelId=456A4CB30167
    virtual bool ReturnNearestPoint(IGeo_Point& rPoint, poenumSegmentExtent enumExtent, IGeo_Point* pPoint) = 0;

};



#endif /* IGEO_PROXIMITYOPERATOR_H_HEADER_INCLUDED_B9D30653 */
