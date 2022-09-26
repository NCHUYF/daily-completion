#include "stdafx.h"
#include "MSRegDlg.h"

static std::map<CString, CMSRegDlg*> regDlgMap;	///< ���ҶԻ�������
static std::vector<CMSRegDlg*> dlgCoexistVec;	///< ������Ի�������
static CMSRegDlg* pMutexDlg = NULL;	///< ����Ի���

CMSRegDlg::CMSRegDlg(bool bIsMutex, const CString& strDlgName)
{
	RegistDialog(this, bIsMutex);

	if (!strDlgName.IsEmpty())
	{
		regDlgMap[strDlgName] = this;
	}
}

CMSRegDlg::~CMSRegDlg()
{
	UnRegistDialog(this);
	DeleteDialogInMap(this);
}

void CMSRegDlg::UpdateDialog()
{

}

void CMSRegDlg::RegistDialog(CMSRegDlg* pDlg, bool bIsMutex)
{
	// ����Ի���
	if (bIsMutex)
	{
		if (pMutexDlg != NULL)
		{
			pMutexDlg->CloseDialog();
		}

		pMutexDlg = pDlg;
		return;
	}

	// ����Ի���
	if (std::find(dlgCoexistVec.begin(), dlgCoexistVec.end(), pDlg) != dlgCoexistVec.end())
	{
		return;
	}

	dlgCoexistVec.push_back(pDlg);
}

void CMSRegDlg::UnRegistDialog(CMSRegDlg* pDlg)
{
	if (pDlg == pMutexDlg)
	{
		pMutexDlg = NULL;
		return;
	}

	// ɾ������Ի���
	std::vector<CMSRegDlg*>::iterator vecIter = dlgCoexistVec.begin();
	std::vector<CMSRegDlg*>::iterator endIter = dlgCoexistVec.end();

	for (; vecIter != endIter; ++vecIter)
	{
		if (*vecIter != pDlg)
		{
			continue;
		}

		dlgCoexistVec.erase(vecIter);

		break;
	}
}

void CMSRegDlg::DeleteDialogInMap(CMSRegDlg* pDlg)
{
	if (pDlg == nullptr)
	{
		return;
	}
	std::map<CString, CMSRegDlg*>::iterator iter = regDlgMap.begin();
	for ( ; iter != regDlgMap.end(); ++iter)
	{
		if (iter->second != pDlg)
		{
			continue;
		}
		regDlgMap.erase(iter->first);
	}
}

/*-----------------------------------���¹�������---------------------------------------------*/

void CDlgMgrTool::UpdateDialog()
{
	if (pMutexDlg != NULL)
	{
		pMutexDlg->UpdateDialog();
	}

	size_t nCount = dlgCoexistVec.size();
	for (size_t i = 0; i < nCount; ++i)
	{
		CMSRegDlg *pCurMDlg = dlgCoexistVec.at(i);
		CDialog *pCurDlg = dynamic_cast<CDialog*>(pCurMDlg);
		if (pCurDlg == NULL)
		{
			continue;
		}

		pCurMDlg->UpdateDialog();
	}
}

void CDlgMgrTool::CloseDialog()
{
	if (pMutexDlg != NULL)
	{
		pMutexDlg->CloseDialog();
		pMutexDlg = NULL;
	}

	// ��������
	for (size_t i = 0; i < dlgCoexistVec.size(); ++i)
	{
		CMSRegDlg *pCurMDlg = dlgCoexistVec.at(i);
		CDialog *pCurDlg = dynamic_cast<CDialog*>(pCurMDlg);
		if (pCurDlg == NULL)
		{
			continue;
		}

		pCurMDlg->CloseDialog();
	}

	dlgCoexistVec.clear();
}

CMSRegDlg* CDlgMgrTool::GetDlgPter(const CString& strName)
{
	if (regDlgMap.count(strName) > 0)
	{
		return regDlgMap[strName];
	}
	
	return NULL;
}
