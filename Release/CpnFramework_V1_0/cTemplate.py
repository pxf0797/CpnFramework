#!usr/bin/env python3
#coding: utf-8
#cTemplate.py

import sys
import datetime
import os

class cTemplate:
    """文件生成脚本
    使用方法：python cTemplate.py path filename
    脚本只能有3个参数，
    路径path，当前路径可以使用/或\，其他路径一定要以非/或\开头，否则生成不了
    filename根据需要选取"""
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __fileName = ''
    __sourceName = ''
    __headerName = ''
    __originPath = ''
    __filePath = ''
    __timeFormatFull = datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S')
    __timeFormatShort = datetime.datetime.now().strftime('%y%m%d')
    __fileComments = {'@copyright':':Copyright(C), 2019, pxf, person.',
                      '@file':':',
                      '@author':':pxf',
                      '@version':':v1.0',
                      '@date':':'+__timeFormatFull,
                      '@brief':':',
                      '@others':':',
                      '@history':':'+__timeFormatShort+' pxf 初次建立',
    }# 私有变量
    fileComments2 = {'Copyright': ': Copyright(C), 2019, pxf, person.',
                      'File name':': ',
                      'Author':': pxf',
                      'Version':': v1.0',
                      'Created on':': '+__timeFormatFull,
                      'Description':': ',
                      'Others':': ',
                      'History':': '+__timeFormatShort+' pxf 初次建立',
    }# 块变量
    __functionComments = {'@function':':',
                      '@description':':',
                      '@input':':',
                      '@output':':',
                      '@calls':':',
                      '@calledBy':':',
                      '@others':':',
    }
    functionComments2 = {'名称':': 无',
                      '输入':': 无',
                      '输出':': 无',
                      '其他':': 无',
    }

    __fCommentsOrder = ('@copyright','@file','@author','@version','@date','@brief','@others','@history')
    __fCommentsOrder2 = ('Copyright','File name','Author','Version','Created on','Description','Others','History')
    __funcCommentsOrder = ('@function','@description','@input','@output','@calls','@calledBy','@others')
    __funcCommentsOrder2 = ('名称','输入','输出','其他')
    
    __CpnErrCfgHeaderPath = 'cpnBasics/CpnErr/CpnErrCfg.h'

    def __init__(self,sys_args):
        """根据输入参数初始化参数

        主要功能：
        1.生成文件名称
        2.生成文件路径"""
        if sys_args[1] != '/' and sys_args[1] != '\\':
            self.__filePath = sys_args[1]
        else:
            self.__filePath = ''
        self.__originPath = os.getcwd()
        self.__fileName = sys_args[2]
        self.__sourceName = sys_args[2] + ".c"
        self.__headerName = sys_args[2] + '.h'


    #========================================================
    # 文件基础生成函数
    #--------------------------------------------------------
    def generateFilePath(self):
        """生成文件存放路径"""
        if self.__filePath != '':
            if not os.path.exists(self.__filePath):
                os.makedirs(self.__filePath)
            os.chdir(self.__filePath)
    
    def backupOriginPath(self):
        """回退原始路径"""
        if self.__originPath != '':
            os.chdir(self.__originPath)
    
    def generateFileHeadComment(self,name):
        """生成文件头注释"""
        #set filename for every file generate
        self.__fileComments['@file'] = ':'+name
        comments = ('/**************************************************************************\n')
        #find max length of string
        maxLen = 0
        for s in self.__fCommentsOrder:
            if(len(s) > maxLen):
                maxLen = len(s)
        #align space generate line
        for k in self.__fCommentsOrder:
            alignSpaceAmount = maxLen - len(k) + 4
            alignSpace = alignSpaceAmount * ' '
            comments += ('* '+ k + alignSpace + self.__fileComments[k] + '\n')
        comments += ('***************************************************************************/\n\n')
        return comments
        
    def generateFileHeadComment2(self,name):
        """生成文件头注释"""
        #set filename for every file generate
        self.fileComments2['File name'] = ': '+name
        comments = ('/**************************************************************************\n')
        #find max length of string
        maxLen = 0
        for s in self.__fCommentsOrder2:
            if(len(s) > maxLen):
                maxLen = len(s)
        #align space generate line
        for k in self.__fCommentsOrder2:
            alignSpaceAmount = maxLen - len(k) + 2
            alignSpace = alignSpaceAmount * ' '
            comments += ('* '+ k + alignSpace + self.fileComments2[k] + '\n')
        comments += ('***************************************************************************/\n\n')
        return comments

    def generateFileEndComment(self):
        """生成文件尾注释"""
        return ("/**************************** Copyright(C) pxf ****************************/\n")

    def generateFunctionComment(self,name):
        """生成函数头注释"""
        #set function name for every function generate
        self.__functionComments['@function'] = ':'+name
        comments = ('/***********************************************************\n')
        #find max length of string
        maxLen = 0
        for s in self.__funcCommentsOrder:
            if(len(s) > maxLen):
                maxLen = len(s)
        #align space generate line
        for k in self.__funcCommentsOrder:
            alignSpaceAmount = maxLen - len(k) + 4
            alignSpace = alignSpaceAmount * ' '
            comments += ('* '+ k + alignSpace + self.__functionComments[k] + '\n')
        comments += ('***********************************************************/\n')
        return comments

    def generateFunctionComment2(self,name,input,output,others):
        """生成函数头注释类型2"""
        #set function name for every function generate
        self.functionComments2['名称'] = ': '+name
        self.functionComments2['输入'] = ': '+input
        self.functionComments2['输出'] = ': '+output
        self.functionComments2['其他'] = ': '+others
        comments = ('')
        #find max length of string
        maxLen = 0
        for s in self.__funcCommentsOrder2:
            if(len(s) > maxLen):
                maxLen = len(s)
        #align space generate line
        for k in self.__funcCommentsOrder2:
            alignSpaceAmount = maxLen - len(k) + 1
            alignSpace = alignSpaceAmount * ' '
            if(k == '名称'):
                comments += ('/*'+ k + alignSpace + self.functionComments2[k] + '\n')
            else:
                comments += ('* '+ k + alignSpace + self.functionComments2[k] + '\n')
        comments += ('***********************************************/\n')
        return comments
    
    def generateCpnConfigParams(self):
        """成生组件配置参数"""
        comments = ('/***********************************************************\n')
        comments += ('* 配置参数\n')
        comments += ('***********************************************************/\n')
        comments += ('/*%s错误上报ID，需要在CpnErrCfg.h文件内进行注册\n' %self.__fileName)
        comments += ('***********************************************/\n')
        maxLen = len('#define %s_ERR_ID' %self.__fileName.upper())
        if(maxLen > 40):
            maxLen = maxLen + 1
        else:
            maxLen = 40
        alignSpaceAmount = maxLen - len('#define %s_ERR_ID' %self.__fileName.upper())
        comments += ('//#define %s_ERR_ID' %self.__fileName.upper())
        comments += alignSpaceAmount * ' '
        comments += ('0U    /* %s组件报错配置ID */\n' %self.__fileName)
        return comments
    #========================================================
    
    
    #========================================================
    # 模板生成源文件及头文件控制函数
    #--------------------------------------------------------
    def createSource(self):
        """生成源文件"""
        fh = open(self.__sourceName,mode = 'w',encoding=self.__encoding)
        cm = self.generateFileHeadComment2(self.__sourceName)
        cm += ("/*头文件包含*/\n")
        cm += ("#include \"./%s\"\n" %self.__headerName) 
        cm += ("\n"*1)
        cm += self.generateFunctionComment2(self.__fileName+'()','无','无','无')
        cm += ("void %s(void){\n}\n" %self.__fileName)
        cm += ("\n"*1)
        cm += self.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createHeader(self):
        """生成头文件"""
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        cm = self.generateFileHeadComment2(self.__headerName)
        cm += "#ifndef %s_H_\n" %self.__fileName.upper()
        cm += "#define %s_H_\n" %self.__fileName.upper()
        cm += ("\n"*1)
        cm += ("/*头文件包含*/\n")
        cm += ("\n"*1)
        cm += self.generateFunctionComment2(self.__fileName+'()','无','无','无')
        cm += ("void %s(void);\n" %self.__fileName)
        cm += ("\n"*1)
        cm += "#endif /*%s_H_*/\n\n" %self.__fileName.upper()
        cm += self.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createCpnCfgHeader(self):
        """生成头文件"""
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        cm = self.generateFileHeadComment2(self.__headerName)
        cm += "#ifndef %s_H_\n" %self.__fileName.upper()
        cm += "#define %s_H_\n" %self.__fileName.upper()
        cm += ("\n"*1)
        cm += ("/*头文件包含*/\n")
        if self.__filePath != '':
            refPath = '../'*len(self.__filePath.split('/'))
        else:
            refPath = './'
        cm += ('#include \"'+refPath+self.__CpnErrCfgHeaderPath+'\"\n') 
        cm += ("\n"*1)
        cm += self.generateCpnConfigParams()
        cm += ("\n"*1)
        cm += "#endif /*%s_H_*/\n\n" %self.__fileName.upper()
        cm += self.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createTemplate(self):
        """模板生成"""
        self.generateFilePath()
        self.createSource()
        self.createHeader()
        self.backupOriginPath()
        
    #========================================================

if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.stderr.write("please input corret parameter !!!")
    else:
        ct = cTemplate(sys.argv)
        ct.createTemplate()
        