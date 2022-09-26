
#pragma once

#pragma pack (push, 8)

//ʵ��������
typedef struct tag_AppstartCtx
{
	// ����ʹ��(���32��64λ�ڴ湲���С����)
	INT hWnd;		// ��ǰ���е�CAD�����ھ��
	TCHAR filePath[MAX_PATH * 2]; // ���ڴ򿪵��ļ�·��
	INT hPrjDesignWnd; // ��Ŀ���������
	bool bReaded;

	tag_AppstartCtx()
		:filePath(TEXT(""))
	{
		hWnd = NULL;
		hPrjDesignWnd = NULL;
		bReaded = false;
	}

	void SetFilePath(const CString& filePathIn)
	{
		lstrcpyn(filePath, filePathIn.GetString(), MAX_PATH * 2);
	}

	/**
	*  @brief    ����ͬ����ɵı��
	*
	*  @return   void
	*/
	void SetReaded()
	{
		bReaded = true;
	}
}AppstartCtx;
