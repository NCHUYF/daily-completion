//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           IMSRegDlg.H
//    @author         zhuyu
//    @data           2018/3/28 10:37
//    @brief          ƽ̨ע��Ի���
//*****************************************************

#pragma once

#define BUSATTSDLG L"ҵ�����ԶԻ���"

/**
*  @class    ����ͳһ���£��رնԻ���
*
*  @brief
*/
class COMMONCONTROLS_API CMSRegDlg
{
public:
	/**
	*  @brief    ����
	*
	*  @param    bool bIsMutex	�Ƿ�Ϊ����Ի���
	*  @return   
	*/
	CMSRegDlg(bool bIsMutex, const CString& strDlgName = L"");
	virtual ~CMSRegDlg();

public:
	/**
	*  @brief    ���¶Ի���
	*
	*  @return
	*/
	virtual void UpdateDialog();

	/**
	*  @brief    �رնԻ���
	*
	*  @return   
	*/
	virtual void CloseDialog() = 0;

protected:
	/**
	*  @brief    ע��Ի���
	*
	*  @param    IMSRegDlg * pDlg
	*  @param    bool bIsMutex	�Ƿ�Ϊ����Ի���
	*  @return   void
	*/
	void RegistDialog(CMSRegDlg* pDlg, bool bIsMutex);

	/**
	*  @brief    ж�ضԻ���
	*
	*  @param    CMSRegDlg * pDlg
	*  @return   void
	*/
	void UnRegistDialog(CMSRegDlg* pDlg);
	
	/**
	*  @brief    ��map��ɾ���رյĶԻ���ָ��
	*
	*  @param    CMSRegDlg * pDlg
	*  @return   void
	*/
	void DeleteDialogInMap(CMSRegDlg* pDlg);
};



/**
*  @class    ����ͳһ���£��رնԻ���
*
*  @brief
*/
class COMMONCONTROLS_API CDlgMgrTool
{
public:

	/**
	*  @brief    ���¶Ի���
	*
	*  @return   void
	*/
	static void UpdateDialog();

	/**
	*  @brief    �رնԻ���
	*
	*  @return   void
	*/
	static void CloseDialog();

	/**
	*  @brief    ��ȡ�Ի���ָ��
	*
	*  @param    const CString&
	*  @return   CMSRegDlg*
	*/
	static CMSRegDlg* GetDlgPter(const CString& strName);

protected:

};