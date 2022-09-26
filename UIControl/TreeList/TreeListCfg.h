//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           TreeListCfg.H
//    @author         KG
//    @date           2015/3/23 14:23
//    @brief          �����б����ü�����
//*****************************************************

#pragma once

using namespace CommBase;

#include <vector>

namespace ControlUI
{
	// ��Ԫ������
	struct tagCELLDINFO;
	typedef tagCELLDINFO* HCELLINFO;

	// ������
	struct tagITEMDATA;
	typedef tagITEMDATA* HITEMDATA;

	// ��ͷ����
	struct tagCOLUMNDATA;
	typedef tagCOLUMNDATA* HCOLUMNDATA;

	// �༭��������
	struct tagEDITCONFIG;
	typedef tagEDITCONFIG* HEDITCONFIG;

	// ��Ԫ����������
	struct tagCELLCONFIG;
	typedef tagCELLCONFIG* HCELLCONFIG;

	class CTreeListCtrl;

	// ��Ԫ�����ö�ά����
	typedef std::vector<HCELLCONFIG> CellConfigVector;
	typedef CellConfigVector::iterator CellConfigVectorIter;

	typedef std::vector<CellConfigVector> CellConfigVectors;
	typedef CellConfigVectors::iterator	CellConfigVectorsIter;
	typedef CellConfigVectors::const_iterator CellConfigVectorsConstIter;

	enum EFormatType
	{
		FORMAT_LEFT = 0,		/**< ����� */
		FORMAT_MIDDLE,			/**< ���ж��� */
		FORMAT_RIGHT,			/**< �Ҷ��� */
	};

	DECL_DYN_ENUM(EFormatType);
	DECL_DYN_ENUM(ETreeListEditFlag);
	DECL_DYN_ENUM(EValidEditControlFlag);
	DECL_DYN_ENUM(ETreeComboEditControlFlag);
	DECL_DYN_ENUM(EProgressControlFlag);
	DECL_DYN_ENUM(EDateTimeEditFlag);

	/**
	*  @class    ���ü�����
	*
	*  @brief
	*/
	class CONTROL_UI CTreeListConfig
	{
	public:
		CTreeListConfig(CTreeListCtrl* pTreeListCtrl);
		virtual ~CTreeListConfig();

	public:
		/**
		*  @brief    ��ȡ�����б�ؼ�
		*
		*  @return   CTreeListCtrl* �����б�ؼ�
		*/
		CTreeListCtrl* GetTreeListCtrl();

		/**
		*  @brief    ���������б������ļ�
		*
		*  @param    const CString & strCfgFile �����ļ�
		*  @param    const CString & strCfgName ������
		*  @return   bool �ɹ�����true
		*/
		bool LoadConfig(const CString& strCfgFile, const CString& strCfgName);

		/**
		*  @brief    �����Ƿ��ڽڵ����������
		*
		*  @param    int nType ����Դ�ڵ�����
		*  @return   bool ���ҵ�����true
		*/
		bool IsTypeInFilter(int nType);

		/**
		*  @brief    ��ȡ��Ԫ����������
		*
		*  @return   const CellConfigVectors& ������������
		*/
		const CellConfigVectors& GetCellConfigVectors();

		/**
		*  @brief    ��ȡ��Ӧ������������
		*
		*  @param    size_t nRow ���������
		*  @param    size_t nCol ���������
		*  @param	 HCELLCONFIG& pCellCfg  ��������
		*  @return   �ɹ�����true
		*/
		bool GetCellConfigByRowCol(size_t nRow, size_t nCol, HCELLCONFIG& pCellCfg);

		/**
		*  @brief    ������ʱ�������ݣ����ڿؼ��༭��ʱʹ�ã�
		*
		*  @param    const CVariantData& xData ��ʱ����
		*/
		void SetTempData(const CString& strTmpData);

		/**
		*  @brief    ������ʱ�������ݣ����ڿؼ��༭��ʱʹ�ã�
		*
		*  @return    CVariantData ������ʱ����
		*/
		const CString& GetTempData();

	private:
		/**
		*  @brief    ���������б��ͷ
		*
		*  @param    CXmlElement * pColumnCfg �б�ͷXML�ڵ�
		*  @param    HCOLUMNDATA hPrarentColumn ����ͷ
		*  @return   bool �ɹ�����true
		*/
		bool LoadColumn(CXmlElement* pColumnCfg, HCOLUMNDATA hPrarentColumn);

		/**
		*  @brief    �����б�����������
		*
		*  @param    CXmlElement * pListData ��XML�ڵ�
		*/
		void LoadListData(CXmlElement* pListData);

		/**
		*  @brief    ���ؽڵ����͹�����
		*
		*  @param    CXmlElement * pTypeFilter ���͹�����XML�ڵ�
		*/
		void LoadTypeFilter(CXmlElement* pTypeFilter);

		/**
		*  @brief    ���ص�Ԫ��༭����
		*
		*  @param    CXmlElement* pCellCfg ��Ԫ����
		*  @param    HEDITCONFIG hEditConfig ��Ԫ��༭����
		*  @param    HEDITCONFIG hColEditConfig �����ڱ༭����
		*/
		void LoadEditConfig(CXmlElement* pCellCfg, HEDITCONFIG hEditConfig,
			HEDITCONFIG hColEditConfig = NULL);

		/**
		*  @brief    ��ȡ�ַ�����ɫ
		*
		*  @param    const CString & strColor �ַ�����ɫ
		*  @return   COLORREF �����ַ�����ɫ
		*/
		COLORREF GetStringColor(const CString& strColor);

		/**
		*  @brief    �����Ԫ�����ö�ά����
		*
		*/
		void ClearCellConfigVectors();

		/**
		*  @brief    ����Format�ؼ��ֵ��ַ�����ȡö��ֵ
		*
		*  @param    const CString & ������ַ���
		*  @return   int �����ö��ֵ
		*/
		int GetFormatEnum(const CString& str);

		/**
		*  @brief    ����Option�ؼ��ֵ��ַ�����ȡö��ֵ
		*
		*  @param    const CString & ������ַ���
		*  @return   int �����ö��ֵ
		*/
		int GetOptionEnum(const CString& str);

	private:
		CString _strTmpData;	// ���ڴ������ؼ��༭ʱ��������
		std::vector<int> _typeFilter;	///< ����Դ�ڵ����͹�������
		CTreeListCtrl* _pTreeListCtrl;	///< �������ؼ�
		CellConfigVectors _cellCfgVectors; ///< ��Ԫ�����ö�ά����
		double _colWdithScale; ///< ��ͷ�������ű���(125%)
	};
}