#include "StdAfx.h"
#include "Gdi_Image2.h"

//��Ϣӳ��
BEGIN_MESSAGE_MAP(CGdi_Image2, CWnd)
	//{{AFX_MSG_MAP
	ON_WM_PAINT()//��ͼ����
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CGdi_Image2::CGdi_Image2(void)
{
	m_pImageBuf = NULL;

	m_Image = NULL;

	m_bDown = FALSE;

	m_bMoveDown = FALSE;

	m_bAdjustDown = FALSE;

	m_intMoveHomeX = 0;

	m_intMoveHomeY = 0;
}


CGdi_Image2::~CGdi_Image2(void)
{
	//�ͷż���DC
	m_dcCompatible.DeleteDC();

	//�ͷ�����ͼ���ݵ�λͼ
	m_Bitmap.DeleteObject();

	if (m_pImageBuf != NULL)
	{
		delete[] m_pImageBuf;

		m_pImageBuf = NULL;
	}

	Release_Image(&m_Image);
}


void CGdi_Image2::OnPaint() 
{
	//��ȡ��ͼ�豸DC
	CPaintDC dc(this);

	//������ο�
	CRect t_Rect;

	//��ȡ���ڿͻ���������
	this->GetClientRect(&t_Rect);

	//������DC�����ݸ��Ƶ���ǰDC
	dc.BitBlt(0,0,t_Rect.Width(),t_Rect.Height(),&m_dcCompatible,0,0,SRCCOPY);
}


void CGdi_Image2::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL t_bClickIn = FALSE;

	BOOL t_bAdjust = FALSE;

	if (m_NMHDR.top != -1 && m_NMHDR.bottom != -1 && m_NMHDR.left != -1 && m_NMHDR.right != -1)
	{
		if (  abs(point.x - (long)m_NMHDR.right) <= 10 && abs(point.y - (long)m_NMHDR.bottom) <= 10 )
		{
			t_bAdjust = TRUE;
		}
		else
		{
			if ( (point.x >= (long)m_NMHDR.left && point.x <= (long)m_NMHDR.right || point.x >= (long)m_NMHDR.right && point.x <= (long)m_NMHDR.left ) &&
				(point.y >= (long)m_NMHDR.top && point.y <= (long)m_NMHDR.bottom || point.y >= (long)m_NMHDR.bottom && point.y <= (long)m_NMHDR.top ))
			{
				t_bClickIn = TRUE;
			}
		}
	}


	if (t_bAdjust)
	{
		m_intMoveHomeX = point.x;

		m_intMoveHomeY = point.y;

		m_bAdjustDown = TRUE;
	}
	else
	{
		if (t_bClickIn)
		{
			m_intMoveHomeX = point.x;

			m_intMoveHomeY = point.y;

			m_bMoveDown = TRUE;
		}
		else
		{
			m_NMHDR.left = point.x;

			m_NMHDR.top = point.y;

			m_bDown = TRUE;
		}
	}
}


void CGdi_Image2::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDown)
	{
		m_NMHDR.right = point.x;

		m_NMHDR.bottom = point.y;

		GetParent()->SendMessage(WM_NOTIFY, (WPARAM)m_NMHDR.nmhdr.idFrom,(LPARAM)&m_NMHDR);
	}
	else
	{
		m_NMHDR2.right = point.x;

		m_NMHDR2.bottom = point.y;

		GetParent()->SendMessage(WM_NOTIFY, (WPARAM)m_NMHDR2.nmhdr.idFrom,(LPARAM)&m_NMHDR2);
	}

	if (m_bMoveDown)
	{
		m_NMHDR.left += point.x - m_intMoveHomeX;

		m_NMHDR.right += point.x - m_intMoveHomeX;

		m_NMHDR.top += point.y - m_intMoveHomeY;

		m_NMHDR.bottom += point.y - m_intMoveHomeY;

		m_intMoveHomeX = point.x;

		m_intMoveHomeY = point.y;

		GetParent()->SendMessage(WM_NOTIFY, (WPARAM)m_NMHDR.nmhdr.idFrom,(LPARAM)&m_NMHDR);
	}


	if (m_bAdjustDown)
	{
		m_NMHDR.right += point.x - m_intMoveHomeX;

		m_NMHDR.bottom += point.y - m_intMoveHomeY;

		m_intMoveHomeX = point.x;

		m_intMoveHomeY = point.y;

		GetParent()->SendMessage(WM_NOTIFY, (WPARAM)m_NMHDR.nmhdr.idFrom,(LPARAM)&m_NMHDR);
	}
}



