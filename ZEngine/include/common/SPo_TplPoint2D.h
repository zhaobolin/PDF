#ifndef SPO_TPLPOINT2D_H_HEADER_INCLUDED_B883F76F
#define SPO_TPLPOINT2D_H_HEADER_INCLUDED_B883F76F

// 模版型二维点坐标
//##ModelId=477C489D0177
template <class TYPE> class SPo_TplPoint2D
{
public:
	// \brief 构造器
    // 
    //  构造器。根据给定参数初始化所有坐标值。
    // 
    // \param X：x坐标初始值
    // \param Y：y坐标初始值
    // \param Z：z坐标初始值
    //##ModelId=44278E890242
    SPo_TplPoint2D(TYPE X, TYPE Y){	x = X ; y = Y;}; 
	// \brief 构造器
    // 
    //  构造器。根据给定参数初始化所有坐标值。
    // 
    // \param X：x坐标初始值
    // \param Y：y坐标初始值
    // \param Z：z坐标初始值
    //##ModelId=44278E890242
    SPo_TplPoint2D(){	x = 0 ; y = 0;}; 
	//重写拷贝初始化函数
	SPo_TplPoint2D(const SPo_TplPoint2D &other)
	{
		x = other.x;
		y = other.y;
	};
	//重写拷贝初始化函数
	SPo_TplPoint2D(const POINT &other)
	{
		x = other.x;
		y = other.y;
	};
    //析构函数
	~SPo_TplPoint2D()
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
    bool operator==(const SPo_TplPoint2D &right){return (x == right.x && y == right.y ) ;};
	
    
    // \brief 不相等运算
    // 
    // 判断给定点结构的数值是否与当前点结构的数值不相等
    // 
    // \return 如果不相等，则返回1；否则，返回0。
    // 
    // \param right：不相等运算右操作数
    //##ModelId=44278EC3007D
    bool operator!=(const SPo_TplPoint2D &right){return !(*this == right) ;};
	
    
    // \brief 赋值运算
    // 
    // 将给定点结构的数值赋给当前点结构
    // 
    // \return 当前点结构的引用
    // 
    // \param right：赋值运算右操作数
    //##ModelId=44278F3F0261
    SPo_TplPoint2D& operator=(const SPo_TplPoint2D &right)
	{
		x = right.x ;
		y = right.y ;
		
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
    SPo_TplPoint2D& operator=(const POINT &right)
	{
		x = right.x ;
		y = right.y ;
		
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

	//坐标偏移/////////////
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
