#include "stdafx.h"
#include "AbstractProjectWriter.h"
#include "../../../Toolkit/include/FileDataStream2.h"

/**
* {@inheritDoc}
*/
void AbstractProjectWriter::write(ProjectFile* projectFile, CString fileName)
{
	//// ��д���ڴ��У�����ɹ��ͼ���д���ļ�
	//BwProj::toolkit::CMemoryDataWriteStream2 buffer;
	//write(projectFile, &buffer);

	CAtlFile file;
	if(file.Create(fileName, GENERIC_WRITE, FILE_SHARE_READ, CREATE_ALWAYS) != S_OK)
		throw toolkit::Exception(_T("д���ļ�ʧ�ܡ�"));

	write(projectFile, &file);

	file.Close();
}

/**
* {@inheritDoc}
*/
void AbstractProjectWriter::write(ProjectFile* projectFile, CAtlFile* file)
{
	BwProj::toolkit::CFileDataWriteStream fso(*file);
	write(projectFile, &fso);
}