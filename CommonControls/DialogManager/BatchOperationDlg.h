//*****************************************************
//    
//    @copyright      �������
//    @version        v1.0
//    @file           BatchOperationDlg.H
//    @author         LC
//    @data           2018/10/16 16:59
//    @brief          ���������Ի���(�����������滻/����/ɾ���ȳ���)
//****************************************************/

#pragma once

/**
*  @class 	���������Ի���
*
*  @brief
*/
class CBatchOperationDlg : public CDialog
{
	enum { IDD = IDD_DLG_BATCHOPERATION };

public:
	CBatchOperationDlg(LPCTSTR strMess, LPCTSTR strTitle, CWnd* pParent = NULL);
	~CBatchOperationDlg();

	DECLARE_MESSAGE_MAP()

protected:
	/**
	*  @brief    ���ݽ���
	*
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	// ��ʼ���Ի���ʱ������ҳ��
	afx_msg BOOL OnInitDialog();

	afx_msg void OnOK();
	afx_msg void OnCancel();

private:
	CStatic			_staticMess;		///< ��ʾ��Ϣ�ؼ�
	CButton			_checkBox;			///< ��ѡ��

	CString			_strMess;			///< ��ʾ��Ϣ
	CString			_strTitle;			///< ������
};

