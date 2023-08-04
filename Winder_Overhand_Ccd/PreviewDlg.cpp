// PreviewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Winder_Overhand_Ccd.h"
#include "PreviewDlg.h"
#include "afxdialogex.h"


// CPreviewDlg 对话框

IMPLEMENT_DYNAMIC(CPreviewDlg, CDialogEx)

CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPreviewDlg::IDD, pParent)
{

}

CPreviewDlg::~CPreviewDlg()
{
}

void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPreviewDlg, CDialogEx)
END_MESSAGE_MAP()


// CPreviewDlg 消息处理程序
