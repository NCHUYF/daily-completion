//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           TreeListCtrl.H
//    @author         KG
//    @date           2015/3/10 11:50
//    @brief		  �����б�ؼ�
//*****************************************************

#pragma once

#include <map>
#include <vector>
#include <list>
#include "..\GdiTools.h"
#include "TreeListCfg.h"
#include "Editor\ListEdit.h"
#include "Editor\ListComboBox.h"
#include "Editor\ListAngleEdit.h"
#include "Editor\ListDataTime.h"
#include "Editor\ListTreeComboBox.h"
#include "Editor\AutoSearchCombo.h"
#include "TitleTip.h"
#include "IEventHandle.h"

namespace ControlUI
{
	/**
	*  @class    �б�����Դ
	*
	*  @brief
	*/
	class CONTROL_UI IListDataSource
	{
		friend class CTreeListCtrl;
	public:
		virtual ~IListDataSource() {}

	public:
		/**
		*  @brief    ��ȡ������Ŀ
		*
		*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
		*  @return   size_t ����������Ŀ
		*/
		virtual size_t GetCount(CTreeListConfig* pConfig) = 0;

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
			HITEMDATA hItemData, CTreeListConfig* pConfig) = 0;

		/**
		*  @brief    ��ȡ��Ԫ��������Ϣ
		*			 ֻ�е�editConfig.comboDataFile��Ϊ��ʱ��
		*			 ����Ҫ���editConfig.comboList��editConfig.comboDataFileֵ
		*			 ������߿ؼ����ܡ�
		*
		*  @param    size_t nCol ��Ԫ��������
		*  @param    size_t nRow ��Ԫ��������
		*  @param    const HCOLUMNDATA hColumnData ��ͷ��Ϣ
		*  @param    HCELLDATA hCellData ���ص�Ԫ��������
		*  @param    HEDITCONFIG hEditConfig ���ر༭��������
		*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
		*/
		virtual void GetCellData(size_t nCol, size_t nRow,
			const HCOLUMNDATA hColumnData, HCELLINFO hCellData, HEDITCONFIG hEditConfig, CTreeListConfig* pConfig) = 0;

		/**
		*  @brief    ��ȡ��Ԫ���ı�����
		*
		*  @param    size_t nCol ��Ԫ��������
		*  @param    size_t nRow ��Ԫ��������
		*  @param    const HEDITCONFIG hEditConfig �༭��������
		*  @param    CTreeListConfig*& pConfig ���б�ؼ�����
		*  @return   CString ���ص�Ԫ���ı�����
		*/
		virtual CString GetCellText(size_t nCol, size_t nRow,
			const HEDITCONFIG hEditConfig, CTreeListConfig* pConfig) = 0;

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
		virtual bool SetCellText(size_t nCol, size_t nRow,
			const HEDITCONFIG hEditConfig, const CString& strNewValue, CTreeListConfig* pConfig) = 0;

	private:
		/**
		*  @brief    ��ȡ����ԴΨһ��ʶ(ֻ�ܿؼ�����)
		*
		*  @return   size_t ��������ԴΨһ��ʶ
		*/
		virtual size_t GetKey() = 0;
	};

	/**
	*  @class    �༭��������
	*
	*  @brief
	*/
	typedef struct tagEDITCONFIG
	{
		friend class CTreeListCtrl;
	public:
		tagEDITCONFIG()
		{
			image = -1;
			dotNum = 2;
			option = 0;
			isShowTips = true;
			isEditMode = false;
			bImageCenter = false;
		}

		void CopyFrom(const tagEDITCONFIG& value)
		{
			// ֱ�Ӹ��Ʊ�ͷ����
			bImageCenter = value.bImageCenter;
			image = value.image;
			dotNum = value.dotNum;
			option = value.option;
			field = value.field;
			enumerate = value.enumerate;
			eventHandle = value.eventHandle;
			isShowTips = value.isShowTips;

			// ֻ�������༭ʱ����Ҫ����ֵ���ӿ�����
			if (isEditMode)
			{
				comboList = value.comboList;
				comboDataFile = value.comboDataFile;
			}
		}

		bool			bImageCenter;	///< ͼƬ������ʾ
		CHAR			image;			///< ͼƬ����
		CHAR			dotNum;			///< С����λ��
		int				option;			///< ����ѡ��
		CString			field;			///< ��ʾ�ֶ�����
		CString			enumerate;		///< ��Ӧö��;
		CStringVector	comboList;		///< ����������
		CString			comboDataFile;	///< �����������ļ��������ڵ�XML�����ȼ�����comboList��
		bool			isEditMode;		///< �Ƿ��������������
		bool			isShowTips;		///< �Ƿ���ʾ��ʾ��Ϣ
		CString         eventHandle;	///< ��Ϣ��Ӧ��չ��
		CString			splitChar;		///< ��ѡ��ָ���
	}EDITCONFIG, *HEDITCONFIG;


	// �������б�
	typedef std::vector<HCOLUMNDATA> ColumnDataVector;

	// ��ͷ����
#define TLC_NO_SORT 0		// ������
#define TLC_ASC_SORT 1		// ����
#define TLC_DSC_SORT -1		// ����

