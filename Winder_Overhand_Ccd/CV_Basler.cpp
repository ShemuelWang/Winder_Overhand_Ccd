#include "StdAfx.h"
#include "CV_Basler.h"

using namespace Pylon;

using namespace GenApi;


CCV_Basler::CCV_Basler(void)
{
	m_pCamera = NULL;

	m_bOpen = FALSE;

	//��ʼ��Pylon����ʱ
	PylonInitialize();
}


CCV_Basler::~CCV_Basler(void)
{
	//�ͷ�����pylon��Դ
	PylonTerminate();  
}

BOOL CCV_Basler::Open_Camera()
{
	if (m_bOpen)
	{
		AfxMessageBox("����Ѿ���");
		return FALSE;
	}

	//��ȡ����㹤��
	CTlFactory& t_Factory = CTlFactory::GetInstance();

	DeviceInfoList_t t_Devices;

	//�������
	int t_intCameraCount = t_Factory.EnumerateDevices(t_Devices);

	if (t_intCameraCount == 0)
	{
		AfxMessageBox("û���ҵ����");
		return FALSE;
	}

	//�����������
	CInstantCameraArray t_CameraArray(t_intCameraCount);

	//�����ʹ����е����
	for (int i = 0; i < t_CameraArray.GetSize(); i++)
	{
		t_CameraArray[i].Attach(t_Factory.CreateDevice(t_Devices[i]));

		//�������
		CString t_strCameraName;

		t_strCameraName.Format("���%d �������=%s ���к�=%s",i,t_CameraArray[i].GetDeviceInfo().GetModelName().c_str(),t_CameraArray[i].GetDeviceInfo().GetSerialNumber().c_str() );

		OutputDebugString(t_strCameraName);
	}

	//�ر��ѹ������������
	t_CameraArray.DetachDevice();

	//�ҵ���һ�����ӵ��������
	m_pCamera = new CInstantCamera(t_Factory.CreateDevice(t_Devices[0]) );

	//�����
	m_pCamera->Open();

	m_bOpen = TRUE;

	return TRUE;

}

BOOL CCV_Basler::Start_Grabbing(Pylon::EGrabStrategy strategy)
{
	if (!m_bOpen)
	{
		AfxMessageBox("��ʼץȡͼ��ʱ,�����û��");
		return FALSE;
	}

	m_pCamera->StartGrabbing(strategy,GrabLoop_ProvidedByUser);

	return TRUE;
}

BOOL CCV_Basler::Stop_Grabbing()
{
	if (!m_bOpen)
	{
		AfxMessageBox("ֹͣץȡͼ��ʱ,�����û��");
		return FALSE;
	}

	//ֹͣ�ɼ�ͼ��
	m_pCamera->StopGrabbing();

	return TRUE;
}

BOOL CCV_Basler::Open_Camera(CString v_strID)
{
	if (m_bOpen)
	{
		AfxMessageBox("����Ѿ���!");
		return FALSE;
	}

	//��ȡ����㹤��
	CTlFactory& t_Factory = CTlFactory::GetInstance();

	DeviceInfoList_t t_Devices;

	//�������
	int t_intCameraCount = t_Factory.EnumerateDevices(t_Devices);

	if (t_intCameraCount == 0)
	{
		AfxMessageBox("û���ҵ����!\r\n��������Ƿ�������");
		return FALSE;
	}

	//�����������
	CInstantCameraArray t_CameraArray(t_intCameraCount);

	//�Ƿ��ҵ����趨�����к�ƥ������
	int t_intFindID = -1;

	//�����ʹ����е����
	for (int i = 0; i < t_CameraArray.GetSize(); i++)
	{
		t_CameraArray[i].Attach(t_Factory.CreateDevice(t_Devices[i]));

		CString t_strCameraID = t_CameraArray[i].GetDeviceInfo().GetSerialNumber().c_str();

		CString t_strCameraName = t_CameraArray[i].GetDeviceInfo().GetModelName().c_str();

		//�������
		CString t_strData;

		t_strData.Format("���%d �������=%s ���к�=%s",i,t_strCameraName,t_strCameraID);

		OutputDebugString(t_strData);

		if (t_strCameraID.Find(v_strID) >= 0)
		{
			t_intFindID = i;
			break;
		}
	}

	//�ر��ѹ������������
	t_CameraArray.DetachDevice();

	if (t_intFindID < 0 || t_intFindID >= t_intCameraCount)
	{
		AfxMessageBox("û���ҵ�ָ����ŵ����!\r\n���: " + v_strID);
		return FALSE;
	}

	//�ҵ���һ�����ӵ��������
	m_pCamera = new CInstantCamera(t_Factory.CreateDevice(t_Devices[t_intFindID]) );

	//�����
	m_pCamera->Open();

	m_bOpen = TRUE;

	return TRUE;
}

