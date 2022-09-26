#pragma once

// begin namespace
namespace BwProj{ namespace toolkit {

/** @addtogroup CriticalSectionHandle
* @{
*/

//! ��ʵ�����������
class COnlyOneInstance
{
public:
	COnlyOneInstance (LPCTSTR MutexName);
	~COnlyOneInstance (void);
	/**
	* �������õ�ʵ���Ƿ�ɹ�
	* @return �������õ�ʵ���Ƿ�ɹ�
	* - true �ɹ��� false ʧ��
	*/
	bool GetSuccess (void);
protected:
	/** ��ʵ���������� */
	HANDLE _Mutex;
};


/** @} */
}}