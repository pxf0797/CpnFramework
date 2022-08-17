#!usr/bin/env python3
#coding: utf-8
#ClassTemplate.py

import sys
import datetime
import os
sys.path.append(os.getcwd())
import CTemplate

class ClassTemplate:
    """ files generate shell
    how to use: python ClassTemplate.py path className func_list
    shell need at least 4 paramters,
    path, file path can use \/ or \\, other file path should not begain with \/ and(or) \\, otherwise files can not be generated.
    className, className can be defined by yourself.
    func_list is multy parameter, you need configure at least one function. """
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __fileName = ''
    __sourceName = ''
    __headerName = ''
    __filePath = ''
    __func_list = []
    __cTemp = ''
    __OopcHeaderPath = 'Oopc.h'
    __StandTypeHeaderPath = 'StandType.h'

    def __init__(self,sys_args):
        """ according input to initial

        main function:
        1.generate file name
        2.generate file path
        3.generate function list """
        if sys_args[1] != '/' and sys_args[1] != '\\':
            self.__filePath = sys_args[1]
        else:
            self.__filePath = ''
        self.__fileName = sys_args[2]
        self.__sourceName = sys_args[2] + ".c"
        self.__headerName = sys_args[2] + '.h'
        self.__func_list = sys_args[3:]
        self.__cTemp = CTemplate.CTemplate(sys_args[0:3])

    #========================================================
    # class specific generate functions
    #--------------------------------------------------------
    def creatDatasDeclaration(self):
        """ data type declaration """
        comments = ('/***********************************************************\n')
        comments += (' * Data type declaration.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Data declaration.\n')
        comments += (' **********************************************/\n')
        comments += ('/* typedef struct{\n')
        comments += ('    uint16 id;\n')
        comments += ('    uint16 code;\n')
        comments += ('} tsErrCode;\n */\n')
        comments += ('/* TODO */\n')
        comments += ('/* Data reference.\n')
        comments += (' **********************************************/\n')
        comments += ('/* TODO */\n')
        return comments

    def creatDatasDefinition(self):
        """ data type definition """
        comments = ('/***********************************************************\n')
        comments += (' * Data type definition.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Data definition.\n')
        comments += (' **********************************************/\n')
        comments += ('/* TODO */\n')
        return comments

    def creatInterfaceDeclaration(self):
        """ interface declaration """
        comments = ('/***********************************************************\n')
        comments += (' * Interface definition.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Interface declaration\n')
        comments += (' **********************************************/\n')
        comments += ('//INF(get){\n//  uint16(*get)(void);\n//};\n')
        comments += ('/* TODO */\n')
        return comments

    def creatClassDeclaration(self):
        """ class declaration """
        comments = ('/***********************************************************\n')
        comments += (' * %s class definition.\n' %self.__fileName)
        comments += (' **********************************************************/\n')
        comments += ('/* %s class declaration.\n' %self.__fileName)
        comments += (' **********************************************/\n')
        comments += ('CL(%s){\n' %self.__fileName)
        comments += ('    h%s self;\n    h%s (*init)(h%s cthis);\n' %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('\n'*1)
        comments += ('    /* %s class parameters. */\n' %self.__fileName)
        comments += ('    /* TODO */\n')
        comments += ('\n'*1)
        comments += ('    /* %s class functions. */\n' %self.__fileName)
        for func in self.__func_list:
            comments += ('    void (*%s)(h%s cthis);\n' %(func,self.__fileName))
        comments += ('    /* TODO */\n')
        comments += ('};\n')
        return comments
    #========================================================


    #========================================================
    # functions for generate source and head files.
    #--------------------------------------------------------
    def createSource(self):
        """ generate source files """
        fh = open(self.__sourceName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription(self.__fileName+' class functions definition source file.')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__sourceName)
        cm += ("/* Include head files. */\n")
        cm += ("#include \"%s\"\n" %self.__headerName)
        cm += ('\n'*1)
        cm += self.creatDatasDefinition()
        cm += ("\n"*1)
        cm += ('/***********************************************************\n')
        cm += (' * %s class definition.\n' %self.__fileName)
        cm += (' **********************************************************/\n')
        for func in self.__func_list:
            cm += self.__cTemp.generateFunctionCommentUsed(self.__fileName+'_'+func+'('+'h'+self.__fileName+' cthis)','cthis - '+self.__fileName+' class pointer',' ',self.__fileName+' class function.')
            cm += ('void %s_%s(h%s cthis){\n' %(self.__fileName,func,self.__fileName))
            cm += ('    /* TODO */\n}\n\n')
        cm += self.__cTemp.generateFunctionCommentUsed('h'+self.__fileName+' '+self.__fileName+'_init('+'h'+self.__fileName+' cthis)','cthis - '+self.__fileName+' class pointer','h'+self.__fileName+' - cthis/OOPC_NULL',self.__fileName+' class initial function.')
        cm += ('h%s %s_init(h%s cthis){\n' %(self.__fileName,self.__fileName,self.__fileName))
        cm += ('    h%s retRes = cthis;\n\n' %self.__fileName)
        cm += ('    do{\n')
        cm += ('        /* specific failure detected */\n')
        cm += ('        /*\n        if(condition){\n            break;\n        }\n        */\n')
        cm += ('        /* Configure functions. */\n        //cthis->%s = %s_%s;\n        /* TODO */\n\n' %(self.__func_list[0],self.__fileName,self.__func_list[0]))
        cm += ('        /* Configure parameters. */\n')
        cm += ('        /* TODO */\n')
        cm += ('    }while(0);\n')
        cm += ('    return retRes;\n}\n\n')
        cm += self.__cTemp.generateFunctionCommentUsed('h'+self.__fileName+' '+self.__fileName+'_ctor('+'h'+self.__fileName+' cthis)','cthis - '+self.__fileName+' class pointer','h'+self.__fileName+' - cthis/OOPC_NULL',self.__fileName+' class constructor.')
        cm += ('CC(%s){\n' %self.__fileName)
        cm += ('    h%s retRes = cthis;\n\n' %self.__fileName)
        cm += ('    do{\n')
        cm += ('        /* specific failure detected */\n')
        cm += ('        /*\n        if(condition){\n            break;\n        }\n        */\n')
        cm += ('        cthis->init = %s_init;\n' %self.__fileName)
        for func in self.__func_list:
            cm += ('        cthis->%s = %s_%s;\n' %(func,self.__fileName,func))
        cm += ('        /* TODO */\n\n')
        cm += ('        /* Configure parameters. */\n')
        cm += ('        /* TODO */\n')
        cm += ('    }while(0);\n')
        cm += ('    return retRes;\n}\n\n')
        cm += self.__cTemp.generateFunctionCommentUsed('h'+self.__fileName+' '+self.__fileName+'_dtor('+'h'+self.__fileName+' cthis)','cthis - '+self.__fileName+' class pointer','OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE',self.__fileName+' class destructor.')
        cm += ('CD(%s){\n    return OOPC_TRUE;\n}' %self.__fileName)
        cm += ('\n'*2)
        cm += self.__cTemp.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createHeader(self):
        """ generate head files """
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription(self.__fileName+' class and interface declaration file.')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__headerName)
        cm += "#ifndef %s_H_\n" %self.__fileName.upper()
        cm += "#define %s_H_\n" %self.__fileName.upper()
        cm += ("\n/* Include head files. */\n")
        #if self.__filePath != '':
        #    refPath = '../'*len(self.__filePath.split('/'))
        #else:
        #    refPath = './'
        refPath = ''
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
        """ generate files """
        self.__cTemp.generateFilePath()
        self.createSource()
        self.createHeader()
        self.__cTemp.backupOriginPath()

    #========================================================

if __name__ == '__main__':
    if len(sys.argv) <= 3:
        sys.stderr.write("please input no less than 4 parameter !!!")
    else:
        ct = ClassTemplate(sys.argv)
        ct.createTemplate()