/**
*  @class    �����ݽṹ
*
*  @brief
*/
	typedef struct CONTROL_UI tagCOLUMNDATA
	{
		friend class CTreeListCtrl;

	public:
		tagCOLUMNDATA::tagCOLUMNDATA()
		{
			width = 20;
			image = -1;
			format = DT_LEFT;
			fixed = false;
			textColor = GetSysColor(COLOR_WINDOWTEXT);
			colRect.SetRectEmpty();
			hParent = NULL;
			sortType = TLC_NO_SORT;
		}

		~tagCOLUMNDATA()
		{
		}

		void SetWidth(SHORT inWidth)
		{
			SHORT nDifWidth = (inWidth - width);

			width = inWidth;

			if (hParent)
				hParent->AdjustParentWidth();

			AdjustChildWidth(nDifWidth);
		}

		SHORT GetWidth()
		{
			return width;
		}

	private:
		void AdjustParentWidth()
		{
			width = 0;

			// ȷ��������ͷ��СΪ����ͷ��С֮��
			size_t nChildSize = childColumn.size();
			for (size_t i = 0; i < nChildSize; ++i)
			{
				width += childColumn[i]->GetWidth();
			}

			if (hParent)
			{
				hParent->AdjustParentWidth();
			}
		}

		void AdjustChildWidth(SHORT nDifWidth)
		{
			size_t nChildSize = childColumn.size();
			if (0 == nChildSize)
				return;

			childColumn[nChildSize - 1]->width += nDifWidth;
			childColumn[nChildSize - 1]->AdjustChildWidth(nDifWidth);
		}

		bool IsLeafCol()
		{
			return (0 == childColumn.size());
		}

	public:
		bool fixed; ///< �Ƿ�̶����
		CHAR image; ///< ͼƬ����
		USHORT format; ///< �и�ʽ 
		COLORREF textColor; ///< ������ɫ
		CString title; ///< �б���
		EDITCONFIG editConfig; ///< �༭��������
		CHAR sortType;	// ��ͷ��������

	private:
		SHORT width; // �п�
		CRect colRect; ///< ����������
		HCOLUMNDATA hParent; // ����ͷ
		ColumnDataVector childColumn; // �ӱ�ͷ����
	}COLUMNDATA, *HCOLUMNDATA;

	/**
	*  @class    ��Ԫ�����ݽṹ
	*
	*  @brief
	*/
	typedef struct tagCELLDINFO
	{
		friend class CTreeListCtrl;
	public:
		tagCELLDINFO()
		{
			readonly = false;
			wpHeight = 0;
			backColor = GetSysColor(COLOR_WINDOW);
			textColor = GetSysColor(COLOR_WINDOWTEXT);
		}

		~tagCELLDINFO()
		{
		}

	public:
		int wpHeight;		///< �����ı���ʾ����߶�	
		bool readonly;		///< �Ƿ�ֻ��
		COLORREF backColor; ///< ����ɫ
		COLORREF textColor; ///< �ı���ɫ

	}CELLINFO, *HCELLINFO;

	/**
	*  @class    ��Ԫ����������
	*
	*  @brief
	*/
	typedef struct tagCELLCONFIG
	{
		friend class CTreeListCtrl;
	public:
		tagCELLCONFIG()
		{
		}

	public:
		CString cellText; ///< ��Ԫ���ı�
		CELLINFO cellInfo; ///< ��Ԫ��Ϣ
		EDITCONFIG editConfig; ///< �༭����

	}CELLCONFIG, *HCELLCONFIG;

	typedef std::vector<CELLCONFIG> CellConfigArray;

	/**
	*  @class    �����б�֪ͨ�ṹ
	*
	*  @brief
	*/
	struct CTreeListNotify
	{
		NMHDR hdrNotify;			///< ֪ͨ��Ϣ�ṹ
		int row;					///< ������
		int col;					///< ������
		CString strOldText;			///< ԭֵ
		CString *pStrNewText;		///< ��ֵ
		HEDITCONFIG hEditConfig;	///< ��Ԫ����Ϣ
		int nClickType;				///< ������� ��� = 0���һ� = 1
	};

	/**
	*  @class    ����֪ͨ�¼�
	*
	*  @brief
	*/
	struct CColumnSortNotify
	{
		NMHDR hdrNotify;			///< ֪ͨ��Ϣ�ṹ
		HCOLUMNDATA hColData;		///< ������
		size_t nColIndex;			///< ��ͷ����
		CHAR sortType;				// ��ͷ��������
	};

	class IListDataSource;

	/**
	*  @class    �б�������
	*
	*  @brief
	*/
	typedef struct tagITEMDATA
	{
		friend class CTreeListCtrl;
	public:
		tagITEMDATA()
		{
			expand = true;

			seleced = false;
			hasChild = false;
			lastChild = false;
			treeLevel = 0;
			hParentData = NULL;
			rowRect.SetRectEmpty();
			pDataSource = NULL;
		}

		~tagITEMDATA()
		{
			DelDataSource();
		}

		/**
		*  @brief    �������Դָ��
		*
		*/
		void DelDataSource()
		{
			if (NULL != pDataSource)
			{
				delete pDataSource;
				pDataSource = NULL;
			}
		}

		/**
		*  @brief    �жϵ�ǰ�ڵ��Ƿ�����״̬
		*
		*  @return   bool ��������״̬
		*/
		bool IsCollapse()
		{
			if (!expand)
				return true;

			if (NULL == hParentData)
				return !expand;

			return hParentData->IsCollapse();
		}

		/**
		*  @brief    �жϵ�ǰ�ڵ���ָ���㼶�Ƿ�Ϊ���ڵ�
		*
		*  @return   bool �����Ƿ�Ϊ���ڵ�
		*/
		bool IsLevelLastChild(int level)
		{
			if (level <= 0)
				return lastChild;

			if (NULL == hParentData)
				return false;

			return hParentData->IsLevelLastChild(--level);
		}

		/**
		*  @brief    ��������Դ
		*
		*  @return   IListDataSource*	����Դָ��
		*/
		IListDataSource* GetDataSource()
		{
			return pDataSource;
		}

		/**
		*  @brief    �ж��Ƿ񻹴����ӽڵ�
		*
		*  @return   bool	�����Ƿ�����ӽڵ�
		*/
		bool HasChildNode()
		{
			return hasChild;
		}


	public:
		bool expand; ///< �Ƿ�չ��

	private:
		UCHAR treeLevel; ///< �ڵ����������(��һ��0,�ڶ���1)
		bool hasChild; ///< �Ƿ����ӽڵ�
		bool lastChild; ///< ��ǰ�ڵ����Ƿ�Ϊ���һ���ӽڵ�
		bool seleced; ///< �Ƿ�ѡ��
		CRect rowRect; ///< ������
		CRect expandRect;	///< չ������������;	 	
		HITEMDATA hParentData; ///< ���ڵ�
		IListDataSource* pDataSource; ///< ���ж�Ӧ������Դ
	}ITEMDATA, *HITEMDATA;

	// ��������Դ��ʶ�������ݶ�Ӧ��ϵ
	typedef std::map<size_t, HITEMDATA> MapDataSource;
	typedef MapDataSource::iterator MapDataSourceIter;

	typedef std::list<std::pair<size_t, HITEMDATA>> ListDataSource;
	typedef ListDataSource::iterator ListDataSourceIter;

	typedef std::vector<IListDataSource*>	DataSourceArray;
	typedef DataSourceArray::iterator DataSourceArrayIter;

	/**
	*  @class    �����б�ؼ���
	*
	*  @brief
	*/
	class CONTROL_UI CTreeListCtrl : public CWnd
	{
	public:
		CTreeListCtrl();
		virtual ~CTreeListCtrl();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/**
		*  @brief   ���¿ؼ���ʾ
		*
		*  @param   bool bDataChange ��Ϊtrue������������ݣ�����ֱˢ�½���
		*  @remark	��ǰ������л���������ʱ
		*			���ô˷������ڸ��½�����ʾ�������
		*/
		void UpdateList(bool bDataChange = false, bool bCancelSel = false);

		/**
		*  @brief    �����ؼ�
		*
		*  @param    const RECT & rect ��������
		*  @param    CWnd * pParentWnd ������
		*  @param    UINT nID �ؼ�ID
		*  @param    DWORD dwStyle ��ʽ
		*  @return   bool �ɹ�����TRUE
		*/
		bool Create(const RECT& rect, CWnd* pParentWnd, UINT nID = 0xfff0,
			DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE);

		/**
		*  @brief    ��������Դ
		*
		*  @param    IListDataSource * pDataSource ����Դָ��
		*  @param    bool bDelete �Ƿ�ɾ������Դָ��
		*/
		void SetDataSource(IListDataSource* pDataSource, bool bDelete);

		/**
		*  @brief    �����б������ļ�
		*
		*  @param    const CStirng & strCfg �����ļ�·��
		*  @param    const CString & strCfgName ������(һ�������ļ����ڶ������,Ϊ�������һ��)
		*  @return   bool �ɹ�����true
		*/
		bool LoadConfig(const CString& strCfg, const CString& strCfgName = L"");

		/**
		*  @brief    ���ÿؼ�ͼ��
		*
		*  @param    CImageList* pImageList �ؼ�ͼ�꼯
		*  @param    bool bAutoDel �Ƿ��Զ��ͷ�ͼ���б�
		*/
		void SetImageList(CImageList* pImageList, bool bAutoDel = true);

		/**
		*  @brief    �����¼�֪ͨ������
		*
		*  @param    CWnd * pParent	�����ھ��
		*/
		void SetNofityWnd(HWND hNotifyWnd);

		/**
		*  @brief    �����Ƿ�֧�ֶ�ѡ;
		*
		*  @param    bool bSingleSelect �Ƿ�֧�ֶ�ѡ, true:Ϊ��ѡ��false:Ϊ��ѡ
		*/
		void SetSingleSelect(bool bSingleSelect = true);

		/**
		*  @brief    ���ý�����;
		*
		*  @param    size_t nSelectIndex Ĭ��ѡ���У�����������
		*/
		void SetFocusItem(size_t nSelectIndex = 0);

		/**
		*  @brief    ���ý�����
		*
		*  @param    size_t nKey �����ý����е�����Դ
		*/
		void SetFocusItemByKey(size_t nKey);

		/**
		*  @brief    ���ý�����
		*
		*  @param    size_t nKey �����ý����е�����Դ
		*/
		void SetFocusItemByDataSource(IListDataSource* pDataSource);

		/**
		*  @brief    ��ƽ�����
		*
		*  @param    const CString & strSel	������
		*  @return   bool	�ҵ����ݲ����÷���true
		*/
		bool SetFocusItemByCString(const CString& strSel);

		/**
		*  @brief    ��ȡѡ�еĵ�������Դ����
		*
		*  @return   IListDataSource* ѡ�е�����Դ����δѡ���򷵻�NULL
		*/
		IListDataSource* GetSelectedItem();

		/**
		*  @brief    ��ȡѡ��Ķ������Դ�ڵ�;
		*
		*  @param    DataSourceArray & datasourceArray �������Դ�ڵ�;
		*/
		void GetSelectedItems(DataSourceArray &datasourceArray);

		/**
		*  @brief    ��ȡ��ǰ�ؼ���������Դ
		*
		*  @param    DataSourceArray & datasourceArray ����Դ�ڵ�;
		*/
		void GetDataSourceArray(DataSourceArray &datasourceArray);

		/**
		*  @brief    ��ȡѡ�е��е���������ֵ(����0)
		*
		*  @return   int û��ѡ�з���-1
		*/
		int GetSelectedIndex();

		/**
		*  @brief    ��ȡ��������
		*
		*  @return   ��������
		*/
		size_t GetTotalRowCount();

		/**
		*  @brief    ����ؼ�����
		*
		*/
		void DeleteAllItem();

		/**
		*  @brief    �Ƿ���ʾ����
		*
		*  @param    bool bShow trueΪ��ʾfalseΪӰ��
		*/
		void SetHasGrid(bool bShow = true);

		/**
		*  @brief    ��ȡ��ǰ�ؼ��߶�
		*
		*  @return   int	���ظ߶�ֵ
		*/
		int GetCtrlHeight();

		/**
		*  @brief    ������ͷ�߶�
		*
		*  @param   int	nHeight ��ͷ�߶�ֵ
		*/
		void SetHeadItemHeight(int nHeight);

		/**
		*  @brief    ѡ�����ؼ���һ��Ҷ�ӽڵ�
		*
		*  @param    CTreeListCtrl & ���õ����ؼ�
		*  @param    bool �۽���һ���ӽڵ���Ƿ���ʾ�ض���
		*  @return   void
		*/
		void SelectFirstLeafNode(bool bFocusOnTop = false);

		/**
		*  @brief    ȷ��ָ���������ɼ���������������������״̬��
		*
		*  @param	 int nDataRowIndex ����������
		*/
		void MakeRowVisible(int nDataRowIndex);

		/**
		*  @brief    ������ͷ�����Ƿ��Զ����У���ͷ�뵥Ԫ��
		*
		*  @param	 bool bWorldWarp �Ƿ���
		*/
		void SetColumnWordWarp(bool bWorldWarp);

		/**
		*  @brief    �����������Ƿ��Զ�����
		*
		*  @param	 bool bWorldWarp �Ƿ���
		*/
		void SetRowWordWarp(bool bWorldWarp);

		/**
		*  @brief    �����Ƿ�ȥ���ո�
		*
		*  @param    bool bTrim
		*  @return   void
		*/
		void SetTrim(bool bTrim);

		/**
		*  @brief    �����Ƿ���ѡ�����Ƿ�仯
		*
		*  @param    bool bCheck ���ѡ�����Ƿ�仯
		*  @return   void
		*/
		void SetSelectChangeCheck(bool bCheck);

		/**
		*  @brief    ������������չ��ͼ����ʽ
		*
		*  @return   void
		*/
		void SetCollapseStyle(bool bStyle = false);

	public:
		/**
		*  @brief    ��ʾ��ͷ
		*
		*  @param    bool bShow trueΪ��ʾfalseΪ����
		*/
		void ShowHeader(bool bShow = true);

		/**
		*  @brief    �Ƿ���ʾ���ṹ��
		*
		*  @param    bool bShow trueΪ��ʾfalseΪ����
		*/
		void SetHasLine(bool hasLine = true);

		/**
		*  @brief    ����������ʾΪ��;
		*
		*  @param    int nColumnIndex ��ʾΪ������(��һ���ͷ����)
		*  @param    HCOLUMNDATA hParentCol ����ͷ
		*/
		void SetTreeColumn(int nColumnIndex = 0);

		/**
		*  @brief    ���ý����б�ؼ���ͷ������;
		*
		*  @param    bool bEnable �Ƿ�����������
		*/
		void EnableColumnSort(bool bEnable);

		/**
		*  @brief    ��ȡ����Ŀ
		*
		*  @param    HCOLUMNDATA hParentCol ����ͷ
		*  @return   size_t ��������Ŀ
		*/
		size_t GetColumnCount(HCOLUMNDATA hColumnData = NULL);

		/**
		*  @brief    ��ȡָ��������
		*
		*  @param    size_t nCol ָ����
		*  @param    HCOLUMNDATA hParentCol ����ͷ
		*  @return   HCOLUMNDATA ����������
		*/
		HCOLUMNDATA GetColumn(size_t nCol, HCOLUMNDATA hColumnData = NULL);

		/**
		*  @brief    �����
		*
		*  @param    size_t nCol �����е�λ��
		*  @param    HCOLUMNDATA hParentCol ����ͷ
		*  @return   HCOLUMNDATA �����²�����
		*/
		HCOLUMNDATA InsertColumn(size_t nCol, HCOLUMNDATA hParentCol = NULL);

		/**
		*  @brief    ɾ����
		*
		*  @param    size_t nCol ɾ���е�λ��
		*  @param    HCOLUMNDATA hParentCol ����ͷ
		*
		*/
		void DeleteColumn(size_t nCol, HCOLUMNDATA hParentCol = NULL);

		/**
		*  @brief    ɾ��������ͷ
		*
		*/
		void DeleteAllColumn();

		/**
		*  @brief    ��ȡ��ͷ�������ű���
		*
		*  @return   double ����ֵ
		*/
		double GetFontScale();

		/**
		*  @brief    ȡ����ǰ�༭
		*
		*/
		void CancelEdit();

		/**
		*  @brief    �༭������ָ����
		*
		*  @param    int nCol �༭����
		*/
		void EditFocusItem(int nCol);

	public:
		/**
		*  @brief    �����п���ݿؼ���ȱ仯���Զ�����
		*
		*  @param    bool bIsAutoColumnWidth	�Զ���ʶ
		*/
		void SetAutoColumnWidth(bool bIsAutoColumnWidth = true);

		/**
		*  @brief    ����ѡ����չ��״̬
		*
		*  @param    bool bExpand	չ��״̬����
		*  @return   bool	true�����óɹ�������ʧ��
		*/
		bool SetExpandBySelectItem(bool bExpand = true);

		/**
		*  @brief    ��������Դ�ҵ��в�����չ��״̬
		*
		*  @param    size_t nKey	����Դ����KEY
		*  @param    bool bExpand	չ��״̬
		*  @param    bool bParent	�ݹ����ø��ڵ�չ��״̬
		*  @return   bool	true�����óɹ�������ʧ��
		*/
		bool SetExpandItemByKey(size_t nKey, bool bExpand = true, bool bParent = false);

	protected:
		/**
		*  @brief    �༭ǰ�߼��ж�
		*
		*  @param    int nCol �༭��
		*  @param    int nRow �༭��
		*  @param    HEDITCONFIG hEditCfg ��Ԫ����Ϣ
		*  @param    const CString& strOldCellText ��Ԫ����ı�
		*  @return   bool ���Ա༭����true�����򷵻�false
		*/
		virtual bool OnBeginEdit(int nCol, int nRow,
			HEDITCONFIG hEditCfg, const CString& strOldCellText);

		/**
		*  @brief    �༭�����߼�
		*
		*  @param    int nCol �༭��
		*  @param    int nRow �༭��
		*  @param    HEDITCONFIG hEditCfg ��Ԫ����Ϣ
		*  @param    const CString& strOldCellText ��Ԫ����ı�
		*  @param    CString& strNewCellText ��Ԫ�����ı�(���޸�)
		*  @return   bool �����༭����true�����򷵻�false
		*/
		virtual bool OnEndEdit(int nCol, int nRow,
			HEDITCONFIG hEditCfg, const CString& strOldCellText, CString& strNewCellText);

		/**
		*  @brief    ��ʾ��ִ���Ҽ��˵�����
		*
		*  @return   bool ִ�гɹ�����true�����򷵻�false
		*/
		virtual bool ShowRightMenu();

		/**
		*  @brief    ������Ϣ������
		*
		*  @param    MSG * pMsg	��Ϣ����
		*  @return   BOOL	������Ϣ
		*/
		BOOL PreTranslateMessage(MSG* pMsg);

		/**
		*  @brief    ͨ����༭��Ԫ��
		*
		*  @param    CPoint ptMs ���ͻ�����
		*  @param    bool bIsDbClk �Ƿ�Ϊ����
		*/
		void EditItemByPoint(CPoint ptMs, bool bIsDbClk = false);

		/**
		*  @brief   �༭ָ����������
		*
		*  @param   IListDataSource* pDataSource ��ǰ�༭������Դ
		*  @param   int nRow �༭��
		*  @param   int nCol �༭��
		*  @param   CRect rect ������
		*  @param   HCOLUMNDATA hColumnData ��ͷ��Ϣ
		*  @param   bool bIsDbClk �Ƿ�Ϊ����
		*/
		void EditItemByParam(IListDataSource* pDataSource,
			int nRow, int nCol, CRect rect, HCOLUMNDATA hColumnData, bool bIsDbClk);

	private:
		/**
		*  @brief    ��ʼ���ؼ�����
		*
		*/
		void InitControlData();

		/**
		*  @brief    ע��ؼ���
		*
		*  @return   bool �ɹ�����TRUE
		*/
		bool RegisterTreeList();

		/**
		*  @brief    ɾ��������ͷ
		*
		*  @param    HCOLUMNDATA hParentCol ����ͷ
		*/
		void DeleteAllColumn(HCOLUMNDATA hParentCol);

		/**
		*  @brief    ִ���϶���
		*
		*/
		void DoDragColumn();

		/**
		*  @brief    ����������
		*
		*  @param   bool bUpdateSel �Ƿ��������״̬
		*  @return   bool ����true����Ҫˢ�½���
		*/
		bool UpdateHitTest(bool bUpdateSel);

		/**
		*  @brief    ���¹�����
		*
		*  @param    int scrollMode ��Ҫ���µĹ�����
		*/
		void UpdateScrollBar(int scrollMode = SB_BOTH);

		/**
		*  @brief    �ռ�����Դ����
		*
		*/
		void CollectItemListData();

		/**
		*  @brief    �ݹ��ռ�����Դ����
		*
		*  @param    IListDataSource * pDataSource ����Դָ��
		*  @param    ListDataSource & dataSouceList ����Դ�б�
		*  @param    DataSourceMap & dataSourceMap ����Դ���ж�Ӧ��ϵ
		*  @param    HITEMDATA hParentData ���׽ڵ�ָ��
		*  @param    int nTreeLevel ����Դ�������ڵ���
		*  @param    HITEMDATA &hLastChildItem ���һ���ӽڵ�
		*  @return   bool �Ƿ����ӽڵ�
		*/
		bool CollectItemListData(IListDataSource* pDataSource,
			ListDataSource& dataSouceList, MapDataSource& dataSourceMap,
			HITEMDATA hParentData, int nTreeLevel, HITEMDATA& hLastChildItem);

		/**
		*  @brief    ������ͷ����״̬
		*/
		void UpdateColumnSortState();

	private:
		/**
		*  @brief    �����ͷ����
		*
		*  @return   ���ر�ͷ����
		*/
		CRect CalcHeaderRect();

		/**
		*  @brief    ���Ʊ�ͷ
		*
		*  @param    CMemoryDC & dcMemory �ڴ�DC
		*  @param    const CRect& rcHeader ��������
		*/
		void DrawHeader(CMemoryDC& dcMemory, const CRect& rcHeader);

		/**
		*  @brief    ���Ʊ�ͷ��
		*
		*  @param    CMemoryDC & dcMemory �ڴ�DC
		*  @param    const CRect& rcHeader ��������
		*  @param    HCOLUMNDATA hColumnData ������
		*/
		void DrawColumn(CMemoryDC& dcMemory, const CRect& rcColumn, HCOLUMNDATA hColumnData);

	private:
		/**
		*  @brief    �����б�����
		*
		*  @return   �����б�����
		*/
		CRect CalcListRect();

		/**
		*  @brief    ������
		*
		*  @param    CMemoryDC & dcMemory �ڴ�DC
		*  @param    const CRect& rcHeader ��ͷ��������
		*  @param    const CRect& rcList ��ȥ��ͷ�Ļ�������
		*/
		void DrawRow(CMemoryDC& dcMemory, const CRect& rcHeader,
			const CRect& rcList);

		/**
		*  @brief    �����б���
		*
		*  @param    CMemoryDC & dcMemory �ڴ�DC
		*  @param    HITEMDATA hItemData �б�������
		*  @param    const CRect & rcRow  �л�������
		*  @param    ColumnDataVector& leafColumnVector ��ͷҶ�ӽڵ�
		*  @param    bool bFirstRow  �Ƿ�Ϊ��һ��
		*/
		void DrawRowBackground(CMemoryDC& dcMemory, HITEMDATA hItemData,
			const CRect& rcRow, ColumnDataVector& leafColumnVector, bool bFirstRow = false);

		/**
		*  @brief    ���Ƶ�Ԫ��
		*
		*  @param    CMemoryDC & dcMemory �ڴ�DC
		*  @param    const CRect& rcCell ��������
		*  @param    bool bTreeNode �Ƿ���ʾΪ���ڵ�
		*  @param    bool bFirstCell �Ƿ��ǵ�һ��
		*  @param    HITEMDATA hItemData �б�������
		*  @param    HCELLDATA hCellData ��Ԫ����
		*  @param    HEDITCONFIG hEditConfig �༭����
		*  @param    HCOLUMNDATA hColumnData ��ͷ����
		*  @param    const CString& strCellText ��Ԫ���ı�
		*/
		void DrawCell(CMemoryDC& dcMemory, const CRect& rcCell, bool bTreeNode, bool bFirstCell,
			HITEMDATA hItemData, HCELLINFO hCellData, HEDITCONFIG hEditConfig, HCOLUMNDATA hColumnData,
			const CString& strCellText);

		/**
		*  @brief    ���õ�ѡ��
		*
		*  @param    HITEMDATA hItemSelect ѡ�еĽڵ�
		*  @return   bool ���óɹ�����true�����򷵻�false
		*/
		bool SetItemSelectFlag(HITEMDATA hItemSelect);

		/**
		*  @brief    �������Notify֪ͨ��Ϣ
		*
		*  @param    UINT nMessage ��ϢID
		*  @param    int nClickType ��� = 0���һ� = 1
		*  @param    int nCol �༭��
		*  @param    int nRow �༭��
		*  @param    HEDITCONFIG hEditCfg ��Ԫ����Ϣ
		*  @param    const CString & strOldText �޸�ǰ��Ԫ���ı�
		*  @param    CString* pStrNewText �޸ĺ�Ԫ���ı�ָ��
		*  @return   LRESULT �¼�֪ͨ���
		*/
		LRESULT NotifyParent(UINT nMessage, int nCol = -1, int nRow = -1, HEDITCONFIG hEditCfg = NULL,
			const CString& strCellText = L"", CString* pStrNewText = NULL, int nClickType = 0);

		/**
		*  @brief    ��ȡ��ǰ���ָ��λ�õĵ�Ԫ������
		*
		*  @param    int nCol ��Ԫ��������
		*  @param    int nRow ��Ԫ��������
		*  @param    HCOLUMNDATA& hColData ��ǰѡ����ͷ����
		*  @param    CRect & rect ��ǰ���ָ��λ�õĵ�Ԫ������
		*  @param    IListDataSource* &pDataSource ���ص�����Դ�ڵ�
		*  @param    CPoint* pPtMs ��ǰ���ͻ�����
		*  @return   bool �����ڿؼ���Χ���򷵻�true�����򷵻�false
		*/
		bool GetFocusRect(int &nCol, int &nRow, HCOLUMNDATA& hColData,
			CRect &rect, IListDataSource* &pDataSource, CPoint* ptMs = NULL);

		/**
		*  @brief    �ͷ��Զ���ؼ�;
		*
		*/
		void DeleteControl();

		/**
		*  @brief    �����༭�ؼ�
		*
		*  @param    int nOption �༭ѡ��
		*  @param    EDITCONFIG editConfig �༭����
		*  @param    CRect rect ��������
		*  @param    const CString& strDefaultValue �ؼ�չ�ֵ��ı�
		*  @param    const CString& strDefaultData �ؼ�չ�ֵ���չ
		*/
		void CreateEditorControl(int nOption,
			EDITCONFIG editConfig,
			CRect rect,
			const CString& strDefaultValue,
			const CString& strDefaultData);

		/**
		*  @brief    ���ݿؼ�����Զ������п�
		*/
		void AutoColumnWidth();

		/**
		*  @brief    ��ȡ��Ԫ���ı���ʾ����
		*
		*  @param    CDC* pDcTest ����DC
		*  @param    const CString & strText ��Ԫ���ı�
		*  @param    CRect & rcCell ��Ԫ������
		*  @param    bool bTreeNode �Ƿ�Ϊ���ڵ�
		*  @param    HITEMDATA hItemData ������
		*  @param    HEDITCONFIG hEditConfig �༭����
		*  @param    HCOLUMNDATA hColumnData ������
		*  @param    CRect & rcTextOut ʵ����ʾ��Ҫ�Ĵ�С
		*/
		void CalcCellTextOutRect(CDC* pDcTest, const CString& strText,
			CRect& rcCell, bool bTreeNode, HITEMDATA hItemData,
			HEDITCONFIG hEditConfig, HCOLUMNDATA hColumnData, CRect& rcTextOut);

		/**
		*  @brief    ����Ԫ����ʾ��Ϣ
		*
		*/
		void ProcessCellTooltip();

		/**
		*  @brief    ���̰�������ѡ����
		*
		*  @param    bool bNextRow	trueѡȡ��һ�У�����ѡȡ��һ��
		*  @return   void
		*/
		void SetSelRowByKey(bool bNextRow);

		/**
		*  @brief    ��ȡ��ͷ���㼶
		*
		*  @return   HCOLUMNDATA hColumnData ��ͷ
		*/
		void GetMaxColumnLevel(int& nMaxLevel,
			HCOLUMNDATA hColumnData = NULL, int nCurLevel = 0);

		/**
		*  @brief    ��ȡ��ͷ���Խṹ
		*
		*  @param   ColumnDataVector& outColumnVector ��ͷ���Խṹ
		*  @param   HCOLUMNDATA hColumnData ��ͷ(�ݹ�ʹ��)
		*/
		void GetColumnLinearityStruct(ColumnDataVector& outColumnVector,
			HCOLUMNDATA hColumnData = NULL);

		/**
		*  @brief    ��ȡ��ͷҶ�ӽṹ
		*
		*  @param   ColumnDataVector& leafColumnVector ��ͷ���Խṹ
		*  @param   HCOLUMNDATA hColumnData ��ͷ(�ݹ�ʹ��)
		*/
		void GetColumnAllLeafStruct(ColumnDataVector& leafColumnVector,
			HCOLUMNDATA hColumnData = NULL);

	public:
		void OnPaint();
		BOOL OnEraseBkgnd(CDC* pDC);
		void OnMouseMove(UINT nFlags, CPoint point);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnLButtonDblClk(UINT nFlags, CPoint point);
		void OnRButtonDown(UINT nFlags, CPoint point);
		BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
		void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		void OnSize(UINT nType, int cx, int cy);

		LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
		LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
		LRESULT OnEndEdit(WPARAM wParam, LPARAM lParam);
		LRESULT OnHyperLink(WPARAM wParam, LPARAM lParam);
		void OnKillFocus(CWnd* pNewWnd);
		LRESULT OnThemeChanged();

	protected:
		CListEdit				_listEdit;				///< ����У�鹦�ܵ��ı��༭��
		CListComboBox			_listCombo;				///< ��Ͽ�༭
		CListDataTime			_listDataTime;			///< ʱ��༭
		CListAngleEdit			_listAngleEdit;			///< �Ƕȱ༭
		CListTreeComboBox		_listTreeCombo;			///< ����Ͽ�༭
		CAutoSearchCombo		_autoCombo;				///< �Զ�������Ͽ�
		CWnd					*_pControl;				///< �Զ���ؼ����

	protected:
		bool					_bCheckSelChange;		///< �Ƿ���ѡ�����
		bool					_bLinkOn;				///< ��ǰ�г����Ӵ���
		bool					_lockTipUpdate;			///< ��ס��ʾ����
		bool					_showHeader;			///< �Ƿ���ʾ��ͷ
		bool					_hasGrid;				///< �Ƿ�������
		bool					_hasLine;				///< �Ƿ���ʾ���ṹ��
		bool					_bMouseOver;			///< ����Ƿ���ͣ
		bool					_bBtnDown;				///< �������Ƿ���
		bool					_bSingleSelect;			///< �Ƿ�֧�ֶ�ѡ
		bool					_bDelDataSource;		///< �Ƿ�ɾ������Դָ��
		int						_nHeaderHeight;			///< ��ͷ�߶�
		int						_nRowHeight;			///< ��Ĭ�ϸ߶�
		int						_treeColumn;			///< ������ʾΪ��
		int						_nEditRowIndex;			///< ��ǰ�༭��������
		int						_nEditColIndex;			///< ��ǰ�༭��������(������ͷҶ�ӽڵ�)
		HWND					_hNofigyWnd;			///< �¼�֪ͨ����
		CSize					_iconSize;				///< �ؼ�ͼ���С
		CFont					_treeListFont;			///< �ؼ�����
		CFont					_underlineFont;			///< �»�������
		CPoint					_dragStartPt;			///< ���ϵ���ʼλ��
		COLORREF				_bkColor;				///< �ؼ�������ɫ
		COLORREF				_selTopColor;			///< ��ѡ��ʱ������ɫ
		COLORREF				_selBottomColor;		///< ��ѡ��ʱ������ɫ
		COLORREF				_hotTopColor;			///< ������ʱ������ɫ
		COLORREF				_hotBottomColor;		///< ������ʱ������ɫ
		COLORREF				_selBorderColor;		///< ��ѡ�б����߿�
		COLORREF				_hotBorderColor;		///< ������ʱ�����߿�
		COLORREF				_gridColor;				///< ������ɫ
		CTheme					_headerTheme;			///< ��ͷƤ��
		CTheme					_progressTheme;			///< ������Ƥ��
		HICON					_hIconCollapse;			///< ����ͼ��
		HICON					_hIconExpand;			///< չ��ͼ��
		CImageList*				_pImageList;			///< ͼ���б�
		bool					_bDelImageList;			///< �Ƿ��ͷ�ͼ���б�
		HCOLUMNDATA				_hHoverCol;				///< ��굱ǰ��ͣ����
		HCOLUMNDATA				_hPressCol;				///< ��굱ǰ���µ���
		HCOLUMNDATA				_hDragingCol;			///< ��굱ǰ�ж�����
		HITEMDATA				_hHoverRow;				///< ��굱ǰ��ͣ����
		int						_nHoverRowIndex;		///< ��굱ǰ��ͣ����
		ColumnDataVector		_columnVector;			///< ��ͷ����
		ListDataSource			_listDataSource;		///< ����Դ��ʶ��ؼ�����(��¼״̬����)
		IListDataSource			*_pListDataSource;		///< �ؼ�����Դָ��
		CTreeListConfig			*_pConfig;				///< �����б�����
		CRect					_rcLastRect;			///< ��¼�ؼ���һ�δ�С
		bool					_bAutoColumnWidth;		///< �Զ������п��ʶ
		int						_nLastSelectItem;		///< ��һ��ѡ����
		CTitleTip				_cellToolTip;			///< ��Ԫ����ʾ��Ϣ
		bool					_bUpDownFlag;			///< �������°�����־
		bool					_bNoChild;				///< ��ǰ�����Ƿ�Ϊһά����(Ϊ���ֲ�_treeColumnĬ��ֵ��Ϊ-1��ɶ�������bw-134327)
		bool					_bColumnWordWarp;		///< ��ͷ�Ƿ����ֻ�����ʾ
		bool					_bRowWordWarp;			///< ���Ƿ����ֻ�����ʾ
		bool					_bColumnSort;			///< �Ƿ�����ͷ������
		bool					_bIsTrim;				///< �Ƿ�ȥ���ո�
		bool					_bCollapseStyle;		///< ���ؼ��۵�չ����ʽ
		float					_fHightLightFactor;     ///< ����ɫ����
	};
}