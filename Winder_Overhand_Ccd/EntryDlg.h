#pragma once


// CEntryDlg 对话框

class CEntryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEntryDlg)

public:
	CEntryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEntryDlg();

	//设定 浮点数的范围
	BOOL Set_Double_Range(double v_douMin,double v_douMax,double *v_pdouInput);

	//设定 整型的范围
	BOOL Set_Int_Range(int v_intMin,int v_intMax,int *v_pintInput);

private:

	//背景图片
	CGdi_Background m_gdiBackground;

	//自定义字体
	CFont m_Font;


	//输入类型,1=整型,2=浮点型
	int m_intType;

	//整型的最小值
	int m_intMin;

	//整型的最大值
	int m_intMax;

	//返回整型数据的指针
	int *m_pintInput;


	//浮点的最小值
	double m_douMin;

	//浮点的最大值
	double m_douMax;

	//返回浮点数据的指针
	double *m_pdouInput;

// 对话框数据
	enum { IDD = IDD_ENTRY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedItem1();
	afx_msg void OnBnClickedOk();
};
