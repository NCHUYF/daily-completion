//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           TreeComboBox.H
//    @author         KG
//    @date           2015/3/8 11:19
//    @brief          ������Ͽ�ؼ�
//*****************************************************

#pragma once

using namespace CommBase;

namespace ControlUI
{
	// �Զ�����Ͽ������ر���Ϣ
#define UM_DROP_CLOSE	(WM_USER + 101)

#define UM_CHECK_EDIT (WM_USER + 102)

	class CTreeComboBox;


	/**
	*  @class    ��Ͽ��������ؼ�
	*
	*  @brief    �ڲ����벻Ҫ���ؼ�ʹ��
	*/
	class CONTROL_UI CComboBoxTree : public CTreeCtrl
	{
	public:
		CComboBoxTree();
		virtual ~CComboBoxTree();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/**
		*  @brief    ��ʾ������
		*
		*  @param    CRect rect
		*/
		virtual void Display(CRect rect);

		/**
		*  @brief    ��Ϣ����
		*
		*  @param    MSG * pMsg
		*  @return   BOOL
		*/
		virtual BOOL PreTranslateMessage(MSG* pMsg);

		/**
		*  @brief    ��ʼ��
		*
		*  @param    CTComboBox * pCombo
		*/
		void Init(CTreeComboBox* pCombo) { _pCombo = pCombo; };

	public:
		/**
		*  @brief    ����ˢ���Ӽ���ѡ״̬
		*
		*  @param    HTREEITEM hItem ��ǰ�ڵ�
		*/
		void ConsistentChildCheck(HTREEITEM hItem);

		/**
		*  @brief    ����ˢ�¸���ѡ״̬
		*
		*  @param    HTREEITEM hItem ��ǰ�ڵ�
		*/
		void ConsistentParentCheck(HTREEITEM hItem);

		/**
		*  �ر������ؼ�
		*/
		void CloseTree(int nTag = 0);

	protected:
		afx_msg void OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnDestroy();
		afx_msg LRESULT OnAcadKeepFocus(WPARAM wParam, LPARAM lParam);

	private:
		CTreeComboBox*		_pCombo;		///< ��������Ͽ�ؼ�
	};

	//// ������Ͽ�����չ����Ϣ
#define UM_DROP_DOWN (WM_USER +102 )

/**
*  @class    ������Ͽ�ؼ�
*
*  @brief
*/
	class CONTROL_UI CTreeComboBox : public CComboBox
	{
		DECLARE_DYNAMIC(CTreeComboBox)

	public:
		CTreeComboBox();
		virtual ~CTreeComboBox();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/**
		*  @brief    ��ʾ������
		*
		*/
		void DisplayTree();

		/**
		*  @brief    ��ȡ�������ؼ�
		*
		*  @return   CTreeCtrl&
		*/
		CTreeCtrl& GetTreeCtrl();

		/**
		*  @brief    �ؼ��Ƿ񼤻�
		*
		*  @return   BOOL
		*/
		BOOL IsControlActive() const;

		/**
		*  @brief    ��ȡ���������
		*
		*  @param    const int nHeight
		*/
		int GetDroppedWidth();

		/**
		*  @brief    ��ȡ�������߶�
		*
		*  @param    const int nHeight
		*/
		int GetDroppedHeight() const;

		/**
		*  @brief    �������������
		*
		*  @param    const int nHeight
		*			 (Ϊ0ʱ�Զ���Ӧ��չ���Ŀ��)
		*/
		void SetDroppedWidth(const int nWidth);

		/**
		*  @brief    �����������߶�
		*
		*  @param    const int nHeight
		*/
		void SetDroppedHeight(const int nHeight);

		/**
		*  @brief    �Ƿ�Ϊѡ���ģʽ
		*
		*  @return    bool �����Ƿ��ѡ���ģʽ
		*/
		bool IsCheckMode();

		/**
		*  @brief    �����Ƿ�Ϊѡ���ģʽ
		*
		*  @return    bool �����Ƿ��ѡ���ģʽ
		*/
		void SetCheckMode(bool bCheckModel);

