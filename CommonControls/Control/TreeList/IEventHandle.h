//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           IEventHandle.H
//    @author         LOL
//    @date           2016/1/11 9:35
//    @brief          ���ؼ���������Ӧ�ӿ�
//*****************************************************

#pragma once

class CTreeListCtrl;
class IListDataSource;

class IEventHandle /*: public IOSGiObject*/
{
public:
	virtual void ExcuteHandle(CTreeListCtrl* pTreeList,
		int nCol, int nRow, IListDataSource* pSelDataSource, HEDITCONFIG editConfig = NULL, CTreeListConfig* pConfig = NULL) = 0;
	virtual ~IEventHandle(){}
};

typedef std::map<CString, IEventHandle*> EventHandleMap;
typedef EventHandleMap::iterator		 EventHandleIter;