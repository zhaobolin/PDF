#ifndef SPO_PAGEVIEWPARAM_H_HEADER_INCLUDED_B054D663
#define SPO_PAGEVIEWPARAM_H_HEADER_INCLUDED_B054D663

//##ModelId=4FAB437703A9

////
typedef struct SPo_PageViewParam
{
	SPo_PageViewParam(CView *pView=NULL,float fStartX=0,float fStartY=0,int fUpageX=0,int fUpageY=0,float fZoomP=1)
	{
		m_pView = pView;m_startX = fStartX;m_startY = fStartY;m_UpageX = fUpageX;m_UpageY = fUpageY;m_zoomP = fZoomP;
	};
	//页面起始位置；逻辑象素坐标
	//##ModelId=4B49E7FE005F
	float m_startX;//不带缩放，保持不变,缩放前的坐标
	//##ModelId=4B49E7FE006D
	float m_startY;//不带缩放，保持不变,缩放前的坐标
	//页面缩放倍数；
	//##ModelId=4B49E7FE009C
	float m_zoomP;
	//页面大小；像素单位；
	//##ModelId=4B49E7FE007E
	int m_UpageX;//不带缩放，保持不变,缩放前的坐标
	//##ModelId=4B49E7FE007F
	int m_UpageY;//不带缩放，保持不变,缩放前的坐标
	//页面窗口指针
	CView *m_pView;

} PageViewParam;



#endif /* SPO_PAGEVIEWPARAM_H_HEADER_INCLUDED_B054D663 */
