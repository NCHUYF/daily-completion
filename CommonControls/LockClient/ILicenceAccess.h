#pragma once

// ��������
#define LINCENCE_ACCESS L"LicAcc"

/*
* ��������ӿ�
*/
class ILicenceAccess
{
public:
	virtual ~ILicenceAccess() {}

	/**
	*  @brief    ���ָ�������֤�Ƿ����;
	*
	*  @param    nMode �����֤�ĺ궨�壬�ο�GetSupportLicenceByModeʵ��
	*/
	virtual bool CheckLicence(int nMode) = 0;
};