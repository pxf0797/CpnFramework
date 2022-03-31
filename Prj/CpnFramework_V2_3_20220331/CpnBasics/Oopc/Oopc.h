/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : Oopc.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 11:23:10
 * Description  :
 *                1. At present, the basic relational operations between object-oriented interfaces, abstract classes and real classes have been implemented;
 *                2. INF/AC/CL are used to declare interfaces, abstract classes, and real classes, and their use should be placed in the .h file as much as possible;
 *                3. ACC/ACD/CC/CD are used to define abstract class, real class structure and destructor respectively, and their use must be in the .c file;
 *                4. CACC/CACD/CCC/CCD are respectively used to call the structure and destructor of the inherited class (abstract class, real class)
 *                in the constructor when the real class is instantiated to instantiate the inherited class. Its use must be in. c file;
 *                5. IMPL/EXT are used to inherit interfaces and abstract classes and real classes respectively;
 *                6. INJ real class can inject multiple instances of one class;
 *                7. SUB/SUBC are used to obtain the inherited subclass pointer cthis in the interface, abstract class, and function in the real class respectively;
 *                8. CN/CNNP/CF instantiates or releases real objects;
 *                9. Since there is no return value after CN/CNNP/CF/CCC operation, you can check the result of the previous step through OPRS;
 *                10. Two parameters self and init must be attached to the real class declaration;
 *                   self-a pointer to itself, which can also indicate whether the current instance is available,
 *                       the real class is available when self points to itself, and the real class is released when self is OOPC_NULL;
 *                   init-configure the parameters in the real class, the init function has a requirement that the pointer to its own real class must be declared as cthis in the function parameter declaration;
 *                       In order to initialize more uniformly, interfaces and abstract classes need to be passed through init for configuration,
 *                       Real class own functions need to be set through FS, unless special requirements can be configured through init;
 *                       If the real class has inheritance, all related functions of the inherited class must be configured through init;
 *                11. In order to adapt to the instantiation of real classes by different compilers, a special non-parameter macro CNNP is used.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef OOPC_H_
#define OOPC_H_

/* Include head files. */

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define OOPC_MACRO_VERSION              0xC03D00    /* C represent V,D represent ., Current version is V3.00 */
/* General Macros.
 **********************************************/
#define OOPC_FALSE                      0           /* (Operation) False */
#define OOPC_TRUE                       1           /* (Operation) True */
#define OOPC_NULL                       ((void *)0) /* void pointer */
/* Configure Macros.
 **********************************************/
#define OOPC_USE_USER_DEFINED_OFFSETOF  OOPC_TRUE   /* Whether to use user-defined OOPC_OFFSETOF, use offsetof in the C standard library when OOPC_FALSE */
#define OOPC_USE_STATIC_INLINE_OPTIMIZE OOPC_TRUE   /* Whether to use static inline to optimize the construction and destructor code calls */
#define OOPC_CN_CCC_SUPPORT_FLEXIABLE_PARAM OOPC_TRUE /* Whether to support variable parameters to instantiate the class */
#define OOPC_RETURN_DATATYPE            int         /* Define return data types such as destructors */

/* Configure generate Macros.
 **********************************************/
#if (OOPC_USE_USER_DEFINED_OFFSETOF == OOPC_TRUE)
    #define OOPC_OFFSETOF(type, member) (size_t)&(((type *)0)->member)
#else
    #include <stddef.h>
    /* size_t offsetof(structName, memberName);
     * The first parameter is the name of the structure, and the second parameter is the name of the structure member.
     * This macro returns the offset of memberName in the structure structName. The offset is of type size_t.
     */
    #define OOPC_OFFSETOF               offsetof
#endif
#if (OOPC_USE_STATIC_INLINE_OPTIMIZE == OOPC_TRUE)
    #define OOPC_STATIC_INLINE          static inline
#else
    #define OOPC_STATIC_INLINE
#endif

/* Interface and class inheritance relationship Macros.
 **********************************************/
#define IMPL(type)                      type type   /* [Implement] Interface, abstract class for inheritance */
#define EXT(type)                       h##type type/* [Extends] Real class inheritance */
#define INJ(type, obj)                  h##type obj /* [Injection] Real class for dependency injection */

/* Class inheritance Macros.
 * Class inheritance is recommended for one-level inheritance, and multi-level inheritance is not recommended.
 **********************************************/
/* Real class inheritance subclass (inheritance class) pointer subordinate, self pointer */
#define SUBC(selfpointer, hselftype, childtype)                      \
h##childtype cthis = ((h##childtype)((char *)(*selfpointer) - OOPC_OFFSETOF(childtype, hselftype)))
/* Abstract class or interface inheritance subclass (inherited class) pointer */
#define SUB(selfpointer, selftype, childtype)                        \
h##childtype cthis = ((h##childtype)((char *)selfpointer - OOPC_OFFSETOF(childtype, selftype)))

/* Declaration of interface and abstract class and real class Macros.
 **********************************************/
/* Interface interface declaration */
#define INF(type)                                                    \
typedef struct type *h##type, type;                                  \
struct type
/* Abstract class declaration */
#define AC(type)                                                     \
typedef struct type *h##type, type;                                  \
struct type
/* Real class declaration. */
/* The following self must be required in the real class declaration, and the init two have parameter definitions.
 * self points to itself, it is best to put it in the first parameter, h##type self.
 * init requires parameters and returns a pointer to its own type, h##type (*init)(classptr cthis,...).
 * The class pointer in the init parameter must be declared as cthis.
 * Interface functions, abstract class functions, and functions
 * that are not in the same file as the class itself can be initialized by passing parameters through the init function.
 * Example:
 * CL(Aaa){
 *      hAaa self;
 *      hAaa (*init)(hAaa cthis, ...);
 *      ...
 * }
 **********************************************/
