#pragma once

//���ͷ�ļ�
#include <pylon/PylonIncludes.h>

#include <pylon/BaslerUniversalInstantCamera.h>

#include "CV_Func_Pro.h"

//����ɼ�ʱ��,��λ����
#define _CAMERA_SNAP_TIME 50

class CCV_Basler
{
public:
	CCV_Basler(void);
	~CCV_Basler(void);

	//�����
	BOOL Open_Camera();

	//�����,��������ı��
	BOOL Open_Camera(CString v_strID);

	//��ʼץȡͼ��
	BOOL Start_Grabbing(Pylon::EGrabStrategy strategy = Pylon::GrabStrategy_LatestImageOnly);

	//ֹͣץ��ͼ��
	BOOL Stop_Grabbing();

	//�ر����
	BOOL Close_Camera();

	//���ͼ�����������ͼ��,������
	BOOL Skip_Frame();

	//��ȡ�ⴥ��������֡
	BOOL Get_Trigger_Frame(IPL *v_Image);

	//��ȡ����֡
	BOOL Get_Frame(IPL *v_Image);

	//�����ع�ʱ��
	BOOL Set_Exposure(int v_intExpose);

	//��������
	BOOL Set_Gain(int v_intGain);

	//�趨�ɼ���ͼ��ߴ�
	BOOL Set_Size(int v_intWidth,int v_intHeight);

	//�趨������ʼλ��
	BOOL Set_Offset(int v_intOffsetX,int v_intOffsetY);

	//�����ⴥ��ģʽ
	BOOL Set_Trigger_Mode();

	//��������ģʽ
	BOOL Set_Software_Mode();

	//���ô��������ݰ���С
	BOOL Set_Packet_Size(int v_intSize);

	//����֡��
	BOOL Set_Frame_Rate(int v_intRate);

private:

	//���ָ��
	Pylon::CInstantCamera *m_pCamera;

	//�Ƿ�����
	BOOL m_bOpen;
};

