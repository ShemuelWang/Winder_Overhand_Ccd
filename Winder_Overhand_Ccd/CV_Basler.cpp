#include "StdAfx.h"
#include "CV_Basler.h"

using namespace Pylon;

using namespace GenApi;


CCV_Basler::CCV_Basler(void)
{
	m_pCamera = NULL;

	m_bOpen = FALSE;

	//初始化Pylon运行时
	PylonInitialize();
}


CCV_Basler::~CCV_Basler(void)
{
	//释放所有pylon资源
	PylonTerminate();  
}

BOOL CCV_Basler::Open_Camera()
{
	if (m_bOpen)
	{
		AfxMessageBox("相机已经打开");
		return FALSE;
	}

	//获取传输层工厂
	CTlFactory& t_Factory = CTlFactory::GetInstance();

	DeviceInfoList_t t_Devices;

	//相机个数
	int t_intCameraCount = t_Factory.EnumerateDevices(t_Devices);

	if (t_intCameraCount == 0)
	{
		AfxMessageBox("没有找到相机");
		return FALSE;
	}

	//创建相机数组
	CInstantCameraArray t_CameraArray(t_intCameraCount);

	//遍历和打开所有的相机
	for (int i = 0; i < t_CameraArray.GetSize(); i++)
	{
		t_CameraArray[i].Attach(t_Factory.CreateDevice(t_Devices[i]));

		//相机名称
		CString t_strCameraName;

		t_strCameraName.Format("编号%d 相机名称=%s 序列号=%s",i,t_CameraArray[i].GetDeviceInfo().GetModelName().c_str(),t_CameraArray[i].GetDeviceInfo().GetSerialNumber().c_str() );

		OutputDebugString(t_strCameraName);
	}

	//关闭已关联的所有相机
	t_CameraArray.DetachDevice();

	//找到第一个连接的相机对象
	m_pCamera = new CInstantCamera(t_Factory.CreateDevice(t_Devices[0]) );

	//打开相机
	m_pCamera->Open();

	m_bOpen = TRUE;

	return TRUE;

}

BOOL CCV_Basler::Start_Grabbing(Pylon::EGrabStrategy strategy)
{
	if (!m_bOpen)
	{
		AfxMessageBox("开始抓取图像时,相机还没打开");
		return FALSE;
	}

	m_pCamera->StartGrabbing(strategy,GrabLoop_ProvidedByUser);

	return TRUE;
}

BOOL CCV_Basler::Stop_Grabbing()
{
	if (!m_bOpen)
	{
		AfxMessageBox("停止抓取图像时,相机还没打开");
		return FALSE;
	}

	//停止采集图像
	m_pCamera->StopGrabbing();

	return TRUE;
}

BOOL CCV_Basler::Open_Camera(CString v_strID)
{
	if (m_bOpen)
	{
		AfxMessageBox("相机已经打开!");
		return FALSE;
	}

	//获取传输层工厂
	CTlFactory& t_Factory = CTlFactory::GetInstance();

	DeviceInfoList_t t_Devices;

	//相机个数
	int t_intCameraCount = t_Factory.EnumerateDevices(t_Devices);

	if (t_intCameraCount == 0)
	{
		AfxMessageBox("没有找到相机!\r\n请检查相机是否已连接");
		return FALSE;
	}

	//创建相机数组
	CInstantCameraArray t_CameraArray(t_intCameraCount);

	//是否找到与设定的序列号匹配的相机
	int t_intFindID = -1;

	//遍历和打开所有的相机
	for (int i = 0; i < t_CameraArray.GetSize(); i++)
	{
		t_CameraArray[i].Attach(t_Factory.CreateDevice(t_Devices[i]));

		CString t_strCameraID = t_CameraArray[i].GetDeviceInfo().GetSerialNumber().c_str();

		CString t_strCameraName = t_CameraArray[i].GetDeviceInfo().GetModelName().c_str();

		//相机名称
		CString t_strData;

		t_strData.Format("编号%d 相机名称=%s 序列号=%s",i,t_strCameraName,t_strCameraID);

		OutputDebugString(t_strData);

		if (t_strCameraID.Find(v_strID) >= 0)
		{
			t_intFindID = i;
			break;
		}
	}

	//关闭已关联的所有相机
	t_CameraArray.DetachDevice();

	if (t_intFindID < 0 || t_intFindID >= t_intCameraCount)
	{
		AfxMessageBox("没有找到指定编号的相机!\r\n编号: " + v_strID);
		return FALSE;
	}

	//找到第一个连接的相机对象
	m_pCamera = new CInstantCamera(t_Factory.CreateDevice(t_Devices[t_intFindID]) );

	//打开相机
	m_pCamera->Open();

	m_bOpen = TRUE;

	return TRUE;
}