#define CL(type)                                                     \
typedef struct type **hh##type, *h##type, type;                      \
h##type type##_new(void *self);                                      \
OOPC_RETURN_DATATYPE type##_delete(h##type t);                       \
struct type

/* Abstract class, real class constructor and destructor definition Macros.
 **********************************************/
/* Define abstract class constructor, need to return value cthis/OOPC_NULL. */
#define ACC(type)                                                    \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis);               \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis)
/* Define abstract class destructor, need to return value OOPC_TRUE/OOPC_FALSE. */
#define ACD(type)                                                    \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis);  \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis)
/* Define real class constructor, need to return value cthis/OOPC_NULL. */
#define CC(type)                                                     \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis);               \
h##type type##_new(void *self){                                      \
    h##type cthis = (h##type)self;                                   \
    h##type Rtv = OOPC_NULL;                                         \
    if(OOPC_NULL != cthis){                                          \
        cthis->self = cthis;                                         \
        Rtv = type##_ctor(cthis);                                    \
        if(OOPC_NULL == Rtv){                                        \
            cthis->self = OOPC_NULL;                                 \
        }                                                            \
    }                                                                \
    return Rtv;                                                      \
    /* Currently, the memory is not obtained, only the memory that is transferred in is configured */ \
}                                                                    \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis)
/* Define the real class destructor, need to return value OOPC_TRUE/OOPC_FALSE. */
#define CD(type)                                                     \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis);  \
OOPC_RETURN_DATATYPE type##_delete(h##type cthis){                   \
    OOPC_RETURN_DATATYPE Rtv = OOPC_FALSE;                           \
    if(OOPC_NULL != cthis){                                          \
        cthis->self = OOPC_NULL;                                     \
        Rtv = type##_dtor(cthis);                                    \
    }                                                                \
    return Rtv;                                                      \
    /* Currently, the memory is not released, only the transferred memory is configured. */ \
}                                                                    \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis)

/* When the class is instantiated, abstract class, real class parent class construction and destructor call Macros.
 **********************************************/
/* Call abstract class constructor, return value cthis/OOPC_NULL. */
#define CACC(father)                    father##_ctor(&(cthis->father))
/* Call abstract class destructor, return value cthis/OOPC_NULL. */
#define CACD(father)                    father##_dtor(&(cthis->father))
/* Call real class constructor, return value cthis/OOPC_NULL. */
#if (OOPC_CN_CCC_SUPPORT_FLEXIABLE_PARAM == OOPC_TRUE)
#define CCC(father, fatherptr, ...) do{                              \
 cthis->father = father##_new((void *)(fatherptr));               \
 if(OOPC_NULL != cthis->father){                                  \
     if(OOPC_NULL == cthis->father->init(cthis->father, __VA_ARGS__)){ \
         if(OOPC_TRUE == father##_delete(cthis->father)){}        \
         cthis->father = OOPC_NULL;                               \
     }                                                            \
 }                                                                \
}while(0)
#else
//#define ccc_param  param1,param2...
#define CCC(father, fatherptr, param) do{                            \
 cthis->father = father##_new((void *)(fatherptr));               \
 if(OOPC_NULL != cthis->father){                                  \
     if(OOPC_NULL == cthis->father->init(cthis->father, param)){  \
         if(OOPC_TRUE == father##_delete(cthis->father)){}        \
         cthis->father = OOPC_NULL;                               \
     }                                                            \
 }                                                                \
}while(0)
#endif
/* Call real class destructor, return value cthis/OOPC_NULL. */
#define CCD(father)                     father##_delete((cthis->father))

/* Real class instantiation and release Class New/Free, any number of parameters Macros.
 **********************************************/
/* The multiple parameters of CN are determined by the parameter passing of the class instantiation configured through the init function. */
#if (OOPC_CN_CCC_SUPPORT_FLEXIABLE_PARAM == OOPC_TRUE)
#define CN(type, classptr, ...) do{                                  \
    if(OOPC_NULL != type##_new((void *)(classptr))){                 \
        if(OOPC_NULL == (classptr)->init((classptr), __VA_ARGS__)){  \
            if(OOPC_TRUE == type##_delete(classptr)){}               \
        }                                                            \
    }                                                                \
}while(0)
#else
//#define cn_param  param1,param2...
#define CN(type, classptr, param) do{                                \
    if(OOPC_NULL != type##_new((void *)(classptr))){                 \
        if(OOPC_NULL == (classptr)->init((classptr), param)){        \
            if(OOPC_TRUE == type##_delete(classptr)){}               \
        }                                                            \
    }                                                                \
}while(0)
#endif
/* Class New Without(No) Param. */
#define CNNP(type, classptr) do{                                     \
    if(OOPC_NULL != type##_new((void *)(classptr))){                 \
        if(OOPC_NULL == (classptr)->init(classptr)){                 \
            if(OOPC_TRUE == type##_delete(classptr)){}               \
        }                                                            \
    }                                                                \
}while(0)
/* ClassFree, Release class resources. */
#define CF(type, classptr) do{                                       \
    if(OOPC_NULL != (classptr)){                                     \
        if(OOPC_TRUE == type##_delete(classptr)){}                   \
    }                                                                \
}while(0)
/* Since there is no return value after calling CN/CNNP/CF/CCC,
 * use the following macro to view the operation result operation result, self/OOPC_NULL. */
#define OPRS(class)                     (class).self

#endif /*OOPC_H_*/

/**************************** Copyright(C) pxf ****************************/
