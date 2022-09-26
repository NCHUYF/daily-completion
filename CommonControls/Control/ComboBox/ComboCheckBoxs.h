#pragma once
#include "ComboAnyOne.h"
#include <vector>

// �������б�
class COMMONCONTROLS_API CCheckBoxList : public CTreeCtrl, public IPopupCtrl
{
public:
	CCheckBoxList();
	~CCheckBoxList();

	// ������������
	int AddItem(LPCTSTR szItem, DWORD_PTR extraData);

	// ��������Ϣ
	HTREEITEM GetItemAt(int nIndex);

	// ɾ������Ϣ
	void DeleteItem(int nIndex);

	// ɾ��������
	void DeleteAllItem();

	// ����ѡ��״̬
	BOOL SetCheck(HTREEITEM hItem, BOOL fCheck = TRUE);

protected:

	// ����������
	int GetIndex(HTREEITEM hItem);

	// ����֪ͨ��Ϣ
	void SendNotify(UINT code, HTREEITEM item);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMDBClickTree(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	// ���ش���
	virtual CWnd* GetWnd(CWnd *pOwner);

	// ������Ҫ��Combo����ʾ������
	virtual CString GetCtrlTextForShow();

	// ֪ͨ�ؼ���ʾ
	virtual void OnPreShowCtrl(LPCTSTR curComboTxt);

	// ���ؿؼ�����ʾ�������ĳߴ�
	virtual CSize GetBestSize();

protected:
	std::vector<HTREEITEM> m_arrTreeItems;	// ���е�����
	std::vector<HTREEITEM> m_arrSelItems;	// ���е�ѡ������
};

class COMMONCONTROLS_API CComboCheckBoxs : public CComboAnyOne
{
public:
	CComboCheckBoxs();
	~CComboCheckBoxs();

	// ������������
	int AddItem(LPCTSTR szItem, DWORD_PTR extraData = NULL);

	// ���������
	void DeleteAllItem();

	// ����ĳһ���Ƿ�ѡ��
	void SetItemSelectStatus(int nIndex, BOOL bSelected);

	// ����ָ����ѡ��״̬
	BOOL GetItemStatus(int nIndex);

	// ������������
	void GetSelectionIndexs(std::vector<int> &indexBuffer);

	// ��������ѡ������
	void GetSelectionExtraDatas(std::vector<DWORD_PTR> &indexBuffer);

	void GetSeletionItemTexts(std::vector<CString> &selItemTexts);

	void SetSelectionItemText(CString strSelItemTexts);
};

