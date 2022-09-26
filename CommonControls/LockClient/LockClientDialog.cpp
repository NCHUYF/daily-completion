#include "stdafx.h"
#include "LockClientDialog.h"

/////////////////////////////////////////////////////////////////////
// �Ҳ��������ʾ��
/////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CNoFoundLienceDlg, CDialog)
	ON_STN_CLICKED(IDC_REG_LIS, OnStnClickedAddLic)
	ON_BN_CLICKED(IDC_LOCK_RETRY, OnBtnRetry)
	ON_BN_CLICKED(ID_NET_LOGIN, OnBtnNetLogin)
	ON_BN_CLICKED(IDC_CHK_LOGIN, OnCheckManualLogin)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

CNoFoundLienceDlg::CNoFoundLienceDlg(CWnd *pParent) 
	: CDialog(CNoFoundLienceDlg::IDD, pParent)
{
	_noFoundMode = eQuitLock;
}

void CNoFoundLienceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REG_LIS, _addLisLink);
	DDX_Control(pDX, IDC_CHK_LOGIN, _checkManualLogin);
}


BOOL CNoFoundLienceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString strCfg = CLockTool::GetLockCfgFile();
	CString str;
	GetPrivateProfileString(L"NetLock", L"ManualLogin", L"", str.GetBuffer(MAX_PATH), MAX_PATH, strCfg);
	str.ReleaseBuffer();

	_checkManualLogin.SetCheck(str == L"true" ? TRUE : FALSE);

	return TRUE;
}

void CNoFoundLienceDlg::OnBtnRetry()
{
	_noFoundMode = eRetryDet;
	OnCancel();
}

void CNoFoundLienceDlg::OnBtnNetLogin()
{
	_noFoundMode = eNetLogin;
	OnCancel();
}

void CNoFoundLienceDlg::OnStnClickedAddLic()
{
	_noFoundMode = eShowLic;
	OnCancel();
}

ENotFoundMode CNoFoundLienceDlg::GetNoFoundMode()
{
	return _noFoundMode;
}

void CNoFoundLienceDlg::OnCheckManualLogin()
{
	CString strCfg = CLockTool::GetLockCfgFile();
	WritePrivateProfileString(L"NetLock", L"ManualLogin", _checkManualLogin.GetCheck() ? L"true" : L"false", strCfg);
}

BOOL CNoFoundLienceDlg::IsManualLoginIn()
{
	CString strCfg = CLockTool::GetLockCfgFile();
	CString str;
	GetPrivateProfileString(L"NetLock", L"ManualLogin", L"", str.GetBuffer(MAX_PATH), MAX_PATH, strCfg);
	str.ReleaseBuffer();

	return str == L"true";
}

BOOL CNoFoundLienceDlg::PreTranslateMessage(MSG* pMsg)
{
	if ((pMsg->message == WM_KEYDOWN)
		&& (pMsg->wParam == VK_ESCAPE))
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CNoFoundLienceDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	_noFoundMode = eQuitLock;
	CDialog::OnClose();
}

/////////////////////////////////////////////////////////////////////
// ������֤����Ի���
/////////////////////////////////////////////////////////////////////
CServerLicenceMgrDlg::CServerLicenceMgrDlg(CWnd *pParent) :
CDialog(CServerLicenceMgrDlg::IDD, pParent)
{
}

CServerLicenceMgrDlg::~CServerLicenceMgrDlg()
{
}

/////////////////////////////////////////////////////////////////////
// ������֤����
/////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CServerLicenceMgrDlg, CDialog)
	ON_BN_CLICKED(IDC_ZCRJ, OnAddLience)
	ON_BN_CLICKED(IDC_AUTOENROL, OnAutoAddLience)
	ON_CBN_SELCHANGE(IDC_LOCKLIST, OnSelLockItem)
END_MESSAGE_MAP()

BOOL CServerLicenceMgrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow(GetParent());

	_licListCtrl.Attach(GetDlgItem(IDC_LIC_LIST)->GetSafeHwnd());
	_licListCtrl.InsertColumn(0, _T("���"), LVCFMT_LEFT, 40);
	_licListCtrl.InsertColumn(1, _T("��ҵ����"), LVCFMT_LEFT, 180);
	_licListCtrl.InsertColumn(2, _T("�������"), LVCFMT_LEFT, 210);
	_licListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	IBooLockClientServicePtr hostlock = CLicenceAccess::GetNatServer();

	if (NULL == hostlock)
		return FALSE;

	CComboBox lockList;
	lockList.Attach(GetDlgItem(IDC_LOCKLIST)->GetSafeHwnd());
	for (int i = 0; i < hostlock->GetDeviceCount(); i++)
	{
		IBooReadLockInfoPtr senseitem = hostlock->ReadDeviceInfo(i);
		if (senseitem->GetLockType() == StandardLock)
		{
			lockList.AddString((LPCTSTR)senseitem->GetLockLabel());
		}
	}

	if (lockList.GetCount())
	{
		lockList.SetCurSel(0);
		OnSelLockItem();
	}
	lockList.Detach();

	return TRUE;
}

