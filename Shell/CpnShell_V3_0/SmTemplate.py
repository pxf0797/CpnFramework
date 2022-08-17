#!usr/bin/env python3
#coding: utf-8
#SmTemplate.py

import sys
import datetime
import os
sys.path.append(os.getcwd())
import CTemplate

class SmTemplate:
    """ files generate shell
    how to use: python SmTemplate.py path stateMachineName stateList
    shell need at least 4 paramters,
    path, file path can use \/ or \\, other file path should not begain with \/ and(or) \\, otherwise files can not be generated.
    stateMachineName, it can be defined by yourself.
    stateList is multy parameter, you need configure at least one state."""
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __fileName = ''
    __sourceName = ''
    __headerName = ''
    __filePath = ''
    __sta_list = []
    __cTemp = ''
    __SmHeaderPath = 'Sm.h'
    __StandTypeHeaderPath = 'StandType.h'

    def __init__(self,sys_args):
        """ according input to initial

        main function:
        1.generate file name
        2.generate file path
        3.generate state list """
        if sys_args[1] != '/' and sys_args[1] != '\\':
            self.__filePath = sys_args[1]
        else:
            self.__filePath = ''
        self.__fileName = sys_args[2]
        self.__sourceName = sys_args[2] + ".c"
        self.__headerName = sys_args[2] + '.h'
        self.__sta_list = sys_args[3:]
        self.__cTemp = CTemplate.CTemplate(sys_args[0:3])

    #========================================================
    # generate state machine specific functions
    #--------------------------------------------------------
    def generateSmStaList(self):
        """ generate state list """
        #find max length of string
        maxLen = len('#define %s_LIST(_)' %self.__fileName.upper())
        for sta in self.__sta_list:
            sta_len = len('    _(%s, %s)' %(self.__fileName,sta))
            if(sta_len > maxLen):
                maxLen = sta_len
        alignSpaceAmount = maxLen - len('#define %s_LIST(_)' %self.__fileName.upper()) + 4
        alignSpace = alignSpaceAmount * ' '
        comments = ('/* State machine %s state list definition.\n * Note: %s_init undefined in this list, it will be given by default.\n' %(self.__fileName,self.__fileName))
        comments += ('***********************************************/\n')
        comments += ('#define %s_LIST(_)' %self.__fileName.upper())
        comments += alignSpace+'\\\n'
        for sta in self.__sta_list:
            alignSpaceAmount = maxLen - len('    _(%s, %s)' %(self.__fileName,sta)) + 4
            alignSpace = alignSpaceAmount * ' '
            comments += ('    _(%s, %s)' %(self.__fileName,sta))
            comments += alignSpace+'\\\n'
        return comments

    def generateSmDeclaration(self):
        """ generate state machine declaration """
        comments = ('/* State machine %s declaration.\n * It is given state record next, and last state record last. You can added other parameters.\n' %self.__fileName)
        comments += (' **********************************************/\n')
        comments += ('SMDC(%s, %s_LIST){\n' %(self.__fileName,self.__fileName.upper()))
        comments += ('    sta next; /* running state record. */\n')
        comments += ('    sta last; /* last state record. */\n')
        comments += ('    /* TODO */\n};')
        return comments
        
    def generateSmDefine(self):
        """ generate state machine definition"""
        comments = ('/* State machine %s definition.\n * Configure state process functions.\n' %self.__fileName)
        comments += (' **********************************************/\n')
        comments += ('SMDF(%s, %s_LIST);\n' %(self.__fileName,self.__fileName.upper()))
        return comments
        
    def generateSmStaActionDefine(self):
        """ generate state machine state action """
        comments = self.__cTemp.generateFunctionCommentUsed(self.__fileName+'_act_init()',self.__fileName+'Rec - state record pointer',' ','initial state action.')
        comments += ("void %s_act_init(void *%sRec){\n" %(self.__fileName,self.__fileName))
        comments += ("    h%sRec hRec = (h%sRec)%sRec;\n\n" %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('    /* TODO */\n\n')
        comments += ('    hRec->next = %s_sta_init;\n' %self.__fileName)
        comments += ('    hRec->last = %s_sta_init;\n}\n' %self.__fileName)
        comments += ("\n"*1)
        for sta in self.__sta_list:
            comments += self.__cTemp.generateFunctionCommentUsed(self.__fileName+'_act_'+sta+'()',self.__fileName+'Rec - state record pointer',' ','state '+sta+' action.')
            comments += ("void %s_act_%s(void *%sRec){\n" %(self.__fileName,sta,self.__fileName))
            comments += ("    h%sRec hRec = (h%sRec)%sRec;\n\n" %(self.__fileName,self.__fileName,self.__fileName))
            comments += ('    /* TODO */\n\n')
            comments += ('    hRec->next = %s_sta_init;\n' %self.__fileName)
            comments += ('    hRec->last = %s_sta_%s;\n}\n' %(self.__fileName,sta))
            comments += ("\n"*1)
        return comments
        
    def generateSmUseExample(self):
        """ generate state machine use example """
        comments = ('/* State machine %s use example:\n * State machine %s has been defined in SMDF, all you need to do is let it running.\n' %(self.__fileName,self.__fileName))
        comments += ('* There are two operation modes of the state machine: \n * SMR directly driven by the clock and SMRE driven by the custom recording state.\n')
        comments += (' **********************************************\n')
        comments += (' * type SMR\n')
        comments += (' **********************************************\n')
        comments += ('void test(void){\n')
        comments += ('    while(1){SMR(%s);};\n}\n' %self.__fileName)
        comments += (' **********************************************\n')
        comments += (' * type SMRE\n')
        comments += (' **********************************************\n')
        comments += ('void test2(void){\n')
        comments += ('    static %sRec %sRunRec = {%s_sta_init};\n' %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('    while(1){SMRE(%s, %sRunRec);};\n}\n' %(self.__fileName,self.__fileName))
        comments += (' **********************************************/\n')
        return comments
    #========================================================
    
    
    #========================================================
    # template generate source and head files
    #--------------------------------------------------------
    def createSource(self):
        """ generate source files """
        fh = open(self.__sourceName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription('State machine '+self.__fileName+' definition and state action definition.')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__sourceName)
        cm += ("/* Include head files. */\n")
        cm += ("#include \"%s\"\n" %self.__headerName)
        cm += ("\n"*1)
        cm += self.generateSmDefine()
        cm += ("\n"*1)
        cm += self.generateSmStaActionDefine()
        cm += self.__cTemp.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createHeader(self):
        """ generate head files """
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription('State machine '+self.__fileName+' declaration and state machine use cases.')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__headerName)
        cm += "#ifndef %s_H_\n" %self.__fileName.upper()
        cm += "#define %s_H_\n" %self.__fileName.upper()
        cm += ("\n/* Include head files. */\n")
        #if self.__filePath != '':
        #    refPath = '../'*len(self.__filePath.split('/'))
        #else:
        #    refPath = './'
        refPath = ''
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
        """ template generate """
        self.__cTemp.generateFilePath()
        self.createSource()
        self.createHeader()
        self.__cTemp.backupOriginPath()
        
    #========================================================

if __name__ == '__main__':
    if len(sys.argv) <= 3:
        sys.stderr.write("please input no less than 4 parameter !!!")
    else:
        ct = SmTemplate(sys.argv)
        ct.createTemplate()
        