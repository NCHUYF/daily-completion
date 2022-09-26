//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           UnityView.h
//    @author         yf
//    @data           2021/08/24  
//    @brief          unity view��������unity�Ի�����ʵ���ô�������һ��������
//
//*****************************************************

#pragma once

class CUnityView : public CView, public d3s::views::view::IViewPort
{
public:

	CUnityView(d3s::designfile::model::DesignModel *pModel, d3s::share_ptr<d3s::views::view::CViewInfo> pInfo);


	virtual ~CUnityView();


	/**
	* �����ӿ�
	* @return
	*/
	virtual bool CreateViewport(HWND parent);

	/**
	* ��ȡ����������·��
	* @return
	*/
	virtual CString GetToolbarConfig();
	
	/**
	* ���ù���������·��
	* @return
	*/
	virtual void SetToolbarConfig(CString strToolBarFile);

	/**
	* ��ȡ�߳�ID
	* @return
	*/
	virtual int GetThreadID();


	/**
	* �������٣��������ٷ����������������������߳��л�������
	* @return void
	*/
	virtual void PostNcDestroy();


	virtual void OnDraw(CDC* pDC);

	/**
	* ��ȡ��ͼ����
	* @return
	*/
	virtual CString GetViewName() override;

	/**
	* ��ȡosg���
	* @return
	*/
	virtual HWND GetHwnd() override;

	/**
	* ��ȡ��ͼ����
	* @return
	*/
	virtual CString GetViewTitle() override;

	/**
	* �����Զ������ͼ����
	* @return
	*/
	virtual void SetViewTitle(CString strViewTitle) override;
protected:
	afx_msg void OnSize(UINT nFlags, int cx, int cy);
	afx_msg void OnMouseLeave();
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()


private:
	CUnityViewPort *_pUnityDlg; // unity�Ի���
	CString _strTitle; // ��������
	bool _bMouseTracking; // �Ƿ������
	CString _strToolConfigBarFile; // ����������·��
};

