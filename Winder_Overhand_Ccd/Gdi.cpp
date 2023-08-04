
#include "stdafx.h"

#include "GDI.h"

CGDI:: CGDI()
{
	//��ʼ��CGDI
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

	//������ɫĬ�Ϻ�ɫ
	m_BkColor = Color(255,0,0,0);

	//�ַ�����ɫĬ��Ϊ��ɫ
	m_TextColor = Color(255,255,255,255);

	//ͼԪ��ɫĬ��Ϊ��ɫ
	m_MetaColor = Color(255,255,255,255);

	//�ؼ����
	m_CtrWidth = 200;
	
	//�ؼ��߶�
	m_CtrHeight = 150;

	//Ĭ�ϲ���ʾ�߿�
	m_bShowBorder = FALSE;

	//�߿���ɫ
	m_BorderColor = Color(255,255,255,255);

	//�߿���Ĭ��Ϊ2
	m_BorderWidth = 2;

	//�ַ����ߴ�
	m_TextSize = 20;

	//Ĭ�����ű���
	m_douTimes = 1;

	//�ı����뷽ʽĬ��Ϊ���ж���
	m_TextAlign = StringAlignmentCenter;

	//����ͼƬָ��
	m_pBkImage = NULL;
}

CGDI::  ~CGDI() 
{
	//���֮ǰ��ָ�򱳾�ͼƬ,���ͷ�
	if (m_pBkImage != NULL)
	{
		delete m_pBkImage;
		m_pBkImage = NULL;
	}

	//�ͷ�CGDI
	GdiplusShutdown(m_gdiplusToken);

}

void CGDI:: Relate_CTR(CWnd *v_pWnd)
{
	//������ο�
	CRect t_Rect;
	
	//��ȡ���ڿͻ���������
	v_pWnd->GetClientRect(&t_Rect);
	
	//���ÿؼ��ߴ�
	Set_CTR_Size(t_Rect.Width(),t_Rect.Height());
}

void CGDI::Set_CTR_Size(UINT v_intWidth,UINT v_intHeight)
{
	//���ÿؼ��ߴ�
	if (v_intWidth == 0 || v_intHeight == 0)
	{
		AfxMessageBox("�ؼ��ߴ����!");
		return;
	}
	
	//�ؼ��Ŀ��
	m_CtrWidth = v_intWidth;
	
	//�ؼ��ĸ߶�
	m_CtrHeight = v_intHeight;
}

void CGDI::Set_BK_Color(Color v_Color)
{
	m_BkColor = v_Color;
}

void CGDI::Set_BK_Image(CString v_strBkImage)
{
	//ת����COM���ݸ�ʽ
    BSTR t_BSTR = v_strBkImage.AllocSysString(); 
	
	//��ʱָ��
	Gdiplus::Image *t_pBkImage;
	
	//ָ��ԭ����ͼƬ�������ͷ�
	t_pBkImage = m_pBkImage;
	
	//����ͼƬ,�ѷ��䣬��Ҫ�ֶ��ͷ�
	m_pBkImage = new Gdiplus::Bitmap(t_BSTR);
	
	//���֮ǰ��ָ�򱳾�ͼƬ,���ͷ�
	if (t_pBkImage != NULL)
	{
		delete t_pBkImage;
		t_pBkImage = NULL;
	}
}

void CGDI::Set_Border_Color(Color v_Color)
{
	m_BorderColor = v_Color;

	m_bShowBorder = TRUE;
}

void CGDI::Set_Border_Width(UINT v_intWidth)
{
	m_BorderWidth = v_intWidth;

	//����߿�����Ϊ0,����ʾ�߿�
	if (v_intWidth == 0)
	{
		m_bShowBorder = FALSE;
	}
	else
	{
		m_bShowBorder = TRUE;
	}
}

void  CGDI::DB_Draw(HDC v_HDC)
{
	//�ؼ��ߴ粻��ȷ
	if(m_CtrWidth == 0 || m_CtrHeight == 0)
	{
		return;
	}

	//�ַ����ߴ粻��ȷ
	if (m_TextSize == 0)
	{
		return;
	}

	//�������⻭��
	Bitmap t_Bitmap(m_CtrWidth,m_CtrHeight);

	//���⻭�����������豸�У�����Ļ�ͼ���������豸��
	Graphics t_VirtualGraphics(&t_Bitmap);

	//�����豸�������ͼ��
	t_VirtualGraphics.Clear(m_BkColor);

	//���Ʊ���ͼƬ
	Draw_BK_Image(&t_VirtualGraphics);

	//�����ַ���
	Draw_Text(&t_VirtualGraphics);
	
	//��ʾ�߿�
	Draw_Border(&t_VirtualGraphics);

	//�ؼ����豸�����ģ�������ʾ������������Ϣ��Windows ���ݽṹ
	Graphics t_Graphics(v_HDC);
	
	//��ʾ����
	t_Graphics.DrawImage(&t_Bitmap,0,0);
}

