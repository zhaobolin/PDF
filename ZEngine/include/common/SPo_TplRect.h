#ifndef SPO_TPLRECT_H_HEADER_INCLUDED_B9A1D13B
#define SPO_TPLRECT_H_HEADER_INCLUDED_B9A1D13B

#include "SPo_IPoint.h"

const double SPLITRATIO = 0.55;


// 模版型矩形
//##ModelId=465E3A30004E
template <class TYPE> class SPo_TplRect
{
public:
    //##ModelId=40C8F9A102FD
    TYPE left;
	
    //##ModelId=40C8F9A102FE
    TYPE right;
	
    //##ModelId=40C8F9A102FF
    TYPE top;
	
    //##ModelId=40C8F9A10300
    TYPE bottom;
public:
    // \brief 构造器
    // 
    // 构造器。将根据参数初始化矩形四个边界值。
    // 
    // \param iLeft：左边界值
    // \param iTop：上边界值
    // \param iRight：右边界值
    // \param iBottom：下边界值
    //##ModelId=44277F3502EE
    SPo_TplRect(TYPE x1 = 0, TYPE y1 = 0, TYPE x2 = 0, TYPE y2 = 0)
	{
		left	= min(x1,x2) ;
		top		= min(y1,y2) ;
		right	= max(x1,x2) ;
		bottom	= max(y1,y2) ;
	};
	//重写拷贝初始化函数
	template <class TYPE1> SPo_TplRect(const SPo_TplRect<TYPE1> &other)
	{
		left = (TYPE)(other.left);
		right = (TYPE)(other.right);
		top = (TYPE)(other.top);
		bottom = (TYPE)(other.bottom);
	};
	//重写拷贝初始化函数
	SPo_TplRect(const RECT &other)
	{
		left = other.left;
		right = other.right;
		top = other.top;
		bottom = other.bottom;
	};
	//析构函数
	~SPo_TplRect()
	{
	}
    // \brief 获取矩形的宽度。
    // 
    // 获取矩形的宽度。
    // 
    // \return 矩形的宽度
    // 
    // \param 无
    //##ModelId=44277FB5002E
    TYPE GetWidth()
	{
		return (right > left ) ? right - left : left - right ;
	};

    // \brief 获取矩形的高度。
    // 
    // 获取矩形的高度。
    // 
    // \return 矩形的高度,一般认为y坐标方向从下往上
    // 
    // \param 无
    //##ModelId=44277FB5002F
    TYPE GetHeight()
	{
		return (top > bottom ) ? top - bottom : bottom - top ;
	};

    // \brief 获取矩形的中心点
    // 
    // 获取矩形的中心点
    // 
    // \return 矩形的中心点
    // 
    // \param 无
    //##ModelId=44277FB50030
    SPo_TplPoint<TYPE> GetCenterPoint()
	{
		SPo_TplPoint<TYPE> point (0, 0, 0) ;
		
		SPo_TplRect rect = *this ;
		rect.NormalizeRect () ;
		
		point.x = rect.left + (TYPE)(rect.GetWidth()) / 2  ;
		point.y = rect.bottom + (TYPE)(rect.GetHeight()) / 2 ;
		
		
		return point ;
	};

	TYPE CenterX()
	{
		return (left+right)/2;
	};

	TYPE CenterY()
	{
		return (top+bottom)/2;
	};


    // \brief 矩形规格化
    // 
    // 对矩形进行规格化处理，即，保证处理后的数值中，left <= right, bottom <= top。
    // 
    // \return 无
    // 
    // \param 无
    // 
    // \note 该方法是为世界坐标而设计的。对于世界坐标而言，top 的数值要大于 bottom 的数值。而对于屏幕坐标，top 的数值要小于
    // bottom 的数值。在处理时要特别注意。
    //##ModelId=44277FB50031
    void NormalizeRect()
	{
		TYPE value ;
		
		if (left > right)
		{
            value = right ;
            right = left;
            left = value ;
		}
		
		if (bottom > top)
		{
            value = bottom ;
            bottom = top ;
            top = value ;
		}
	};

    // \brief 矩形反向规格化
    // 
    // 对矩形进行反向规格化处理，即，保证处理后的数值中，left <= right, bottom >= top。
    // 
    // \return 无
    // 
    // \param 无
    // 
    // \note 该方法是为屏幕坐标而设计的。对于世界坐标而言，top 的数值要大于 bottom 的数值。而对于屏幕坐标，top 的数值要小于
    // bottom 的数值。在处理时要特别注意。
    //##ModelId=44277FB50032
    void ReserveNormalizeRect()
	{
		TYPE value ;
		
		if (left > right )
		{
            value = right ;
            right = left;
            left = value ;
		}
		
		if (bottom < top)
		{
            value = bottom ;
            bottom = top ;
            top = value ;
		}
	};
    // \brief 赋值运算
    // 
    // 将给定矩形结构的数值赋给当前矩形结构
    // 
    // \return 当前矩形结构的引用
    // 
    // \param right：赋值运算右操作数
    //##ModelId=44277FB50040
    SPo_TplRect<TYPE> operator=(const SPo_TplRect<TYPE> &right)
	{
		this->left		= right.left ;
		this->right		= right.right ;
		this->top		= right.top ;
		this->bottom	= right.bottom ;
		
		return *this ;
	};

    // \brief 整型-浮点型转换赋值运算
    // 
    // 将给定windows矩形的数值赋给当前矩形结构
    // 
    // \return 当前矩形结构的引用
    // 
    // \param right：转换赋值运算右操作数
    //##ModelId=44277FB50042
    SPo_TplRect<TYPE> operator=(const RECT &right)
	{
		this->left		= right.left ;
		this->right		= right.right ;
		this->top		= right.top ;
		this->bottom	= right.bottom ;
		
		return *this ;
	};
    // \brief 整型-浮点型转换赋值运算
    // 
    // 将给定windows矩形的数值赋给当前矩形结构
    // 
    // \return 当前矩形结构的引用
    // 
    // \param right：转换赋值运算右操作数
    //##ModelId=44277FB50042	
//    SPo_TplRect<TYPE> operator=(const Rect &right)
//	{
//		this->left		= min(right.GetLeft(),right.GetRight());
//		this->right		= max(right.GetLeft(),right.GetRight());
//		this->top		= max(right.GetTop(),right.GetBottom());
//		this->bottom	= min(right.GetTop(),right.GetBottom());
//		
//		return *this ;
//	};
    // \brief 整型-浮点型转换赋值运算
    // 
    // 将给定windows矩形的数值赋给当前矩形结构
    // 
    // \return 当前矩形结构的引用
    // 
    // \param right：转换赋值运算右操作数
    //##ModelId=44277FB50042
//    SPo_TplRect<TYPE> operator=(const RectF &right)
//	{
//		this->left		= min(right.GetLeft(),right.GetRight());
//		this->right		= max(right.GetLeft(),right.GetRight());
//		this->top		= max(right.GetTop(),right.GetBottom());
//		this->bottom	= min(right.GetTop(),right.GetBottom());
//		
//		return *this ;
//	};
	//在原来矩形基础上偏移点
	template <class TYPE2> void OffsetPoint(TYPE2 dx,TYPE2 dy)
	{
		left+=dx;right+=dx;
		bottom+=dy;top+=dy;
	};
    // \brief 相等运算
    // 
    // 判断给定矩形结构的数值是否与当前矩形结构的数值相等
    // 
    // \return 如果相等，则返回1；否则，返回0。
    // 
    // \param right：相等运算右操作数
    //##ModelId=44277FB50044
	bool operator==(const SPo_TplRect<TYPE> &right)
	{
		if (	(this->left	== right.left ) &&
            (this->right	== right.right) &&  
            (this->top	== right.top)   && 
            (this->bottom	== right.bottom) ) 
            return 1 ;
		else
            return 0 ;
	};
	//在精度允许范围内的相同
	bool AcurateEqual(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> me=*this;
		SPo_TplRect<TYPE> ot=right;
		me.NormalizeRect();ot.NormalizeRect();
		if( fabs((double)(me.left)-(double)(ot.left))<DDVAL_CBT_MIAOACURATE&&
			fabs((double)(me.right)-(double)(ot.right))<DDVAL_CBT_MIAOACURATE&&
			fabs((double)(me.top)-(double)(ot.top))<DDVAL_CBT_MIAOACURATE&&
			fabs((double)(me.bottom)-(double)(ot.bottom))<DDVAL_CBT_MIAOACURATE)
			return true;
		else 
			return false;
	}
    // \brief 不相等运算
    // 
    // 判断给定矩形结构的数值是否与当前矩形结构的数值不相等
    // 
    // \return 如果不相等，则返回1；否则，返回0。
    // 
    // \param right：不相等运算右操作数
    //##ModelId=44277FB50046
    bool operator!=(const SPo_TplRect<TYPE> &right)
	{
		if ( *this == right )
            return 0 ;
		else 
            return 1 ;
	};
    // \brief 判断点在矩形内
    // 
    // 判断某个点是否落在该矩形区域内。
    // 
    // \return 如果点在矩形外，则返回false；如果点在矩形内1,或者点在矩形边界上2，返回true。
    // 
    // \param dx：待判断的点的x值
    // \param dy：待判断的点的y值
    // \param iTolerance：判断的误差值。缺省为0，即精确判断。
    // 
    // \note：该方法可能对矩形有副作用：将对矩形进行规格化处理，即将使得left < right, bottom < top。
    //##ModelId=44277FB50048
    template<class TYPE2,class TYPE3> int PtInRect(TYPE2 x, TYPE3 y, TYPE iTolerance = 0)
	{
		if (   (x < (left - iTolerance))
            || (x > (right + iTolerance))
            || (y < (min(bottom,top)  - iTolerance))
            || (y > (max(bottom,top) + iTolerance)) )
		{
            return 0 ;
		}
		else if ( (x > (left - iTolerance))
            && (x < (right + iTolerance) )
            && (y > (min(bottom,top)  - iTolerance) )
            && (y < (max(bottom,top) + iTolerance)) )
		{
            return 1 ;
		}			
		else
		{
            return 2 ;
		}
	};
	template<class TYPE2> int PtInRect(SPo_TplPoint<TYPE2> pt,TYPE2 iRolerance = 0)
	{
		return PtInRect(pt.x,pt.y,iRolerance);
	}
	int PtInRect(POINT pt,TYPE iRolerance = 0)
	{
		return PtInRect(pt.x,pt.y,iRolerance);
	}
    // \brief 判断两个矩形是否相交
    // 
    // 判断给定矩形是否与当前矩形相交。
    // 
    // \return 如果相交，则返回1；否则，返回0。
    // 
    // \param pRect：待判断矩形的指针
    // \param iTolerance：判断的误差值。缺省为0，即精确判断。
    //##ModelId=44277FB5006D
    template<class TYPE2> bool IsIntersect(SPo_TplRect<TYPE2>* pRect, TYPE iTolerance = 0)
	{
		SPo_TplRect<TYPE> rect1;SPo_TplRect<TYPE2> rect2;
		rect1 = *this;
		rect2 = *pRect;
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		if (rect1.left < (rect2.right + iTolerance) && rect1.right > (rect2.left - iTolerance)
            && rect1.bottom < (rect2.top + iTolerance) && rect1.top > (rect2.bottom - iTolerance))
		{
            return 1 ;
		}
		else
            return 0 ;
	};
    // \brief 判断两个矩形是否相交
    // 
    // 判断给定矩形是否与当前矩形相交。
    // 
    // \return 如果相交，则返回1；否则，返回0。
    // 
    // \param pRect：待判断矩形的指针
    // \param iTolerance：判断的误差值。缺省为0，即精确判断。
    //##ModelId=44277FB5006D
    template<class TYPE2> bool IsIntersect(TYPE2 x1,TYPE2 y1,TYPE x2,TYPE y2, TYPE iTolerance = 0)
	{
		SPo_TplRect<TYPE> rect1;SPo_TplRect<TYPE2> rect2(x1,y1,x2,y2);
		rect1 = *this;
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		if (rect1.left < (rect2.right + iTolerance) && rect1.right > (rect2.left - iTolerance)
            && rect1.bottom < (rect2.top + iTolerance) && rect1.top > (rect2.bottom - iTolerance))
		{
            return 1 ;
		}
		else
            return 0 ;
	};
    // \brief 判断两个矩形是否相交
    // 
    // 判断给定矩形是否与当前矩形相交。
    // 
    // \return 如果相交，则返回1；否则，返回0。
    // 
    // \param pRect：待判断矩形的指针
    // \param iTolerance：判断的误差值。缺省为0，即精确判断。
    //##ModelId=44277FB5006D
    bool IsIntersect(RECT* pRect, TYPE iTolerance = 0)
	{
		SPo_TplRect<TYPE> rect1;SPo_TplRect<TYPE> rect2(pRect->left,pRect->top,pRect->right,pRect->bottom);
		rect1 = *this;
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		if (rect1.left < (rect2.right + iTolerance) && rect1.right > (rect2.left - iTolerance)
            && rect1.bottom < (rect2.top + iTolerance) && rect1.top > (rect2.bottom - iTolerance))
		{
            return 1 ;
		}
		else
            return 0 ;
	};
    // \brief 判断当前矩形是否被给定矩形包含
    // 
    // 判断当前矩形是否被给定矩形包含。
    // 
    // \return 如果被包含，则返回1；否则，返回0。
    // 
    // \param pRect：待判断矩形的指针
    // \param iTolerance：判断的误差值。缺省为0，即精确判断。
    //##ModelId=442781E702FD
    template<class TYPE2> bool IsWithin(SPo_TplRect<TYPE2>* pRect, TYPE iTolerance = 0)
	{
		SPo_TplRect<TYPE> rect1; SPo_TplRect<TYPE2> rect2;
		rect1 = *this;
		rect2 = *pRect;
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		
		if (rect1.left > (rect2.left - iTolerance) && rect1.right < (rect2.right + iTolerance)
            && rect1.bottom > (rect2.bottom - iTolerance) && rect1.top < (rect2.top + iTolerance))
		{
            return 1 ;
		}
		else
            return 0 ;
	};

    // \brief 判断当前矩形是否与另一矩形相等
    // 
    // 判断当前矩形是否与另一矩形相等
    // 
    // \return 如果重合，则返回1；否则，返回0。
    // 
    // \param pRect：另一矩形结构的指针
    // \param iTolerance：判断的误差值。缺省为0，即精确判断。
    //##ModelId=44278245009C
	template<class TYPE2> bool IsEqual(SPo_TplRect<TYPE2> *pRect, TYPE iTolerance = 0)
	{
		if (abs(this->left	- pRect->left ) <= iTolerance &&
            abs(this->right	- pRect->right) <= iTolerance &&  
            abs(this->top - pRect->top) <= iTolerance && 
            abs(this->bottom - pRect->bottom) <= iTolerance) 
            return 1 ;
		else
            return 0 ;
	};

    // \brief 计算两个矩形的交集
    // 
    // 计算两个矩形的交集，并将结果保存到本结构中。如果两矩形不相交，则本结构等于SPo_TplRect(0,0,0,0)。
    // 
    // \return 是否有相交部分,是相交的返回true,没有相交部分返回false
    // 
    // \param pRect1：待求交矩形1的指针
    // \param pRect2：待求交矩形2的指针
    // 
    // \note 计算结果是规格化的，但原来两个待求交矩形不受影响。
    //##ModelId=4427829900BB
    template<class TYPE2,class TYPE3> bool Intersect(SPo_TplRect<TYPE2>* pRect1, SPo_TplRect<TYPE3>* pRect2)
	{
		assert(pRect1) ;
		assert(pRect2) ;
		bool bval = false;
		if (pRect1 && pRect2)
		{
			SPo_TplRect<TYPE2> rect1;
			SPo_TplRect<TYPE3> rect2;
			
			rect1 = *pRect1;
			rect2 = *pRect2;
			rect1.NormalizeRect();
			rect2.NormalizeRect();
			
			if (rect1.left > rect2.right || rect1.right < rect2.left
                || rect1.bottom > rect2.top || rect1.top < rect2.bottom)
			{
                left = 0 ;
                right = 0 ;
                
                top = 0 ;
                bottom = 0 ;
			}
			else
			{				
                left = (rect1.left > rect2.left ) ? rect1.left : rect2.left ; // 取大值
                right = ( rect1.right < rect2.right ) ? rect1.right : rect2.right ; // 取小值
                
                top = ( rect1.top < rect2.top ) ? rect1.top : rect2.top ; // 取小值
                bottom = ( rect1.bottom > rect2.bottom ) ? rect1.bottom : rect2.bottom ; // 取大值
				bval = true;
			}
		}
		return bval;
	};


    // \brief 计算两个矩形的交集
    // 
    // 计算两个矩形的交集，并将结果保存到本结构中。如果两矩形不相交，则本结构等于SPo_TplRect(0,0,0,0)。
    // 
    // \return 无
    // 
    // \param pRect1：待求交矩形1的指针
    // \param pRect2：待求交矩形2的指针
    // 
    // \note 计算结果是规格化的，但原来两个待求交矩形不受影响。
    //##ModelId=4427829900BB
    template<class TYPE> bool Intersect(SPo_TplRect<TYPE>* pRect1, RECT *pRect2)
	{
		assert(pRect1) ;
		assert(pRect2) ;
		bool bval = false;
		if (pRect1 && pRect2)
		{
			SPo_TplRect<TYPE> rect1;
			SPo_TplRect<TYPE> rect2;
			
			rect1 = *pRect1;
			rect2.left = pRect2->left;rect2.right=pRect2->right;rect2.bottom=pRect2->bottom;rect2.top=pRect2->top;
			
			rect1.NormalizeRect();
			rect2.NormalizeRect();
			
			if (rect1.left > rect2.right || rect1.right < rect2.left
                || rect1.bottom > rect2.top || rect1.top < rect2.bottom)
			{
                left = 0 ;
                right = 0 ;
                
                top = 0 ;
                bottom = 0 ;
			}
			else
			{				
                left = (rect1.left > rect2.left ) ? rect1.left : rect2.left ; // 取大值
                right = ( rect1.right < rect2.right ) ? rect1.right : rect2.right ; // 取小值
                
                top = ( rect1.top < rect2.top ) ? rect1.top : rect2.top ; // 取小值
                bottom = ( rect1.bottom > rect2.bottom ) ? rect1.bottom : rect2.bottom ; // 取大值
				bval = true;
			}
		}
		return bval;
	};
    // \brief 计算两个矩形的并集
    // 
    // 计算两个矩形的并集，并将结果保存到本结构中。
    // 
    // \return 无
    // 
    // \param pRect1：待求并矩形1的指针
    // \param pRect2：待求并矩形2的指针
    // 
    // \note 计算结果是规格化的，但原来两个待求并矩形不受影响。
    //##ModelId=44277FB50070
    template<class TYPE2,class TYPE3> void Union(SPo_TplRect<TYPE2>* pRect1, SPo_TplRect<TYPE3>* pRect2)
	{
		assert(pRect1) ;
		assert(pRect2) ;
		
		if (pRect1 && pRect2)
		{
			SPo_TplRect<TYPE2> rect1;
			SPo_TplRect<TYPE3> rect2;
			
			rect1 = *pRect1;
			rect2 = *pRect2;
			rect1.NormalizeRect();
			rect2.NormalizeRect();
			
			left = ( rect1.left < rect2.left ) ? rect1.left : rect2.left ; // 取大值
			right = ( rect1.right > rect2.right ) ? rect1.right : rect2.right ; // 取小值
			
			top = ( rect1.top > rect2.top ) ? rect1.top : rect2.top ; // 取大值
			bottom = ( rect1.bottom < rect2.bottom ) ? rect1.bottom : rect2.bottom ; // 取小值
		}
	};
	//////////////////////////////////////////////////////////
	template <class TYPE2> void Union(SPo_TplRect<TYPE2> *pRect2)
	{
		assert(pRect2);
		
		NormalizeRect();
		SPo_TplRect<TYPE2> rect2 = *pRect2;
		rect2.NormalizeRect();
		left = min(left,rect2.left);
		right = max(right,rect2.right);
		top = max(top,rect2.top);
		bottom = min(bottom,rect2.bottom);
	};

	///////////////////////////////////////////////////////
	void Union(RECT *pRect2)
	{
		assert(pRect2);

		NormalizeRect();

		left = min(left,pRect2->left);
		right = max(right,pRect2->right);
		top = max(top,max(pRect2->top,pRect2->bottom));
		bottom = min(bottom,min(pRect2->bottom,pRect2->top));
	};
	///////////////////////////////////////////////////////
	template<class XYTYPE> void Union(XYTYPE x1,XYTYPE y1,XYTYPE x2,XYTYPE y2)
	{
		left = min(left,min(x1,x2));
		right = max(right,max(x1,x2));
		top = max(top,max(y1,y2));
		bottom = min(bottom,min(y1,y2));
	}
//	void Union(Rect *pRect2)
//	{
//		assert(pRect2);
//
//		NormalizeRect();
//
//		left = min(left,min(pRect2->GetLeft(),pRect2->GetRight()));
//		right = max(right,max(pRect2->GetLeft(),pRect2->GetRight()));
//		top = max(top,max(pRect2->GetTop(),pRect2->GetBottom()));
//		bottom = min(bottom,min(pRect2->GetTop(),pRect2->GetBottom()));
//	};
	///////////////////////////////////////////////////////
//	void Union(RectF *pRect2)
//	{
//		assert(pRect2);
//		
//		NormalizeRect();
//		
//		left = min(left,min(pRect2->GetLeft(),pRect2->GetRight()));
//		right = max(right,max(pRect2->GetLeft(),pRect2->GetRight()));
//		top = max(top,max(pRect2->GetTop(),pRect2->GetBottom()));
//		bottom = min(bottom,min(pRect2->GetTop(),pRect2->GetBottom()));
//	};
    // \brief 并集运算
    // 
    // 计算当前矩形与给定矩形的并集，并将结果保存到结果结构中。
    // 
    // \return 结果结构
    // 
    // \param right：并集运算右操作数。
    // 
    // \note 计算结果是规格化的，但原来两个待求并矩形不受影响。
    //##ModelId=442783170128
	SPo_TplRect<TYPE> operator+(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> this_rect, right_rect;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();
		
		return SPo_TplRect(( this_rect.left < right_rect.left ) ? this_rect.left :right_rect.left, // 取小值
			( this_rect.top > right_rect.top ) ? this_rect.top :right_rect.top,// 取大值
			( this_rect.right > right_rect.right ) ? this_rect.right : right_rect.right,// 取大值
			( this_rect.bottom < right_rect.bottom ) ? this_rect.bottom : right_rect.bottom);// 取小值

	};
	

    // \brief 并集赋值运算
    // 
    //  计算当前矩形与给定矩形的并集，并将结果保存到当前结构中。
    // 
    // \return 当前结构的引用
    // 
    // \param right：并集赋值运算右操作数。
    // 
    // \note 计算结果是规格化的，但原来右操作数矩形不受影响。
    //##ModelId=44278374033C
    SPo_TplRect<TYPE> operator+=(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> this_rect, right_rect;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();

		this->left = ( this_rect.left < right_rect.left ) ? this_rect.left : right_rect.left ; // 取小值
		this->right = ( this_rect.right > right_rect.right ) ? this_rect.right : right_rect.right ; // 取大值
		
		this->top = ( this_rect.top > right_rect.top ) ? this_rect.top :right_rect.top ; // 取大值
		this->bottom = ( this_rect.bottom < right_rect.bottom ) ? this_rect.bottom : right_rect.bottom ; // 取小值
		
		return *this ;
	};
	

    // \brief 交集运算
    // 
    // 计算当前矩形与给定矩形的交集，并将结果保存到结果结构中。如果两矩形不相交，则结果结构等于SGIS_Rect(0,0,0,0)。
    // 
    // \return 结果结构
    // 
    // \param right：交集运算右操作数。
    // 
    // \note 计算结果是规格化的，但原来两个待求交矩形不受影响。
    //##ModelId=442783C90167
    SPo_TplRect<TYPE> operator&(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> this_rect, right_rect, rect_result ;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();
		
		if (this_rect.left > right_rect.right || this_rect.right < right_rect.left
            || this_rect.bottom > right_rect.top || this_rect.top < right_rect.bottom)
		{
			rect_result.left = 0 ;
			rect_result.right = 0 ;
			
			rect_result.top = 0 ;
			rect_result.bottom = 0 ;
		}
		else
		{				
			rect_result.left = ( this_rect.left > right.left ) ? this_rect.left : right_rect.left ; // 取大值
			rect_result.right = ( this_rect.right < right.right ) ? this_rect.right : right_rect.right ; // 取小值
			
			rect_result.top = ( this_rect.top < right.top ) ? this_rect.top :right_rect.top ; // 取小值
			rect_result.bottom = ( this_rect.bottom > right.bottom ) ? this_rect.bottom : right_rect.bottom ; // 取大值
		}
		
		return rect_result ;
	};

    // \brief 交集赋值运算
    // 
    // 计算当前矩形与给定矩形的交集，并将结果保存到当前结构中。如果两矩形不相交，则当前结构等于SGIS_Rect(0,0,0,0)。
    // 
    // \return 当前结构的引用
    // 
    // \param right：交集赋值运算右操作数。
    // 
    // \note 计算结果是规格化的，但原来右操作数矩形不受影响。
    //##ModelId=4427841902FD
    SPo_TplRect<TYPE> operator&=(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> right_rect;
		
		right_rect = right;
		right_rect.NormalizeRect();
		this->NormalizeRect();
		
		if (this->left > right_rect.right || this->right < right_rect.left
            || this->bottom > right_rect.top || this->top < right_rect.bottom)
		{
			this->left = 0 ;
			this->right = 0 ;
			
			this->top = 0 ;
			this->bottom = 0 ;
		}
		else
		{				
			this->left = ( this->left > right.left ) ? this->left : right_rect.left ; // 取大值
			this->right = ( this->right < right.right ) ? this->right : right_rect.right ; // 取小值
			
			this->top = ( this->top < right.top ) ? this->top :right_rect.top ; // 取小值
			this->bottom = ( this->bottom > right.bottom ) ? this->bottom : right_rect.bottom ; // 取大值
		}
		
		return *this ;
	};

    // \brief 被包含运算
    // 
    // 判断当前矩形是否被另一矩形包含。
    // 
    // \return 如果被包含，则返回1；否则，返回0。
    // 
    // \param right：包含运算右操作数
    //##ModelId=4427845103C8
    bool operator<(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> this_rect, right_rect;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();
		
		if (this_rect.left > right_rect.left && this_rect.right < right_rect.right
            && this_rect.bottom > right_rect.bottom && this_rect.top < right_rect.top)
		{
            return 1 ;
		}
		else
            return 0 ;
	};

    // \brief 被包含/重合运算
    // 
    // 判断当前矩形是否被另一矩形包含(可以边界相重合)。
    // 
    // \return 如果被包含，则返回1；否则，返回0。
    // 
    // \param right：包含运算右操作数
    //##ModelId=4427848403D8
    bool  operator<=(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE>  this_rect, right_rect;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();
		
		if (this_rect.left >= right_rect.left && this_rect.right <= right_rect.right
            && this_rect.bottom >= right_rect.bottom && this_rect.top <= right_rect.top)
		{
            return 1 ;
		}
		else
            return 0 ;
	};

	//ycc add for R-tree 2007-12-3
	template<class TYPE2> bool Contains(const SPo_TplRect<TYPE2> &right)
	{
		SPo_TplRect<TYPE> rc;
		rc.bottom = right.bottom;rc.top = right.top;
		rc.left = right.left;rc.right = right.right;
		return rc <= *this;
	}

	TYPE GetArea()
	{
		return 1 * GetWidth() * GetHeight() ;
	};

	template<class TYPE2,class TYPE3> void SplitRtree(SPo_TplRect<TYPE2> &r0,SPo_TplRect<TYPE3> & r1) const
	{
		this->NormalizeRect();
		double range;
		//r0 = r1 = *this;	 ////////////////
		r0.left = left;r1.left = left;
		r0.right = right;r1.right=right;
		r0.top = top;r1.top=top;
		r0.bottom=bottom;r1.bottom=bottom;
		// Split in the widest direction
		if ((right - left) > (top - bottom)) {
			// X direction
			range = right - left;
			
			r0.right = left + (long) (range * SPLITRATIO +.5);
			r1.left = right - (long) (range * SPLITRATIO +.5);
		} else {
			// Y direction
			range = top - bottom;
			
			r0.top = bottom + (long) (range * SPLITRATIO +.5);
			r1.bottom = top - (long) (range * SPLITRATIO +.5);
		}

	}
	//判断矩形与两点定义的直线段是否相交
	template<class TYPE2> bool RectIntersectLine(TYPE2 *px1,TYPE2 *py1,TYPE2 *px2,TYPE2 *py2)
	{
		double rxmin = left;		double rymin = (top<bottom?top:bottom);
		double rxmax = right;		double rymax = (bottom>top?bottom:top);
		
		bool bxval = true;				bool byval = true;
		int i31 = 0;					int i32 = 0;//定义三值变量，区间左边－1，区间中间0，区间右边1
		
		if(*px1<rxmin)						i31 = -1;
		else if(*px1>=rxmin&&*px1<=rxmax)	i31 = 0;
		else if(*px1>rxmax)					i31 = 1;
		
		if(*px2<rxmin)						i32 = -1;
		else if(*px2>=rxmin&&*px2<=rxmax)	i32 = 0;
		else if(*px2>rxmax)					i32 = 1;
		
		if(i32*i31>0)	bxval = false;//x区间不相交
		
		if(*py1<rymin)						i31 = -1;
		else if(*py1>=rymin&&*py1<=rymax)	i31 = 0;
		else if(*py1>rymax)					i31 = 1;
		
		if(*py2<rymin)						i32 = -1;
		else if(*py2>=rymin&&*py2<=rymax)	i32 = 0;
		else if(*py2>rymax)					i32 = 1;
		
		if(i32*i31>0)	byval = false;//y区间不相交
		
		return bxval&&byval;
	};
	//计算对角线长度
	TYPE GetInvAx()
	{
		double w = GetWidth();
		double h = GetHeight();
		double ax = sqrt(w*w+h*h);
		return (TYPE)ax;
	};
	//hls added 20100520
	size_t BytesSerializeSize()
	{
		return sizeof(left)+sizeof(right)+sizeof(top)+sizeof(bottom);
	};
	size_t BytesSerialize(bool bRead,PBYTE *ppBytes)
	{
		size_t pos = 0;

		pos += _cbrw(bRead,&left,sizeof(left),1,(*ppBytes)+pos);
		pos += _cbrw(bRead,&right,sizeof(right),1,(*ppBytes)+pos);
		pos += _cbrw(bRead,&top,sizeof(top),1,(*ppBytes)+pos);
		pos += _cbrw(bRead,&bottom,sizeof(bottom),1,(*ppBytes)+pos);

		return pos;
	};
	//ycc add end 2007-12-3
	//序列化函数
	void Serialize(CArchive &ar)
	{
		double dl = left;double dr = right;double dt = top;double db = bottom;
		if(ar.IsStoring())
		{
			ar << dl;ar << dr;ar << dt;ar << db;
		}
		else
		{
			ar >> dl;ar >> dr;ar >> dt;ar >> db;
			left = (TYPE)dl;right = (TYPE)dr;top = (TYPE)dt;bottom = (TYPE)db;
		}
	};
};