BOOL CCV_Basler::Close_Camera()
{
	if (m_bOpen)
	{
		//�Ѿ���ʼ�ɼ�ͼ��
		if ( m_pCamera->IsGrabbing() )
		{
			//ֹͣ�ɼ�ͼ��
			m_pCamera->StopGrabbing();
		}

		//�ر����
		m_pCamera->Close();

		m_bOpen = FALSE;
	}

	return TRUE;
}

BOOL CCV_Basler::Skip_Frame()
{
	if (!m_bOpen)
	{
		AfxMessageBox("��ȡͼ������ʱ,�����û��");
		return FALSE;
	}

	if ( !m_pCamera->IsGrabbing() )
	{
		AfxMessageBox("��ȡͼ������ʱ,���û�п�ʼ�����ɼ�");
		return FALSE;
	}

	//������ָ�����ڽ���ץȡ�������
	CGrabResultPtr t_ptrGrabResult;

	//�ȴ�����ͼ��,��Ҫ�趨��ʱʱ��
	if(m_pCamera->RetrieveResult(1, t_ptrGrabResult, TimeoutHandling_Return) )
	{
		OutputDebugString("ͼ����������л���");
		return FALSE;
	}

	return TRUE;
}

BOOL CCV_Basler::Get_Trigger_Frame(IPL *v_Image)
{
	if (!m_bOpen)
	{
		AfxMessageBox("��ȡͼ������ʱ,�����û��");
		return FALSE;
	}

	if ( !m_pCamera->IsGrabbing() )
	{
		AfxMessageBox("��ȡͼ������ʱ,���û�п�ʼ�����ɼ�");
		return FALSE;
	}

	//������ָ�����ڽ���ץȡ�������
	CGrabResultPtr t_ptrGrabResult;

	//�ȴ�����ͼ��,��Ҫ�趨��ʱʱ��
	//���ͼ���������û��ͼƬ,���ҵ�ǰ���Ǵ������ڲɼ�ͼ��Ĺ�����,ֱ�ӷ���FALSE
	//����ⴥ��,ֻ��ȡ���һ��ͼ��,Ȼ����յײ㻺�����
	//����ⴥ��,Ҳֻ�ܻ�ȡ1��ͼ��
	if(!m_pCamera->RetrieveResult(_CAMERA_SNAP_TIME, t_ptrGrabResult, TimeoutHandling_Return) )
	{
		OutputDebugString("RetrieveResult�ɼ�ͼ�����");

		//�ɼ�ʧ�ܵ�ʱ��,��ͼ���趨Ϊȫ��
		if (*v_Image != NULL)
		{
			Set_Color(*v_Image);
		}
		else
		{
			AfxMessageBox("RetrieveResult�ɼ�ͼ�����\r\nͼ��Ϊ��");
		}

		//��ʱ,��ʱ���غ�ͼ
		return FALSE;
	}
	
	if (!t_ptrGrabResult->GrabSucceeded() )
	{
		CString t_strError;

		t_strError.Format("�������%d,������Ϣ",t_ptrGrabResult->GetErrorCode(),t_ptrGrabResult->GetErrorDescription().c_str() );

		AfxMessageBox("��ȡͼ������ʧ��\r\n" + t_strError);

		return FALSE;
	}

	if (t_ptrGrabResult->GetWidth() * t_ptrGrabResult->GetHeight() != t_ptrGrabResult->GetImageSize()) 
	{
		AfxMessageBox("��ȡͼ������ʱ,ֻ֧�ֻҶ�ͼ��(��ͨ��)");
		return FALSE;
	}

	if (*v_Image == NULL || (*v_Image)->nChannels != 1 ||
		(*v_Image)->width != t_ptrGrabResult->GetWidth() || (*v_Image)->height != t_ptrGrabResult->GetHeight() )
	{
		Create_Image(v_Image,t_ptrGrabResult->GetWidth(),t_ptrGrabResult->GetHeight(),1);

		Set_Color(*v_Image);

		OutputDebugString("�����ڴ�ռ�");
	}

	memcpy((*v_Image)->imageData,(BYTE*)t_ptrGrabResult->GetBuffer(),t_ptrGrabResult->GetWidth() * t_ptrGrabResult->GetHeight() );

	return TRUE;
}




