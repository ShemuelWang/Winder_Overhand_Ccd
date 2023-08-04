#ifndef _LEISAI_IOC0640_H
#define _LEISAI_IOC0640_H

#define __IOC0640_EXPORTS
//������������
#ifdef __IOC0640_EXPORTS
	#define IOC0640_API __declspec(dllexport)
#else
	#define IOC0640_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//�жϻص�����ָ�붨��
typedef unsigned int        UINT;
typedef UINT (__stdcall *IOC0640_OPERATE)(PVOID operate_data);



//---------------------   �忨��ʼ�����ú���  ----------------------
/********************************************************************************
** ��������: ioc_board_init
** ��������: ���ư��ʼ�������ó�ʼ�����ٶȵ�����
** �䡡  ��: ��
** �� �� ֵ: 0���޿��� 1-8���ɹ�(ʵ�ʿ���) 
**     
*********************************************************************************/
IOC0640_API int __stdcall ioc_board_init(void);

/********************************************************************************
** ��������: ioc_board_close
** ��������: �ر����п�
** �䡡  ��: ��
** �� �� ֵ: ��
** ��    ��: 2010.11.1
*********************************************************************************/
IOC0640_API void __stdcall ioc_board_close(void); 

//IO���ƺ���
IOC0640_API int __stdcall ioc_read_inbit(WORD cardno, WORD bitno);
IOC0640_API int __stdcall  ioc_read_outbit(WORD cardno, WORD bitno);
IOC0640_API DWORD __stdcall ioc_write_outbit(WORD cardno, WORD bitno,WORD on_off);
IOC0640_API DWORD __stdcall ioc_reverse_outbit(WORD cardno, WORD bitno,double ms_time);

IOC0640_API long __stdcall ioc_read_inport(WORD cardno,WORD m_PortNo);
IOC0640_API long __stdcall ioc_read_outport(WORD cardno,WORD m_PortNo) ;
IOC0640_API DWORD __stdcall ioc_write_outport(WORD cardno,WORD m_PortNo, DWORD port_value);

IOC0640_API DWORD __stdcall ioc_config_intbitmode(WORD cardno, WORD bitno,WORD enable,WORD logic);
IOC0640_API DWORD __stdcall ioc_read_intbitmode(WORD cardno, WORD bitno,WORD *enable,WORD *logic);
IOC0640_API int __stdcall ioc_read_intbitstatus(WORD cardno, WORD bitno);

IOC0640_API DWORD __stdcall ioc_config_intporten(WORD cardno,WORD m_PortNo, DWORD port_en);
IOC0640_API DWORD __stdcall ioc_config_intportlogic(WORD cardno,WORD m_PortNo, DWORD port_logic);

IOC0640_API DWORD __stdcall ioc_read_intporten(WORD cardno,WORD m_PortNo,DWORD *port_en);
IOC0640_API DWORD __stdcall ioc_read_intportlogic(WORD cardno,WORD m_PortNo,DWORD *port_logic);
IOC0640_API DWORD __stdcall ioc_read_intportmode(WORD cardno, WORD m_PortNo,DWORD *enable,DWORD *logic);
IOC0640_API long __stdcall ioc_read_intportstatus(WORD cardno,WORD m_PortNo);

IOC0640_API DWORD __stdcall ioc_set_filter(WORD cardno, double filter);

IOC0640_API DWORD __stdcall ioc_int_enable(WORD cardno, IOC0640_OPERATE funcIntHandler, PVOID operate_data);
IOC0640_API DWORD __stdcall ioc_int_disable(WORD cardno);

IOC0640_API DWORD  __stdcall ioc_write_outbit_nosp(WORD cardno, WORD bitno,WORD on_off);

IOC0640_API DWORD __stdcall ioc_get_addrword(short cardno,DWORD addr);
IOC0640_API DWORD __stdcall ioc_get_password(short cardno);
IOC0640_API int __stdcall ioc_check_sn(WORD cardno, char * str_sn);
IOC0640_API int __stdcall ioc_get_hard_version(WORD cardno, char * hard_version);

#ifdef __cplusplus
}
#endif

#endif 