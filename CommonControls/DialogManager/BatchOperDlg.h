//*****************************************************
//    
//    @copyright      �������
//    @version        v1.0
//    @file           BatchOperDlg.H
//    @author         LC
//    @data           2018/10/17 8:54
//    @brief          ����������
//****************************************************/

#pragma once

class CBatchOperationDlg;

/**
*  @class 	���������Ի������ӿ���
*
*  @brief	���ڴ����������滻/����/ɾ�����Ի���
*/
class COMMONCONTROLS_API CBatchOperDlg
{
public:
	CBatchOperDlg(LPCTSTR strMess, LPCTSTR strTitle, CWnd* pParent = NULL);
	~CBatchOperDlg();
	
	/**
	*  @brief    ģ̬����
	*
	*  @return   int
	*/
	int DoModal();

protected:
	
	/**
	*  @brief    ��ʼ������
	*
	*  @param    LPCTSTR strMess		��ʾ��Ϣ
	*  @param    LPCTSTR strTitle		�Ի������
	*  @param    CWnd * pParent			������
	*  @return   void
	*/
	void InitData(LPCTSTR strMess, LPCTSTR strTitle, CWnd* pParent = NULL);

private:
	CBatchOperationDlg*		_pDlg;
};

