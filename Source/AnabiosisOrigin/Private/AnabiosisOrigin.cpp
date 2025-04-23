/* 
 * Copyright (C) 2025 [Wang]
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see https://www.gnu.org/licenses/. 
 */

/*
* 文件名: AnabiosisOrigin.cpp
* 功能描述： 游戏模块 AnabiosisOrigin 的主要实现文件。
*            负责注册游戏模块和定义全局日志类别。
* 结构：
* - 使用 IMPLEMENT_PRIMARY_GAME_MODULE 宏注册模块。
* - 使用 DEFINE_LOG_CATEGORY 宏定义日志类别 LogAnabiosisOrigin。
*/

#include "AnabiosisOrigin.h" // 包含模块公共头文件
#include "Modules/ModuleManager.h"
#include "AnabiosisOriginTypes.h" // 包含类型定义

// 实现主游戏模块
IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, AnabiosisOrigin, "AnabiosisOrigin");

// 定义项目的日志类别
DEFINE_LOG_CATEGORY(LogAnabiosisOrigin);

