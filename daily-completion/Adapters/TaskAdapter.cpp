#include "pch.h"
#include "TaskAdapter.h"
#include "../System/TaskSystem.h"
#include "../Model/Task.h"

using namespace ControlUI;

size_t CTaskAdapter::GetCount(CTreeListConfig * pConfig)
{
	if (_bRoot)
	{
		return GetSystem<CTaskSystem>()->GetTaskCnt();
	}
	return 0;
}

size_t CTaskAdapter::GetKey()
{
	return (size_t)_task.get();
}

IListDataSource * CTaskAdapter::GetItem(size_t nIndex, bool & bShowItem, HITEMDATA hItemData, CTreeListConfig * pConfig)
{
	if (!_bRoot)
	{
		return NULL;
	}
	
	auto taskSys = GetSystem<CTaskSystem>();
	for (int i = 0; i < taskSys->GetTaskCnt(); ++i)
	{
		auto task = taskSys->GetTask(i);
		CTaskAdapter *pChildSource = new CTaskAdapter(task, false);
		return pChildSource;
	}
	return NULL;
}

void CTaskAdapter::GetCellData(size_t nCol, size_t nRow, const HCOLUMNDATA hColumnData, HCELLINFO hCellData, HEDITCONFIG hEditConfig, CTreeListConfig * pConfig)
{
	// ֱ�Ӹ��Ʊ�ͷ����
	hEditConfig->CopyFrom(hColumnData->editConfig);
}

CString CTaskAdapter::GetCellText(size_t nCol, size_t nRow, const HEDITCONFIG hEditConfig, CTreeListConfig * pConfig)
{
	if (_bRoot)return L"";
	CString strField = hEditConfig->field;
	if (strField == L"���")
	{
		return L"";
	}
	else if (strField == L"��������")
	{
		return _task->strName; 
	}
	return L"";
}

bool CTaskAdapter::SetCellText(size_t nCol, size_t nRow, const HEDITCONFIG hEditConfig, const CString & strNewValue, CTreeListConfig * pConfig)
{
	CString strField = hEditConfig->field;
	if (strField == L"��������")
	{
		_task->strName = strNewValue;
	}
	return true;
}