void CGDI::Set_Text_Color(Color v_Color)
{
	//�����ַ�����ɫ
	m_TextColor = v_Color;
}

void CGDI::Set_Text_Size(UINT v_intSize)
{
	//�����ַ����ߴ�
	m_TextSize = v_intSize;
}

void CGDI::Set_Text_String(CString v_strData)
{
	//�����ַ�������
	m_TextString = v_strData;
}

void CGDI::Set_Align(StringAlignment v_Align)
{
	//�����ı����뷽ʽ
	m_TextAlign = v_Align;
}

//˫�����ͼ,��ʾͼ��
void CGDI::DB_Draw_CAD(HDC v_HDC)
{
	//�ؼ��ߴ粻��ȷ
	if(m_CtrWidth <= 0 || m_CtrHeight <= 0)
	{
		return;
	}
	
	//�������⻭��
	Bitmap t_Bitmap(m_CtrWidth,m_CtrHeight);

	//���⻭�����������豸�У�����Ļ�ͼ���������豸��
	Graphics t_VirtualGraphics(&t_Bitmap);
	
	//�����豸�������ͼ��
	t_VirtualGraphics.Clear(m_BkColor);
	
	//��ʾ����ͼƬ
	Draw_BK_Image(&t_VirtualGraphics);
	
	//��ʾ�߿�
	Draw_Border(&t_VirtualGraphics);
	
	//��ʾ����,���Ͻ�����
	Graphics t_Graphics(v_HDC);
	
	t_Graphics.DrawImage(&t_Bitmap,0,0);
}

void CGDI::Set_Meta_Color(Color v_Color)
{
	m_MetaColor = v_Color;
}



void CGDI::Set_Times(double v_douTimes)
{
	if (v_douTimes <= 0.01)
	{
		AfxMessageBox("���ű���������Χ");
		return;
	}

	m_douTimes = v_douTimes;
}

void CGDI::Clear()
{
	
}

void  CGDI::Draw_Border(Graphics *v_bmpGraphics)
{
	//��ʾ�߿�
	if (m_bShowBorder)
	{
		//���ÿؼ��ߴ�
		if (m_CtrWidth <= 0 || m_CtrHeight <= 0)
		{
			return;
		}

		Draw_Rectange(v_bmpGraphics,0,0,m_CtrWidth,m_CtrHeight,m_BorderColor);
	}
}

void CGDI::Draw_BK_Image(Graphics *v_bmpGraphics)
{
	//���ÿؼ��ߴ�
	if (m_CtrWidth <= 0 || m_CtrHeight <= 0)
	{
		return;
	}
	
	if (m_pBkImage == NULL)
	{
		return;
	}
	
	//�������ٻ���λͼ
	CachedBitmap t_CachedBitmap(m_pBkImage,v_bmpGraphics);

	//��ʾ����λͼ
	v_bmpGraphics->DrawCachedBitmap(&t_CachedBitmap,0,0);

	//�����豸����ͼƬ
  // bmpGraphics->DrawImage(m_pBkImage,0,0,m_pBkImage->GetWidth(),m_pBkImage->GetHeight());
}

void  CGDI::Draw_Text(Graphics *v_bmpGraphics)
{
	//�ַ�������
	FontFamily t_FontFamily(L"΢���ź�");
	
	//�ַ�����ɫ
	SolidBrush t_SolidBrush(m_TextColor);
	
	//�ַ�����ʽ
	Gdiplus::Font t_Font(&t_FontFamily,(float)m_TextSize,FontStyleRegular,UnitPixel);
	
	//ת�����ַ�������
	BSTR t_BSTR = m_TextString.AllocSysString(); 
	
	//�ַ������Ͻ�λ��
	PointF t_PointF(0,(float)(m_CtrHeight/2.0-m_TextSize/1.6));
	
	//�ַ������뷽ʽ
	StringFormat t_StringFormat;                         
	
	//ˮƽ���ж���
	t_StringFormat.SetAlignment(m_TextAlign); 
	
	//�����ַ���
	v_bmpGraphics->DrawString(t_BSTR,-1,&t_Font,t_PointF,&t_StringFormat,&t_SolidBrush);
	
	//���ͷŻ�����ڴ�й¶
	SysFreeString(t_BSTR);
}

