#include "afxwin.h"

class COMMONCONTROLS_API StaticPic : public CStatic
{
public:
	StaticPic(void);
	~StaticPic(void);

	BOOL LoadPicFiles(const CString& strMainPicFilePath, const CString& strClosePicFilePath = L"");
	void FreeData();

	CString GetMainPicPath();

protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnEraseBkgnd(CDC* pDC);

	IStream* FileStream(const CString& strPicFilePath);

private:
	IStream* m_pStream;
	IStream* m_pStreamClosePic; // �ر�ͼƬ��
	BOOL m_bIsPicLoaded; // �ļ����ر�ʶ
	bool m_bIsClosePicLoaded;
	ULONG_PTR m_gdiplusToken;
	CString m_strMainPicFilePath;
};