		/**
		*  @brief    �ؼ�����֮���ټ���XML��������
		*
		*  @param    const CString& xmlFile ������Xml�����ļ�(��XML�����ַ���)
		*  @param    bool bNoLimitOrSelAll true�Զ���Ӳ��޻�ȫѡ
		*  @return   bool �ɹ�����true
		*/
		bool LoadXmlData(const CString& xmlFile, bool bNoLimitOrSelAll = false);

		/**
		*  @brief    �����ļ��ڵ����xml��������
		*
		*  @param    CXmlElement * pElm
		*  @param    bool bNoLimitOrSelAll
		*  @return   bool
		*/
		bool LoadXmlData(CXmlElement* pElm, bool bNoLimitOrSelAll = false);

		/**
		*  @brief    �����ַ�������
		*
		*  @param    CStringVector & listData �ַ�������
		*  @param    bool bNoLimitOrSelAll true�Զ���Ӳ��޻�ȫѡ
		*/
		void LoadStringVector(CStringVector& listData,
			bool bNoLimitOrSelAll = false, const CString strSelAll = L"");

		/**
		*  @brief    ����ؼ�����(����CheckModeΪtrueʱ֧��)
		*
		*  @param    CXmlElement* pElm ����ؼ����ݸ��ڵ�
		*/
		void SaveXmlData(CXmlElement* pElm);

		/**
		*  @brief    ��ȡѡ���ַ���
		*
		*/
		CString GetCheckString();

		/**
		*  @brief   ����ѡ���ַ���
		*
		*  @param    const CString& strCheck ��ʾ���ı�
		*/
		void SetCheckString(const CString& strCheck);

		/**
		*  @brief    ���ø�ѡģʽ�ָ���
		*
		*  @param    const CString & ch
		*  @return   void
		*/
		void SetSplitChar(const CString& ch);

		/**
		*  @brief    ��ø�ѡģʽ�ָ���
		*
		*  @return   CString
		*/
		CString GetSplitChar() const;

		/**
		*  @brief    ��ȡ�ؼ���ǰѡ��ĸ�������
		*
		*  @return   CString ���ؿؼ�ѡ����ĸ�������
		*/
		CString GetCurrentSelData();

		/**
		*  @brief    ��ȡ�ؼ���ǰѡ�����ʾ�ı�
		*
		*  @return
		*/
		CString GetCurrentSelText();

		/**
		*  @brief    ���ö��㴰��
		*
		*  @param    CWnd * pOwner
		*/
		void SetParentOwner(CWnd* pOwner);

		/**
		*  @brief    ��ȡ������
		*
		*  @return   CWnd*
		*/
		CWnd* GetParentOwner();

		/**
		*  @brief    �ֶ��������ʾ�ڵ�
		*
		*  @param    const CString & strTest ��ʾ�ַ�
		*  @param    CString strData ��������
		*  @param    HTREEITEM hParent ���ڵ�
		*  @param    bool isLeafNode �Ƿ�ΪҶ�ӽڵ�
		*  @return   HTREEITEM �����½ڵ�
		*/
		HTREEITEM InsertItem(const CString& strTest,
			CString strData, HTREEITEM hParent = TVI_ROOT, bool isLeafNode = false);

		/**
		*  @brief    �������
		*
		*/
		virtual void ResetContent();

		/**
		*  �������ܣ� ��ս���ʾ�ڵ�
		*  ���������
		*  ����ֵ��     void
		*/
		virtual void ResetItemContent();

		/**
		*  @brief    ��ѡ�����ֻ��ѡ��һ��
		*
		*/
		void SetSingleCheck(bool bCheck) { _bSigleCheck = bCheck; }

		/**
		*  @brief    �Ƿ�ֻ��ѡ��һ����ѡ��
		*
		*/
		bool IsSingleCheck() { return _bSigleCheck; }

		void SetSelectByText(bool bSelectByText)
		{
			_bSelectByText = bSelectByText;
		}

		void SetSelectData(CString strText, CString StrData)
		{
			_strCurSelText = strText;
			_strCurSelData = StrData;
		}

