#!usr/bin/env python3
#coding: utf-8
#CpnTemplate.py  component

import sys
import datetime
import os
sys.path.append(os.getcwd())
import CTemplate
import ClassTemplate

class CpnTemplate:
    """ files generate shell
    how to use: python CpnTemplate.py path cpnName func_list
    shell need at least 4 paramters,
    path, file path can use \/ or \\, other file path should not begain with \/ and(or) \\, otherwise files can not be generated.
    cpnName, cpnName can be defined by yourself.
    func_list is multy parameter, you need configure at least one function.
    Functions are also divided into oopc function and serv signal function, serv signal function function must start with \/ or \\. """
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __fileName = ''
    __sourceName = ''
    __headerName = ''
    __ClassHeaderName = ''
    __filePath = ''
    __serv_func_list = []
    __oopc_func_list = []
    __cTemp_args = ''
    __classTemp_args = ''
    __cpnTemp_args = ''
    __cTemp = ''
    __classTemp = ''
    #__OopcHeaderPath = 'Oopc/Oopc.h'
    #__StandTypeHeaderPath = 'StandType/StandType.h'
    __RteHeaderPath = 'Rte.h'
    __RteSigsHeaderPath = 'RteSigs.h'
    __AlignWidth = 80

    __RteSigsConfigListPath = './CpnRte/RteSigs'
    __RteSigsConfigListHeaderFile = 'RteSigsConfigList.h'
    __CpnSchPath = './CpnBasics/CpnSch'
    __CpnSchSigsHeaderFile = 'CpnSchSigs.h'
    __CpnSchSigsSourceFile = 'CpnSchSigs.c'
    __CpnSchSigsConfigFile = 'CpnSchCfg.h'
    __CpnErrPath = './CpnBasics/CpnErr'
    __CpnSchErrConfigFile = 'CpnErrCfg.h'

    __RteSigsConfigListfPath = __RteSigsConfigListPath + '/' + __RteSigsConfigListHeaderFile
    __CpnSchSigsHeaderfPath = __CpnSchPath + '/' + __CpnSchSigsHeaderFile
    __CpnSchSigsSourcefPath = __CpnSchPath + '/' + __CpnSchSigsSourceFile
    __CpnSchSigsConfigfPath = __CpnSchPath + '/' + __CpnSchSigsConfigFile
    __CpnSchErrConfigfPath = __CpnErrPath + '/' + __CpnSchErrConfigFile

    __IncludeHeader = 'Component signals'
    __SigSetList = 'SIGNAL_SET_LIST_RTEASYN(_)'
    __SigGetList = 'SIGNAL_GET_MAP_LIST_RTEASYN(_)'
    __SigServList = 'SIGNAL_SERV_LIST_RTESYN(_)'
    __SigTrigList = 'SIGNAL_TRIG_MAP_LIST_RTESYN(_)'
    __RteSigsConfigList = [__IncludeHeader,__SigSetList,__SigGetList,__SigServList,__SigTrigList]
    __CpnSchSigTrigList = 'SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)'
    __CpnSchInitCpn = 'void trig_CpnSch_inf_initCpn(void)'
    __CpnSchEvent = '/* Event definition.'
    __CpnErrId = '/* Error reporting ID'

    __newRteSigsConfig = []
    __newCpnSchTrigHeader = ''
    __newCpnSchTrigSource = ''
    __newCpnSchTrigConfig = ''
    __newCpnErrIdConfig = ''

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
        self.__sourceName = sys_args[2] + "Sigs.c"
        self.__headerName = sys_args[2] + 'Sigs.h'
        self.__ClassHeaderName = sys_args[2] + '.h'
        #self.__serv_func_list = sys_args[3:]
        for func in sys_args[3:]:
            if(func[0] != '/' and func[0] != '\\'):
                self.__oopc_func_list.append(func)
            else:
                self.__serv_func_list.append(func[1:])
        self.__cTemp_args = sys_args[0:3]
        self.__cTemp_args[2] = sys_args[2]+'Cfg'
        self.__cTemp = CTemplate.CTemplate(self.__cTemp_args)
        self.__classTemp_args = sys_args[0:3] + self.__oopc_func_list
        self.__classTemp = ClassTemplate.ClassTemplate(self.__classTemp_args)
        self.__cpnTemp_args = sys_args[0:3] + self.__serv_func_list

        newHeaderLine = ('#include \"'+self.__headerName+'\"\n')
        newSetLine = ('SIGNAL_SET_LIST_RTEASYN_%s(_)' %self.__fileName.upper())
        newGetLine = ('SIGNAL_GET_MAP_LIST_RTEASYN_%s(_)' %self.__fileName.upper())
        newServLine = ('SIGNAL_SERV_LIST_RTESYN_%s(_)' %self.__fileName.upper())
        newTrigLine = ('SIGNAL_TRIG_MAP_LIST_RTESYN_%s(_)' %self.__fileName.upper())
        newStr = ('        '+newSetLine)
        newSetLine = newStr + self.getAlignSpaceAmount(newStr, self.__AlignWidth)*' '+'\\\n'
        newStr = ('        '+newGetLine)
        newGetLine = newStr + self.getAlignSpaceAmount(newStr, self.__AlignWidth)*' '+'\\\n'
        newStr = ('        '+newServLine)
        newServLine = newStr + self.getAlignSpaceAmount(newStr, self.__AlignWidth)*' '+'\\\n'
        newStr = ('        '+newTrigLine)
        newTrigLine = newStr + self.getAlignSpaceAmount(newStr, self.__AlignWidth)*' '+'\\\n'
        self.__newRteSigsConfig = [newHeaderLine,newSetLine,newGetLine,newServLine,newTrigLine]
        self.__newCpnSchTrigHeader = ('    _(sig_trig_%s_init,sig_serv_%s_init)' %(self.__fileName,self.__fileName))
        self.__newCpnSchTrigHeader = self.__newCpnSchTrigHeader + self.getAlignSpaceAmount(self.__newCpnSchTrigHeader, self.__AlignWidth)*' '+'\\\n'
        self.__newCpnSchTrigSource = ('    SYN_TRIG(sig_trig_%s_init, OOPC_NULL);\n' %self.__fileName)
        self.__newCpnSchTrigConfig = ('    e_%s,\n' %self.__fileName)
        self.__newCpnErrIdConfig = ('    %sCFG_ERR_ID,\n' %self.__fileName.upper())

    #========================================================
    # signal generate functions
    #--------------------------------------------------------
    def creatSetDataTypeDeclaration(self):
        """ send data type declaration """
        comments = ('/***********************************************************\n')
        comments += (' * Get Set data type definition.\n')
        comments += (' * Generally, only the set data is defined, and the get type refers to the current header file.\n')
        comments += (' * Only need to define the data send, the transceiver interface uses a unified interface, no other definitions.\n')
        comments += (' * Generally speaking, the signal data type must be defined once,\n * otherwise it is difficult to know what the corresponding data of the signal is.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Send data type.\n')
        comments += (' **********************************************/\n')
        return comments

    def creatServDataTypeDeclaration(self):
        """ serve data type declaration """
        comments = ('/***********************************************************\n')
        comments += (' * Serv Trig data type definition.\n')
        comments += (' * Generally, only the serv data is defined, and the trig type refers to the current header file.\n')
        comments += (' * Only need to define the data send, the transceiver interface uses a unified interface, no other definitions.\n')
        comments += (' * Generally speaking, the signal data type must be defined once,\n * otherwise it is difficult to know what the corresponding data of the signal is.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Serv data type.\n')
        comments += (' **********************************************/\n')
        return comments

    def creatServTrigInterfaceDeclaration(self):
        """ serv trig signal interface declaration """
        comments = ('/***********************************************************\n')
        comments += (' * Serv Trig signal interface definition.\n')
        comments += (' * The interface inherited by the class is the trigger signal interface,\n * and the trigger signal is used in the interface function to trigger.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Component initial serv.\n')
        comments += (' **********************************************/\n')
        comments += ('void serv_%s_init(void);\n' %self.__fileName)
        for func in self.__serv_func_list:
            comments += ('/* %s Service.\n' %func)
            comments += (' **********************************************/\n')
            comments += ('void serv_%s_%s(void);\n' %(self.__fileName,func))
        comments += ('\n')
        comments += ('/* Trigger interface.\n')
        comments += (' **********************************************/\n')
        comments += ('//void trig_%s_inf_infFunc(void);\n' %self.__fileName)
        return comments

    def creatSetGetSigsListDefinition(self):
        """ get set signal list """
        comments = ('/***********************************************************\n')
        comments += (' * Get Set signal list.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Set signal list.\n')
        comments += (' **********************************************/\n')
        sigSetCpn = ('#define SIGNAL_SET_LIST_RTEASYN_%s(_)' %self.__fileName.upper())
        comments += sigSetCpn+self.getAlignSpaceAmount(sigSetCpn, self.__AlignWidth)*' '+'\\\n'
        comments += '\n'
        comments += ('/* Get signal list.\n')
        comments += (' * When configuring the signal, you need to check the length of the transmitted signal to map the signal.\n')
        comments += (' **********************************************/\n')
        sigGetCpn = ('#define SIGNAL_GET_MAP_LIST_RTEASYN_%s(_)' %self.__fileName.upper())
        comments += sigGetCpn+self.getAlignSpaceAmount(sigGetCpn, self.__AlignWidth)*' '+'\\\n'
        return comments

    def creatServTrigSigsListDefinition(self):
        """ serv trig signal list """
        comments = ('/***********************************************************\n')
        comments += (' * Trig Serv signal list.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Serv signal list.\n')
        comments += (' **********************************************/\n')
        newLine = ('#define SIGNAL_SERV_LIST_RTESYN_%s(_)' %self.__fileName.upper())
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_serv_%s_init,serv_%s_init)' %(self.__fileName,self.__fileName))
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        for func in self.__serv_func_list:
            newLine = ('    _(sig_serv_%s_%s,serv_%s_%s)' %(self.__fileName,func,self.__fileName,func))
            comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        comments += '\n'
        comments += ('/* Trig signal list.\n')
        comments += (' * When configuring the signal, you need to check the length of the service signal to map the signal.\n')
        comments += (' **********************************************/\n')
        newLine = ('#define SIGNAL_TRIG_MAP_LIST_RTESYN_%s(_)' %self.__fileName.upper())
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_trig_%s_initTask,sig_serv_CpnSch_initTask)' %self.__fileName)
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_trig_%s_delay,sig_serv_CpnSch_delay)' %self.__fileName)
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_trig_%s_now,sig_serv_CpnSch_now)' %self.__fileName)
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_trig_%s_setErr,sig_serv_CpnErr_setErr)' %self.__fileName)
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        return comments

    def creatTaskCpnDeclaration(self):
        """ component running task """
        comments = ('/***********************************************************\n')
        comments += (' * Component running task.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Running task declaration.\n')
        comments += (' **********************************************/\n')
        comments += ('void task%s(void);\n' %self.__fileName)
        return comments

    def creatTaskCpnDefinition(self):
        """ component running task """
        comments = ('/***********************************************************\n')
        comments += (' * Component running task.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Running task definition.\n')
        comments += (' **********************************************/\n')
        comments += ('void task%s(void){}\n' %self.__fileName)
        return comments

    def creatCpnClassDefinition(self):
        """ Component class definition """
        comments = ('/***********************************************************\n')
        comments += (' * %s class definition.\n' %self.__fileName)
        comments += (' **********************************************************/\n')
        comments += ('/* %s class.\n' %self.__fileName)
        comments += (' **********************************************/\n')
        comments += ('static %s cl%s;' %(self.__fileName,self.__fileName))
        return comments

    def creatServTrigInterfaceDefinition(self):
        """ serv trig interface definition """
        comments = ('/***********************************************************\n')
        comments += (' * Serv Trig signal interface definition.\n')
        comments += (' * The interface inherited by the class is the trigger signal interface,\n * and the trigger signal is used in the interface function to trigger.\n')
        comments += (' **********************************************************/\n')
        comments += ('/* Component initial serv.\n')
        comments += (' **********************************************/\n')
        comments += ('void serv_%s_init(void){\n' %self.__fileName)
        comments += ('    CNNP(%s,&cl%s);\n' %(self.__fileName,self.__fileName))
        comments += ('    if(OPRS(cl%s) != NULL){\n' %self.__fileName)
        comments += ('        tsInitTask taskParam;\n')
        comments += ('        taskParam.level = level1;\n')
        comments += ('        taskParam.t = task%s;\n' %self.__fileName)
        comments += ('        taskParam.prdTick = 11*MS_T;\n')
        comments += ('        taskParam.startTick = 5*MS_T;\n')
        comments += ('        taskParam.e.all = e_%s;\n' %self.__fileName)
        comments += ('        SYN_TRIG(sig_trig_%s_initTask, &taskParam);\n' %self.__fileName)
        comments += ('    }\n')
        comments += ('}\n')
        comments += ('\n')
        for func in self.__serv_func_list:
            comments += ('/* %s Service.\n' %func)
            comments += (' **********************************************/\n')
            comments += ('void serv_%s_%s(void){}\n' %(self.__fileName,func))
        comments += ('\n')
        comments += ('/* Interface trigger.\n')
        comments += (' **********************************************/\n')
        comments += ('//void trig_%s_inf_infFunc(void){}\n' %self.__fileName)
        return comments

    #========================================================
    # template generate register signals list
    #--------------------------------------------------------
    def getAlignSpaceAmount(self,str,alignWidth):
        """ get align space width """
        maxLen = len(str)
        if(maxLen > alignWidth):
            maxLen = maxLen + 1
        else:
            maxLen = alignWidth
        return maxLen - len(str)

    def getStrBlockEndIndex(self,str,readLines):
        """ get string in file, and return end line number of the block. """
        for i in range(0,len(readLines)):
            if str in readLines[i]:
                for j in range(i,len(readLines)):
                    if readLines[j] == '\n':
                        return j
        return 0

    def getStrLineIndex(self,str,readLines):
        """get string in file, and return line number. """
        for i in range(0,len(readLines)):
            if str in readLines[i]:
                return i
        return 0

    def openFileReadLines(self,filePath):
        """ read every line in file. """
        try:
            fRead = open(filePath,mode = 'r',encoding=self.__encoding)
            fReadLines = fRead.readlines()
            fRead.close()
        except IOError as e:
                print( "Can't Open File!!!" + filePath, e)
        return fReadLines

    def openFileWriteLines(self,filePath,fileData):
        """ if data is not null, then write data in the file. """
        try:
            if (fileData != ''):
                fWrite = open(filePath,mode = 'w',encoding=self.__encoding)
                fWrite.write(fileData)
                fWrite.close()
        except IOError as e:
            print( "Can't Open File!!!" + filePath, e)

    def getCpnSpecificIndex(self,fPath,specificStr,newTarget):
        """ read file, and get file index. """
        fReadLines = self.openFileReadLines(fPath)
        fData = ''

        fCpnFileStart = self.getStrLineIndex(specificStr,fReadLines)
        print('start index:')
        print(fCpnFileStart)

        fCpnFileEnd = self.getStrBlockEndIndex(specificStr,fReadLines)
        print('end index:')
        print(fCpnFileEnd)

        fCpnFileIndex = self.getStrLineIndex(newTarget,fReadLines)
        print('exist index:')
        print(fCpnFileIndex)

        listIndex = [fCpnFileIndex,fCpnFileStart,fCpnFileEnd]
        return listIndex

    #========================================================
    # General file operation
    #--------------------------------------------------------
    def addCpnFileCfg(self,fPath,specificStr,newTarget):
        """ read and modify file, new added newTarget in file. """
        fReadLines = self.openFileReadLines(fPath)
        fData = ''

        indexList = self.getCpnSpecificIndex(fPath,specificStr,newTarget)
        existIndex = indexList[0]
        startIndex = indexList[1]
        endIndex = indexList[2]
        print(indexList)

        #cover orignal datas
        if (existIndex != 0):
            endIndex = existIndex
        else:
            if endIndex > 1:
                endIndex = (endIndex-1)

        for i in range(len(fReadLines)):
            fData += fReadLines[i]
            if (0 == existIndex) and (i == endIndex):
                fData += newTarget
        self.openFileWriteLines(fPath,fData)

    def delCpnFileCfg(self,fPath,specificStr,newTarget):
        """ read and modify file, delete specific string. """
        fReadLines = self.openFileReadLines(fPath)
        fData = ''

        indexList = self.getCpnSpecificIndex(fPath,specificStr,newTarget)
        existIndex = indexList[0]
        startIndex = indexList[1]
        endIndex = indexList[2]
        print(indexList)

        for i in range(len(fReadLines)):
            if (0 != existIndex) and (i == existIndex):
                continue
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)

    def upCpnFileCfg(self,fPath,specificStr,newTarget):
        """ read and modify file, move up one line in file. """
        fReadLines = self.openFileReadLines(fPath)
        fData = ''

        indexList = self.getCpnSpecificIndex(fPath,specificStr,newTarget)
        existIndex = indexList[0]
        startIndex = indexList[1]
        endIndex = indexList[2]
        print(indexList)

        for i in range(len(fReadLines)):
            if (0 != existIndex) and ((existIndex-1) > startIndex) and (i == (existIndex-1)):
                fData += fReadLines[i+1]
                continue
            if (0 != existIndex) and ((existIndex-1) > startIndex) and (i == existIndex):
                fData += fReadLines[i-1]
                continue
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)

    def downCpnFileCfg(self,fPath,specificStr,newTarget):
        """ read and modify file, move down one line in file. """
        fReadLines = self.openFileReadLines(fPath)
        fData = ''

        indexList = self.getCpnSpecificIndex(fPath,specificStr,newTarget)
        existIndex = indexList[0]
        startIndex = indexList[1]
        endIndex = indexList[2]
        print(indexList)

        for i in range(len(fReadLines)):
            if (0 != existIndex) and ((existIndex+1) < endIndex) and (i == existIndex):
                fData += fReadLines[i+1]
                continue
            if (0 != existIndex) and ((existIndex+1) < endIndex) and (i == (existIndex+1)):
                fData += fReadLines[i-1]
                continue
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)

    #========================================================
    # RteSigsConfigList operation
    #--------------------------------------------------------
    def addCpn(self):
        """ read and modify file, and register new added component. """
        #add component, regist list
        for i in range(len(self.__newRteSigsConfig)):
            self.addCpnFileCfg(self.__RteSigsConfigListfPath,self.__RteSigsConfigList[i],self.__newRteSigsConfig[i])
        #add initial signal
        self.addCpnFileCfg(self.__CpnSchSigsHeaderfPath,self.__CpnSchSigTrigList,self.__newCpnSchTrigHeader)
        #trigger initial signal
        self.addCpnFileCfg(self.__CpnSchSigsSourcefPath,self.__CpnSchInitCpn,self.__newCpnSchTrigSource)
        #add event
        self.addCpnFileCfg(self.__CpnSchSigsConfigfPath,self.__CpnSchEvent,self.__newCpnSchTrigConfig)
        #add error id
        self.addCpnFileCfg(self.__CpnSchErrConfigfPath,self.__CpnErrId,self.__newCpnErrIdConfig)

    def delCpn(self):
        """ read and modify file, delete component in configure list. """
        #delete component, regist list
        for i in range(len(self.__newRteSigsConfig)):
            self.delCpnFileCfg(self.__RteSigsConfigListfPath,self.__RteSigsConfigList[i],self.__newRteSigsConfig[i])
        #delete initial signal
        self.delCpnFileCfg(self.__CpnSchSigsHeaderfPath,self.__CpnSchSigTrigList,self.__newCpnSchTrigHeader)
        #delete trigger initial signal
        self.delCpnFileCfg(self.__CpnSchSigsSourcefPath,self.__CpnSchInitCpn,self.__newCpnSchTrigSource)
        #delete event
        self.delCpnFileCfg(self.__CpnSchSigsConfigfPath,self.__CpnSchEvent,self.__newCpnSchTrigConfig)
        #delete error id
        self.delCpnFileCfg(self.__CpnSchErrConfigfPath,self.__CpnErrId,self.__newCpnErrIdConfig)

    def upCpn(self):
        """ read and modify file, component move up one line in configure list. """
        #move up component, regist list
        for i in range(len(self.__newRteSigsConfig)):
            self.upCpnFileCfg(self.__RteSigsConfigListfPath,self.__RteSigsConfigList[i],self.__newRteSigsConfig[i])
        #move up initial signal
        self.upCpnFileCfg(self.__CpnSchSigsHeaderfPath,self.__CpnSchSigTrigList,self.__newCpnSchTrigHeader)
        #move up trigger initial signal
        self.upCpnFileCfg(self.__CpnSchSigsSourcefPath,self.__CpnSchInitCpn,self.__newCpnSchTrigSource)
        #move up event
        self.upCpnFileCfg(self.__CpnSchSigsConfigfPath,self.__CpnSchEvent,self.__newCpnSchTrigConfig)
        #move up error id
        self.upCpnFileCfg(self.__CpnSchErrConfigfPath,self.__CpnErrId,self.__newCpnErrIdConfig)

    def downCpn(self):
        """ read and modify file, component move down one line in configure list. """
        #move down component, regist list
        for i in range(len(self.__newRteSigsConfig)):
            self.downCpnFileCfg(self.__RteSigsConfigListfPath,self.__RteSigsConfigList[i],self.__newRteSigsConfig[i])
        #move down initial signal
        self.downCpnFileCfg(self.__CpnSchSigsHeaderfPath,self.__CpnSchSigTrigList,self.__newCpnSchTrigHeader)
        #move down trigger initial signal
        self.downCpnFileCfg(self.__CpnSchSigsSourcefPath,self.__CpnSchInitCpn,self.__newCpnSchTrigSource)
        #move down event
        self.downCpnFileCfg(self.__CpnSchSigsConfigfPath,self.__CpnSchEvent,self.__newCpnSchTrigConfig)
        #move down error id
        self.downCpnFileCfg(self.__CpnSchErrConfigfPath,self.__CpnErrId,self.__newCpnErrIdConfig)

    #========================================================
    # template generate source and head files
    #--------------------------------------------------------
    def createSource(self):
        """ generate source file """
        fh = open(self.__sourceName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription(self.__fileName+' component signals definition source file.')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__sourceName)
        cm += ("/* Include head files. */\n")
        #if self.__filePath != '':
        #    refPath = '../'*len(self.__filePath.split('/'))
        #else:
        #    refPath = './'
        refPath = ''
        cm += ("#include \"%s\"\n" %self.__ClassHeaderName)
        cm += ("#include \"%s\"\n" %self.__headerName)
        cm += ('#include \"'+refPath+self.__RteSigsHeaderPath+'\"\n')
        cm += ("\n"*1)
        cm += self.creatCpnClassDefinition()
        cm += ("\n"*3)
        cm += self.creatServTrigInterfaceDefinition()
        cm += ("\n"*3)
        cm += self.creatTaskCpnDefinition()
        cm += ("\n"*1)
        cm += self.__cTemp.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createHeader(self):
        """ generate head file """
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.updatefCommentUsedDescription(self.__fileName+' component signals declaration head file.')
        cm = self.__cTemp.generateFileHeadCommentUsed(self.__headerName)
        cm += "#ifndef %sSIGS_H_\n" %self.__fileName.upper()
        cm += "#define %sSIGS_H_\n" %self.__fileName.upper()
        cm += ("\n/* Include head files. */\n")
        #if self.__filePath != '':
        #    refPath = '../'*len(self.__filePath.split('/'))
        #else:
        #    refPath = './'
        refPath = ''
        #cm += ('#include \"'+refPath+self.__StandTypeHeaderPath+'\"\n')
        cm += ('#include \"'+refPath+self.__RteHeaderPath+'\"\n')
        cm += ('\n'*1)
        cm += self.__cTemp.generateMacroVersionDeclaration(self.__fileName+'Sigs')
        cm += ('\n'*1)
        cm += self.creatSetDataTypeDeclaration()
        cm += ('\n'*3)
        cm += self.creatServDataTypeDeclaration()
        cm += ('\n'*3)
        cm += self.creatServTrigInterfaceDeclaration()
        cm += ('\n'*3)
        cm += self.creatSetGetSigsListDefinition()
        cm += ('\n'*3)
        cm += self.creatServTrigSigsListDefinition()
        cm += ('\n'*3)
        cm += self.creatTaskCpnDeclaration()
        cm += ("\n"*1)
        cm += "#endif /*%sSIGS_H_*/\n\n" %self.__fileName.upper()
        cm += self.__cTemp.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createTemplate(self):
        """ template generate """
        self.__cTemp.generateFilePath()
        self.__cTemp.createCpnCfgHeader()
        self.createSource()
        self.createHeader()
        self.__cTemp.backupOriginPath()
        self.addCpn()

        #generate class template
        self.__classTemp.createTemplate()

    #========================================================
    # calling function
    #--------------------------------------------------------
if __name__ == '__main__':
    if len(sys.argv) <= 3:
        sys.stderr.write("please input no less than 4 parameter !!!")
    else:
        cpn = CpnTemplate(sys.argv)
        cpn.createTemplate()