void CGdi_Image2::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDown)
	{
		m_NMHDR.right = point.x;

		m_NMHDR.bottom = point.y;

		GetParent()->SendMessage(WM_NOTIFY, (WPARAM)m_NMHDR.nmhdr.idFrom,(LPARAM)&m_NMHDR);

		m_bDown = FALSE;
	}

	if (m_bMoveDown)
	{
		m_NMHDR.left += point.x - m_intMoveHomeX;

		m_NMHDR.right += point.x - m_intMoveHomeX;

		m_NMHDR.top += point.y - m_intMoveHomeY;

		m_NMHDR.bottom += point.y - m_intMoveHomeY;

		m_intMoveHomeX = point.x;

		m_intMoveHomeY = point.y;

		GetParent()->SendMessage(WM_NOTIFY, (WPARAM)m_NMHDR.nmhdr.idFrom,(LPARAM)&m_NMHDR);

		m_bMoveDown = FALSE;
	}


	if (m_bAdjustDown)
	{
		m_NMHDR.right += point.x - m_intMoveHomeX;

		m_NMHDR.bottom += point.y - m_intMoveHomeY;

		m_intMoveHomeX = point.x;

		m_intMoveHomeY = point.y;

		GetParent()->SendMessage(WM_NOTIFY, (WPARAM)m_NMHDR.nmhdr.idFrom,(LPARAM)&m_NMHDR);

		m_bAdjustDown = FALSE;
	}
}


BOOL CGdi_Image2::SubclassDlgItem(UINT nID, CWnd* pParent)
{
	//��������,����������ؼ�
	CWnd::SubclassDlgItem(nID,pParent);

	//������ο�
	CRect t_Rect;

	//��ȡ���ڿͻ���������
	this->GetClientRect(&t_Rect);

	m_pImageBuf = new BYTE[t_Rect.Width() * t_Rect.Height() * 4];

	for (int j = 0; j < t_Rect.Height(); j++)
	{
		for (int i = 0; i < t_Rect.Width(); i++)
		{
			m_pImageBuf[(j * t_Rect.Width() + i) * 4 + 0] = 0;
			m_pImageBuf[(j * t_Rect.Width() + i) * 4 + 1] = 0;
			m_pImageBuf[(j * t_Rect.Width() + i) * 4 + 2] = 0;
			m_pImageBuf[(j * t_Rect.Width() + i) * 4 + 3] = 0;
		}
	}

	CClientDC dc(this);

	//����λͼ
	if(!m_Bitmap.CreateCompatibleBitmap(&dc,t_Rect.Width(),t_Rect.Height()) )
	{
		AfxMessageBox("����λͼʧ��");
		return FALSE;	
	}

	//��������DC
	if(!m_dcCompatible.CreateCompatibleDC(&dc))
	{
		AfxMessageBox("��������DCʧ��");
		return FALSE;
	}

	//������λͼѡ�����DC
	m_dcCompatible.SelectObject(&m_Bitmap);

	//����WM_PAINT����Ϣ����
	Invalidate(FALSE);

	Clear();

	//���
	m_NMHDR.nmhdr.hwndFrom = GetSafeHwnd();

	//�ؼ�ID
	m_NMHDR.nmhdr.idFrom = GetDlgCtrlID();

	//�Զ�����Ϣ
	m_NMHDR.nmhdr.code = WM_CLICK_CTRL;


	//���
	m_NMHDR2.nmhdr.hwndFrom = GetSafeHwnd();

	//�ؼ�ID
	m_NMHDR2.nmhdr.idFrom = GetDlgCtrlID();

	//�Զ�����Ϣ
	m_NMHDR2.nmhdr.code = WM_MOUSE_MOVE2;

	return TRUE;
}

BOOL CGdi_Image2::Clear()
{
	m_NMHDR.top    = -1;

	m_NMHDR.bottom = -1;

	m_NMHDR.left   = -1;

	m_NMHDR.right  = -1;

	return TRUE;
}


void CGdi_Image2::Show(IPL v_Image)
{
	if (v_Image == NULL)
	{
		AfxMessageBox("��ʾ��ͼ����Ϊ��");
		return;
	}

	//������ο�
	CRect t_Rect;

	//��ȡ���ڿͻ���������
	this->GetClientRect(&t_Rect);

	//ͼ��ĳߴ���ؼ��ĳߴ�һ��
	if (t_Rect.Width() ==  v_Image->width && t_Rect.Height() == v_Image->height)
	{
		//ֱ����ʾͼ��
		Show_Direct(v_Image);
	}
	else
	{
		//���ݿؼ��ߴ�����ͼ��
		CGdi_Image2::Zoom(v_Image,&m_Image,t_Rect.Width(),t_Rect.Height() );

		Show_Direct(m_Image);
	}
}