void CServerLicenceMgrDlg::OnAutoAddLience()
{
	return;
}

void CServerLicenceMgrDlg::OnAddLience()
{
	CString strSelLockLabel;

	CComboBox lockList;
	lockList.Attach(GetDlgItem(IDC_LOCKLIST)->GetSafeHwnd());
	

	int nSel = lockList.GetCurSel();
	if (LB_ERR == nSel)
	{
		lockList.Detach();
		return;
	}

	lockList.GetLBText(nSel, strSelLockLabel);
	lockList.Detach();

	if (!AddLicence(strSelLockLabel))
		return;

	// ���¼���
	OnSelLockItem();
}

bool CServerLicenceMgrDlg::AddLicence(CString strSelLockLabel)
{
	IBooLockClientServicePtr hostlock = CLicenceAccess::GetNatServer();
	if (NULL == hostlock)
		return false;

	IBooReadLockInfoPtr lockInfo;
	if (!FindLockByLabel(hostlock, strSelLockLabel, lockInfo))
	{
		MessageBox(_T("ѡ�������������ڡ�"), L"����", MB_ICONINFORMATION);
		return false;
	}

	CAddLienceDlg dlg(this);
	while (true)
	{
		dlg._strCorpname = GetDefaultCorpName();
		if (dlg.DoModal() != IDOK)
			break;

		SupportLicMap licMap = CLicenceAccess::GetInstance()->GetAppSupperLicenceMap();

		size_t i = 0; 
		for (SupportLicMap::iterator iter = licMap.begin(); iter != licMap.end(); ++iter, ++i)
		{
			CString strLic = iter->second;

			try
			{
				CWaitCursor wait;
				hostlock->RegisterLicence((LPCTSTR)lockInfo->GetDeviceId(),
					(LPCTSTR)dlg._strCorpname, (LPCTSTR)(strLic.GetString()), (LPCTSTR)dlg._strLicence);

				break;
			}
			catch (_com_error& e)
			{
				// ����ע�����
				e;
			}
			catch (...)
			{
				MessageBox(_T("�������֤ʧ�ܣ����������֤���Ƴ���ƥ�䡣"), L"����", MB_ICONINFORMATION);
				break;
			}
		}

		if (i < licMap.size())
		{
			break;
		}
		else
		{
			MessageBox(_T("��������֤��Ч�����������롣"), L"����", MB_ICONINFORMATION);
		}
	}

	return true;
}

void CServerLicenceMgrDlg::OnOK()
{
	CDialog::OnOK();
}

void CServerLicenceMgrDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CServerLicenceMgrDlg::OnSelLockItem()
{
	IBooLockClientServicePtr hostlock = CLicenceAccess::GetNatServer();
	if (NULL == hostlock)
		return;

	CComboBox lockList;
	lockList.Attach(GetDlgItem(IDC_LOCKLIST)->GetSafeHwnd());

	CString strSelLockLabel;
	if (lockList.GetCurSel() != LB_ERR)
		lockList.GetLBText(lockList.GetCurSel(), strSelLockLabel);
	lockList.Detach();

	IBooReadLockInfoPtr lockInfo;
	if (!FindLockByLabel(hostlock, (LPCTSTR)strSelLockLabel, lockInfo))
		return;

	_licListCtrl.DeleteAllItems();

	int licCount = hostlock->GetLicenceCount((LPCTSTR)lockInfo->GetDeviceId());
	for (int j = 0; j < licCount; j++)
	{
		IBooReadLicInfoPtr lic = hostlock->ReadLicenceInfo(lockInfo->GetDeviceId(), j);

		CString strIndex;
		strIndex.Format(L"%d", j + 1);
		int nItem = _licListCtrl.InsertItem(j, strIndex);

		_licListCtrl.SetItemText(nItem, 1, (LPCTSTR)lockInfo->GetLockCorp());
		_licListCtrl.SetItemText(nItem, 2, (LPCTSTR)lic->GetName());
	}
}

