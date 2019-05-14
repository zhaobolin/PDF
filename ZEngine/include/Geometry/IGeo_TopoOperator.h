#ifndef IGEO_TOPOOPERATOR_H_HEADER_INCLUDED_B9D3074C
#define IGEO_TOPOOPERATOR_H_HEADER_INCLUDED_B9D3074C
class IGeo_Geometry;
class IGeo_Envelope;

/// \brief ���������������������ü��������������
//##ModelId=442B783C0119
class IGeo_TopoOperator
{
  public:
    //brief
    //     ��ȡ���ζ���߽磬ά�����ͣ����ߵı߽�Ϊ�㣬��ı߽�Ϊ��
    //param
    //     rBoundary:���ڷ��ر߽�ֵ
    //return
    //     ���سɹ�����true
    //##ModelId=45666284008C
    virtual Boolean GetBoundary(IGeo_Geometry& rBoundary) = 0;

    //brief
    //     �󼸺ζ���Ļ�����
    //param
    //     dDistance:�����������ľ���
    //     pBuffer:���ؽ����Ļ��������ζ��� 
    //return
    //     �����������ɹ�������true
    //##ModelId=456901230138
    virtual bool Buffer(double dDistance, IGeo_Geometry* pBuffer) = 0;

    //brief
    //     ������ķ��ײü����ζ���
    //param
    //     rEnvelope:�ü����ζ���ķ���
    //     pResult:�ü���õ��ļ��ζ���
    //return:
    //     ����ü��ɹ�������true
    //##ModelId=456901F9034B
    virtual bool Clip(IGeo_Envelope& rEnvelope, IGeo_Geometry* pResult) = 0;

    //brief
    //     ���㼸�ζ����͹��
    //param
    //     ��
    //return
    //     ����ɹ�����true
    //    
    //##ModelId=456902CE0261
    virtual bool ConvexHull() = 0;

    //brief
    //     �����ߴ��и�ζ���
    //param
    //     rPolyline:�����и�����ߴ�
    //     pLeftGeom:�и����벿���ζ���
    //     pRightGeom:�и���Ұ벿���ζ���
    //return
    //     ����и�ɹ�����true
    //##ModelId=45690347031C
    virtual bool Cut(IGeo_Polyline &rPolyline, IGeo_Geometry* pLeftGeom, IGeo_Geometry* pRightGeom) = 0;

    //brief
    //     �󼸺ζ���֮��
    //param
    //     rOtherGeo:����ļ��ζ�����ǰ���ζ�����ö���֮��
    //     pOutGeom:���ؽ�����ζ���
    //return
    //     �������ɹ�������true
    //##ModelId=4569042C034B
    virtual bool Difference(IGeo_Geometry& rOtherGeom, IGeo_Geometry* pOutGeom) = 0;

    //brief
    //     ������֪���ζ��������뼸�ζ���Ľ�
    //param
    //     rOtherGeom:����ļ��ζ���
    //     rGeoDim:������ε�ά��
    //     pOutGeom:���ؽ�����ζ���
    //return
    //     ����ɹ�������true
    //##ModelId=456904E60271
    virtual bool Intersect(IGeo_Geometry& rOtherGeom, poenumGeometryDimension& rGeoDim, IGeo_Geometry* pOutGeom) = 0;

    //brief
    //     ��
    //param
    //     rOtherGeom:����ļ��ζ���
    //     pOutGeom:���ؽ�����ζ���
    //return
    //     �������ɹ�����true
    //##ModelId=456905F6031C
    virtual bool Union(IGeo_Geometry& rOtherGeom, IGeo_Geometry* pOutGeom) = 0;

};



#endif /* IGEO_TOPOOPERATOR_H_HEADER_INCLUDED_B9D3074C */
