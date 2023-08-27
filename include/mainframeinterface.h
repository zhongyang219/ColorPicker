﻿#ifndef MAINWINDOWINTERFACE
#define MAINWINDOWINTERFACE

class IModule;

//界面框架接口
//接口中所有const char*类型均为UTF8编码。
class IMainFrame
{
public:
    /**
     * @brief       设置主窗口Ribbin工具栏命令的启用/禁用状态
     * @param[in]	strId: 命令的ID
     * @param[in]	enable: 是否启用
     */
    virtual void SetItemEnable(const char* strId, bool enable) = 0;

    /**
     * @brief       判断主窗口Ribbin工具栏的一个命令是否被被启用
     * @param[in]	strId: 命令的ID
     * @return      是否被启用
     */
    virtual bool IsItemEnable(const char* strId) = 0;

    /*
     * 函数说明: 设置主窗口Ribbin工具栏命令的选中状态
     * 输入参数:
     *   strId: 命令的ID
     *   enable: 是否选中
     */
    virtual void SetItemChecked(const char* strId, bool checked) = 0;

    /**
     * @brief       判断主窗口Ribbin工具栏的一个命令是否被选中
     * @param[in]	strId: 命令的ID
     * @return      是否被选中
     */
    virtual bool IsItemChecked(const char* strId) = 0;

    /**
     * @brief       获取Ribbon标签中一个元素的文本
     * @param[in]	strId: 命令的ID
     * @return      获取的文本
     */
    virtual const char* GetItemText(const char* strId) = 0;

    /**
     * @brief       设置Ribbon标签中一个元素的文本
     * @param[in]	strId: 命令的ID
     * @param[in]	text: 设置的文本
     */
    virtual void SetItemText(const char* strId, const char* text) = 0;

    /**
    * @brief       设置Ribbon标签中一个元素的图标
    * @param[in]	strId: 命令的ID
    * @param[in]	iconPath: 图标的路径
    * @param[in]	iconSize: 图标的大小
    */
    virtual void SetItemIcon(const char* strId, const char* iconPath, int iconSize) = 0;

    /**
     * @brief       根据模块名称获取模块对象的指针
     * @param[in]	moduleName 模块名称，由模块接口GetModuleName()返回。
     * @return      模块对象的指针
     */
    virtual IModule *GetModule(const char* strModuleName) const = 0;

    /**
     * @brief       向一个模块发送消息
     * @param[in]	moduleName 模块名称
     * @param[in]	msgType 消息类型
     * @param[in]	para1 para2 可选参数
     * @return      返回的消息
     */
    virtual void* SendModuleMessage(const char* moduleName, const char* msgType, void* para1 = nullptr, void* para2 = nullptr) = 0;

    virtual void* GetAcion(const char* strId) = 0;
    virtual void* GetWidget(const char* strId) = 0;
};

#endif // MAINWINDOWINTERFACE

