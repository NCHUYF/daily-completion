#pragma once

#include "ProjectReader.h"

#include "..\StaticResourceClear.h"

/**
 * This class contains utility methods for working with ProjectReaderss.
 */
class COMMONCONTROLS_API ProjectReaderUtility
{
private:
   /**
    * Constructor.
    */
	ProjectReaderUtility();

public:
   /**
    * Retrieves a ProjectReader instance which can read a file of the
    * type specified by the supplied file name.  
    * 
    * @param name file name
    * @return ProjectReader instance
    */
	static ProjectReaderPtr getProjectReader(CString name);


	/**
	* ��ȡ���ļ��İ汾
	*
	* @param   �ļ�ȫ·��
	* @return password
	*/
	static CString getApplicationName(CString strFileName);
 //  /**
 //   * Retrieves a set containing the file extensions supported by the
 //   * getProjectReader method.
 //   * 
 //   * @return set of file extensions
 //   */
	//static const List<CString>* getSupportedFileExtensions();
};