BOOL CCV_Basler::Close_Camera()
{
	if (m_bOpen)
	{
		//已经开始采集图像
		if ( m_pCamera->IsGrabbing() )
		{
			//停止采集图像
			m_pCamera->StopGrabbing();
		}

		//关闭相机
		m_pCamera->Close();

		m_bOpen = FALSE;
	}

	return TRUE;
}

BOOL CCV_Basler::Skip_Frame()
{
	if (!m_bOpen)
	{
		AfxMessageBox("获取图像数据时,相机还没打开");
		return FALSE;
	}

	if ( !m_pCamera->IsGrabbing() )
	{
		AfxMessageBox("获取图像数据时,相机没有开始连续采集");
		return FALSE;
	}

	//该智能指针用于接收抓取结果数据
	CGrabResultPtr t_ptrGrabResult;

	//等待接收图像,需要设定超时时间
	if(m_pCamera->RetrieveResult(1, t_ptrGrabResult, TimeoutHandling_Return) )
	{
		OutputDebugString("图像队列里面有缓存");
		return FALSE;
	}

	return TRUE;
}

BOOL CCV_Basler::Get_Trigger_Frame(IPL *v_Image)
{
	if (!m_bOpen)
	{
		AfxMessageBox("获取图像数据时,相机还没打开");
		return FALSE;
	}

	if ( !m_pCamera->IsGrabbing() )
	{
		AfxMessageBox("获取图像数据时,相机没有开始连续采集");
		return FALSE;
	}

	//该智能指针用于接收抓取结果数据
	CGrabResultPtr t_ptrGrabResult;

	//等待接收图像,需要设定超时时间
	//如果图像队列里面没有图片,并且当前不是处于正在采集图像的过程中,直接返回FALSE
	//多次外触发,只获取最后一张图像,然后清空底层缓冲队列
	//多次外触发,也只能获取1张图像
	if(!m_pCamera->RetrieveResult(_CAMERA_SNAP_TIME, t_ptrGrabResult, TimeoutHandling_Return) )
	{
		OutputDebugString("RetrieveResult采集图像出错");

		//采集失败的时候,把图像设定为全黑
		if (*v_Image != NULL)
		{
			Set_Color(*v_Image);
		}
		else
		{
			AfxMessageBox("RetrieveResult采集图像出错\r\n图像为空");
		}

		//超时,暂时返回黑图
		return FALSE;
	}
	
	if (!t_ptrGrabResult->GrabSucceeded() )
	{
		CString t_strError;

		t_strError.Format("错误代码%d,错误信息",t_ptrGrabResult->GetErrorCode(),t_ptrGrabResult->GetErrorDescription().c_str() );

		AfxMessageBox("获取图像数据失败\r\n" + t_strError);

		return FALSE;
	}

	if (t_ptrGrabResult->GetWidth() * t_ptrGrabResult->GetHeight() != t_ptrGrabResult->GetImageSize()) 
	{
		AfxMessageBox("获取图像数据时,只支持灰度图像(单通道)");
		return FALSE;
	}

	if (*v_Image == NULL || (*v_Image)->nChannels != 1 ||
		(*v_Image)->width != t_ptrGrabResult->GetWidth() || (*v_Image)->height != t_ptrGrabResult->GetHeight() )
	{
		Create_Image(v_Image,t_ptrGrabResult->GetWidth(),t_ptrGrabResult->GetHeight(),1);

		Set_Color(*v_Image);

		OutputDebugString("创建内存空间");
	}

	memcpy((*v_Image)->imageData,(BYTE*)t_ptrGrabResult->GetBuffer(),t_ptrGrabResult->GetWidth() * t_ptrGrabResult->GetHeight() );

	return TRUE;
}




