
#pragma once

/**********************************************************************

  * 文件名称: GDI_Text.h
  *
  * 摘	要: GDI+文本控件，用于显示静态文本
  * 
  * 当前版本: 1.0
  *
  * 作	者: 林木松
  *
  * 完成日期: 2014年7月2日
  
/**********************************************************************/


//绘图头文件
#include "Gdi.h"

class CGdi_Text : public CWnd 
{
		
public: 

	//构造函数
	CGdi_Text();
	
	//析构函数
	~CGdi_Text();

	//关联对象与控件
	virtual BOOL SubclassDlgItem(UINT nID, CWnd* pParent);

	//设置背景颜色
	void Set_BK_Color(Color m_Color);

	//设置背景图片
	void Set_BK_Image(CString m_strImage);
	
	//设置字符串颜色
	void Set_Text_Color(Color m_Color);

	//设置字符串尺寸
	void Set_Text_Size(UINT m_Size);

	//设置字符串内容
	void Set_Text_String(CString m_strData);

	//设置文本对齐方式
	void Set_Align(StringAlignment m_Align);

	//设置边框颜色
	void Set_Border_Color(Color m_Color);

protected:
	//GDI+绘图对象
	CGDI m_GDI;

protected:
	//{{AFX_MSG
	afx_msg void OnPaint();//绘图函数
	//}}AFX_MSG
	
	//向类中添加消息映射必要的结构体和函数声明
	DECLARE_MESSAGE_MAP()
};