BOOL CCV_Basler::Get_Frame(IPL *v_Image)
{
	if (!m_bOpen)
	{
		AfxMessageBox("��ȡͼ������ʱ,�����û��");
		return FALSE;
	}

	//��ʱС��1����
	if( !m_pCamera->CanWaitForFrameTriggerReady() )
	{
		AfxMessageBox("���û��׼����");
		return FALSE;
	}

	//������ָ�����ڽ���ץȡ�������
	CGrabResultPtr t_ptrGrabResult;

	//ִ������,��ʱ1-2����
	m_pCamera->ExecuteSoftwareTrigger();

	//�ȴ�����ͼ��,��Ҫ�趨��ʱʱ��
	if( !m_pCamera->RetrieveResult(_CAMERA_SNAP_TIME,t_ptrGrabResult, TimeoutHandling_Return) )
	{
		OutputDebugString("��ȡͼ�����ݳ�ʱ");
		return FALSE;
	}

	if (!t_ptrGrabResult->GrabSucceeded() )
	{
		CString t_strError;

		t_strError.Format("�������%u,������Ϣ\r\n%s",t_ptrGrabResult->GetErrorCode(),t_ptrGrabResult->GetErrorDescription().c_str() );

		OutputDebugString(t_strError);

		AfxMessageBox("��ȡͼ������ʧ��\r\n" + t_strError);

		return FALSE;
	}

	if (t_ptrGrabResult->GetWidth() * t_ptrGrabResult->GetHeight() != t_ptrGrabResult->GetImageSize()) 
	{
		AfxMessageBox("��ȡͼ������ʱ,ֻ֧�ֻҶ�ͼ��(��ͨ��)");
		return FALSE;
	}

	//��ȸ߶Ȳ���ȷ�Ĵ���ʽ
	if (t_ptrGrabResult->GetWidth() == 0)
	{
		OutputDebugString("��ȡͼ������ʱ,ͼ���ȳ�����Χ");
		return FALSE;
	}

	//��ȸ߶Ȳ���ȷ�Ĵ���ʽ
	if (t_ptrGrabResult->GetHeight() == 0)
	{
		OutputDebugString("��ȡͼ������ʱ,ͼ��߶ȳ�����Χ");
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
		AfxMessageBox("�����ع�ʱ��ʱ,�����û��");
		return FALSE;
	}

	//��ȡ�����������
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	//�ر��Զ��ع�
	CEnumParameter t_ExposureAuto(t_nodemap, "ExposureAuto");

	t_ExposureAuto.TrySetValue("Off");



	CIntegerParameter t_Exposure(t_nodemap, "ExposureTimeRaw");

	if (v_intExposure < t_Exposure.GetMin())
	{
		CString t_strData;

		t_strData.Format("����ع�ֵ������Сֵ\r\n��ǰֵ=%d ��Сֵ%d",v_intExposure,t_Exposure.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intExposure > t_Exposure.GetMax() )
	{
		CString t_strData;

		t_strData.Format("����ع�ֵ�������ֵ\r\n��ǰֵ=%d ���ֵ%d",v_intExposure,t_Exposure.GetMax() );

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
		AfxMessageBox("��������ʱ,�����û��");
		return FALSE;
	}


	//��ȡ�����������
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	//�ر��Զ�����
	CEnumParameter t_GainAuto(t_nodemap, "GainAuto");

	t_GainAuto.TrySetValue("Off");



	CIntegerParameter t_Gain(t_nodemap, "GainRaw");

	if (v_intGain < t_Gain.GetMin())
	{
		CString t_strData;

		t_strData.Format("����ع�ֵ������Сֵ\r\n��ǰֵ=%d ��Сֵ%d",v_intGain,t_Gain.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intGain > t_Gain.GetMax() )
	{
		CString t_strData;

		t_strData.Format("����ع�ֵ�������ֵ\r\n��ǰֵ=%d ���ֵ%d",v_intGain,t_Gain.GetMax() );

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
		AfxMessageBox("�����ⴥ��ģʽʱ,�����û��");
		return FALSE;
	}

	//��ȡ�����������
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	CEnumParameter t_TriggerSelector(t_nodemap, "TriggerSelector");

	if (t_TriggerSelector.CanSetValue("FrameStart") )
	{
		if ( !t_TriggerSelector.TrySetValue("FrameStart"))
		{
			AfxMessageBox("�����ⴥ��ѡ����ʧ��1");
			return FALSE;
		}
	}
	else
	{
		if(t_TriggerSelector.CanSetValue("AcquisitionStart") )
		{
			if ( !t_TriggerSelector.TrySetValue("AcquisitionStart") )
			{
				AfxMessageBox("�����ⴥ��ѡ����ʧ��2");
				return FALSE;
			}
		}
		else
		{
			AfxMessageBox("�����ⴥ��ѡ����ʧ��3");
			return FALSE;
		}
	}


	CEnumParameter t_TriggerMode(t_nodemap, "TriggerMode");

	if(!t_TriggerMode.TrySetValue("On") )
	{
		AfxMessageBox("�����ⴥ��ģʽʧ��");
		return FALSE;
	}


	CEnumParameter t_TriggerSource(t_nodemap, "TriggerSource");

	if(!t_TriggerSource.TrySetValue("Line1") )
	{
		AfxMessageBox("�����ⴥ���ź�Դʧ��");
		return FALSE;
	}


	CEnumParameter t_TriggerActivation(t_nodemap, "TriggerActivation");

	if(!t_TriggerActivation.TrySetValue("RisingEdge") )
	{
		AfxMessageBox("�����ⴥ����ƽʧ��");
		return FALSE;
	}

	return TRUE;
}


BOOL CCV_Basler::Set_Software_Mode()
{
	if (!m_bOpen)
	{
		AfxMessageBox("��������ģʽʱ,�����û��");
		return FALSE;
	}

	//ע���������ģʽ
	m_pCamera->RegisterConfiguration( new CSoftwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);

	return TRUE;
}


BOOL CCV_Basler::Set_Size(int v_intWidth,int v_intHeight)
{
	if (!m_bOpen)
	{
		AfxMessageBox("����ͼ��ߴ�ʱ,�����û��");
		return FALSE;
	}

	//��ȡ�����������
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	CIntegerParameter t_Width(t_nodemap, "Width");

	if (v_intWidth < t_Width.GetMin() )
	{
		CString t_strData;

		t_strData.Format("���������ȳ�����Сֵ\r\n��ǰֵ=%d ��Сֵ%d",v_intWidth, t_Width.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intWidth > t_Width.GetMax() )
	{
		CString t_strData;

		t_strData.Format("���������ȳ������ֵ\r\n��ǰֵ=%d ���ֵ%d",v_intWidth, t_Width.GetMax() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	t_Width.SetValue(v_intWidth,IntegerValueCorrection_Nearest);



	CIntegerParameter t_Height(t_nodemap, "Height");

	if (v_intHeight < t_Height.GetMin() )
	{
		CString t_strData;

		t_strData.Format("��������߶ȳ�����Сֵ\r\n��ǰֵ=%d ��Сֵ%d",v_intHeight, t_Height.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intHeight > t_Height.GetMax() )
	{
		CString t_strData;

		t_strData.Format("��������߶ȳ������ֵ\r\n��ǰֵ=%d ���ֵ%d",v_intHeight, t_Height.GetMax() );

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
		AfxMessageBox("����ͼ�����λ��ʱ,�����û��");
		return FALSE;
	}

	//��ȡ�����������
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	CIntegerParameter t_OffsetX(t_nodemap, "OffsetX");

	if (v_intOffsetX < t_OffsetX.GetMin() )
	{
		CString t_strData;

		t_strData.Format("����ͼ�����λ��X������Сֵ\r\n��ǰֵ=%d ��Сֵ%d",v_intOffsetX, t_OffsetX.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intOffsetX > t_OffsetX.GetMax() )
	{
		CString t_strData;

		t_strData.Format("����ͼ�����λ��X�������ֵ\r\n��ǰֵ=%d ���ֵ%d",v_intOffsetX, t_OffsetX.GetMax() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	t_OffsetX.SetValue(v_intOffsetX,IntegerValueCorrection_Nearest);




	CIntegerParameter t_OffsetY(t_nodemap, "OffsetY");

	if (v_intOffsetY < t_OffsetY.GetMin() )
	{
		CString t_strData;

		t_strData.Format("����ͼ�����λ��Y������Сֵ\r\n��ǰֵ=%d ��Сֵ%d",v_intOffsetY, t_OffsetY.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intOffsetY > t_OffsetY.GetMax() )
	{
		CString t_strData;

		t_strData.Format("����ͼ�����λ��Y�������ֵ\r\n��ǰֵ=%d ���ֵ%d",v_intOffsetY, t_OffsetY.GetMax() );

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
		AfxMessageBox("����ͼ�����λ��ʱ,�����û��");
		return FALSE;
	}


	//��ȡ�����������
	INodeMap& t_nodemap = m_pCamera->GetNodeMap();

	CIntegerParameter t_PacketSize(t_nodemap, "GevSCPSPacketSize");

	if (v_intSize < t_PacketSize.GetMin() )
	{
		CString t_strData;

		t_strData.Format("���ô�������ݰ��ߴ糬����Сֵ\r\n��ǰֵ=%d ��Сֵ%d",v_intSize, t_PacketSize.GetMin() );

		AfxMessageBox( t_strData);

		return FALSE;
	}

	if (v_intSize > t_PacketSize.GetMax() )
	{
		CString t_strData;

		t_strData.Format("���ô�������ݰ��ߴ糬�����ֵ\r\n��ǰֵ=%d ���ֵ%d",v_intSize, t_PacketSize.GetMax() );

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