
#pragma once

/**********************************************************************

  * �ļ�����: GDI_Text.h
  *
  * ժ	Ҫ: GDI+�ı��ؼ���������ʾ��̬�ı�
  * 
  * ��ǰ�汾: 1.0
  *
  * ��	��: ��ľ��
  *
  * �������: 2014��7��2��
  
/**********************************************************************/


//��ͼͷ�ļ�
#include "Gdi.h"

class CGdi_Text : public CWnd 
{
		
public: 

	//���캯��
	CGdi_Text();
	
	//��������
	~CGdi_Text();

	//����������ؼ�
	virtual BOOL SubclassDlgItem(UINT nID, CWnd* pParent);

	//���ñ�����ɫ
	void Set_BK_Color(Color m_Color);

	//���ñ���ͼƬ
	void Set_BK_Image(CString m_strImage);
	
	//�����ַ�����ɫ
	void Set_Text_Color(Color m_Color);

	//�����ַ����ߴ�
	void Set_Text_Size(UINT m_Size);

	//�����ַ�������
	void Set_Text_String(CString m_strData);

	//�����ı����뷽ʽ
	void Set_Align(StringAlignment m_Align);

	//���ñ߿���ɫ
	void Set_Border_Color(Color m_Color);

protected:
	//GDI+��ͼ����
	CGDI m_GDI;

protected:
	//{{AFX_MSG
	afx_msg void OnPaint();//��ͼ����
	//}}AFX_MSG
	
	//�����������Ϣӳ���Ҫ�Ľṹ��ͺ�������
	DECLARE_MESSAGE_MAP()
};