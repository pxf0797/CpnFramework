/*************************************************
 * Copyright ? person
 * File name    : oopc.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2018/2/8
 * Description  : ���ļ��ڶ���ĺ���������C������������
 *                1.Ŀǰ�������Ľӿڡ������ࡢʵ��֮��Ļ�����ϵ��������ʵ�֣�
 *                2.INF/AC/CL�ֱ����������ӿڡ������ࡢʵ�࣬��ʹ�þ�������.h�ļ��У�
 *                3.ACC/ACD/CC/CD�ֱ����ڶ�������ࡢʵ�๹�켰������������ʹ�ñ�����.c�ļ��У�
 *                4.CACC/CACD/CCC/CCD�ֱ�����ʵ��ʵ����ʱ���캯���е��ñ��̳��ࣨ�����ࡢʵ�ࣩ
 *                  �Ĺ��켰����������ʵ�������̳��࣬��ʹ�ñ�����.c�ļ��У�
 *                5.IMPL/EXT�ֱ����ڼ̳нӿڼ������ࡢʵ�ࣻ
 *                6.INJʵ���ע��һ������ʵ����
 *                7.SUB/SUBC�ֱ������ڽӿڼ������ࡢʵ���еĺ����ڻ�ü̳�����ָ��cthis��
 *                8.CN/CNNP/CFʵ�������ͷ�ʵ�����
 *                9.����CN/CNNP/CF/CCC������û�з���ֵ������ͨ��OPRS�鿴ǰһ�����������
 *                10.ʵ�������б��븽����������self,init��
 *                   self - ָ�������ָ�룬Ҳ����ָʾ��ǰʵ���Ƿ���ã�selfָ������ʱʵ����ã�selfΪOOPC_NULLʱʵ�����ͷţ�
 *                   init - ����ʵ���в�����init�����и�Ҫ���ں�������������ָ������ʵ��ָ���������Ϊcthis��
 *                          Ϊ�˳�ʼ������ͳһ���ӿڼ���������Ҫͨ��init���ݽ������ã�
 *                          ʵ����������Ҫͨ��FS�������ã������ر������ͨ��init���ã�
 *                          ʵ�����м̳У��򱻼̳���������غ�������ͨ��init�������ã�
 * Others       : ��
 * History      : 180208 pxf ���ν���
 *                180302 pxf 1.Ϊ��Ӧ��ͬ��������ʵ����е�ʵ����������������޲κ�CNNP
 *                           2.���Ӻ�汾���壬��ǰ�汾Ϊv1.01
 *                180816 pxf 1.��ʹ��Ƶ���ر�ͣ�ʹ�ô���ֱ��������ӷ��㣬ɾ����FS
 *                           2.��������ע���INJ��ʹ��ʵ���ע��һ������ʵ��
 *                           3.CN/CCC�����ڴ��ݲ��ɱ����ʱ��ʹ�ú궨��������д���
 *                           4.�汾����v1.02
 ************************************************/

#ifndef OOPC_H_
#define OOPC_H_

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// �汾����---------------------------------------------------------------------
#define OOPC_MACRO_VERSION              0xC01D02    // C����v��D����.���汾v1.02

// ͨ�ú궨��-------------------------------------------------------------------
#define OOPC_FALSE                      0           // ��������ʧ��
#define OOPC_TRUE                       1           // ���������ɹ�
#define OOPC_NULL                       ((void *)0) // ��ָ��

// ����ѡ��---------------------------------------------------------------------
#define OOPC_USE_USER_DEFINED_OFFSETOF  OOPC_TRUE   // �Ƿ�ʹ���û������OOPC_OFFSETOF��OOPC_FALSEʱʹ��C��׼���е�offsetof
#define OOPC_USE_STATIC_INLINE_OPTIMIZE OOPC_TRUE   // �Ƿ�ʹ��static inline�Թ��켰��������������ý����Ż�
#define OOPC_CN_CCC_SUPPORT_FLEXIABLE_PARAM OOPC_TRUE // �Ƿ�֧�ֿɱ�����������ʵ����
#define OOPC_RETURN_DATATYPE            int         // �������������ȷ�����������

// ����ѡ��---------------------------------------------------------------------
#if (OOPC_USE_USER_DEFINED_OFFSETOF == OOPC_TRUE)   // ����OOPC_OFFSETOF
    // ��Щ�������ܲ�֧�֣��������������μ��ٳ���
    #define OOPC_OFFSETOF(type, member) (size_t)&(((type *)0)->member)
