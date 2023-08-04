#pragma once

//相机头文件
#include <pylon/PylonIncludes.h>

#include <pylon/BaslerUniversalInstantCamera.h>

#include "CV_Func_Pro.h"

//相机采集时间,单位毫秒
#define _CAMERA_SNAP_TIME 50

class CCV_Basler
{
public:
	CCV_Basler(void);
	~CCV_Basler(void);

	//打开相机
	BOOL Open_Camera();

	//打开相机,关联相机的编号
	BOOL Open_Camera(CString v_strID);

	//开始抓取图像
	BOOL Start_Grabbing(Pylon::EGrabStrategy strategy = Pylon::GrabStrategy_LatestImageOnly);

	//停止抓拍图像
	BOOL Stop_Grabbing();

	//关闭相机
	BOOL Close_Camera();

	//如果图像队列里面有图像,先跳过
	BOOL Skip_Frame();

	//获取外触发的数据帧
	BOOL Get_Trigger_Frame(IPL *v_Image);

	//获取数据帧
	BOOL Get_Frame(IPL *v_Image);

	//设置曝光时间
	BOOL Set_Exposure(int v_intExpose);

	//设置增益
	BOOL Set_Gain(int v_intGain);

	//设定采集的图像尺寸
	BOOL Set_Size(int v_intWidth,int v_intHeight);

	//设定裁切起始位置
	BOOL Set_Offset(int v_intOffsetX,int v_intOffsetY);

	//设置外触发模式
	BOOL Set_Trigger_Mode();

	//设置软触发模式
	BOOL Set_Software_Mode();

	//设置传输层的数据包大小
	BOOL Set_Packet_Size(int v_intSize);

	//设置帧率
	BOOL Set_Frame_Rate(int v_intRate);

private:

	//相机指针
	Pylon::CInstantCamera *m_pCamera;

	//是否打开相机
	BOOL m_bOpen;
};

