
#pragma once

/**********************************************************************

  * 文件名称: GDI_Background.h
  *
  * 摘	要: 使用GDI绘制对话框背景图片
  * 
  * 当前版本: 1.0
  *
  * 作	者: 林木松
  *
  * 完成日期: 2014年7月2日
  
/**********************************************************************/

class CGdi_Background
{
public:
	//构造函数
	CGdi_Background();

	//析构函数
	virtual ~CGdi_Background();

	//设置背景图片
	void Set_Background(CString m_strBackground);

	//获取画刷,在
	CBrush* Get_Brush();
	
protected:

	//画刷
	CBrush m_Brush;
};

