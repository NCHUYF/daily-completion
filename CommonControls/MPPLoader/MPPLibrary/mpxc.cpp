// mpxc.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "mpxj\reader\ProjectReaderUtility.h"
#include "mpxj\reader\ProjectWriterUtility.h"
//#include "mpxj\GarbageCollector.h"

void test_sample1_xml(LPCTSTR filename, LPCTSTR filename2)
{
	// ���ļ�
	ProjectReaderPtr reader = ProjectReaderUtility::getProjectReader(filename);
	ProjectFilePtr project = reader->read(filename);

	// д�ļ�
	ProjectWriterPtr writer = ProjectWriterUtility::getProjectWriter(filename2);
	writer->write(project.get(), filename2);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	return 0;
}