BOOL CCV_Basler::Get_Frame(IPL *v_Image)
{
	if (!m_bOpen)
	{
		AfxMessageBox("获取图像数据时,相机还没打开");
		return FALSE;
	}

	//用时小于1毫秒
	if( !m_pCamera->CanWaitForFrameTriggerReady() )
	{
		AfxMessageBox("相机没有准备好");
		return FALSE;
	}

	//该智能指针用于接收抓取结果数据
	CGrabResultPtr t_ptrGrabResult;

	//执行软触发,用时1-2毫秒
	m_pCamera->ExecuteSoftwareTrigger();

	//等待接收图像,需要设定超时时间
	if( !m_pCamera->RetrieveResult(_CAMERA_SNAP_TIME,t_ptrGrabResult, TimeoutHandling_Return) )
	{
		OutputDebugString("获取图像数据超时");
		return FALSE;
	}

	if (!t_ptrGrabResult->GrabSucceeded() )
	{
		CString t_strError;

		t_strError.Format("错误代码%u,错误信息\r\n%s",t_ptrGrabResult->GetErrorCode(),t_ptrGrabResult->GetErrorDescription().c_str() );

		OutputDebugString(t_strError);

		AfxMessageBox("获取图像数据失败\r\n" + t_strError);

		return FALSE;
	}

	if (t_ptrGrabResult->GetWidth() * t_ptrGrabResult->GetHeight() != t_ptrGrabResult->GetImageSize()) 
	{
		AfxMessageBox("获取图像数据时,只支持灰度图像(单通道)");
		return FALSE;
	}

	//宽度高度不正确的处理方式
	if (t_ptrGrabResult->GetWidth() == 0)
	{
		OutputDebugString("获取图像数据时,图像宽度超出范围");
		return FALSE;
	}

	//宽度高度不正确的处理方式
	if (t_ptrGrabResult->GetHeight() == 0)
	{
		OutputDebugString("获取图像数据时,图像高度超出范围");
		return FALSE;
	}

	if (*v_Image == NULL || (*v_Image)->nChannels != 1 ||
		(*v_Image)->width != t_ptrGrabResult->GetWidth() || (*v_Image)->height != t_ptrGrabResult->GetHeight() )
	{
		Create_Image(v_Image,t_ptrGrabResult->GetWidth(),t_ptrGrabResult->GetHeight(),1);

		Set_Color(*v_Image);
	}

	memcpy((*v_Image)->imageData,(BYTE*)t_ptrGrabResult->GetBuffer(),t_ptrGrabResult->GetWidth() * t_ptrGrabResult->GetHeight() );

	return TRUE;
}


