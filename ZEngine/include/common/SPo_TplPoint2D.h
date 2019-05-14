#ifndef SPO_TPLPOINT2D_H_HEADER_INCLUDED_B883F76F
#define SPO_TPLPOINT2D_H_HEADER_INCLUDED_B883F76F

// ģ���Ͷ�ά������
//##ModelId=477C489D0177
template <class TYPE> class SPo_TplPoint2D
{
public:
	// \brief ������
    // 
    //  �����������ݸ���������ʼ����������ֵ��
    // 
    // \param X��x�����ʼֵ
    // \param Y��y�����ʼֵ
    // \param Z��z�����ʼֵ
    //##ModelId=44278E890242
    SPo_TplPoint2D(TYPE X, TYPE Y){	x = X ; y = Y;}; 
	// \brief ������
    // 
    //  �����������ݸ���������ʼ����������ֵ��
    // 
    // \param X��x�����ʼֵ
    // \param Y��y�����ʼֵ
    // \param Z��z�����ʼֵ
    //##ModelId=44278E890242
    SPo_TplPoint2D(){	x = 0 ; y = 0;}; 
	//��д������ʼ������
	SPo_TplPoint2D(const SPo_TplPoint2D &other)
	{
		x = other.x;
		y = other.y;
	};
	//��д������ʼ������
	SPo_TplPoint2D(const POINT &other)
	{
		x = other.x;
		y = other.y;
	};
    //��������
	~SPo_TplPoint2D()
	{
	};
    // \brief �������
    // 
    // �жϸ�����ṹ����ֵ�Ƿ��뵱ǰ��ṹ����ֵ���
    // 
    // \return �����ȣ��򷵻�1�����򣬷���0��
    // 
    // \param right����������Ҳ�����
    //##ModelId=44278F0A02FD
    bool operator==(const SPo_TplPoint2D &right){return (x == right.x && y == right.y ) ;};
	
    
    // \brief ���������
    // 
    // �жϸ�����ṹ����ֵ�Ƿ��뵱ǰ��ṹ����ֵ�����
    // 
    // \return �������ȣ��򷵻�1�����򣬷���0��
    // 
    // \param right������������Ҳ�����
    //##ModelId=44278EC3007D
    bool operator!=(const SPo_TplPoint2D &right){return !(*this == right) ;};
	
    
    // \brief ��ֵ����
    // 
    // ��������ṹ����ֵ������ǰ��ṹ
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right����ֵ�����Ҳ�����
    //##ModelId=44278F3F0261
    SPo_TplPoint2D& operator=(const SPo_TplPoint2D &right)
	{
		x = right.x ;
		y = right.y ;
		
		return *this ;
	};

    // \brief ת����ֵ����
    // 
    // ������windows�����ֵ������ǰ��ṹ
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right��ת����ֵ�����Ҳ�����
    //##ModelId=44278F7601D4
    SPo_TplPoint2D& operator=(const POINT &right)
	{
		x = right.x ;
		y = right.y ;
		
		return *this ;
	};
    // \brief ת����ֵ����
    // 
    // ������windows�����ֵ������ǰ��ṹ
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right��ת����ֵ�����Ҳ�����
    //##ModelId=44278F7601D4
//    SPo_TplPoint2D& operator=(const PointF &right)
//	{
//		x = right.X ;
//		y = right.Y ;
//		
//		return *this ;
//	};

	template <class TYPE1> SPo_TplPoint2D operator + (SPo_TplPoint2D<TYPE1> pt1)
	{
		SPo_TplPoint2D<TYPE> point(*this);
		
		point.Offset(pt1);
		
		return point;
	};
	
	template <class TYPE1> SPo_TplPoint2D operator - (SPo_TplPoint2D<TYPE1> pt1)
	{
		SPo_TplPoint2D<TYPE> point(*this);
		
		point.Offset(-pt1.x,-pt1.y);
		
		return point;
	};

	//����ƫ��/////////////
	template <class TYPE1> void Offset(TYPE1 dx,TYPE1 dy)
	{
		x += dx;
		y += dy;
	};
	
	template <class TYPE1> void Offset(SPo_TplPoint2D<TYPE1> pt1)
	{
		x += pt1.x;
		y += pt1.y;
	};

	template <class TYPE1> void operator += (const SPo_TplPoint2D<TYPE1> pt1)
	{
		Offset(pt1);
	};

	template <class TYPE1> void operator -= (const SPo_TplPoint2D<TYPE1> pt1)
	{
		Offset(-pt1.x,-pt1.y);
	};
	//##ModelId=40C8F9530242
	TYPE x;
	
	//##ModelId=40C8F9530243
	TYPE y;		
};

#endif /* SPO_TPLPOINT2D_H_HEADER_INCLUDED_B883F76F */
