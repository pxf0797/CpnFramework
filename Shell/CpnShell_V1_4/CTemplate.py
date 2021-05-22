#!usr/bin/env python3
#coding: utf-8
#CTemplate.py

import sys
import datetime
import os

class CTemplate:
    """ files generate shell
    how to use: python CTemplate.py path filename
    shell only have 3 parameters,
    path, file path can use \/ or \\, other file path should not begain with \/ and(or) \\, otherwise files can not be generated.
    filename, filename can be defined by yourself. """
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __exchangeCommentType = 2 # 1-comment, 2-comment2, ...
    __fileName = ''
    __sourceName = ''
    __headerName = ''
    __originPath = ''
    __filePath = ''
    __wirteStartColumn = 48
    __timeFormatFull = datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S')
    __timeFormatShort = datetime.datetime.now().strftime('%Y%m%d')#strftime('%y%m%d')
    
    __fileComments = {'@copyright':': Copyright(C), 2021, pxf, person.',
                      '@file':': ',
                      '@author':': pxf',
                      '@version':': v1.0',
                      '@date':': '+__timeFormatFull,
                      '@brief':': ',
                      '@others':': ',
                      '@history':': '+__timeFormatShort+' pxf Initially established.',
    }# private value
    __fCommentsOrder = ('@copyright','@file','@author','@version','@date','@brief','@others','@history')
    
    #fileComments2 = {'Copyright':': Copyright(C), 2021, pxf, person.',
    #                  'File name':': ',
    #                  'Author':': pxf',
    #                  'Version':': v1.0',
    #                  'Created on':': '+__timeFormatFull,
    #                  'Description':': ',
    #                  'Others':': ',
    #                  'History':': '+__timeFormatShort+' pxf Initially established.',
    #}# block value
    __fileComments2 = {'Copyright':': Copyright(C), 2021, pxf, person.',
                      'File name':': ',
                      'Author':': pxf',
                      'Version':': v1.0',
                      'Created on':': '+__timeFormatFull,
                      'Description':': ',
                      'Others':': ',
                      'History':': '+__timeFormatShort+' pxf Initially established.',
    }
    __fCommentsOrder2 = ('Copyright','File name','Author','Version','Created on','Description','Others','History')
    
    __functionComments = {'@function':': ',
                          '@input':': ',
                          '@output':': ',
                          '@calls':': ',
                          '@calledBy':': ',
                          '@others':': ',
    }
    __funcCommentsOrder = ('@function','@input','@output','@calls','@calledBy','@others')
    
    __functionComments2 = {'Function':': ',
                          'Input':': ',
                          'Output':': ',
                          'Others':': ',
    }
    __funcCommentsOrder2 = ('Function','Input','Output','Others')
    
    __fileCommentsUsed=''
    __functionCommentsUsed=''
    __fCommentsOrderUsed=''
    __funcCommentsOrderUsed=''
    
    __CpnErrCfgHeaderPath = 'CpnBasics/CpnErr/CpnErrCfg.h'

    def __init__(self,sys_args):
        """ according input to initial

        main function:
        1.generate file name
        2.generate file path """
        if sys_args[1] != '/' and sys_args[1] != '\\':
            self.__filePath = sys_args[1]
        else:
            self.__filePath = ''
        self.__originPath = os.getcwd()
        self.__fileName = sys_args[2]
        self.__sourceName = sys_args[2] + ".c"
        self.__headerName = sys_args[2] + '.h'
        
        self.changeUsedTemplate()


    #========================================================
    # basic file generate functions
    #--------------------------------------------------------
    def generateFilePath(self):
        """ generate file path. """
        if self.__filePath != '':
            if not os.path.exists(self.__filePath):
                os.makedirs(self.__filePath)
            os.chdir(self.__filePath)
    
    def backupOriginPath(self):
        """ back up to original path. """
        if self.__originPath != '':
            os.chdir(self.__originPath)
    
    def generateFileHeadCommentUsed(self,name):
        """ generate file head comments. """
        #set filename for every file generate
        self.__fileCommentsUsed[self.__fCommentsOrderUsed[1]] = ': '+name
        comments = ('/**************************************************************************\n')
        #find max length of string
        maxLen = 0
        for s in self.__fCommentsOrderUsed:
            if(len(s) > maxLen):
                maxLen = len(s)
        #align space generate line
        for k in self.__fCommentsOrderUsed:
            alignSpaceAmount = maxLen - len(k) + 2
            alignSpace = alignSpaceAmount * ' '
            comments += (' * '+ k + alignSpace + self.__fileCommentsUsed[k] + '\n')
        comments += (' **************************************************************************/\n\n')
        return comments
        
    def updatefCommentUsedDescription(self,desc):
        """ update file head description. """
        # update description every time called
        self.__fileCommentsUsed[self.__fCommentsOrderUsed[5]] = ': '+desc
        

    def generateFileEndComment(self):
        """ generate file end comments. """
        return ("/**************************** Copyright(C) pxf ****************************/\n")
        
    def generateMacroVersionDeclaration(self, name):
        """ generate MACRO VERTION. """
        comments = ('/***********************************************************\n')
        comments += (' * MACRO VERTION\n')
        comments += (' **********************************************************/\n')
        define_macro = ('#define %s_MACRO_VERSION' %name.upper())
        define_macro_len = len(define_macro)
        comments += define_macro
        if(define_macro_len >= self.__wirteStartColumn):
            comments += ' '
        else:
            comments += (self.__wirteStartColumn-define_macro_len)*' '
        comments += ('0xC01D00    /* C represent V,D represent ., Current version is V1.00 */\n')
        return comments

    def generateFunctionCommentUsed(self,name,input,output,others):
        """ generate function head description. """
        #set function name for every function generate
        self.__functionCommentsUsed[self.__funcCommentsOrderUsed[0]] = ': '+name
        self.__functionCommentsUsed[self.__funcCommentsOrderUsed[1]] = ': '+input
        self.__functionCommentsUsed[self.__funcCommentsOrderUsed[2]] = ': '+output
        self.__functionCommentsUsed[self.__funcCommentsOrderUsed[-1]] = ': '+others
        comments = ('')
        #find max length of string
        maxLen = 0
        for s in self.__funcCommentsOrderUsed:
            if(len(s) > maxLen):
                maxLen = len(s)
        #align space generate line
        for k in self.__funcCommentsOrderUsed:
            alignSpaceAmount = maxLen - len(k) + 1
            alignSpace = alignSpaceAmount * ' '
            if((k == 'Function')or(k == '@function')):
                comments += ('/* '+ k + alignSpace + self.__functionCommentsUsed[k] + '\n')
            else:
                comments += (' * '+ k + alignSpace + self.__functionCommentsUsed[k] + '\n')
        comments += (' **********************************************/\n')
        return comments
    
    def generateCpnConfigParams(self):
        """ generate component configure parameters. """
        comments = ('/***********************************************************\n')
        comments += (' * Configure parameters.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* %s error report ID need to be registered in file CpnErrCfg.h.\n' %self.__fileName)
        comments += (' **********************************************/\n')
        maxLen = len('#define %s_ERR_ID' %self.__fileName.upper())
        if(maxLen > self.__wirteStartColumn):
            maxLen = maxLen + 1
        else:
            maxLen = self.__wirteStartColumn
        alignSpaceAmount = maxLen - len('#define %s_ERR_ID' %self.__fileName.upper())
        comments += ('//#define %s_ERR_ID' %self.__fileName.upper())
        comments += alignSpaceAmount * ' '
        comments += ('0U    /* %s component error report ID. */\n' %self.__fileName)
        return comments
        
    def generateCpnConfigErrorCode(self):
        """ generate component configure error code. """
        comments = ('/***********************************************************\n')
        comments += (' * Error classify.\n')
        comments += (' **********************************************************/\n')
        comments += ('typedef enum{\n    ERR_%s_FUNC,\n} TE_%s_ERR_CLASSIFY;\n' %(self.__fileName.upper(),self.__fileName.upper()))
        comments += (' * Error code.\n')
        comments += (' **********************************************************/\n')
        maxLen = len('#define %s_ERR_CODE' %self.__fileName.upper())
        if(maxLen > self.__wirteStartColumn):
            maxLen = maxLen + 1
        else:
            maxLen = self.__wirteStartColumn
        alignSpaceAmount = maxLen - len('#define %s_ERR_CODE' %self.__fileName.upper())
        comments += ('#define %s_ERR_CODE' %self.__fileName.upper())
        comments += alignSpaceAmount * ' '
        comments += ('(ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_%s_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Error code. */\n' %self.__fileName.upper())
        return comments
    #========================================================
    
    
    #========================================================
    # template use function for exchange.
    #--------------------------------------------------------
    def changeUsedTemplate(self):
        """ exchange template. """
        if (self.__exchangeCommentType == 1):
            self.__fileCommentsUsed=self.__fileComments
            self.__functionCommentsUsed=self.__functionComments
            self.__fCommentsOrderUsed=self.__fCommentsOrder
            self.__funcCommentsOrderUsed=self.__funcCommentsOrder
        elif (self.__exchangeCommentType == 2):
            self.__fileCommentsUsed=self.__fileComments2
            self.__functionCommentsUsed=self.__functionComments2
            self.__fCommentsOrderUsed=self.__fCommentsOrder2
            self.__funcCommentsOrderUsed=self.__funcCommentsOrder2
        else:
            self.__fileCommentsUsed=self.__fileComments
            self.__functionCommentsUsed=self.__functionComments
            self.__fCommentsOrderUsed=self.__fCommentsOrder
            self.__funcCommentsOrderUsed=self.__funcCommentsOrder
    
    #========================================================
    
    
    #========================================================
    # functions for generate source and head files.
    #--------------------------------------------------------
    def createSource(self):
        """ generate source file. """
        fh = open(self.__sourceName,mode = 'w',encoding=self.__encoding)
        cm = self.generateFileHeadCommentUsed(self.__sourceName)
        cm += ("/* Include head files. */\n")
        cm += ("#include \"./%s\"\n" %self.__headerName) 
        cm += ("\n"*1)
        cm += self.generateFunctionCommentUsed(self.__fileName+'()',' ',' ',' ')
        cm += ("void %s(void){\n}\n" %self.__fileName)
        cm += ("\n"*1)
        cm += self.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createHeader(self):
        """ generate head files. """
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        cm = self.generateFileHeadCommentUsed(self.__headerName)
        cm += "#ifndef %s_H_\n" %self.__fileName.upper()
        cm += "#define %s_H_\n" %self.__fileName.upper()
        cm += ("\n"*1)
        cm += ("/* Include head files. */\n")
        cm += ("\n"*1)
        cm += self.generateMacroVersionDeclaration(self.__fileName)
        cm += ("\n"*1)
        cm += self.generateFunctionCommentUsed(self.__fileName+'()',' ',' ',' ')
        cm += ("void %s(void);\n" %self.__fileName)
        cm += ("\n"*1)
        cm += "#endif /*%s_H_*/\n\n" %self.__fileName.upper()
        cm += self.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createCpnCfgHeader(self):
        """ generate head files. """
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        cm = self.generateFileHeadCommentUsed(self.__headerName)
        cm += "#ifndef %s_H_\n" %self.__fileName.upper()
        cm += "#define %s_H_\n" %self.__fileName.upper()
        cm += ("\n"*1)
        cm += ("/* Include head files. */\n")
        if self.__filePath != '':
            refPath = '../'*len(self.__filePath.split('/'))
        else:
            refPath = './'
        cm += ('#include \"'+refPath+self.__CpnErrCfgHeaderPath+'\"\n') 
        cm += ("\n"*1)
        cm += self.generateCpnConfigParams()
        cm += ("\n"*1)
        cm += self.generateCpnConfigErrorCode()
        cm += ("\n"*1)
        cm += "#endif /*%s_H_*/\n\n" %self.__fileName.upper()
        cm += self.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createTemplate(self):
        """ template generates """
        self.generateFilePath()
        self.createSource()
        self.createHeader()
        self.backupOriginPath()
        
    #========================================================

if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.stderr.write("please input corret parameter !!!")
    else:
        ct = CTemplate(sys.argv)
        ct.createTemplate()
        