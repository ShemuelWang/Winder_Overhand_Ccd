
#pragma once

/**********************************************************************

  * �ļ�����: GDI_Background.h
  *
  * ժ	Ҫ: ʹ��GDI���ƶԻ��򱳾�ͼƬ
  * 
  * ��ǰ�汾: 1.0
  *
  * ��	��: ��ľ��
  *
  * �������: 2014��7��2��
  
/**********************************************************************/

class CGdi_Background
{
public:
	//���캯��
	CGdi_Background();

	//��������
	virtual ~CGdi_Background();

	//���ñ���ͼƬ
	void Set_Background(CString m_strBackground);

	//��ȡ��ˢ,��
	CBrush* Get_Brush();
	
protected:

	//��ˢ
	CBrush m_Brush;
};

