#!usr/bin/env python3
#coding: utf-8
#classTemplate.py

import sys
import datetime
import os
sys.path.append(os.getcwd())
import cTemplate

class classTemplate:
    """文件生成脚本
    使用方法：python classTemplate.py path className func_list
    脚本至少需要4个参数，
    路径path，当前路径可以使用/或\，其他路径一定要以非/或\开头，否则生成不了
    className根据需要选取
    func_list是多个参数，目前配置类时至少需要给定1个功能函数"""
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __fileName = ''
    __sourceName = ''
    __headerName = ''
    __filePath = ''
    __func_list = []
    __cTemp = ''
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
        self.__cTemp = cTemplate.cTemplate(sys_args[0:3])
        
    #========================================================
    # 类专用生成函数
    #--------------------------------------------------------
    def creatDatasDeclaration(self):
        """数据类型声明"""
        comments = ('/***********************************************************\n')
        comments += ('* 数据类型定义\n')
        comments += ('***********************************************************/\n')
        comments += ('/*数据声明\n')
        comments += ('***********************************************/\n')
        comments += ('//typedef struct{\n')
        comments += ('//    uint16 id;\n')
        comments += ('//    uint16 code;\n')
        comments += ('//} tErrCode;\n')
        comments += ('//TODO\n')
        comments += ('/*数据引用\n')
        comments += ('***********************************************/\n')
        comments += ('//TODO\n')
        return comments
        
    def creatDatasDefinition(self):
        """数据类型定义"""
        comments = ('/***********************************************************\n')
        comments += ('* 数据类型定义\n')
        comments += ('***********************************************************/\n')
        comments += ('/*数据定义\n')
        comments += ('***********************************************/\n')
        comments += ('//TODO\n')
        return comments
    
    def creatInterfaceDeclaration(self):
        """接口声明"""
        comments = ('/***********************************************************\n')
        comments += ('* 接口定义\n')
        comments += ('***********************************************************/\n')
        comments += ('/*接口声明\n')
        comments += ('***********************************************/\n')
        comments += ('//INF(get){\n//  uint16(*get)(void);\n//};\n')
        comments += ('//TODO\n')
        return comments
    
    def creatClassDeclaration(self):
        """类声明"""
        comments = ('/***********************************************************\n')
        comments += ('* %s类定义\n' %self.__fileName)
        comments += ('***********************************************************/\n')
        comments += ('/*%s类声明\n' %self.__fileName)
        comments += ('***********************************************/\n')
        comments += ('CL(%s){\n' %self.__fileName)
        comments += ('    h%s self;\n    h%s (*init)(h%s cthis);\n' %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('\n'*1)
        comments += ('    // %s类参数\n' %self.__fileName)
        comments += ('    //TODO\n')
        comments += ('\n'*1)
        #comments += ('    // %s类功能函数\n    void (*func)(h%s cthis);\n' %(self.__fileName,self.__fileName))
        comments += ('    // %s类功能函数\n' %self.__fileName)
        for func in self.__func_list:
            comments += ('    void (*%s)(h%s cthis);\n' %(func,self.__fileName))
        comments += ('    //TODO\n')
        comments += ('};\n')
        return comments
    #========================================================
    
    
    #========================================================
    # 模板生成源文件及头文件控制函数
    #--------------------------------------------------------
    def createSource(self):
        """生成源文件"""
        fh = open(self.__sourceName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription(self.__fileName+'类各功能函数定义源文件')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__sourceName)
        cm += ("/*头文件包含*/\n")
        cm += ("#include \"./%s\"\n" %self.__headerName) 
        cm += ('\n'*1)
        cm += self.creatDatasDefinition()
        cm += ("\n"*1)
        cm += ('/***********************************************************\n')
        cm += ('* %s类定义\n' %self.__fileName)
        cm += ('***********************************************************/\n')
        for func in self.__func_list:
            cm += self.__cTemp.generateFunctionCommentUsed(self.__fileName+'_'+func+'('+'h'+self.__fileName+' cthis)','cthis - '+self.__fileName+'类指针','无',self.__fileName+'类功能函数')
            cm += ('void %s_%s(h%s cthis){\n' %(self.__fileName,func,self.__fileName))
            cm += ('    //TODO\n}\n\n')
        cm += self.__cTemp.generateFunctionCommentUsed('h'+self.__fileName+' '+self.__fileName+'_init('+'h'+self.__fileName+' cthis)','cthis - '+self.__fileName+'类指针','h'+self.__fileName+' - cthis/OOPC_NULL',self.__fileName+'类初始化函数')
        cm += ('h%s %s_init(h%s cthis){\n' %(self.__fileName,self.__fileName,self.__fileName))
        cm += ('    // 功能函数配置\n    //cthis->%s = %s_%s;\n    //TODO\n\n' %(self.__func_list[0],self.__fileName,self.__func_list[0]))
        cm += ('    // 参数配置\n    //TODO\n\n')
        cm += ('    return cthis;\n}\n\n')
        cm += self.__cTemp.generateFunctionCommentUsed('h'+self.__fileName+' '+self.__fileName+'_ctor('+'h'+self.__fileName+' cthis)','cthis - '+self.__fileName+'类指针','h'+self.__fileName+' - cthis/OOPC_NULL',self.__fileName+'类构造函数')
        cm += ('CC(%s){\n' %self.__fileName)
        cm += ('    cthis->init = %s_init;\n' %self.__fileName)
        for func in self.__func_list:
            cm += ('    cthis->%s = %s_%s;\n' %(func,self.__fileName,func))
        cm += ('    //TODO\n\n')
        cm += ('    // 参数配置\n')
        cm += ('    //TODO\n')
        cm += ('    return cthis;\n}\n\n')
        cm += self.__cTemp.generateFunctionCommentUsed('h'+self.__fileName+' '+self.__fileName+'_dtor('+'h'+self.__fileName+' cthis)','cthis - '+self.__fileName+'类指针','OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE',self.__fileName+'类析构函数')
        cm += ('CD(%s){\n    return OOPC_TRUE;\n}' %self.__fileName)
        cm += ('\n'*2)
        cm += self.__cTemp.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createHeader(self):
        """生成头文件"""
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription(self.__fileName+'类及接口声明头文件')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__headerName)
        cm += "#ifndef %s_H_\n" %self.__fileName.upper()
        cm += "#define %s_H_\n" %self.__fileName.upper()
        cm += ("\n/*头文件包含*/\n")
        if self.__filePath != '':
            refPath = '../'*len(self.__filePath.split('/'))
        else:
            refPath = './'
        cm += ('#include \"'+refPath+self.__StandTypeHeaderPath+'\"\n') 
        cm += ('#include \"'+refPath+self.__OopcHeaderPath+'\"\n') 
        cm += ('\n'*1)
        cm += self.__cTemp.generateMacroVersionDeclaration(self.__fileName)
        cm += ('\n'*1)
        cm += self.creatDatasDeclaration()
        cm += ('\n'*1)
        cm += self.creatInterfaceDeclaration()
        cm += ('\n'*1)
        cm += self.creatClassDeclaration()
        cm += ("\n"*1)
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
        ct = classTemplate(sys.argv)
        ct.createTemplate()
        