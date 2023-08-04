#pragma once


// CPreviewDlg 对话框

class CPreviewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPreviewDlg)

public:
	CPreviewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPreviewDlg();

// 对话框数据
	enum { IDD = IDD_PREVIEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