BOOL CCV_Basler::Set_Exposure(int v_intExposure)
{
	if (!m_bOpen)
	{
		AfxMessageBox("设置曝光时间时,相机还没打开");
		return FALSE;
	}

	//获取相机参数对象
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	//关闭自动曝光
	CEnumParameter t_ExposureAuto(t_nodemap, "ExposureAuto");

	t_ExposureAuto.TrySetValue("Off");



	CIntegerParameter t_Exposure(t_nodemap, "ExposureTimeRaw");

	if (v_intExposure < t_Exposure.GetMin())
	{
		CString t_strData;

		t_strData.Format("相机曝光值超过最小值\r\n当前值=%d 最小值%d",v_intExposure,t_Exposure.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intExposure > t_Exposure.GetMax() )
	{
		CString t_strData;

		t_strData.Format("相机曝光值超过最大值\r\n当前值=%d 最大值%d",v_intExposure,t_Exposure.GetMax() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	t_Exposure.SetValue(v_intExposure,IntegerValueCorrection_Nearest);
	
	return TRUE;
}

BOOL CCV_Basler::Set_Gain(int v_intGain)
{
	if (!m_bOpen)
	{
		AfxMessageBox("设置增益时,相机还没打开");
		return FALSE;
	}


	//获取相机参数对象
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	//关闭自动增益
	CEnumParameter t_GainAuto(t_nodemap, "GainAuto");

	t_GainAuto.TrySetValue("Off");



	CIntegerParameter t_Gain(t_nodemap, "GainRaw");

	if (v_intGain < t_Gain.GetMin())
	{
		CString t_strData;

		t_strData.Format("相机曝光值超过最小值\r\n当前值=%d 最小值%d",v_intGain,t_Gain.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intGain > t_Gain.GetMax() )
	{
		CString t_strData;

		t_strData.Format("相机曝光值超过最大值\r\n当前值=%d 最大值%d",v_intGain,t_Gain.GetMax() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	t_Gain.SetValue(v_intGain,IntegerValueCorrection_Nearest);

	return TRUE;
}

BOOL CCV_Basler::Set_Trigger_Mode()
{
	if (!m_bOpen)
	{
		AfxMessageBox("设置外触发模式时,相机还没打开");
		return FALSE;
	}

	//获取相机参数对象
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	CEnumParameter t_TriggerSelector(t_nodemap, "TriggerSelector");

	if (t_TriggerSelector.CanSetValue("FrameStart") )
	{
		if ( !t_TriggerSelector.TrySetValue("FrameStart"))
		{
			AfxMessageBox("设置外触发选择器失败1");
			return FALSE;
		}
	}
	else
	{
		if(t_TriggerSelector.CanSetValue("AcquisitionStart") )
		{
			if ( !t_TriggerSelector.TrySetValue("AcquisitionStart") )
			{
				AfxMessageBox("设置外触发选择器失败2");
				return FALSE;
			}
		}
		else
		{
			AfxMessageBox("设置外触发选择器失败3");
			return FALSE;
		}
	}


	CEnumParameter t_TriggerMode(t_nodemap, "TriggerMode");

	if(!t_TriggerMode.TrySetValue("On") )
	{
		AfxMessageBox("设置外触发模式失败");
		return FALSE;
	}


	CEnumParameter t_TriggerSource(t_nodemap, "TriggerSource");

	if(!t_TriggerSource.TrySetValue("Line1") )
	{
		AfxMessageBox("设置外触发信号源失败");
		return FALSE;
	}


	CEnumParameter t_TriggerActivation(t_nodemap, "TriggerActivation");

	if(!t_TriggerActivation.TrySetValue("RisingEdge") )
	{
		AfxMessageBox("设置外触发电平失败");
		return FALSE;
	}

	return TRUE;
}


BOOL CCV_Basler::Set_Software_Mode()
{
	if (!m_bOpen)
	{
		AfxMessageBox("设置软触发模式时,相机还没打开");
		return FALSE;
	}

	//注册软件触发模式
	m_pCamera->RegisterConfiguration( new CSoftwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);

	return TRUE;
}


BOOL CCV_Basler::Set_Size(int v_intWidth,int v_intHeight)
{
	if (!m_bOpen)
	{
		AfxMessageBox("设置图像尺寸时,相机还没打开");
		return FALSE;
	}

	//获取相机参数对象
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	CIntegerParameter t_Width(t_nodemap, "Width");

	if (v_intWidth < t_Width.GetMin() )
	{
		CString t_strData;

		t_strData.Format("设置相机宽度超过最小值\r\n当前值=%d 最小值%d",v_intWidth, t_Width.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intWidth > t_Width.GetMax() )
	{
		CString t_strData;

		t_strData.Format("设置相机宽度超过最大值\r\n当前值=%d 最大值%d",v_intWidth, t_Width.GetMax() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	t_Width.SetValue(v_intWidth,IntegerValueCorrection_Nearest);



	CIntegerParameter t_Height(t_nodemap, "Height");

	if (v_intHeight < t_Height.GetMin() )
	{
		CString t_strData;

		t_strData.Format("设置相机高度超过最小值\r\n当前值=%d 最小值%d",v_intHeight, t_Height.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intHeight > t_Height.GetMax() )
	{
		CString t_strData;

		t_strData.Format("设置相机高度超过最大值\r\n当前值=%d 最大值%d",v_intHeight, t_Height.GetMax() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	t_Height.SetValue(v_intHeight,IntegerValueCorrection_Nearest);


	return TRUE;
}


BOOL CCV_Basler::Set_Offset(int v_intOffsetX,int v_intOffsetY)
{
	if (!m_bOpen)
	{
		AfxMessageBox("设置图像裁切位置时,相机还没打开");
		return FALSE;
	}

	//获取相机参数对象
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	CIntegerParameter t_OffsetX(t_nodemap, "OffsetX");

	if (v_intOffsetX < t_OffsetX.GetMin() )
	{
		CString t_strData;

		t_strData.Format("设置图像裁切位置X超过最小值\r\n当前值=%d 最小值%d",v_intOffsetX, t_OffsetX.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intOffsetX > t_OffsetX.GetMax() )
	{
		CString t_strData;

		t_strData.Format("设置图像裁切位置X超过最大值\r\n当前值=%d 最大值%d",v_intOffsetX, t_OffsetX.GetMax() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	t_OffsetX.SetValue(v_intOffsetX,IntegerValueCorrection_Nearest);




	CIntegerParameter t_OffsetY(t_nodemap, "OffsetY");

	if (v_intOffsetY < t_OffsetY.GetMin() )
	{
		CString t_strData;

		t_strData.Format("设置图像裁切位置Y超过最小值\r\n当前值=%d 最小值%d",v_intOffsetY, t_OffsetY.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intOffsetY > t_OffsetY.GetMax() )
	{
		CString t_strData;

		t_strData.Format("设置图像裁切位置Y超过最大值\r\n当前值=%d 最大值%d",v_intOffsetY, t_OffsetY.GetMax() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	t_OffsetY.SetValue(v_intOffsetY,IntegerValueCorrection_Nearest);


	return TRUE;
}



BOOL CCV_Basler::Set_Packet_Size(int v_intSize)
{
	if (!m_bOpen)
	{
		AfxMessageBox("设置图像裁切位置时,相机还没打开");
		return FALSE;
	}


	//获取相机参数对象
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	CIntegerParameter t_PacketSize(t_nodemap, "GevSCPSPacketSize");

	if (v_intSize < t_PacketSize.GetMin() )
	{
		CString t_strData;

		t_strData.Format("设置传输层数据包尺寸超过最小值\r\n当前值=%d 最小值%d",v_intSize, t_PacketSize.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intSize > t_PacketSize.GetMax() )
	{
		CString t_strData;

		t_strData.Format("设置传输层数据包尺寸超过最大值\r\n当前值=%d 最大值%d",v_intSize, t_PacketSize.GetMax() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	t_PacketSize.SetValue(v_intSize,IntegerValueCorrection_Nearest);

	return TRUE;
}


BOOL CCV_Basler::Set_Frame_Rate(int v_intRate)
{


	return TRUE;
}