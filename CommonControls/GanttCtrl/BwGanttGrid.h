//*****************************************************
//    
//    @copyright      
//    @version        v1.0
//    @file           BwGanttGrid.h
//    @author         yf
//    @data           2020/12/16  
//    @brief          ����ͼGrid�ؼ�
//
//*****************************************************

#pragma once

#include "BCGPGanttGrid.h"
#include <vector>
#define  WM_USER_SORTCOLUM    WM_USER + 901

class COMMONCONTROLS_API CBwGrowthPatternItem : public CBCGPGridItem
{
	DECLARE_DYNCREATE(CBwGrowthPatternItem)
public:
	CBwGrowthPatternItem();
public:
	virtual void OnDrawValue(CDC* pDC, CRect rect);

	// �������(���ã�
	void FreezeItem(bool bFreeze = true);
private:
	COLORREF _clrTextOld;
};

class COMMONCONTROLS_API CNoEditItem : public CBCGPGridItem
{
	DECLARE_DYNCREATE(CNoEditItem)
public:
	CNoEditItem();
};

class COMMONCONTROLS_API CBwDateTimeItem : public CBCGPGridDateTimeItem
{
	DECLARE_DYNCREATE(CBwDateTimeItem)
public:
	CBwDateTimeItem();
	virtual CString FormatItem();
	virtual BOOL OnUpdateValue();
	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
};

class CBwGanttControl;
class CBwGridPanel;

class COMMONCONTROLS_API CBwGanttGrid : public CBCGPGanttGridEx
{
public:
	friend class CBwGridPanel;
public:
	enum EDataType
	{
		eString,
		eDate,
		eBool,
		eInt,
		eDouble,
	};

	///�ж���
	struct ColumnFormat
	{
	public:
		ColumnFormat(const CString& strName, const int width,
			const EDataType editInPlaceFlags = eString,
			CRuntimeClass *runtime = nullptr,
			const CString& dataFieldName = L"",
			const _variant_t& default = _variant_t(),
			const std::vector<CString>& optionValues = {})
			: _strName(strName)
			, _width(width)
			, _editInPlaceFlags(editInPlaceFlags)
			, _runtime(runtime)
			, _dataFieldName(dataFieldName)
			, _default(default)
			, _OptionValues(optionValues)
		{
			if (_dataFieldName.IsEmpty())
			{
				// ����������������
				_dataFieldName = strName;
			}
		}
		CString			_strName;			//����
		int				_width;				//���
		EDataType				_editInPlaceFlags;	//�༭���
		CRuntimeClass	*_runtime;			//��Ԫ����չ����ʱ��
		CString			_dataFieldName;		//��������
		_variant_t		_default;			//Ĭ��ֵ
		std::vector<CString> _OptionValues;  //��ѡ��ֵ���ϣ�ָ��������������(��������Ҫѡ��Ŀؼ�)��ʱ�򽫻�ʹ��
	};
	//�кϲ�����
	struct ColumnMergeFormat
	{
	public:
		ColumnMergeFormat(const CString& strName, const int nLeft, const int nRight, const int nTop, const int nBottom)
			: _strName(strName)
			, _nLeft(nLeft)
			, _nRight(nRight)
			, _nTop(nTop)
			, _nBottom(nBottom)
		{}
		CString			_strName;			//�ϲ�������
		int				_nLeft;				//��ͷ��λ��
		int				_nRight;			//��ͷ��λ��
		int				_nTop;				//��ͷ��λ��
		int				_nBottom;			//��ͷ��λ��
	};

	// �б༭����
	struct stBwGridEditInfo
	{
		stBwGridEditInfo(CBCGPGridItem * pItem, KNode *pNode, ColumnFormat colFormat)
			: _pItem(pItem)
			, _pNode(pNode)
			, _colFormat(colFormat)
			, _result(true)
		{}
		CBCGPGridItem * _pItem;
		KNode *_pNode;
		ColumnFormat _colFormat;
		bool _result; // Ϊfalseʱ�༭ʧ�ܣ�����ֵ��ֵ��KNode
	};

	//��Ԫ����
	struct Cell
	{
	public:
		Cell(const _variant_t& value, const DWORD_PTR data = 0)
			: _Value(value)
			, _Data(data)
		{}
		_variant_t		_Value;//ֵ
		DWORD_PTR		_Data; //����������ָ��
	};
	//һ������
	typedef std::vector<Cell>  RowData;
public:
	CBwGanttGrid();
	virtual ~CBwGanttGrid();
public:
	const std::vector<ColumnFormat> &GetColumnFormats();

	/**
	* ��Ԫ���ʽ����ص�
	* @param [in]  nRow				������
	* @param [in]  nCol				������
	* @param [in] pItem				��Ԫ�����
	* @return
	*/
	typedef void(WINAPI *RowCellFormatCall)(int nRow, int nCol,
		CBCGPGridItem* pItem, VOID* pUserData);
	
