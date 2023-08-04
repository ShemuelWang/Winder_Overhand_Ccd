#pragma once

/**********************************************************************

  * �ļ�����: Gdi_Image3.h
  *
  * ժ	Ҫ: �����ڽӽ�ͼ���Եʱȷ��ROI
  * 
  * ��ǰ�汾: 3.0
  *
  * ��	��: �ƠD
  *
  * �������: 2015��12��25��
  
/**********************************************************************/

#include "CV_Func_Pro.h"

#include "Gdi_Image2.h"

//�Զ�����Ϣ
/*#define WM_CLICK_CTRL WM_USER + 1

//�Զ�����Ϣ
#define WM_MOUSE_MOVE2 WM_USER + 2

//�Զ���USER_NMHDR
struct  USER_NMHDR
{
	NMHDR  nmhdr;

	UINT  top;
	
	UINT  bottom;

	UINT left;

	UINT right;
};
*/

class CGdi_Image3:public CWnd
{
public:

	CGdi_Image3(void);

	~CGdi_Image3(void);

	//����������ؼ�
	virtual BOOL SubclassDlgItem(UINT nID, CWnd* pParent);

	//��ʾOpenCVͼ��
	void Show(IPL v_Image);

	//�������
	BOOL Clear();

protected:

	//��ʾOpenCVͼ��,������
	void Show_Direct(IPL v_Image);

	//����ͼ��
	BOOL Zoom(const IPL v_Image, IPL *v_pTrans,int v_intWidth,int v_intHeight);

protected:

	//����DC,����˫����
	CDC m_dcCompatible;

	//λͼ
	CBitmap m_Bitmap;

	//ͼ�񻺳���
	BYTE *m_pImageBuf;

	//OpenCV��ʾ��ͼ��
	IPL m_Image;

	//��Ϣ�ṹ��
	USER_NMHDR m_NMHDR;

	//��Ϣ�ṹ��
	USER_NMHDR m_NMHDR2;

	//�Ƿ���������
	BOOL m_bDown;

	//�Ƿ���������
	BOOL m_bMoveDown;

	//�ƶ�����ʼ��X
	int m_intMoveHomeX;

	//�ƶ�����ʼ��Y
	int m_intMoveHomeY;


	//�Ƿ���������
	BOOL m_bAdjustDown;

protected:
	//{{AFX_MSG
	afx_msg void OnPaint();//��ͼ����
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	//}}AFX_MSG

	//�����������Ϣӳ���Ҫ�Ľṹ��ͺ�������
	DECLARE_MESSAGE_MAP()
};

