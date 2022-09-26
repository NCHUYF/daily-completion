/*-----------------------------------------------------
* �ļ����ƣ�  PropertyBandCtrl.H
*  ���������� �������
* ������ʶ��  ��־��  2020/7/6 8:59
*
* �޸ı�ʶ��
* �޸�������
*
* �޸ı�ʶ��
* �޸�������
-----------------------------------------------------*/

#pragma once

#include "PropertyBandCtrl.h"

namespace PropEx
{
	class COMMONCONTROLS_API CPropertyBandCtrl2 : public CPropertyBandCtrl
	{
		typedef std::map<IPropertyObjectData*, CBCGPProp*> ItemPropMap;

		DECLARE_DYNAMIC(CPropertyBandCtrl2)

		DECLARE_SINGLE_CLASS(CPropertyBandCtrl2);
	public:
		CPropertyBandCtrl2();
		virtual ~CPropertyBandCtrl2();

	protected:
		DECLARE_MESSAGE_MAP()
		afx_msg void OnSize(UINT nType, int cx, int cy);
		virtual void PostNcDestroy();
	};

}