	public:
		/**
		*  @brief    ��Ϣ����
		*
		*/
		virtual BOOL PreTranslateMessage(MSG* pMsg);

		void ResetItemData();

		static const CString NoData();

		/**
		*  @brief    ͨ���ı���ȡData,��������һ��ƥ����ı�ֵ��Ӧ��Data������
		*
		*  @param    CString & text
		*  @return   CString
		*/
		CString GetDataByText(CString &text);

		/**
		*  @brief    ����Data��λ
		*
		*  @param    CString strData
		*  @return
		*/
		void SetCheckSelectByData(CString strData);

		/**
		*  @brief    ������ʾ�ı�
		*
		*  @param    CString strText
		*  @return
		*/
		void SetShowText(CString strText);

	protected:
		/**
		*  @brief    ��ȡ�ؼ��ı�����
		*
		*  @return   CString ���ؿؼ��ı�
		*/
		CString GetControlText();

		/**
		*  @brief    �������νڵ�����
		*
		*  @param    CTreeCtrl & treeCtrl ���ؼ�
		*  @param    HTREEITEM hParent ���ڵ�
		*  @param    CXmlElement * pElm xml�ļ��ڵ�
		*/
		void SaveTreeCtrl(CTreeCtrl& treeCtrl, HTREEITEM hParent, CXmlElement* pElm);

		/**
		*  @brief    ��ʼ���������ؼ�
		*
		*  @param    HTREEITEM hRoot
		*/
		void InitDropTree();

		/**
		*  @brief    ���������������ڵ�
		*
		*  @param    HTREEITEM hRoot
		*/
		void CollapseAllTreeItem(HTREEITEM hRoot);

		/**
		*  @brief    ͨ���ı����ҶԵ���������
		*
		*  @param    HTREEITEM hRoot
		*  @param    CString strItem
		*  @param    CString strData
		*  @return   HTREEITEM
		*/
		HTREEITEM FindItemByText(HTREEITEM hRoot, CString strItem, CString strData);

		/**
		*  @brief    ��ȡ��ʾ��������
		*
		*  @param    HTREEITEM hRoot
		*  @param    int & nCount
		*/
		void GetShowItem(HTREEITEM hRoot, int& nCount);

		/**
		*  @brief    �ؼ���������
		*
		*/
		virtual void PreSubclassWindow();

		/**
		*  @brief    �ؼ���������
		*
		*/
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

		CString GetDataFromText(CString curText);

		bool SearchDataByText(CTreeCtrl &treeCtrl, HTREEITEM hParent, CString &curText, CString *curData);

		bool CheckDataExist(CTreeCtrl &treeCtrl, HTREEITEM hParent, CString *curData, bool *isExist, CString strShow);

	protected:
		afx_msg void OnDestroy();
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
		afx_msg LRESULT OnCloseControl(WPARAM wParam, LPARAM lParam);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	protected:
		CWnd* _pOwner;				///< �������״���
		int _nDroppedWidth;			///< ��������(Ϊ0ʱ�Զ���Ӧ��չ���Ŀ��, Ĭ����Ӧ�ؼ����(-1))
		int _nDroppedHeight;		///< ������߶�
		bool _bInCreate;			///< �Ƿ����ڴ���
		BOOL _bControlActive;		///< ��ǰ�Ƿ񼤻�
		CComboBoxTree _dropTree;	///< �������ؼ�
		bool _bCheckMode;			///< �Ƿ���ѡ���ģʽ
		bool _bShowComboList;		///< �Ƿ�չʾ��������
		bool _bDelItemData;			///< �Ƿ�ɾ����������ָ��
		bool _bInShowDropDown;		///< �Ƿ������Բ�����
		bool _bSigleCheck;			///< ��ѡ�����ֻ��ѡ��һ��
		bool _bSelectByText;		///< �Ƿ�Ҫ������ʾֵ��λ������
		CString _splitCh;			///< ��ѡ����ѡ��ָ��
		CString _strCurSelText;		///< ��ǰѡ����ı�����λ�ã�
		CString _strCurSelData;		///< ��ǰѡ����ı��������ݣ���λ�ã�

	private:
		static const CString					s_strNoData;
	};
}