#else
    #include <stddef.h>
    // size_t offsetof(structName, memberName);
    // ��һ�������ǽṹ������֣��ڶ��������ǽṹ���Ա�����֡�
    // �ú귵�ؽṹ��structName�г�ԱmemberName��ƫ������ƫ������size_t���͵ġ�
    #define OOPC_OFFSETOF               offsetof
#endif
#if (OOPC_USE_STATIC_INLINE_OPTIMIZE == OOPC_TRUE)  // ����OOPC_STATIC_INLINE
    #define OOPC_STATIC_INLINE          static inline
#else
    #define OOPC_STATIC_INLINE
#endif
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// �ӿڼ���ļ̳й�ϵ-----------------------------------------------------------
#define IMPL(type)                      type type   // �ӿڡ���������м̳�Implement
#define EXT(type)                       h##type type// ʵ����м̳�Extends
#define INJ(type, obj)                  h##type obj // ʵ���������ע��Injection
                                                    // ��ʵ����м̳��������ԣ�����ע�����ע������ͬ����ʵ�����������ƿ��Զ�

// ��ļ̳н���һ���̳У�������༶�̳�------------------------------------------
// ʵ��̳����ࣨ�̳��ָࣩ�� subordinate,self pointer
#define SUBC(selfpointer, hselftype, childtype)                      \
h##childtype cthis = ((h##childtype)((char *)(*selfpointer) - OOPC_OFFSETOF(childtype, hselftype)))
// �������ӿڼ̳����ࣨ�̳��ָࣩ��
#define SUB(selfpointer, selftype, childtype)                        \
h##childtype cthis = ((h##childtype)((char *)selfpointer - OOPC_OFFSETOF(childtype, selftype)))
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// �ӿڼ������ࡢʵ�������------------------------------------------------------
// Interface�ӿڽ�������
#define INF(type)                                                    \
typedef struct type *h##type, type;                                  \
struct type
// Abstract Class�������������
#define AC(type)                                                     \
typedef struct type *h##type, type;                                  \
struct type
// Classʵ���������
// ʵ�������б���Ҫ����self,init�����в�������
// selfָ��������÷��ڲ����ĵ�һ����h##type self
// init�в���Ҫ���ҷ�����������ָ�룬h##type (*init)(classptr cthis,...)
// init��������ָ���������Ϊcthis�����������к��������ж���������cthis�Ĳ�������
// �ӿں����������ຯ�����Լ���������ͬһ�ļ��ڵĺ�������ͨ��init�������ν��г�ʼ��
// ��������ͬһ�ļ��ں������ͨ��FSֱ�ӽ�������
// ʾ����
// CL(Aaa)
// {
//       hAaa self;
//       hAaa (*init)(hAaa cthis, ...);
//       ...
// }
#define CL(type)                                                     \
typedef struct type **hh##type, *h##type, type;                      \
h##type type##_new(void *self);                                      \
OOPC_RETURN_DATATYPE type##_delete(h##type t);                       \
struct type
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// �����ࡢʵ�๹�캯����������������--------------------------------------------
// ��������๹�캯��abstract class constructor����Ҫ����ֵcthis/OOPC_NULL
#define ACC(type)                                                    \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis);               \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis)
// �����������������abstract class destructor����Ҫ����ֵOOPC_TRUE/OOPC_FALSE
#define ACD(type)                                                    \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis);  \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis)
// ����ʵ�๹�캯��class constructor����Ҫ����ֵcthis/OOPC_NULL
#define CC(type)                                                     \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis);               \
h##type type##_new(void *self){                                      \
    h##type cthis = (h##type)self;                                   \
    h##type Rtv = OOPC_NULL;                                         \
    if(OOPC_NULL != cthis){                                          \
        cthis->self = cthis;                                         \
        if(OOPC_NULL == type##_ctor(cthis)){                         \
            cthis->self = OOPC_NULL;                                 \
            Rtv = OOPC_NULL;                                         \
        }else{                                                       \
            Rtv = cthis;                                             \
        }                                                            \
    }else{                                                           \
        Rtv = OOPC_NULL;                                             \
    }                                                                \
    return Rtv;                                                      \
    /* ��ǰ��ȥ��ȡ�ڴ棬ֻ�Դ���������ڴ�������� */               \
}                                                                    \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis)
// ����ʵ����������class destructor����Ҫ����ֵOOPC_TRUE/OOPC_FALSE
#define CD(type)                                                     \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis);  \
OOPC_RETURN_DATATYPE type##_delete(h##type cthis){                   \
    OOPC_RETURN_DATATYPE Rtv = OOPC_FALSE;                           \
    if(OOPC_NULL != cthis){                                          \
        cthis->self = OOPC_NULL;                                     \
        if(OOPC_TRUE == type##_dtor(cthis)){                         \
            Rtv = OOPC_TRUE;                                         \
        }else{                                                       \
            Rtv = OOPC_FALSE;                                        \
        }                                                            \
    }else{                                                           \
        Rtv = OOPC_FALSE;                                            \
    }                                                                \
    return Rtv;                                                      \
    /* ��ǰ��ȥ�ͷ��ڴ棬ֻ�Դ���������ڴ�������� */               \
}                                                                    \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis)
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ��ʵ����ʱ�������ࡢʵ�ุ�๹�켰���������ĵ���-------------------------------
// ���ó����๹�캯��call abstract class constructor���з���ֵcthis/OOPC_NULL
#define CACC(father)                    father##_ctor(&(cthis->father))
// ���ó�������������call abstract class destructor���з���ֵOOPC_TRUE/OOPC_FALSE
#define CACD(father)                    father##_dtor(&(cthis->father))
// �����๹�캯��call class constructor���з���ֵcthis/OOPC_NULL
#if (OOPC_CN_CCC_SUPPORT_FLEXIABLE_PARAM == OOPC_TRUE)
#define CCC(father, fatherptr, ...)                                  \
do{                                                                  \
    cthis->father = father##_new((void *)(fatherptr));               \
    if(OOPC_NULL != cthis->father){                                  \
        if(OOPC_NULL == cthis->father->init(cthis->father, __VA_ARGS__)){ \
            if(OOPC_TRUE == father##_delete(cthis->father)){         \
                ;                                                    \
            }else{                                                   \
                ;                                                    \
            }                                                        \
            cthis->father = OOPC_NULL;                               \
        }else{                                                       \
            ;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
#else
//#define ccc_param  param1,param2...
#define CCC(father, fatherptr, param)                                \
do{                                                                  \
    cthis->father = father##_new((void *)(fatherptr));               \
    if(OOPC_NULL != cthis->father){                                  \
        if(OOPC_NULL == cthis->father->init(cthis->father, param)){  \
            if(OOPC_TRUE == father##_delete(cthis->father)){         \
                ;                                                    \
            }else{                                                   \
                ;                                                    \
            }                                                        \
            cthis->father = OOPC_NULL;                               \
        }else{                                                       \
            ;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
#endif
// ��������������call class destructor���з���ֵOOPC_TRUE/OOPC_FALSE
#define CCD(father)                     father##_delete((cthis->father))
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ʵ��ʵ�������ͷ�Class New/Free��������������----------------------------------
// CF�����������ʵ����ͨ��init�����������õĲ������ݾ�����
#if (OOPC_CN_CCC_SUPPORT_FLEXIABLE_PARAM == OOPC_TRUE)
#define CN(type, classptr, ...)                                      \
do{                                                                  \
    if(OOPC_NULL != type##_new((void *)(classptr))){                 \
        if(OOPC_NULL == (classptr)->init((classptr), __VA_ARGS__)){  \
            if(OOPC_TRUE == type##_delete(classptr)){                \
                ;                                                    \
            }else{                                                   \
                ;                                                    \
            }                                                        \
        }else{                                                       \
            ;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
#else
//#define cn_param  param1,param2...
#define CN(type, classptr, param)                                    \
do{                                                                  \
    if(OOPC_NULL != type##_new((void *)(classptr))){                 \
        if(OOPC_NULL == (classptr)->init((classptr), param)){        \
            if(OOPC_TRUE == type##_delete(classptr)){                \
                ;                                                    \
            }else{                                                   \
                ;                                                    \
            }                                                        \
        }else{                                                       \
            ;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
#endif
// Class New Without(No) Param�޲���ʵ����
#define CNNP(type, classptr)                                         \
do{                                                                  \
    if(OOPC_NULL != type##_new((void *)(classptr))){                 \
        if(OOPC_NULL == (classptr)->init(classptr)){                 \
            if(OOPC_TRUE == type##_delete(classptr)){                \
                ;                                                    \
            }else{                                                   \
                ;                                                    \
            }                                                        \
        }else{                                                       \
            ;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
// ClassFree������Դ�����ͷ�
#define CF(type, classptr)                                           \
do{                                                                  \
    if(OOPC_NULL != (classptr)){                                     \
        if(OOPC_TRUE == type##_delete(classptr)){                    \
            ;                                                        \
        }else{                                                       \
            ;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
// ����CN/CNNP/CF/CCC���ú�û�з���ֵ��ͨ�����º�鿴�������operation result��self/OOPC_NULL
#define OPRS(class)                     (class).self
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif /* OOPC_H_ */

/**************************** Copyright(C) pxf ****************************/