CString CServerLicenceMgrDlg::GetDefaultCorpName()
{
	IBooLockClientServicePtr hostlock = CLicenceAccess::GetNatServer();
	if (!!hostlock && hostlock->IsConnection())
	{
		if (hostlock->GetDeviceCount() > 0)
		{
			IBooReadLockInfoPtr lockInfo = hostlock->ReadDeviceInfo(0);
			return(LPCTSTR)lockInfo->GetLockCorp();
		}
	}

	return L"";
}

bool CServerLicenceMgrDlg::FindLockByLabel(IBooLockClientServicePtr& service,
	LPCTSTR label, IBooReadLockInfoPtr& lock)
{
	int lockCount = service->GetDeviceCount();
	for (int i = 0; i < lockCount; i++)
	{
		IBooReadLockInfoPtr lockInfo = service->ReadDeviceInfo(i);
		if (!_tcscmp((LPCTSTR)lockInfo->GetLockLabel(), label))
		{
			lock = lockInfo;
			return true;
		}
	}

	return false;
}


/////////////////////////////////////////////////////////////////////
// ���֤�༭��
/////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CLicenceEdit, CEdit)
	ON_MESSAGE(WM_PASTE, OnPaste)
END_MESSAGE_MAP()

CLicenceEdit::CLicenceEdit() : CEdit()
{
}

CLicenceEdit::~CLicenceEdit()
{
}

LRESULT CLicenceEdit::OnPaste(WPARAM wParam, LPARAM lParam)
{
	// ��ϵͳ���а��л�ȡ��ȷ��ʽ����
	CString strLicence;
	if (!GetDataFromClipboard(strLicence))
	{
		return 0;
	}

	// ��������ճ��������Ϣ��������
	GetParent()->SendMessage(WM_COMPLETE_PASTE, NULL, (LPARAM)(LPCTSTR)strLicence);

	return 0;
}

bool CLicenceEdit::GetDataFromClipboard(CString& strResult)
{
	HANDLE hClip = NULL;
	if (OpenClipboard())
	{
		if (IsClipboardFormatAvailable(CF_TEXT))
		{
			// ��ȡ���а������
			hClip = GetClipboardData(CF_OEMTEXT);
			if (hClip != NULL)
			{
				strResult = (LPSTR)GlobalLock(hClip);

				// �رռ��а�
				GlobalUnlock(hClip);
				CloseClipboard();

				return IsCorrectFormat(strResult);
			}
		}
	}

	// �رռ��а�
	GlobalUnlock(hClip);
	CloseClipboard();

	return false;
}

/////////////////////////////////////////////////////////////////////
// ������֤��
/////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAddLienceDlg, CDialog)
	ON_MESSAGE(WM_COMPLETE_PASTE, OnCompletePaste)
	ON_EN_CHANGE(IDC_EDIT_LIENCENUM1, OnEditLienceChange1)
	ON_EN_CHANGE(IDC_EDIT_LIENCENUM2, OnEditLienceChange2)
	ON_EN_CHANGE(IDC_EDIT_LIENCENUM3, OnEditLienceChange3)
	ON_EN_CHANGE(IDC_EDIT_LIENCENUM4, OnEditLienceChange4)
END_MESSAGE_MAP()

CAddLienceDlg::CAddLienceDlg(CWnd *pWnd) : CDialog(CAddLienceDlg::IDD, pWnd)
{
}

BOOL CAddLienceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow(GetParent());

	CEdit edit;
	SetDlgItemText(IDC_CORPNAME, _strCorpname);

	// ��������ճ���༭��
	_licenceEdit.SubclassWindow(GetDlgItem(IDC_EDIT_LIENCENUM1)->GetSafeHwnd());

	return TRUE;
}

void CAddLienceDlg::OnOK()
{
	GetDlgItemText(IDC_CORPNAME, _strCorpname);

	CString num1, num2, num3, num4;
	GetDlgItemText(IDC_EDIT_LIENCENUM1, num1);
	GetDlgItemText(IDC_EDIT_LIENCENUM2, num2);
	GetDlgItemText(IDC_EDIT_LIENCENUM3, num3);
	GetDlgItemText(IDC_EDIT_LIENCENUM4, num4);

	_strLicence = num1 + _T("-") + num2 + _T("-") + num3 + _T("-") + num4;

	CDialog::OnOK();
}

void CAddLienceDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CAddLienceDlg::OnEditLienceChange1()
{
	CString strText;
	GetDlgItemText(IDC_EDIT_LIENCENUM1, strText);

	// ȥ�������ַ�����ǰ��ո�
	strText.Trim();
	if (strText.GetLength() == 5)
		NextDlgCtrl();
}

void CAddLienceDlg::OnEditLienceChange2()
{
	CString strText;
	GetDlgItemText(IDC_EDIT_LIENCENUM2, strText);

	// ȥ�������ַ�����ǰ��ո�
	strText.Trim();
	if (strText.GetLength() == 5)
		NextDlgCtrl();
}

void CAddLienceDlg::OnEditLienceChange3()
{
	CString strText;
	GetDlgItemText(IDC_EDIT_LIENCENUM3, strText);

	// ȥ�������ַ�����ǰ��ո�
	strText.Trim();
	if (strText.GetLength() == 5)
		NextDlgCtrl();
}

void CAddLienceDlg::OnEditLienceChange4()
{
	CString strText;
	GetDlgItemText(IDC_EDIT_LIENCENUM4, strText);

	// ȥ�������ַ�����ǰ��ո�
	strText.Trim();
	if (strText.GetLength() == 5)
		NextDlgCtrl();
}

LRESULT CAddLienceDlg::OnCompletePaste(WPARAM wParam, LPARAM lParam)
{
	CString strLicence = (LPCTSTR)lParam;

	CAtlArray<CString> licenceNumbers;
	CStringToolkit::SplitString(strLicence, licenceNumbers, _T("-"));
	size_t nNumCount = licenceNumbers.GetCount();

	if (nNumCount >= 1)
		SetDlgItemText(IDC_EDIT_LIENCENUM1, licenceNumbers[0]);

	if (nNumCount >= 2)
		SetDlgItemText(IDC_EDIT_LIENCENUM2, licenceNumbers[1]);

	if (nNumCount >= 3)
		SetDlgItemText(IDC_EDIT_LIENCENUM3, licenceNumbers[2]);

	if (nNumCount >= 4)
		SetDlgItemText(IDC_EDIT_LIENCENUM4, licenceNumbers[3]);

	return 0;
}

/////////////////////////////////////////////////////////////////////
// ��������½
/////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CNetLoginDlg, CDialog)

END_MESSAGE_MAP();

CNetLoginDlg::CNetLoginDlg(CLicenceAccess *pLinc, CWnd *pParent /*= NULL*/) : CDialog(CNetLoginDlg::IDD, pParent), _pLinc(pLinc), _eSucc(FALSE)
{

}

void CNetLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_NETADDR, _netAddrEdit);
	DDX_Control(pDX, IDC_EDT_ADMIN, _adminEdit);
	DDX_Control(pDX, IDC_EDT_PASS, _passEdit);
}

BOOL CNetLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow(GetParent());

	//��ȡini�ļ��ڶ�Ӧ�ֶ���Ϣ������Ի���
	CString strAddr, strAdmin, strPass;
	GetNetLockInfo(strAddr, strAdmin, strPass);
	_netAddrEdit.SetWindowText(strAddr);
	_adminEdit.SetWindowText(strAdmin);
	_passEdit.SetWindowText(strPass);

	return TRUE;
}

BOOL CNetLoginDlg::SetNetLockInfo(const CString& strServer, const CString& strAccount, const CString& strPassword)
{
	CString strCfg = CLockTool::GetLockCfgFile();
	WritePrivateProfileString(L"NetLock", L"Server", strServer, strCfg);
	WritePrivateProfileString(L"NetLock", L"Account", strAccount, strCfg);
	WritePrivateProfileString(L"NetLock", L"Password", strPassword, strCfg);
	
	return TRUE;
}

void CNetLoginDlg::OnOK()
{
	//�����������ݵ�ini�ļ�
	CString strServer, strAccount, strPassword;
	_netAddrEdit.GetWindowText(strServer);
	_adminEdit.GetWindowText(strAccount);
	_passEdit.GetWindowText(strPassword);
	SetNetLockInfo(strServer, strAccount, strPassword);

	// �����¼�����м��
	if (!(_pLinc->AppNetLogin()))
	{
		::MessageBox(::GetActiveWindow(), _pLinc->GetLastError(), L"����", MB_OK | MB_ICONINFORMATION);
		return;
	}

	_eSucc = TRUE;
	EndDialog(IDCANCEL);
}

void CNetLoginDlg::OnCancel()
{
	EndDialog(IDCANCEL);
}

BOOL CNetLoginDlg::LoginSucceed()
{
	return _eSucc;
}

