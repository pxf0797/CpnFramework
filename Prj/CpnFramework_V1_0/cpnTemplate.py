#!usr/bin/env python3
#coding: utf-8
#cpnTemplate.py  component

import sys
import datetime
import os
sys.path.append(os.getcwd())
import cTemplate
import classTemplate

class cpnTemplate:
    """文件生成脚本
    使用方法：python cpnTemplate.py path cpnName func_list
    脚本至少需要4个参数，
    路径path，当前路径可以使用/或\，其他路径一定要以非/或\开头，否则生成不了
    cpnName根据需要选取
    func_list是多个参数，目前配置类时至少需要给定1个功能函数
    功能函数也分为oopc功能函数和serv信号功能函数，serv信号功能函数必须以/或\开头"""
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
    #__OopcHeaderPath = 'oopc/oopc.h'
    #__StandTypeHeaderPath = 'standType/standType.h'
    __RteHeaderPath = 'cpnRte/Rte/Rte.h'
    __RteSigsHeaderPath = 'cpnRte/RteSigs/RteSigs.h'
    __AlignWidth = 59
    
    __RteSigsConfigListPath = './cpnRte/RteSigs'
    __RteSigsConfigListHeaderFile = 'RteSigsConfigList.h'
    __CpnSchPath = './cpnBasics/CpnSch'
    __CpnSchSigsHeaderFile = 'CpnSchSigs.h'
    __CpnSchSigsSourceFile = 'CpnSchSigs.c'
    
    __IncludeHeader = '组件信号'
    __SigSetList = 'SIGNAL_SET_LIST_RTEASYN(_)'
    __SigGetList = 'SIGNAL_GET_MAP_LIST_RTEASYN(_)'
    __SigServList = 'SIGNAL_SERV_LIST_RTESYN(_)'
    __SigTrigList = 'SIGNAL_TRIG_MAP_LIST_RTESYN(_)'
    __CpnSchSigTrigList = 'SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)'
    __CpnSchInitCpn = 'void trig_CpnSch_inf_initCpn(void)'

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
        self.__cTemp = cTemplate.cTemplate(self.__cTemp_args)
        self.__classTemp_args = sys_args[0:3] + self.__oopc_func_list
        self.__classTemp = classTemplate.classTemplate(self.__classTemp_args)
        self.__cpnTemp_args = sys_args[0:3] + self.__serv_func_list
        
    #========================================================
    # 信号专用生成函数
    #--------------------------------------------------------
    def creatSetDataTypeDeclaration(self):
        """发送数据类型声明"""
        comments = ('/***********************************************************\n')
        comments += ('* get set 数据类型定义\n')
        comments += ('* 一般只定义set数据，get类型引用当前头文件\n')
        comments += ('* 只需要把发送的数据定义出来，收发接口使用的是统一接口，无其他定义\n')
        comments += ('* 信号数据类型一般来说都得强制定义一遍，否则很难知道信号对应数据是什么\n')
        comments += ('***********************************************************/\n')
        comments += ('/*发送数据类型\n')
        comments += ('***********************************************/\n')
        return comments
    
    def creatServDataTypeDeclaration(self):
        """服务数据类型声明"""
        comments = ('/***********************************************************\n')
        comments += ('* serv trig 数据类型定义\n')
        comments += ('* 一般只定义serv数据，trig类型引用当前头文件\n')
        comments += ('* 只需要把发送的数据定义出来，收发接口使用的是统一接口，无其他定义\n')
        comments += ('* 信号数据类型一般来说都得强制定义一遍，否则很难知道信号对应数据是什么\n')
        comments += ('***********************************************************/\n')
        comments += ('/*服务数据类型\n')
        comments += ('***********************************************/\n')
        return comments
    
    def creatServTrigInterfaceDeclaration(self):
        """服务触信号接口声明"""
        comments = ('/***********************************************************\n')
        comments += ('* serv trig 信号接口定义\n')
        comments += ('* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发\n')
        comments += ('***********************************************************/\n')
        comments += ('/*组件初始化服务\n')
        comments += ('***********************************************/\n')
        comments += ('void serv_%s_init(void);\n' %self.__fileName)
        for func in self.__serv_func_list:
            comments += ('/*服务\n')
            comments += ('***********************************************/\n')
            comments += ('void serv_%s_%s(void);\n' %(self.__fileName,func))
        comments += ('\n')
        comments += ('/*接口触发\n')
        comments += ('***********************************************/\n')
        comments += ('//void trig_%s_inf_infFunc(void);\n' %self.__fileName)
        return comments
    
    def creatSetGetSigsListDefinition(self):
        """发送接收信号列表"""
        comments = ('/***********************************************************\n')
        comments += ('* get set信号列表\n')
        comments += ('***********************************************************/\n')
        comments += ('/*发送信号列表\n')
        comments += ('***********************************************/\n')
        sigSetCpn = ('#define SIGNAL_SET_LIST_RTEASYN_%s(_)' %self.__fileName.upper())
        comments += sigSetCpn+self.getAlignSpaceAmount(sigSetCpn, self.__AlignWidth)*' '+'\\\n'
        comments += '\n'
        comments += ('/*接收信号列表\n')
        comments += ('* 配置信号时需要检查发送信号的长度对信号进行映射\n')
        comments += ('***********************************************/\n')
        sigGetCpn = ('#define SIGNAL_GET_MAP_LIST_RTEASYN_%s(_)' %self.__fileName.upper())
        comments += sigGetCpn+self.getAlignSpaceAmount(sigGetCpn, self.__AlignWidth)*' '+'\\\n'
        return comments
    
    def creatServTrigSigsListDefinition(self):
        """服务触发信号列表"""
        comments = ('/***********************************************************\n')
        comments += ('* trig serv信号列表\n')
        comments += ('***********************************************************/\n')
        comments += ('/*服务信号列表\n')
        comments += ('***********************************************/\n')
        newLine = ('#define SIGNAL_SERV_LIST_RTESYN_%s(_)' %self.__fileName.upper())
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_serv_%s_init,serv_%s_init)' %(self.__fileName,self.__fileName))
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        for func in self.__serv_func_list:
            newLine = ('    _(sig_serv_%s_%s,serv_%s_%s)' %(self.__fileName,func,self.__fileName,func))
            comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        comments += '\n'
        comments += ('/*触发信号列表\n')
        comments += ('* 配置信号时需要检查服务信号的长度对信号进行映射\n')
        comments += ('***********************************************/\n')
        newLine = ('#define SIGNAL_TRIG_MAP_LIST_RTESYN_%s(_)' %self.__fileName.upper())
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_trig_%s_addTask,sig_serv_CpnSch_addTask)' %self.__fileName)
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_trig_%s_delTask,sig_serv_CpnSch_delTask)' %self.__fileName)
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_trig_%s_delay,sig_serv_CpnSch_delay)' %self.__fileName)
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_trig_%s_now,sig_serv_CpnSch_now)' %self.__fileName)
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        newLine = ('    _(sig_trig_%s_setErr,sig_serv_CpnErr_setErr)' %self.__fileName)
        comments += newLine+self.getAlignSpaceAmount(newLine, self.__AlignWidth)*' '+'\\\n'
        return comments
    
    def creatTaskCpnDeclaration(self):
        """组件运行任务"""
        comments = ('/***********************************************************\n')
        comments += ('* 组件运行任务\n')
        comments += ('***********************************************************/\n')
        comments += ('/*运行任务声明\n')
        comments += ('***********************************************/\n')
        comments += ('void task%s(void);\n' %self.__fileName)
        return comments
        
    def creatTaskCpnDefinition(self):
        """组件运行任务"""
        comments = ('/***********************************************************\n')
        comments += ('* 组件运行任务\n')
        comments += ('***********************************************************/\n')
        comments += ('/*运行任务定义\n')
        comments += ('***********************************************/\n')
        comments += ('void task%s(void){}\n' %self.__fileName)
        return comments
    
    def creatCpnClassDefinition(self):
        """组件类定义"""
        comments = ('/***********************************************************\n')
        comments += ('* %s类定义\n' %self.__fileName)
        comments += ('***********************************************************/\n')
        comments += ('/*%s类\n' %self.__fileName)
        comments += ('***********************************************/\n')
        comments += ('%s cl%s;' %(self.__fileName,self.__fileName))
        return comments
    
    def creatServTrigInterfaceDefinition(self):
        """服务触信号接口声明"""
        comments = ('/***********************************************************\n')
        comments += ('* serv trig 信号接口定义\n')
        comments += ('* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发\n')
        comments += ('***********************************************************/\n')
        comments += ('/*组件初始化服务\n')
        comments += ('***********************************************/\n')
        comments += ('void serv_%s_init(void){\n' %self.__fileName)
        comments += ('    CNNP(%s,&cl%s);\n' %(self.__fileName,self.__fileName))
        comments += ('    if(OPRS(cl%s) != NULL){\n' %self.__fileName)
        comments += ('        addTaskParam taskParam;\n')
        comments += ('        taskParam.level = level1;\n')
        comments += ('        taskParam.t = task%s;\n' %self.__fileName)
        comments += ('        taskParam.prdTick = 11*MS_T;\n')
        comments += ('        taskParam.startTick = 5*MS_T;\n')
        comments += ('        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_%s_addTask, (uint8*)&taskParam);\n' %self.__fileName)
        comments += ('    }\n')
        comments += ('}\n')
        comments += ('\n')
        for func in self.__serv_func_list:
            comments += ('/*服务\n')
            comments += ('***********************************************/\n')
            comments += ('void serv_%s_%s(void){}\n' %(self.__fileName,func))
        comments += ('\n')
        comments += ('/*接口触发\n')
        comments += ('***********************************************/\n')
        comments += ('//void trig_%s_inf_infFunc(void){}\n' %self.__fileName)
        return comments
    #========================================================
    
    
    #========================================================
    # 模板生成注册信号列表
    #--------------------------------------------------------
    def getAlignSpaceAmount(self,str,alignWidth):
        """获取对齐空格宽度"""
        maxLen = len(str)
        if(maxLen > alignWidth):
            maxLen = maxLen + 1
        else:
            maxLen = alignWidth
        return maxLen - len(str)
        
    def getStrBlockEndIndex(self,str,readLines):
        """获取字符串对应文件中，字符串块结束的行索引"""
        for i in range(0,len(readLines)):
            if str in readLines[i]:
                for j in range(i,len(readLines)):
                    if readLines[j] == '\n':
                        return j
        return 0
    def getStrLineIndex(self,str,readLines):
        """获取字符串对应文件中的行索引"""
        for i in range(0,len(readLines)):
            if str in readLines[i]:
                return i
        return 0
    
    def openFileReadLines(self,filePath):
        """读取文件每一行数据"""
        try:
            fRead = open(filePath,mode = 'r',encoding=self.__encoding)
            fReadLines = fRead.readlines()
            fRead.close()
        except IOError as e:
                print( "Can't Open File：" + fPath, e)
        return fReadLines
    
    def openFileWriteLines(self,filePath,fileData):
        """写入数据不为空，把数据写入到文件"""
        try:
            if (fileData != ''):
                fWrite = open(filePath,mode = 'w',encoding=self.__encoding)
                fWrite.write(fileData)
                fWrite.close()
        except IOError as e:
            print( "Can't Open File：" + filePath, e)

    def getSignalListRegisterIndex(self):
        """读取文件，查询注册列表中对应索引"""
        fPath = self.__RteSigsConfigListPath + '/' + self.__RteSigsConfigListHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        fIncludeHeaderStart = self.getStrLineIndex(self.__IncludeHeader,fReadLines)
        fSetListStart = self.getStrLineIndex(self.__SigSetList,fReadLines)
        fGetListStart = self.getStrLineIndex(self.__SigGetList,fReadLines)
        fServListStart = self.getStrLineIndex(self.__SigServList,fReadLines)
        fTrigListStart = self.getStrLineIndex(self.__SigTrigList,fReadLines)
        print('config list start index:')
        print(fIncludeHeaderStart,fSetListStart,fGetListStart,fServListStart,fTrigListStart)
        
        fIncludeHeaderEnd = self.getStrBlockEndIndex(self.__IncludeHeader,fReadLines)
        fSetListEnd = self.getStrBlockEndIndex(self.__SigSetList,fReadLines)
        fGetListEnd = self.getStrBlockEndIndex(self.__SigGetList,fReadLines)
        fServListEnd = self.getStrBlockEndIndex(self.__SigServList,fReadLines)
        fTrigListEnd = self.getStrBlockEndIndex(self.__SigTrigList,fReadLines)
        print('config list end index:')
        print(fIncludeHeaderEnd,fSetListEnd,fGetListEnd,fServListEnd,fTrigListEnd)
        
        fHeaderIndex = self.getStrLineIndex(self.__headerName,fReadLines)
        newSetLine = ('SIGNAL_SET_LIST_RTEASYN_%s(_)' %self.__fileName.upper())
        fSetListIndex = self.getStrLineIndex(newSetLine,fReadLines)
        newGetLine = ('SIGNAL_GET_MAP_LIST_RTEASYN_%s(_)' %self.__fileName.upper())
        fGetListIndex = self.getStrLineIndex(newGetLine,fReadLines)
        newServLine = ('SIGNAL_SERV_LIST_RTESYN_%s(_)' %self.__fileName.upper())
        fServListIndex = self.getStrLineIndex(newServLine,fReadLines)
        newTrigLine = ('SIGNAL_TRIG_MAP_LIST_RTESYN_%s(_)' %self.__fileName.upper())
        fTrigListIndex = self.getStrLineIndex(newTrigLine,fReadLines)
        print('config list exist index:')
        print(fHeaderIndex,fSetListIndex,fGetListIndex,fServListIndex,fTrigListIndex)
        
        indexList = [fHeaderIndex,fSetListIndex,fGetListIndex,fServListIndex,fTrigListIndex,
        fIncludeHeaderStart,fSetListStart,fGetListStart,fServListStart,fTrigListStart,
        fIncludeHeaderEnd,fSetListEnd,fGetListEnd,fServListEnd,fTrigListEnd]
        return indexList

    def getCpnSchSigsSourceIndex(self):
        """读取文件，查询调度组件源文件中对应索引"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsSourceFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        fCpnSchInitCpnStart = self.getStrLineIndex(self.__CpnSchInitCpn,fReadLines)
        print('CpnSch Source start index:')
        print(fCpnSchInitCpnStart)
        
        fCpnSchInitCpnEnd = self.getStrBlockEndIndex(self.__CpnSchInitCpn,fReadLines)
        print('CpnSch Source end index:')
        print(fCpnSchInitCpnEnd)
        
        newTrigSig = ('sig_trig_%s_init' %self.__fileName)
        fCpnSchInitCpnIndex = self.getStrLineIndex(newTrigSig,fReadLines)
        print('CpnSch Source exist index:')
        print(fCpnSchInitCpnIndex)
        
        listIndex = [fCpnSchInitCpnIndex,fCpnSchInitCpnStart,fCpnSchInitCpnEnd]
        return listIndex
        
    def getCpnSchSigsHeaderIndex(self):
        """读取文件，查询调度组件头文件中对应索引"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        fCpnSchTrigListStart = self.getStrLineIndex(self.__CpnSchSigTrigList,fReadLines)
        print('CpnSch Header start index:')
        print(fCpnSchTrigListStart)
        
        fCpnSchTrigListEnd = self.getStrBlockEndIndex(self.__CpnSchSigTrigList,fReadLines)
        print('CpnSch Header end index:')
        print(fCpnSchTrigListEnd)
        
        newCpnSchTrigLine = ('_(sig_trig_%s_init,sig_serv_%s_init)' %(self.__fileName,self.__fileName))
        fCpnSchTrigListIndex = self.getStrLineIndex(newCpnSchTrigLine,fReadLines)
        print('CpnSch Header exist index:')
        print(fCpnSchTrigListIndex)
        
        listIndex = [fCpnSchTrigListIndex,fCpnSchTrigListStart,fCpnSchTrigListEnd]
        return listIndex

    def addSignalListRegister(self):
        """读取修改文件，对新增组件列表进行注册"""
        fPath = self.__RteSigsConfigListPath + '/' + self.__RteSigsConfigListHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
            
        indexList = self.getSignalListRegisterIndex()
        existIndex = indexList[0:5]
        startIndex = indexList[5:10]
        endIndex = indexList[10:15]
        print(existIndex)
        print(startIndex)
        print(endIndex)
        
        #覆盖原有数据
        for i in range(len(existIndex)):
            if (existIndex[i] != 0):
                endIndex[i] = existIndex[i]
        
        refPath = '../../'
        newHeaderLine = ('#include \"'+refPath+self.__filePath+'/'+self.__headerName+'\"\n')
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
        
        newLineList = [newHeaderLine,newSetLine,newGetLine,newServLine,newTrigLine]
        
        continueFlg = 0
        for i in range(len(fReadLines)):
            continueFlg = 0
            for j in range(len(endIndex)):
                if (i == endIndex[j]):
                    fData += newLineList[j]
                    continueFlg = 1
                    break
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)

    def delSignalListRegister(self):
        """读取修改文件，对组件列表进行删除"""
        fPath = self.__RteSigsConfigListPath + '/' + self.__RteSigsConfigListHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getSignalListRegisterIndex()
        existIndex = indexList[0:5]
        startIndex = indexList[5:10]
        endIndex = indexList[10:15]
        print(existIndex)
        print(startIndex)
        print(endIndex)
        
        continueFlg = 0
        for i in range(len(fReadLines)):
            continueFlg = 0
            for j in range(len(existIndex)):
                if (0 != existIndex[j]) and (i == existIndex[j]):
                    continueFlg = 1
                    break
            if (continueFlg == 1):
                continue
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)

    def upSignalListRegister(self):
        """读取修改文件，对组件列表上移一行"""
        fPath = self.__RteSigsConfigListPath + '/' + self.__RteSigsConfigListHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getSignalListRegisterIndex()
        existIndex = indexList[0:5]
        startIndex = indexList[5:10]
        endIndex = indexList[10:15]
        print(existIndex)
        print(startIndex)
        print(endIndex)
        
        continueFlg = 0
        for i in range(len(fReadLines)):
            continueFlg = 0
            for j in range(len(existIndex)):
                if (0 != existIndex[j]) and ((existIndex[j]-1) > startIndex[j]) and (i == (existIndex[j]-1)):
                    fData += fReadLines[i+1]
                    continueFlg = 1
                    break
                if (0 != existIndex[j]) and ((existIndex[j]-1) > startIndex[j]) and (i == existIndex[j]):
                    fData += fReadLines[i-1]
                    continueFlg = 1
                    break
            if (continueFlg == 1):
                continue
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)
    
    def downSignalListRegister(self):
        """读取修改文件，对组件列表下移一行"""
        fPath = self.__RteSigsConfigListPath + '/' + self.__RteSigsConfigListHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getSignalListRegisterIndex()
        existIndex = indexList[0:5]
        startIndex = indexList[5:10]
        endIndex = indexList[10:15]
        print(existIndex)
        print(startIndex)
        print(endIndex)
        
        continueFlg = 0
        for i in range(len(fReadLines)):
            continueFlg = 0
            for j in range(len(existIndex)):
                if (0 != existIndex[j]) and ((existIndex[j]+1) < endIndex[j]) and (i == existIndex[j]):
                    fData += fReadLines[i+1]
                    continueFlg = 1
                    break
                if (0 != existIndex[j]) and ((existIndex[j]+1) < endIndex[j]) and (i == (existIndex[j]+1)):
                    fData += fReadLines[i-1]
                    continueFlg = 1
                    break
            if (continueFlg == 1):
                continue
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)

    def addCpnSchSigsHeader(self):
        """读取修改文件，对新增组件初始化信号添加到调度组件进行注册"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getCpnSchSigsHeaderIndex()
        existIndex = indexList[0]
        startIndex = indexList[1]
        endIndex = indexList[2]
        print(indexList)
        
        #覆盖原有数据
        if (existIndex != 0):
            endIndex = existIndex
        
        newCpnSchTrigLine = ('_(sig_trig_%s_init,sig_serv_%s_init)' %(self.__fileName,self.__fileName))
        newStr = ('    '+newCpnSchTrigLine)
        newLine = newStr + self.getAlignSpaceAmount(newStr, self.__AlignWidth)*' '+'\\\n'
        
        for i in range(len(fReadLines)):
            if (0 != endIndex) and (i == endIndex):
                fData += newLine
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)

    def delCpnSchSigsHeader(self):
        """读取修改文件，对组件初始化信号进行删除"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getCpnSchSigsHeaderIndex()
        existIndex = indexList[0]
        startIndex = indexList[1]
        endIndex = indexList[2]
        print(indexList)
        
        for i in range(len(fReadLines)):
            if (0 != existIndex) and (i == existIndex):
                continue
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)
        
    def upCpnSchSigsHeader(self):
        """读取修改文件，对组件初始化信号上移一行"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getCpnSchSigsHeaderIndex()
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
        
    def downCpnSchSigsHeader(self):
        """读取修改文件，对组件初始化信号下移一行"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsHeaderFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getCpnSchSigsHeaderIndex()
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
        
    def addCpnSchSigsSource(self):
        """读取修改文件，对新增组件初始化信号添加到调度组件进行初始化"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsSourceFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getCpnSchSigsSourceIndex()
        existIndex = indexList[0]
        startIndex = indexList[1]
        endIndex = indexList[2]
        print(indexList)
        
        #覆盖原有数据
        if (existIndex != 0):
            endIndex = existIndex
        else:
            if endIndex > 1:
                endIndex = (endIndex-1)
        
        newTrigSig = ('sig_trig_%s_init' %self.__fileName)
        newLine = ('    clRteSynSigs.trig(clRteSynSigs.self, '+newTrigSig+', NULL);\n')
        
        for i in range(len(fReadLines)):
            if (0 != endIndex) and (i == endIndex):
                fData += newLine
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)

    def delCpnSchSigsSource(self):
        """读取修改文件，对组件初始化信号在调度组件初始化进行进行删除"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsSourceFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getCpnSchSigsSourceIndex()
        existIndex = indexList[0]
        startIndex = indexList[1]
        endIndex = indexList[2]
        print(indexList)
        
        for i in range(len(fReadLines)):
            if (0 != existIndex) and (i == existIndex):
                continue
            fData += fReadLines[i]
        self.openFileWriteLines(fPath,fData)
    
    def upCpnSchSigsSource(self):
        """读取修改文件，对组件初始化信号上移一行"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsSourceFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getCpnSchSigsSourceIndex()
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
        
    def downCpnSchSigsSource(self):
        """读取修改文件，对组件初始化信号下移一行"""
        fPath = self.__CpnSchPath + '/' + self.__CpnSchSigsSourceFile
        fReadLines = self.openFileReadLines(fPath)
        fData = ''
        
        indexList = self.getCpnSchSigsSourceIndex()
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
    
    
    #========================================================
    # 模板生成源文件及头文件控制函数
    #--------------------------------------------------------
    def createSource(self):
        """生成源文件"""
        fh = open(self.__sourceName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.fileComments2['Description'] = ': '+self.__fileName+'组件信号定义源文件'
        cm = self.__cTemp.generateFileHeadComment2(self.__sourceName)
        cm += ("/*头文件包含*/\n")
        if self.__filePath != '':
            refPath = '../'*len(self.__filePath.split('/'))
        else:
            refPath = './'
        cm += ("#include \"./%s\"\n" %self.__ClassHeaderName) 
        cm += ("#include \"./%s\"\n" %self.__headerName) 
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
        """生成头文件"""
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        self.__cTemp.fileComments2['Description'] = ': '+self.__fileName+'组件信号声明头文件'
        cm = self.__cTemp.generateFileHeadComment2(self.__headerName)
        cm += "#ifndef %sSIGS_H_\n" %self.__fileName.upper()
        cm += "#define %sSIGS_H_\n" %self.__fileName.upper()
        cm += ("\n/*头文件包含*/\n")
        if self.__filePath != '':
            refPath = '../'*len(self.__filePath.split('/'))
        else:
            refPath = './'
        #cm += ('#include \"'+refPath+self.__StandTypeHeaderPath+'\"\n') 
        cm += ('#include \"'+refPath+self.__RteHeaderPath+'\"\n') 
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
        """模板生成"""
        self.__cTemp.generateFilePath()
        self.__cTemp.createCpnCfgHeader()
        self.createSource()
        self.createHeader()
        self.__cTemp.backupOriginPath()
        self.addSignalListRegister()
        self.addCpnSchSigsHeader()
        self.addCpnSchSigsSource()
        
        #创建组件类
        self.__classTemp.createTemplate()
        
    #========================================================

if __name__ == '__main__':
    if len(sys.argv) <= 3:
        sys.stderr.write("please input no less than 4 parameter !!!")
    else:
        cpn = cpnTemplate(sys.argv)
        cpn.createTemplate()
        
        