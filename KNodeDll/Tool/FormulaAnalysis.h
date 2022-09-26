/*//*****************************************************
//    
//    @copyright      ���������
//    @version        v4.0
//    @file           FormulaAnalysis.H
//    @author         mahaidong
//    @date           2019/2/22 10:37
//    @brief          ƽ̨���룬�߼����ʽ������
//******************************************************/

#pragma once

namespace CommBase
{
	class COMMBASE_API CAnalysisFormula
	{
	public:
		/**
		* �������ʽ�������캯��
		* @param [in] formula		�����ı��ʽ
		*/
		CAnalysisFormula(LPCTSTR formula);

		/**
		* & and | �Ƚ�
		* @return ���رȽ��Ƿ�ɹ�
		* - true �ɹ���false ʧ��
		*/
		bool A_AndOr(void);

	private:
		/**
		* ������ �Ƚ�
		* @return ���رȽ��Ƿ�ɹ�
		* - true �ɹ���false ʧ��
		*/
		bool B_Operator(void);

		/**
		* �����Ӽ��������ʽ
		* @return ���ؼӼ�ֵ
		*/
		double C_AddSub(void);

		/**
		* �����ӳ˳��������ʽ
		* @return ���س˳�ֵ
		*/
		double D_MulDiv(void);

		/**
		* ������ֵ
		* @return ������ֵ
		*/
		double E_Number(void);

	protected:
		CString		_Formula;
		CString		_SrcValue;
		CString		_DesValue;
		double		_MulDivReslut;
		double		_AddSubReslut;
		int			_pos;
		bool		_bOp1;
		bool		_bResult;
	};
}