void CGdi_Image2::Show_Direct(IPL v_Image)
{
	//������ο�
	CRect t_Rect;

	//��ȡ���ڿͻ���������
	this->GetClientRect(&t_Rect);

	if (v_Image == NULL)
	{
		AfxMessageBox("��ʾ��ͼ����Ϊ��");
		return;
	}

	int t_intSrc;

	int t_intDst;

	if (v_Image->nChannels == 1)
	{
		for (int j = 0; j < v_Image->height && j < t_Rect.Height() ; j++)
		{
			for (int i = 0; i < v_Image->width && i < t_Rect.Width(); i++)
			{
				t_intSrc = j * v_Image->widthStep + i;

				t_intDst = (j * t_Rect.Width() + i) * 4;

				m_pImageBuf[t_intDst + 0] = v_Image->imageData[t_intSrc];
				m_pImageBuf[t_intDst + 1] = v_Image->imageData[t_intSrc];
				m_pImageBuf[t_intDst + 2] = v_Image->imageData[t_intSrc];
			}
		}
	}
	else
	{
		for (int j = 0; j < v_Image->height && j < t_Rect.Height(); j++)
		{
			for (int i = 0; i < v_Image->width && i < t_Rect.Width(); i++)
			{
				t_intSrc = j * v_Image->widthStep + i * 3 ;

				t_intDst = (j * t_Rect.Width() + i) * 4;

				m_pImageBuf[t_intDst + 0] = v_Image->imageData[t_intSrc + 0];
				m_pImageBuf[t_intDst + 1] = v_Image->imageData[t_intSrc + 1];
				m_pImageBuf[t_intDst + 2] = v_Image->imageData[t_intSrc + 2];
			}
		}
	}

	//����λͼ����
	m_Bitmap.SetBitmapBits(t_Rect.Width() * t_Rect.Height() * 4,(void*)m_pImageBuf);

	//����WM_PAINT����Ϣ����
	Invalidate(FALSE);
}

BOOL CGdi_Image2::Zoom(const IPL v_Image, IPL *v_pTrans,int v_intWidth,int v_intHeight)
{
	if (v_Image == NULL)
	{
		AfxMessageBox("ͼ���С�任ʱ,����ͼ����Ϊ��");
		return FALSE;
	}

	if (*v_pTrans == NULL || (*v_pTrans)->width != v_intWidth || 
		(*v_pTrans)->height != v_intHeight || (*v_pTrans)->nChannels != v_Image->nChannels)
	{
		Create_Image(v_pTrans,v_intWidth,v_intHeight,v_Image->nChannels);
	}

	double t_douScaleX = 1.0 * v_Image->width / v_intWidth;

	double t_douScaleY = 1.0 * v_Image->height / v_intHeight;

	IPL t_Trans = *v_pTrans;

	int t_intWidth = t_Trans->width;

	int t_intHeight = t_Trans->height;

	//�ж� ��ͼ�����ŵ��ؼ��ߴ��С,�������Ƿ񳬳���Χ;���������Χ,����������
	for (int i = 0;i < t_Trans->width; i++)
	{
		if ( (int)(i * t_douScaleX + 0.5) >= v_Image->width)
		{
			t_intWidth = i;
			break;
		}
	}

	//�ж� ��ͼ�����ŵ��ؼ��ߴ��С,�������Ƿ񳬳���Χ;���������Χ,����������
	for (int i = 0;i < t_Trans->height; i++)
	{
		if ( (int)(i * t_douScaleY + 0.5) >= v_Image->height)
		{
			t_intHeight = i;
			break;
		}
	}

	int t_intRow;

	int t_intCol;

	if (v_Image->nChannels == 1)
	{
		for (int j = 0 ;j < t_intHeight; j++)
		{
			t_intRow = (int)(j * t_douScaleY + 0.5);

			for (int i = 0 ;i < t_intWidth; i++)
			{
				t_intCol = (int)(i * t_douScaleX + 0.5);

				t_Trans->at[j][i] = v_Image->at[t_intRow][t_intCol];
			}
		}
	}
	else
	{
		for (int j = 0 ;j < t_intHeight; j++)
		{
			t_intRow = (int)(j * t_douScaleY + 0.5);

			for (int i = 0 ;i < t_intWidth; i++)
			{
				t_intCol = (int)(i * t_douScaleX + 0.5);

				t_Trans->at[j][i * 3 + 0] = v_Image->at[t_intRow][t_intCol * 3 + 0];

				t_Trans->at[j][i * 3 + 1] = v_Image->at[t_intRow][t_intCol * 3 + 1];

				t_Trans->at[j][i * 3 + 2] = v_Image->at[t_intRow][t_intCol * 3 + 2];
			}
		}	
	}

	return TRUE;
}