//////////////////////////////////////////////////////////////////////////
// \brief 计算两个矩形的交集
// 
// 计算两个矩形的交集，并将结果保存到本结构中。如果两矩形不相交，则本结构等于SPo_TplRect(0,0,0,0)。
// 
// \return 是否有相交部分,是相交的返回true,没有相交部分返回false
// 
// \param pRect1：待求交矩形1的指针
// \param pRect2：待求交矩形2的指针
// 
// \note 计算结果是规格化的，但原来两个待求交矩形不受影响。
//##ModelId=4427829900BB
template<class TYPE> inline bool SpoRectIntersect(SPo_TplRect<TYPE>* pRect1, RECT *pRect2)
{
	assert(pRect1) ;
	assert(pRect2) ;
	if (pRect1 && pRect2)
	{
		SPo_TplRect<TYPE> rect1;
		SPo_TplRect<TYPE> rect2;
		
		rect1 = *pRect1;
		rect2.left = pRect2->left;rect2.right=pRect2->right;rect2.bottom=pRect2->bottom;rect2.top=pRect2->top;
		
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		
		if (rect1.left > rect2.right || rect1.right < rect2.left
			|| rect1.bottom > rect2.top || rect1.top < rect2.bottom)
		{
			return false;
		}
		else
		{	
			return true;
		}
	}
	return false;
};
template<class TYPE> inline bool SpoRectIntersect(SPo_TplRect<TYPE>* pRect1, SPo_TplRect<TYPE> *pRect2)
{
	assert(pRect1) ;
	assert(pRect2) ;
	if (pRect1 && pRect2)
	{
		SPo_TplRect<TYPE> rect1;
		SPo_TplRect<TYPE> rect2;
		
		rect1 = *pRect1;
		rect2.left = pRect2->left;rect2.right=pRect2->right;rect2.bottom=pRect2->bottom;rect2.top=pRect2->top;
		
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		
		if (rect1.left > rect2.right || rect1.right < rect2.left
			|| rect1.bottom > rect2.top || rect1.top < rect2.bottom)
		{
			return false;
		}
		else
		{	
			return true;
		}
	}
	return false;
};

template<class TYPE1,class TYPE2> inline bool SpoRectIntersect(TYPE1 x11,TYPE1 y11,TYPE1 x12,TYPE1 y12,TYPE2 x21,TYPE2 y21,TYPE2 x22,TYPE2 y22, double iTolerance = 0)
{
	double minx1=min(x11,x12);
	double maxx1=max(x11,x12);
	double miny1=min(y11,y12);
	double maxy1=max(y11,y12);

	double minx2=min(x21,x22);
	double maxx2=max(x21,x22);
	double miny2=min(y21,y22);
	double maxy2=max(y21,y22);

	if (minx1 < (maxx2 + iTolerance) && maxx1 > (minx2 - iTolerance)
		&& miny1 < (maxy2 + iTolerance) && maxy1 > (miny2 - iTolerance))
		return 1 ;
	else
		return 0 ;
};

#endif /* SPO_TPLRECT_H_HEADER_INCLUDED_B9A1D13B */