	/**
	* �ϲ���Ԫ����ص�������������
	* @param [in]  nCol           ������
	* @param [in] pPriRowItem	  ǰһ�е�Ԫ��
	* @param [in] pAfterRowItem   ��ǰ�е�Ԫ��
	* @param [in] pUserData			SetRowCellCallBack�����pUserData
	* @return	  bool   �����ǰ��Ԫ����Ҫ��ǰһ�е�Ԫ��ϲ�������TRUE�����򷵻�FALSE
	*/
	typedef BOOL(WINAPI *RowCellMergeCall)(int nCol, CBCGPGridItem* pPriRowItem,
		CBCGPGridItem* pcurRowItem, VOID* pUserData);

	// ��������
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	/**
	* ����Ĭ�Ϸ��
	*/
	virtual void SetDefaultStyle();

	/**
	* ������ͷ��Ϣ
	* @param [in]   columnFormats		�ж���
	* @param [in]   nHeaderLineCount	��ͷ����
	* @param [in]   columnFormats		��ͷ�ϲ�����
	* @return
	*/
	virtual void SetColumnFormats(const std::vector<ColumnFormat>& columnFormats, int nHeaderLineCount = 1, const std::vector<ColumnMergeFormat>& ColumnMergeFormat = {});
	
	/**
	* ���õ�Ԫ���ʽ����ص�
	* @param [in]   callfun		�ص�����ָ��
	* @param [in]   pUserData	�û�����
	* @note ��Ҫ�ڸ�������֮ǰ����SetRowCellFormatCallBack,ָ���Ļص��������������ݷ�����Ӻ͸��º󴥷���SetRowDatas\AddRowData\InsertRowData��
	* @return
	*/
	virtual void SetRowCellFormatCallBack(RowCellFormatCall callfun, VOID* pUserData = NULL);
	
	/**
	* ���õ�Ԫ��ϲ�����ص�
	* @param [in]   callfun		�ص�����ָ��
	* @param [in]   pUserData	�û�����
	* @note ��Ҫ�ڸ�������֮ǰ����SetRowCellMergeCallBack,ָ���Ļص��������������ݷ�����Ӻ͸��º󴥷���SetRowDatas\AddRowData\InsertRowData��
	* @return
	*/
	virtual void SetRowCellMergeCallBack(RowCellMergeCall callfun, VOID* pUserData = NULL);

	virtual CBCGPGridColumnsInfo& GetColumnsInfo()  override
	{
		return m_ColumnsEx;
	}

	virtual const CBCGPGridColumnsInfo& GetColumnsInfo() const  override
	{
		return m_ColumnsEx;
	}

	// ��ȡGrid���±�
	int GetGridItemIndex(CBCGPGridRow *pItem);
	int GetGridItemIndex(CBCGPGridItem *pItem);

	// ����Gridֵ
	void SetGridData(int nRow, int nCol, const _variant_t& varValue);

	// ��ȡGridֵ
	_variant_t GetGridData(int nRow, int nCol);

	// �������ƻ�ȡ������
	int GetColIndexByName(const CString &strName);

	// ��ȡѡ���е��±�����
	void GetSelectedIndexes(std::set<int> &arrSelIndexes);

	// ��ȡѡ���е��±�
	int GetSelIndex();

	// ���ÿ�����
	void SetControl(CBwGanttControl *pControl);

	// ������ͷ���뷽ʽ
	void SetHeaderAlign(int nAlign);

	// ��ȡ��
	CBCGPGridRow* GetRow(int nPos);

	// ���»��ƣ���д�÷���������ֹsort�������ػ�
	virtual void DoRebuildTerminalItems();

	// �����ͷ
	virtual void OnHeaderColumnClick(int nColumn);
	
	// ���������
	void ClearSortColumn();
protected:
	virtual BOOL OnTrackHeader() override
	{
		return FALSE; // do not resize columns inside client area by mouse, only at header
	}

	/*
	* ������
	*/
	virtual void CreateColumns();
	virtual CBCGPGanttControl* GetGanttControlNotify() const;
	virtual void  OnItemChanged(CBCGPGridItem* pItem, int nRow, int nColumn);

	virtual CRect OnGetHeaderRect(CDC* pDC, const CRect& rectDraw) override;
	virtual void OnDrawHeader(CDC* pDC) override;
	virtual void OnPrintHeader(CDC* pDC, CPrintInfo* pInfo) override;
	virtual void OnPosSizeChanged() override;
protected:
	virtual void  OnUpdateVScrollPos(int nVOffset, int nPrevVOffset);
protected:
	BOOL _bCreated;										//�Ƿ��Ѵ����ɹ�
	std::vector<ColumnMergeFormat> _ColumnMergeFormat;	// �кϲ����弯��
	std::vector<ColumnFormat> _ColumnFormats;			//�ж��弯��
	CBCGPGridColumnsInfoEx	m_ColumnsEx;				// other header implementation

	RowCellFormatCall _pRowCellFormatCall;				//��Ԫ���ʽ����ص�
	RowCellMergeCall _pRowCellMergeCall;				//�����ݺϲ�����ص�
	VOID* _pFormatUserData;									////��Ԫ���ʽ����ص��û�����ָ��
	VOID* _pMergeUserData;									////�����ݺϲ�����ص��û�����ָ��

	CBwGanttControl *_pControl;							// ����ͼ������ָ��
	std::map<int, int>					_mapColClick;			// ��ͷ�������
	int											_nCurSelColIndex = -1;	// ��ǰ�����������ͷ���±�
};

