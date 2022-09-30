#pragma once
#include "../Base/DCController.h"

class Task;
namespace ControlUI
{
	class CTaskAdapter : public IListDataSource, public DCController
	{
	public:
		/**
		*  @brief    ���캯��
		*
		*  @param    pRoot ���ڵ�ָ��
		*  @param    _bFindMode �Ƿ�Ϊ����ģʽ
		*  @return
		*/
		CTaskAdapter(std::shared_ptr<Task> task, bool bRoot = true)
		{
			_bRoot = bRoot;
			_task = task;
		}
	public:

		/**
		*  @brief    ��ȡ������Ŀ
		*
		*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
		*  @return   size_t ����������Ŀ
		*/
		size_t GetCount(CTreeListConfig* pConfig);

		/**
		*  @brief    Ψһ��ʶ
		*/
		virtual size_t GetKey();

		/**
		*  @brief    ��ȡָ����������
		*
		*  @param    size_t nIndex ��������
		*  @param    bool bShowItem ����true��������ݽ���ʾ�ڿؼ��ϣ����ڹ��˲���Ҫ��ʾ���м�ڵ㣩
		*  @param    HITEMDATA hItemData �б�������(ֻ�е�һ�����ò�����)
		*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
		*  @return   IListDataSource*& pListDataSource ��ǰ��ȡ��������Դ
		*/
		virtual IListDataSource* GetItem(size_t nIndex, bool& bShowItem,
			HITEMDATA hItemData, CTreeListConfig* pConfig);

		/**
		*  @brief    ��ȡ��Ԫ��������Ϣ
		*
		*  @param    size_t nCol ��Ԫ��������
		*  @param    size_t nRow ��Ԫ��������
		*  @param    const HCOLUMNDATA hColumnData ��ͷ��Ϣ
		*  @param    HCELLDATA hCellData ���ص�Ԫ��������
		*  @param    HEDITCONFIG hEditConfig ���ر༭��������
		*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
		*/
		virtual void GetCellData(size_t nCol, size_t nRow, const HCOLUMNDATA hColumnData,
			HCELLINFO hCellData, HEDITCONFIG hEditConfig, CTreeListConfig* pConfig);

		/**
		*  @brief    ��ȡ��Ԫ���ı�����
		*
		*  @param    size_t nCol ��Ԫ��������
		*  @param    size_t nRow ��Ԫ��������
		*  @param    const HEDITCONFIG hEditConfig �༭��������
		*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
		*  @return   CString ���ص�Ԫ���ı�����
		*/
		virtual CString GetCellText(size_t nCol, size_t nRow, const HEDITCONFIG hEditConfig,
			CTreeListConfig* pConfig);

		/**
		*  @brief    ���õ�Ԫ���ı�����
		*
		*  @param    size_t nCol ��Ԫ��������
		*  @param    size_t nRow ��Ԫ��������
		*  @param    const HEDITCONFIG hEditConfig �༭��������
		*  @param    const CString& strNewValueg ��ǰ���õ�ֵ
		*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
		*  @return   bool ����true���޸ĳɹ�
		*/
		virtual bool SetCellText(size_t nCol, size_t nRow, const HEDITCONFIG hEditConfig,
			const CString& strNewValue, CTreeListConfig* pConfig);
	private:
		bool _bRoot; // �Ƿ��Ǹ��ڵ�
		std::shared_ptr<Task> _task;
	};
}
