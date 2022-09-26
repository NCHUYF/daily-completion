/*---------------------------------------------------------------------
*�ļ����ƣ�TimeLineCtrl.h
*����������ʱ����ؼ�
*������ʶ��������2021.9.23.
*
*�޸ı�ʶ��
*�޸�������
----------------------------------------------------------------------*/
#pragma once
#include "ITimeLineCtrlDataSource.h"

class COMMONCONTROLS_API CTimeLineCtrl :public CWnd
{
public:
	CTimeLineCtrl(void);
	virtual ~CTimeLineCtrl(void);

protected:
	DECLARE_DYNAMIC(CTimeLineCtrl)
	DECLARE_MESSAGE_MAP()

public:
	/*
	* �������ܣ�����ʱ����ؼ�
	* ���������const RECT& rect �ؼ�����
	*			CWnd* pParentWnd ������
	*			UINT nID(0xfff0) �ؼ�ID
	*			DWORD dwStyle(WS_BORDER | WS_CHILD | WS_VISIBLE) �ؼ����
	* ���������void
	* ����ֵ  ��bool �Ƿ񴴽��ɹ�
	*/
	bool Create(const CRect& rect, CWnd* pParentWnd, UINT nID = NULL,
		DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE);

	/*
	* �������ܣ������б������ļ�
	* ���������const CStirng & strCfg �����ļ�·��
	*			const CString&  strCfgName ͼ��������(һ�������ļ����ڶ������,Ϊ�������һ��)
	* ���������void
	* ����ֵ  ��bool �ɹ�����true
	*/
	bool LoadConfig(const CString& strCfg, const CString& strLayerCfgName = L"");

	/*
	* �������ܣ���������Դ
	* ���������ITimeLineCtrlDataSource *pDataSource ����Դָ��
	*			bool bDelDataSource �Ƿ�ɾ������Դָ��
	* ���������void
	* ����ֵ  ��void
	*/
	void SetDataSource(ITimeLineCtrlDataSource *pDataSource, bool bDelDataSource);

	/*
	* �������ܣ����¿ؼ�
	* ���������bool bDataChange ��Ϊtrue������������ݣ�����ֱˢ�½���
	* ���������void
	* ����ֵ  ��void
	*/
	void UpdateCtrl(bool bDataChange = false);

	/*
	* �������ܣ������¼�֪ͨ������
	* ���������HWND hNotifyWnd ֪ͨ���ھ��
	* ���������void
	* ����ֵ  ��void
	*/
	void SetNofityWnd(HWND hNotifyWnd);

	/*
	* �������ܣ��������ͼ��������Ϊ��
	* ���������int nColumnIndex(0) ���ͼ����������
	* ���������void
	* ����ֵ  ��void
	*/
	void SetTreeColumn(int nColumnIndex = 0);

	/*
	* �������ܣ����������Ӧ�жϽӿ�
	* ���������IMouseResponseJudgment *pMouseResponseJudgement �����Ӧ�жϽӿ�
	* ���������void
	* ����ֵ  ��void
	*/
	void SetMouseResponseJudgment(IMouseResponseJudgment *pMouseResponseJudgement);

	/*
	* �������ܣ�����ʱ��֡�̶ȵĳ���
	* ���������int nTimeFrameLength ʱ��֡�̶ȵĳ���
	* ���������void
	* ����ֵ  ��void
	*/
	void SetTimeFrameLength(int nTimeFrameLength);

	/*
	* �������ܣ���ȡʱ��֡�̶ȵĳ���
	* ���������void 
	* ���������void
	* ����ֵ  ��int ʱ��֡�̶ȵĳ���
	*/
	int GetTimeFrameLength(void);

	/*
	* �������ܣ���ȡ����Դ�б�
	* ���������void
	* ���������DataSourceArray &datasourceArray ����Դ�б�
	* ����ֵ  ��void
	*/
	void GetDataSourceArray(DataSourceArray &datasourceArray);

	/*
	* �������ܣ���ȡ����Դ��ʶ��ؼ�����(��¼״̬����)
	* ���������void
	* ���������void
	* ����ֵ  ��ListDataSource ����Դ��ʶ��ؼ�����(��¼״̬����)
	*/
	ListDataSource GetListDataSource(void);

	/**
	*  @brief    ��ȡѡ�еĵ�������Դ����
	*
	*  @return   IListDataSource* ѡ�е�����Դ����δѡ���򷵻�NULL
	*/
	IListDataSource* GetSelectItem();

	//���������������
	void SetLayerAreaFocusItem(int nIndex);

	//��ȡ���������������
	int GetLayerAreaSelectedIndex();
private:
	/*
	* �������ܣ�ע��ؼ���
	* ���������void
	* ���������void
	* ����ֵ  ��bool �Ƿ�ɹ�ע��
	*/
	virtual bool RegisterTimeLineCtrl(void);

protected:
	//���ڳߴ��С�仯��Ӧ�¼�
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	CTimeLineSplitCtrl					_verSplit;					// �ָ����ؼ�
	CTimeLineTreeListCtrl				_treeLayerAreaCtrl;			// ���ͼ�����ؼ�
	CTimeFrameListCtrl					_timeFrameListCtrl;			// �Ҳ�ʱ��֡�б�ؼ�

protected:
	ListDataSource						_listDataSource;			// ����Դ��ʶ��ؼ�����(��¼״̬����)
	bool								_bDelDataSource;			// �Ƿ�ɾ������Դָ��
};