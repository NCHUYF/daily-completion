#pragma once

/*******************************************************************
* 文件名称：ControlsExportDef.h
* 作者姓名：熊慧江
* 文件描述：方法、类导出定义
* 需求版本：
* 创建时间：2019-4-22
* Copyright (C) 江西博微新技术有限公司 All rights reserved
*******************************************************************/

#ifdef COMMONCONTROLS_API
#define CONTROLSAPI_EXPORT COMMONCONTROLS_API
#else
#define CONTROLSAPI_EXPORT 
#endif

#include "BCGPBaseInfoEx.h"
#include "BCGPComboBoxEx.h"
#include "BCGPDialogEx.h"
#include "BCGPDialogTEx.h"
#include "BCGPGanttChartEx.h"
#include "BCGPGanttControlEx.h"
#include "BCGPGanttGridEx.h"
#include "BCGPGanttViewEx.h"
#include "BCGPGridItemEx.h"
//#include "BCGPRibbonBarEx.h"
//#include "BCGPRibbonConstructorEx.h"
//#include "BCGPRibbonInfoLoaderEx.h"
//#include "BCGPRibbonMainPanelEx.h"
//#include "BCGPRibbonPanelMenuEx.h"
#include "BCGPSplitterWndEx.h"
#include "BCGPBaseInfoEx.h"
#include "ClosePopupDialogImpl.h"