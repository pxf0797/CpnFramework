#!usr/bin/env python3
#coding: utf-8
#CpnOperation.py

import sys
import datetime
import os
sys.path.append(os.getcwd())
import CpnTemplate

class CpnOperation:
    """ files generate shell
    how to use: python CpnOperation.py path cpnName operation
    shell need at least 4 paramters,
    path, file path can use \/ or \\, other file path should not begain with \/ and(or) \\, otherwise files can not be generated.
    cpnName, cpnName can be defined by yourself.
    operation, it can be instructions as add,del,up,down operations. """
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __fileName = ''
    __sourceName = ''
    __headerName = ''
    __filePath = ''
    __func_list = []
    __cpnTemp = ''
    __cpnTemp_args = ''
    __OopcHeaderPath = 'Oopc.h'
    __StandTypeHeaderPath = 'StandType.h'

    def __init__(self,sys_args):
        """ according input to initial

        main function:
        1.component to add or delete """
        if sys_args[1] != '/' and sys_args[1] != '\\':
            self.__filePath = sys_args[1]
        else:
            self.__filePath = ''
        self.__fileName = sys_args[2]
        self.__sourceName = sys_args[2] + ".c"
        self.__headerName = sys_args[2] + '.h'
        self.__func_list = sys_args[3:]
        self.__cpnTemp_args = sys_args[0:3]+['demo','/demo']
        self.__cpnTemp = CpnTemplate.CpnTemplate(self.__cpnTemp_args)

    #========================================================
    # basic operation functions
    #--------------------------------------------------------
    def addCpn(self):
        """ add component """
        self.__cpnTemp.addSignalListRegister()
        self.__cpnTemp.addCpnSchSigsHeader()
        self.__cpnTemp.addCpnSchSigsSource()
        self.__cpnTemp.addCpnSchCfg()

    def delCpn(self):
        """ delete component """
        self.__cpnTemp.delSignalListRegister()
        self.__cpnTemp.delCpnSchSigsHeader()
        self.__cpnTemp.delCpnSchSigsSource()
        self.__cpnTemp.delCpnSchCfg()

    def upCpn(self):
        """ up move component """
        self.__cpnTemp.upSignalListRegister()
        self.__cpnTemp.upCpnSchSigsHeader()
        self.__cpnTemp.upCpnSchSigsSource()
        self.__cpnTemp.upCpnSchCfg()

    def downCpn(self):
        """ down move component """
        self.__cpnTemp.downSignalListRegister()
        self.__cpnTemp.downCpnSchSigsHeader()
        self.__cpnTemp.downCpnSchSigsSource()
        self.__cpnTemp.downCpnSchCfg()

    #========================================================


    #========================================================
    # component operation
    #--------------------------------------------------------
    def operationAct(self):
        """ component operations """
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
        co = CpnOperation(sys.argv)
        co.operationAct()
