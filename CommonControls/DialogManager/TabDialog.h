#pragma once

enum DialogSetting_PosType { byNameFrame = 1, centerWnd };
DECLARE_ENUM_CONVERSION(DialogSetting_PosType)

// �Ի�������
struct DialogSetting
{
	CString strCaptionName;		// ������
	DialogSetting_PosType posType;
};

class CTabDialog : public CDialog
{
	enum {IDD = IDD_TAB_DIALOG};
public:
	CTabDialog(TabPageContextArray& arrSubPage, DialogSetting dlgSetting);
	~CTabDialog();

protected:
	DECLARE_MESSAGE_MAP()

	// ��ʼ���Ի���ʱ������ҳ��
	afx_msg BOOL OnInitDialog();

	// �������ڴ�Сʱ������tab�ؼ���С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	// ��Ӧtabҳ�л��¼���֪ͨ��ҳ���뿪�ͽ���
	afx_msg void OnTabSelChange();

	// ����ȷ�������ⰴ�س����ͽ�����
	virtual void OnOK();

	virtual void OnCancel();

protected:
	CEditableTabCtrl _tabCtrl;				// tab�ؼ�
	TabPageContextArray &_arrSubPages;		// ����ҳ�����
	ITabPageContext *_pLastSelPage;			// ��һ��ѡ�е�ҳ��
	DialogSetting	_dlgSetting;			// ��������
};

