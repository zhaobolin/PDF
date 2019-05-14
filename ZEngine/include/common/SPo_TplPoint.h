#ifndef SPO_TPLPOINT_H_HEADER_INCLUDED_B9A18345
#define SPO_TPLPOINT_H_HEADER_INCLUDED_B9A18345

//class SPo_TplPoint2D;
// 模版型点坐标
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
    // \brief 构造器
    // 
    //  构造器。根据给定参数初始化所有坐标值。
    // 
    // \param X：x坐标初始值
    // \param Y：y坐标初始值
    // \param Z：z坐标初始值
    //##ModelId=44278E890242
    SPo_TplPoint(TYPE X = 0, TYPE Y = 0, TYPE Z = 0)
	{	x = X ; y = Y ; z = Z ;}; 
	//重写拷贝初始化函数
	SPo_TplPoint(const POINT &other)
	{
		x = other.x;
		y = other.y;
		z = 0;
	};
	//重写拷贝初始化函数
//	SPo_TplPoint(const Point &other)
//	{
//		x = other.X;
//		y = other.Y;
//		z = 0;
//	};
	//重写拷贝初始化函数
//	SPo_TplPoint(const PointF &other)
//	{
//		x = other.X;
//		y = other.Y;
//		z = 0;
//	};
    //析构函数
	~SPo_TplPoint()
	{
	};
    // \brief 相等运算
    // 
    // 判断给定点结构的数值是否与当前点结构的数值相等
    // 
    // \return 如果相等，则返回1；否则，返回0。
    // 
    // \param right：相等运算右操作数
    //##ModelId=44278F0A02FD
    template <class TYPE1> bool operator==(const SPo_TplPoint<TYPE1> &right){return !(x - right.x || y - right.y || z - right.z ) ;};
	
    
    // \brief 不相等运算
    // 
    // 判断给定点结构的数值是否与当前点结构的数值不相等
    // 
    // \return 如果不相等，则返回1；否则，返回0。
    // 
    // \param right：不相等运算右操作数
    //##ModelId=44278EC3007D
    template <class TYPE1> bool operator!=(const SPo_TplPoint<TYPE1> &right){return !(*this == right) ;};
	
    // \brief 转换赋值运算
    // 
    // 将给定windows点的数值赋给当前点结构
    // 
    // \return 当前点结构的引用
    // 
    // \param right：转换赋值运算右操作数
    //##ModelId=44278F7601D4
    SPo_TplPoint& operator=(const POINT &right)
	{
		x = right.x ;
		y = right.y ;
		//z = 0 ;
		
		return *this ;
	};
    // \brief 转换赋值运算
    // 
    // 将给定windows点的数值赋给当前点结构
    // 
    // \return 当前点结构的引用
    // 
    // \param right：转换赋值运算右操作数
    //##ModelId=44278F7601D4
//    SPo_TplPoint& operator=(const Point &right)
//	{
//		x = right.X ;
//		y = right.Y ;
//		//z = 0 ;
//		
//		return *this ;
//	};
    // \brief 转换赋值运算
    // 
    // 将给定windows点的数值赋给当前点结构
    // 
    // \return 当前点结构的引用
    // 
    // \param right：转换赋值运算右操作数
    //##ModelId=44278F7601D4
//    SPo_TplPoint& operator=(const PointF &right)
//	{
//		x = right.X ;
//		y = right.Y ;
//		//z = 0 ;
//		
//		return *this ;
//	};	
    // \brief 赋值运算
    // 
    // 将给定点结构的数值赋给当前点结构
    // 
    // \return 当前点结构的引用
    // 
    // \param right：赋值运算右操作数
    //##ModelId=44278F3F0261
    template <class TYPE1> SPo_TplPoint& operator=(const SPo_TplPoint<TYPE1> &right)
	{
		x = right.x ;
		y = right.y ;
		z = right.z ;
		
		return *this ;
	};
    // \brief 赋值运算
    // 
    // 将给定点结构的数值赋给当前点结构
    // 
    // \return 当前点结构的引用
    // 
    // \param right：赋值运算右操作数
    //##ModelId=44278F3F0261
    template <class TYPE1> SPo_TplPoint& operator=(const SPo_TplPoint2D<TYPE1> &right)
	{
		x = right.x ;
		y = right.y ;
		
		return *this ;
	};

	//重写拷贝初始化函数
	template <class TYPE1> SPo_TplPoint(const SPo_TplPoint<TYPE1> &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	};
	
	//重写拷贝初始化函数
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

	
	//坐标偏移/////////////
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

// 模版型Size
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
