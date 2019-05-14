#ifndef SPO_TPLPOINT_H_HEADER_INCLUDED_B9A18345
#define SPO_TPLPOINT_H_HEADER_INCLUDED_B9A18345

//class SPo_TplPoint2D;
// ģ���͵�����
//##ModelId=465E3A0901F4
template <class TYPE> class SPo_TplPoint
{	
public:
    //##ModelId=40C8F9530242
    TYPE x;
	
    //##ModelId=40C8F9530243
    TYPE y;
	
    //##ModelId=40C8F9530244
    TYPE z;
public:    
    // \brief ������
    // 
    //  �����������ݸ���������ʼ����������ֵ��
    // 
    // \param X��x�����ʼֵ
    // \param Y��y�����ʼֵ
    // \param Z��z�����ʼֵ
    //##ModelId=44278E890242
    SPo_TplPoint(TYPE X = 0, TYPE Y = 0, TYPE Z = 0)
	{	x = X ; y = Y ; z = Z ;}; 
	//��д������ʼ������
	SPo_TplPoint(const POINT &other)
	{
		x = other.x;
		y = other.y;
		z = 0;
	};
	//��д������ʼ������
//	SPo_TplPoint(const Point &other)
//	{
//		x = other.X;
//		y = other.Y;
//		z = 0;
//	};
	//��д������ʼ������
//	SPo_TplPoint(const PointF &other)
//	{
//		x = other.X;
//		y = other.Y;
//		z = 0;
//	};
    //��������
	~SPo_TplPoint()
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
    template <class TYPE1> bool operator==(const SPo_TplPoint<TYPE1> &right){return !(x - right.x || y - right.y || z - right.z ) ;};
	
    
    // \brief ���������
    // 
    // �жϸ�����ṹ����ֵ�Ƿ��뵱ǰ��ṹ����ֵ�����
    // 
    // \return �������ȣ��򷵻�1�����򣬷���0��
    // 
    // \param right������������Ҳ�����
    //##ModelId=44278EC3007D
    template <class TYPE1> bool operator!=(const SPo_TplPoint<TYPE1> &right){return !(*this == right) ;};
	
    // \brief ת����ֵ����
    // 
    // ������windows�����ֵ������ǰ��ṹ
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right��ת����ֵ�����Ҳ�����
    //##ModelId=44278F7601D4
    SPo_TplPoint& operator=(const POINT &right)
	{
		x = right.x ;
		y = right.y ;
		//z = 0 ;
		
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
//    SPo_TplPoint& operator=(const Point &right)
//	{
//		x = right.X ;
//		y = right.Y ;
//		//z = 0 ;
//		
//		return *this ;
//	};
    // \brief ת����ֵ����
    // 
    // ������windows�����ֵ������ǰ��ṹ
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right��ת����ֵ�����Ҳ�����
    //##ModelId=44278F7601D4
//    SPo_TplPoint& operator=(const PointF &right)
//	{
//		x = right.X ;
//		y = right.Y ;
//		//z = 0 ;
//		
//		return *this ;
//	};	
    // \brief ��ֵ����
    // 
    // ��������ṹ����ֵ������ǰ��ṹ
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right����ֵ�����Ҳ�����
    //##ModelId=44278F3F0261
    template <class TYPE1> SPo_TplPoint& operator=(const SPo_TplPoint<TYPE1> &right)
	{
		x = right.x ;
		y = right.y ;
		z = right.z ;
		
		return *this ;
	};
    // \brief ��ֵ����
    // 
    // ��������ṹ����ֵ������ǰ��ṹ
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right����ֵ�����Ҳ�����
    //##ModelId=44278F3F0261
    template <class TYPE1> SPo_TplPoint& operator=(const SPo_TplPoint2D<TYPE1> &right)
	{
		x = right.x ;
		y = right.y ;
		
		return *this ;
	};

	//��д������ʼ������
	template <class TYPE1> SPo_TplPoint(const SPo_TplPoint<TYPE1> &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	};
	
	//��д������ʼ������
	template <class TYPE1> SPo_TplPoint(const SPo_TplPoint2D<TYPE1> &other)
	{
		x = other.x;
		y = other.y;
		z = 0;
	};	

	template <class TYPE1> SPo_TplPoint operator + (SPo_TplPoint<TYPE1> pt1)
	{
		SPo_TplPoint<TYPE> point(*this);
		
		point.Offset(pt1);
		
		return point;
	};
	
	template <class TYPE1> SPo_TplPoint operator - (SPo_TplPoint<TYPE1> pt1)
	{
		SPo_TplPoint<TYPE> point(*this);
		
		point.Offset(-pt1.x,-pt1.y,-pt1.z);
		
		return point;
	};

	
	//����ƫ��/////////////
	template <class TYPE1> void Offset(TYPE1 dx,TYPE1 dy,TYPE1 dz=0)
	{
		x += dx;
		y += dy;
		z += dz;
	};
	
	template <class TYPE1> void Offset(SPo_TplPoint<TYPE1> pt1)
	{
		x += pt1.x;
		y += pt1.y;
		z += pt1.z;
	};

	template <class TYPE1> void operator += (const SPo_TplPoint<TYPE1> pt1)
	{
		Offset(pt1);
	};

	template <class TYPE1> void operator -= (const SPo_TplPoint<TYPE1> pt1)
	{
		Offset(-pt1.x,-pt1.y,-pt1.z);
	};
};

// ģ����Size
template <class TYPE> struct SPo_TplSize
{
public:
	TYPE Width;
	TYPE Height;
	SPo_TplSize(){ Width = 0; Height = 0;};
	SPo_TplSize(TYPE w,TYPE h){ Width = w; Height = h;};
};

typedef SPo_TplSize<int> SPo_ISize;
typedef SPo_TplSize<long> SPo_LSize;
typedef SPo_TplSize<float> SPo_FSize;
typedef SPo_TplSize<double> SPo_DSize;

#endif /* SPO_TPLPOINT_H_HEADER_INCLUDED_B9A18345 */
