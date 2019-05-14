#ifndef IGEO_RELATIONOPERATOR_H_HEADER_INCLUDED_B9D36C17
#define IGEO_RELATIONOPERATOR_H_HEADER_INCLUDED_B9D36C17
class IGeo_Geometry;

/// \brief ��ϵ���������������ഥ���ཻ������
//##ModelId=442B78A70177
class IGeo_RelationOperator
{
  public:
    //brief
    //    ��֪���ζ����Ƿ�������뼸�ζ���
    //param
    //    rOtherGeom:���жϼ��ζ���
    //return
    //    rOtherGeom�����ݷ���true
    //##ModelId=456907110196
    virtual bool Contains(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     �ж������ζ����Ƿ��ཻ,����ά��С�ڰ������ζ���
    //param
    //     rOtherGeom:���жϼ��ζ���
    //return
    //     ����ɹ�������true
    //##ModelId=45690BC503C8
    virtual bool Crosses(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     �ж������ζ����Ƿ�����
    //param
    //     rOtherGeom:���жϼ��ζ���
    //rerurn
    //     ������뷵��true
    //##ModelId=45690D710271
    virtual bool Disjoint(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     �ж������ζ����Ƿ��ϸ����
    //param
    //     rOtherGeom:���жϼ��ζ���
    //return
    //     ��������ζ�����ȷ���true
    //##ModelId=45690DEF0232
    virtual bool Equals(IGe_Geometry &rOtherGeom) = 0;

    //brief
    //     �ж������ζ���Ľ��Ƿ�����֪���ζ��������ͬά��,�Ƿ��ص���
    //param
    //     rOtherGeom:���жϼ��ζ���
    //return
    //     ����ص�������true
    //##ModelId=45690EB9000F
    virtual bool Overlaps(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     �ж������ζ����й�ͬ�߽�
    //param
    //     rOtherGeom:���жϼ��ζ���
    //return
    //    ����ഥ������true
    //##ModelId=45690F8901A5
    virtual bool Touches(IGeo_Geometry& rOtherGeom) = 0;

    //brief
    //     �жϼ��ζ����Ƿ񱻰���
    //return
    //    �������������true
    //##ModelId=45690FFE03D8
    virtual bool Within(IGeo_Geometry& rOtherGeom) = 0;

};



#endif /* IGEO_RELATIONOPERATOR_H_HEADER_INCLUDED_B9D36C17 */