void CGDI::Draw_Text(Graphics *v_bmpGraphics,double v_douX,double v_douY,CString v_strText,Color v_Color)
{
	//�ַ�������
	FontFamily t_FontFamily(L"΢���ź�");

	//�ַ�����ɫ
	SolidBrush t_SolidBrush(v_Color);

	//�ַ�����ʽ
	Gdiplus::Font t_Font(&t_FontFamily,(float)m_TextSize,FontStyleRegular,UnitPixel);

	//ת�����ַ�������
	BSTR t_BSTR = v_strText.AllocSysString(); 

	//�ַ������Ͻ�λ��
	PointF t_PointF((float)v_douX,(float)v_douY);

	//�ַ������뷽ʽ
	StringFormat t_StringFormat;                         

	//ˮƽ���ж���
	t_StringFormat.SetAlignment(m_TextAlign); 

	//�����ַ���
	v_bmpGraphics->DrawString(t_BSTR,-1,&t_Font,t_PointF,&t_StringFormat,&t_SolidBrush);

	//���ͷŻ�����ڴ�й¶
	SysFreeString(t_BSTR);
}

void CGDI::Draw_Line(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intX2,int v_intY2)
{
	//���廭��
	Pen t_Pen(m_MetaColor);

	//���ÿ��
	t_Pen.SetWidth(float(m_BorderWidth));
	
	//��ֱ��
	v_bmpGraphics->DrawLine(&t_Pen, v_intX1, v_intY1, v_intX2, v_intY2);
}

void CGDI::Draw_Line(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intX2,int v_intY2,Color v_Color)
{
	//���廭��
	Pen t_Pen(v_Color);
	
	//���ÿ��
	t_Pen.SetWidth(float(m_BorderWidth));
	
	//��ֱ��
	v_bmpGraphics->DrawLine(&t_Pen, v_intX1, v_intY1, v_intX2, v_intY2);
}

void CGDI:: Draw_Arc(Graphics *v_bmpGraphics,double v_douRaius,double v_douCenterX,double v_douCenterY,double v_douStartAngle,double v_douEndAngle)
{
	//���廭��
	Pen t_Pen(m_MetaColor);
	
	//���ÿ��
	t_Pen.SetWidth(float(m_BorderWidth));
	
	//��Բ��
	Rect t_Rect((int)(v_douCenterX - v_douRaius),(int)(v_douCenterY - v_douRaius),(int)(v_douRaius * 2),(int)(v_douRaius * 2));
	
	double Angle_Dis = v_douEndAngle - v_douStartAngle;
	
	if(Angle_Dis < 0) 
	{
		Angle_Dis += 360;
	}
	
	v_bmpGraphics->DrawArc(&t_Pen,t_Rect,(float)(360 - v_douEndAngle),(float)(Angle_Dis));
}

void CGDI:: Draw_Arc(Graphics *v_bmpGraphics,double v_douRaius,double v_douCenterX,double v_douCenterY,double v_douStartAngle,double v_douEndAngle,Color v_Color)
{
	//���廭��
	Pen t_Pen(v_Color);

	//���ÿ��
	t_Pen.SetWidth(float(m_BorderWidth));

	//��Բ��
	Rect t_Rect((int)(v_douCenterX - v_douRaius),(int)(v_douCenterY - v_douRaius),(int)(v_douRaius * 2),(int)(v_douRaius * 2));

	double Angle_Dis = v_douEndAngle - v_douStartAngle;

	if(Angle_Dis < 0) 
	{
		Angle_Dis += 360;
	}

	v_bmpGraphics->DrawArc(&t_Pen,t_Rect,(float)(360 - v_douEndAngle),(float)(Angle_Dis));
}

void CGDI::Draw_Rectange(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intWidth,int v_intHeight,Color v_Color)
{
	//���廭��
	Pen t_Pen(v_Color);
	
	//���ÿ��
	t_Pen.SetWidth(float(m_BorderWidth));
	
	//������
	v_bmpGraphics->DrawRectangle(&t_Pen, 
		(int)(v_intX1 + m_BorderWidth / 2),
		(int)(v_intY1 + m_BorderWidth / 2),
		(int)(v_intWidth - m_BorderWidth),
		(int)(v_intHeight - m_BorderWidth));
}