
//ͷ�ļ�ֻ����һ��
#pragma once

/**********************************************************************

  * �ļ�����: GDI.h
  *
  * ժ	Ҫ: GDI+��ͼ��
  * 
  * ��ǰ�汾: 2.0
  *
  * ��	��: ��ľ��
  *
  * �������: 2015��3��25��
  
/**********************************************************************/

#ifndef ULONG_PTR

#define ULONG_PTR ULONG 

//���GDIͷ�ļ�
#include <gdiplus.h>

//ʹ��GDIplus�����ռ�
using namespace Gdiplus;

//GDI+���ӿ�
#pragma comment(lib, "gdiplus.lib")

#endif


//ͼ���豸�ӿ�
class CGDI  
{

//�ⲿ�ɵ��ú���
public:

	//���캯��
	CGDI();

	//�麯������������
	~CGDI();

	//�����ؼ�
	void Relate_CTR(CWnd *v_pWnd);

	//���ÿؼ��ߴ�
	void Set_CTR_Size(UINT v_intWidth,UINT v_intHeight);

	//���ñ���ɫ
	void Set_BK_Color(Color v_Color);

	//���ñ���ͼƬ
	void Set_BK_Image(CString v_strBkImage);

	//���ñ߿���ɫ
	void Set_Border_Color(Color v_Color);

	//���ñ߿���
	void Set_Border_Width(UINT v_intWidth);


public:
	
	//˫����,�����ַ���
	void DB_Draw(HDC v_HDC);

	//�����ַ�����ɫ
	void Set_Text_Color(Color v_Color);
	
	//�����ַ����ߴ�
	void Set_Text_Size(UINT v_intSize);
	
	//�����ַ�������
	void Set_Text_String(CString v_strData);

	//�����ı��Ķ��뷽ʽ
	void Set_Align(StringAlignment v_Align);

public:

	//˫�����ͼͼ��
	void DB_Draw_CAD(HDC v_HDC);

	//����ͼԪ��ɫ
	void Set_Meta_Color(Color v_Color);

	//�������ű���
	void Set_Times(double v_douTimes);

	//���ͼ��
	void Clear();

protected:

	//���Ʊ߿�
	void Draw_Border(Graphics *v_bmpGraphics);

	//��ʾ����ͼƬ
	void Draw_BK_Image(Graphics *v_bmpGraphics);

	//�����ַ���
	void Draw_Text(Graphics *v_bmpGraphics);

	//����ֱ��
	void Draw_Text(Graphics *v_bmpGraphics,double v_douX,double v_douY,CString v_strText,Color v_Color);

	//����ֱ��
	void Draw_Line(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intX2,int v_intY2);
	
	//����ֱ��,�����Զ�����ɫ
	void Draw_Line(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intX2,int v_intY2,Color v_Color);

	//����Բ��
	void Draw_Arc(Graphics *v_bmpGraphics,double v_douRaius,double v_douCenterX,double v_douCenterY,double v_douStartAngle,double v_douEndAngle);

	//����Բ��
	void Draw_Arc(Graphics *v_bmpGraphics,double v_douRaius,double v_douCenterX,double v_douCenterY,double v_douStartAngle,double v_douEndAngle,Color v_Color);

	//���ƾ���
	void Draw_Rectange(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intWidth,int v_intHeight,Color v_Color);

protected:

	//GDI�ṹ
	GdiplusStartupInput m_gdiplusStartupInput;

	//�޷��ų�����
    ULONG_PTR m_gdiplusToken;

	//�ؼ��Ŀ��
	UINT m_CtrWidth;

	//�ؼ��ĸ߶�
	UINT m_CtrHeight;

	//������ɫ
	Color m_BkColor;

	//����ͼƬ
	Gdiplus::Bitmap* m_pBkImage;

	//�߿���ɫ
	Color m_BorderColor;

	//�߿���
	UINT m_BorderWidth;

	//�Ƿ���ʾ�߿�
	BOOL m_bShowBorder;


	//�ַ���
protected:
	
	//�ַ�������
	CString m_TextString;
	
	//�ַ�����ɫ
	Color m_TextColor;
	
	//�ַ����ߴ�
	UINT m_TextSize;
	
	//�ı��Ķ��뷽ʽ
	StringAlignment m_TextAlign;
	

	//ͼ������
protected:

	//ͼ����ɫ
	Color m_MetaColor;

	//���ű���
	double m_douTimes;
};
