#!usr/bin/env python3
#coding: utf-8
#cpnOperation.py

import sys
import datetime
import os
sys.path.append(os.getcwd())
import cpnTemplate

class cpnOperation:
    """文件生成脚本
    使用方法：python cpnOperation.py path cpnName operation
    脚本至少需要4个参数，
    路径path，当前路径可以使用/或\，其他路径一定要以非/或\开头，否则生成不了
    cpnName根据需要选取
    operation，可以是add,del,up,down操作"""
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __fileName = ''
    __sourceName = ''
    __headerName = ''
    __filePath = ''
    __func_list = []
    __cpnTemp = ''
    __cpnTemp_args = ''
    __OopcHeaderPath = 'cpnBasics/oopc/oopc.h'
    __StandTypeHeaderPath = 'cpnBasics/standType/standType.h'

    def __init__(self,sys_args):
        """根据输入参数初始化参数

        主要功能：
        1.生成文件名称
        2.生成文件路径
        3.生成函数列表"""
        if sys_args[1] != '/' and sys_args[1] != '\\':
            self.__filePath = sys_args[1]
        else:
            self.__filePath = ''
        self.__fileName = sys_args[2]
        self.__sourceName = sys_args[2] + ".c"
        self.__headerName = sys_args[2] + '.h'
        self.__func_list = sys_args[3:]
        self.__cpnTemp_args = sys_args[0:3]+['demo','/demo']
        self.__cpnTemp = cpnTemplate.cpnTemplate(self.__cpnTemp_args)
        
    #========================================================
    # 基本操作函数
    #--------------------------------------------------------
    def addCpn(self):
        """添加组件模块"""
        self.__cpnTemp.addSignalListRegister()
        self.__cpnTemp.addCpnSchSigsHeader()
        self.__cpnTemp.addCpnSchSigsSource()
        
    def delCpn(self):
        """删除组件模块"""
        self.__cpnTemp.delSignalListRegister()
        self.__cpnTemp.delCpnSchSigsHeader()
        self.__cpnTemp.delCpnSchSigsSource()
        
    def upCpn(self):
        """上移组件模块"""
        self.__cpnTemp.upSignalListRegister()
        self.__cpnTemp.upCpnSchSigsHeader()
        self.__cpnTemp.upCpnSchSigsSource()
        
    def downCpn(self):
        """下移组件模块"""
        self.__cpnTemp.downSignalListRegister()
        self.__cpnTemp.downCpnSchSigsHeader()
        self.__cpnTemp.downCpnSchSigsSource()
        
    #========================================================
    
    
    #========================================================
    # 模板生成源文件及头文件控制函数
    #--------------------------------------------------------
    def operationAct(self):
        """组件操作"""
        for func in self.__func_list:
            print('\ncpn opertion:'+func)
            if func == 'add':
                self.addCpn()
            elif func == 'del':
                self.delCpn()
            elif func == 'up':
                self.upCpn()
            elif func == 'down':
                self.downCpn()
        
    #========================================================

if __name__ == '__main__':
    if len(sys.argv) <= 3:
        sys.stderr.write("please input no less than 4 parameter !!!")
    else:
        co = cpnOperation(sys.argv)
        co.operationAct()
        