#!usr/bin/env python3
#coding: utf-8
#smTemplate.py

import sys
import datetime
import os
sys.path.append(os.getcwd())
import cTemplate

class smTemplate:
    """文件生成脚本
    使用方法：python smTemplate.py path stateMachineName stateList
    脚本至少需要4个参数，
    路径path，当前路径可以使用/或\，其他路径一定要以非/或\开头，否则生成不了
    状态机名称stateMachineName根据需要选取
    stateList是多个参数，目前配置状态机时至少需要给定1个状态"""
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __fileName = ''
    __sourceName = ''
    __headerName = ''
    __filePath = ''
    __sta_list = []
    __cTemp = ''
    __SmHeaderPath = 'cpnBasics/sm/sm.h'
    __StandTypeHeaderPath = 'cpnBasics/standType/standType.h'

    def __init__(self,sys_args):
        """根据输入参数初始化参数

        主要功能：
        1.生成文件名称
        2.生成文件路径
        3.生成状态列表"""
        if sys_args[1] != '/' and sys_args[1] != '\\':
            self.__filePath = sys_args[1]
        else:
            self.__filePath = ''
        self.__fileName = sys_args[2]
        self.__sourceName = sys_args[2] + ".c"
        self.__headerName = sys_args[2] + '.h'
        self.__sta_list = sys_args[3:]
        self.__cTemp = cTemplate.cTemplate(sys_args[0:3])
        
    #========================================================
    # 状态机专用生成函数
    #--------------------------------------------------------
    def generateSmStaList(self):
        """生成状态机状态序列"""
        #find max length of string
        maxLen = len('#define %s_LIST(_)' %self.__fileName.upper())
        for sta in self.__sta_list:
            sta_len = len('    _(%s, %s)' %(self.__fileName,sta))
            if(sta_len > maxLen):
                maxLen = sta_len
        alignSpaceAmount = maxLen - len('#define %s_LIST(_)' %self.__fileName.upper()) + 4
        alignSpace = alignSpaceAmount * ' '
        comments = ('/*状态机%s状态序列定义\n* 注意其中%s_init,%s_default未在此定义，默认会给出\n' %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('***********************************************/\n')
        comments += ('#define %s_LIST(_)' %self.__fileName.upper())
        comments += alignSpace+'\\\n'
        for sta in self.__sta_list:
            alignSpaceAmount = maxLen - len('    _(%s, %s)' %(self.__fileName,sta)) + 4
            alignSpace = alignSpaceAmount * ' '
            #if(sta == self.__sta_list[-1]):
            #    comments += ('    _(%s, %s)\n' %(self.__fileName,sta))
            #else:
            #    comments += ('    _(%s, %s)' %(self.__fileName,sta))
            #    comments += alignSpace+'\\\n'
            comments += ('    _(%s, %s)' %(self.__fileName,sta))
            comments += alignSpace+'\\\n'
        #comments += ("\n"*1)
        return comments
        
    def generateSmDeclaration(self):
        """生成状态机声明"""
        comments = ('/*状态机%s声明\n* 已给出状态记录next,及上一状态last，其他参数需自行添加\n' %self.__fileName)
        comments += ('***********************************************/\n')
        comments += ('SMDC(%s, %s_LIST){\n' %(self.__fileName,self.__fileName.upper()))
        comments += ('    sta next; // 运行状态记录\n')
        comments += ('    sta last; // 上一状态记录\n')
        comments += ('    // TODO\n};')
        return comments
        
    def generateSmDefine(self):
        """生成状态机定义"""
        comments = ('/*状态机%s定义\n* 配置状态机相关处理状态\n' %self.__fileName)
        comments += ('***********************************************/\n')
        comments += ('SMDF(%s, %s_LIST);\n' %(self.__fileName,self.__fileName.upper()))
        return comments
        
    def generateSmStaActionDefine(self):
        """生成状态机各状态操作定义"""
        comments = self.__cTemp.generateFunctionCommentUsed(self.__fileName+'_act_init()',self.__fileName+'Rec - 状态记录参数指针','无','初始状态操作函数')
        comments += ("void %s_act_init(void *%sRec){\n" %(self.__fileName,self.__fileName))
        comments += ("    h%sRec hRec = (h%sRec)%sRec;\n\n" %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('    // TODO\n\n')
        comments += ('    hRec->next = %s_sta_init;\n' %self.__fileName)
        comments += ('    hRec->last = %s_sta_init;\n}\n' %self.__fileName)
        comments += ("\n"*1)
        #comments += self.__cTemp.generateFunctionCommentUsed(self.__fileName+'_act_default()',self.__fileName+'Rec - 状态记录参数指针','无','默认状态操作函数')
        #comments += ("void %s_act_default(void *%sRec){\n" %(self.__fileName,self.__fileName))
        #comments += ("    h%sRec hRec = (h%sRec)%sRec;\n\n" %(self.__fileName,self.__fileName,self.__fileName))
        #comments += ('    // TODO\n\n')
        #comments += ('    hRec->next = %s_sta_default;\n' %self.__fileName)
        #comments += ('    hRec->last = %s_sta_default;\n}\n' %self.__fileName)
        #comments += ("\n"*1)
        for sta in self.__sta_list:
            comments += self.__cTemp.generateFunctionCommentUsed(self.__fileName+'_act_'+sta+'()',self.__fileName+'Rec - 状态记录参数指针','无','状态'+sta+'操作函数')
            comments += ("void %s_act_%s(void *%sRec){\n" %(self.__fileName,sta,self.__fileName))
            comments += ("    h%sRec hRec = (h%sRec)%sRec;\n\n" %(self.__fileName,self.__fileName,self.__fileName))
            comments += ('    // TODO\n\n')
            comments += ('    hRec->next = %s_sta_init;\n' %self.__fileName)
            comments += ('    hRec->last = %s_sta_%s;\n}\n' %(self.__fileName,sta))
            comments += ("\n"*1)
        return comments
        
    def generateSmUseExample(self):
        """生成状态机使用示例"""
        comments = ('/*状态机%s使用示例：\n* 当前状态机已在SMDF中定义出实体%s，需要做的只是让其运行起来\n' %(self.__fileName,self.__fileName))
        comments += ('* 状态机运行方式有两种直接给时钟驱动的SMR和使用自定义记录状态后进驱动的SMRE\n')
        comments += ('***********************************************\n')
        comments += ('* SMR方式\n')
        comments += ('***********************************************\n')
        comments += ('void test(void){\n')
        comments += ('    while(1){SMR(%s);};\n}\n' %self.__fileName)
        comments += ('***********************************************\n')
        comments += ('* SMRE方式\n')
        comments += ('***********************************************\n')
        comments += ('void test2(void){\n')
        comments += ('    static %sRec %sRunRec = {%s_sta_init};\n' %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('    while(1){SMRE(%s, %sRunRec);};\n}\n' %(self.__fileName,self.__fileName))
        comments += ('***********************************************/\n')
        return comments
    #========================================================
    
    
    #========================================================
    # 模板生成源文件及头文件控制函数
    #--------------------------------------------------------
    def createSource(self):
        """生成源文件"""
        fh = open(self.__sourceName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription('状态机'+self.__fileName+'定义及各状态动作定义源文件')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__sourceName)
        cm += ("/*头文件包含*/\n")
        cm += ("#include \"./%s\"\n" %self.__headerName)
        cm += ("\n"*1)
        cm += self.generateSmDefine()
        cm += ("\n"*1)
        cm += self.generateSmStaActionDefine()
        cm += self.__cTemp.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createHeader(self):
        """生成头文件"""
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription('状态机'+self.__fileName+'声明及状态机使用示例头文件')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__headerName)
        cm += "#ifndef %s_H_\n" %self.__fileName.upper()
        cm += "#define %s_H_\n" %self.__fileName.upper()
        cm += ("\n/*头文件包含*/\n")
        if self.__filePath != '':
            refPath = '../'*len(self.__filePath.split('/'))
        else:
            refPath = './'
        #cm += ('#include \"'+refPath+self.__StandTypeHeaderPath+'\"\n') 
        cm += ('#include \"'+refPath+self.__SmHeaderPath+'\"\n') 
        cm += ("\n"*1)
        cm += self.__cTemp.generateMacroVersionDeclaration(self.__fileName)
        cm += ("\n"*1)
        cm += self.generateSmUseExample()
        cm += ("\n"*2)
        cm += self.generateSmStaList()
        cm += ("\n"*2)
        cm += self.generateSmDeclaration()
        cm += ("\n"*2)
        cm += "#endif /*%s_H_*/\n\n" %self.__fileName.upper()
        cm += self.__cTemp.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createTemplate(self):
        """模板生成"""
        self.__cTemp.generateFilePath()
        self.createSource()
        self.createHeader()
        self.__cTemp.backupOriginPath()
        
    #========================================================

if __name__ == '__main__':
    if len(sys.argv) <= 3:
        sys.stderr.write("please input no less than 4 parameter !!!")
    else:
        ct = smTemplate(sys.argv)
        ct.createTemplate()
        