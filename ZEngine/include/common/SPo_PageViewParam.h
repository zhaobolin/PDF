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
	//ҳ����ʼλ�ã��߼���������
	//##ModelId=4B49E7FE005F
	float m_startX;//�������ţ����ֲ���,����ǰ������
	//##ModelId=4B49E7FE006D
	float m_startY;//�������ţ����ֲ���,����ǰ������
	//ҳ�����ű�����
	//##ModelId=4B49E7FE009C
	float m_zoomP;
	//ҳ���С�����ص�λ��
	//##ModelId=4B49E7FE007E
	int m_UpageX;//�������ţ����ֲ���,����ǰ������
	//##ModelId=4B49E7FE007F
	int m_UpageY;//�������ţ����ֲ���,����ǰ������
	//ҳ�洰��ָ��
	CView *m_pView;

} PageViewParam;



#endif /* SPO_PAGEVIEWPARAM_H_HEADER_INCLUDED_B054D663 */
