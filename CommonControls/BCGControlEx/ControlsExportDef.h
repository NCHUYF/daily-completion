#pragma once

/*******************************************************************
* 文件名称：ControlsExportDef.h
* 作者姓名：熊慧江
* 文件描述：方法、类导出定义
* 需求版本：
* 创建时间：2019-4-22
* Copyright (C) 江西博微新技术有限公司 All rights reserved
*******************************************************************/
#ifdef CONTROLS_EXPORTS
#define CONTROLSAPI_EXPORT __declspec(dllexport)
#else
#define CONTROLSAPI_EXPORT __declspec(dllimport)

#ifdef _DEBUG
#ifdef _USE_VLD
#pragma comment(lib, "Controlsd_vld.lib")
#else
#pragma comment(lib, "Controlsd.lib")
#endif
#else
#pragma comment(lib, "Controls.lib")
#endif
#endif
