/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "MocksmPseudoConditionalTestAct.h"

typedef struct _CMOCK_smPCT_tr1_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  SmPseudoConditionalTest* Expected_me;
  RKH_EVT_T* Expected_pe;

} CMOCK_smPCT_tr1_CALL_INSTANCE;

typedef struct _CMOCK_smPCT_tr2_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  SmPseudoConditionalTest* Expected_me;
  RKH_EVT_T* Expected_pe;

} CMOCK_smPCT_tr2_CALL_INSTANCE;

typedef struct _CMOCK_smPCT_setCondition_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  SmPseudoConditionalTest* Expected_me;
  RKH_EVT_T* Expected_pe;

} CMOCK_smPCT_setCondition_CALL_INSTANCE;

typedef struct _CMOCK_smPCT_onEventA_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  rbool_t ReturnVal;
  SmPseudoConditionalTest* Expected_me;
  RKH_EVT_T* Expected_pe;

} CMOCK_smPCT_onEventA_CALL_INSTANCE;

static struct MocksmPseudoConditionalTestActInstance
{
  CMOCK_MEM_INDEX_TYPE smPCT_tr1_CallInstance;
  CMOCK_MEM_INDEX_TYPE smPCT_tr2_CallInstance;
  CMOCK_MEM_INDEX_TYPE smPCT_setCondition_CallInstance;
  CMOCK_MEM_INDEX_TYPE smPCT_onEventA_CallInstance;
} Mock;

extern jmp_buf AbortFrame;

void MocksmPseudoConditionalTestAct_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.smPCT_tr1_CallInstance, cmock_line, "Function 'smPCT_tr1' called less times than expected.");
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.smPCT_tr2_CallInstance, cmock_line, "Function 'smPCT_tr2' called less times than expected.");
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.smPCT_setCondition_CallInstance, cmock_line, "Function 'smPCT_setCondition' called less times than expected.");
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.smPCT_onEventA_CallInstance, cmock_line, "Function 'smPCT_onEventA' called less times than expected.");
}

void MocksmPseudoConditionalTestAct_Init(void)
{
  MocksmPseudoConditionalTestAct_Destroy();
}

void MocksmPseudoConditionalTestAct_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

void smPCT_tr1(SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_smPCT_tr1_CALL_INSTANCE* cmock_call_instance = (CMOCK_smPCT_tr1_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.smPCT_tr1_CallInstance);
  Mock.smPCT_tr1_CallInstance = CMock_Guts_MemNext(Mock.smPCT_tr1_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'smPCT_tr1' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_me), (void*)(me), sizeof(SmPseudoConditionalTest), cmock_line, "Function 'smPCT_tr1' called with unexpected value for argument 'me'.");
  }
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_pe), (void*)(pe), sizeof(RKH_EVT_T), cmock_line, "Function 'smPCT_tr1' called with unexpected value for argument 'pe'.");
  }
}

void CMockExpectParameters_smPCT_tr1(CMOCK_smPCT_tr1_CALL_INSTANCE* cmock_call_instance, SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  cmock_call_instance->Expected_me = (SmPseudoConditionalTest*)me;
  cmock_call_instance->Expected_pe = pe;
}

void smPCT_tr1_CMockExpect(UNITY_LINE_TYPE cmock_line, SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_smPCT_tr1_CALL_INSTANCE));
  CMOCK_smPCT_tr1_CALL_INSTANCE* cmock_call_instance = (CMOCK_smPCT_tr1_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.smPCT_tr1_CallInstance = CMock_Guts_MemChain(Mock.smPCT_tr1_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_smPCT_tr1(cmock_call_instance, me, pe);
}

void smPCT_tr2(SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_smPCT_tr2_CALL_INSTANCE* cmock_call_instance = (CMOCK_smPCT_tr2_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.smPCT_tr2_CallInstance);
  Mock.smPCT_tr2_CallInstance = CMock_Guts_MemNext(Mock.smPCT_tr2_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'smPCT_tr2' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_me), (void*)(me), sizeof(SmPseudoConditionalTest), cmock_line, "Function 'smPCT_tr2' called with unexpected value for argument 'me'.");
  }
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_pe), (void*)(pe), sizeof(RKH_EVT_T), cmock_line, "Function 'smPCT_tr2' called with unexpected value for argument 'pe'.");
  }
}

void CMockExpectParameters_smPCT_tr2(CMOCK_smPCT_tr2_CALL_INSTANCE* cmock_call_instance, SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  cmock_call_instance->Expected_me = (SmPseudoConditionalTest*)me;
  cmock_call_instance->Expected_pe = pe;
}

void smPCT_tr2_CMockExpect(UNITY_LINE_TYPE cmock_line, SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_smPCT_tr2_CALL_INSTANCE));
  CMOCK_smPCT_tr2_CALL_INSTANCE* cmock_call_instance = (CMOCK_smPCT_tr2_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.smPCT_tr2_CallInstance = CMock_Guts_MemChain(Mock.smPCT_tr2_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_smPCT_tr2(cmock_call_instance, me, pe);
}

void smPCT_setCondition(SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_smPCT_setCondition_CALL_INSTANCE* cmock_call_instance = (CMOCK_smPCT_setCondition_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.smPCT_setCondition_CallInstance);
  Mock.smPCT_setCondition_CallInstance = CMock_Guts_MemNext(Mock.smPCT_setCondition_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'smPCT_setCondition' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_me), (void*)(me), sizeof(SmPseudoConditionalTest), cmock_line, "Function 'smPCT_setCondition' called with unexpected value for argument 'me'.");
  }
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_pe), (void*)(pe), sizeof(RKH_EVT_T), cmock_line, "Function 'smPCT_setCondition' called with unexpected value for argument 'pe'.");
  }
}

void CMockExpectParameters_smPCT_setCondition(CMOCK_smPCT_setCondition_CALL_INSTANCE* cmock_call_instance, SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  cmock_call_instance->Expected_me = (SmPseudoConditionalTest*)me;
  cmock_call_instance->Expected_pe = pe;
}

void smPCT_setCondition_CMockExpect(UNITY_LINE_TYPE cmock_line, SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_smPCT_setCondition_CALL_INSTANCE));
  CMOCK_smPCT_setCondition_CALL_INSTANCE* cmock_call_instance = (CMOCK_smPCT_setCondition_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.smPCT_setCondition_CallInstance = CMock_Guts_MemChain(Mock.smPCT_setCondition_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_smPCT_setCondition(cmock_call_instance, me, pe);
}

rbool_t smPCT_onEventA(SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_smPCT_onEventA_CALL_INSTANCE* cmock_call_instance = (CMOCK_smPCT_onEventA_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.smPCT_onEventA_CallInstance);
  Mock.smPCT_onEventA_CallInstance = CMock_Guts_MemNext(Mock.smPCT_onEventA_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'smPCT_onEventA' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_me), (void*)(me), sizeof(SmPseudoConditionalTest), cmock_line, "Function 'smPCT_onEventA' called with unexpected value for argument 'me'.");
  }
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_pe), (void*)(pe), sizeof(RKH_EVT_T), cmock_line, "Function 'smPCT_onEventA' called with unexpected value for argument 'pe'.");
  }
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_smPCT_onEventA(CMOCK_smPCT_onEventA_CALL_INSTANCE* cmock_call_instance, SmPseudoConditionalTest* const me, RKH_EVT_T* pe)
{
  cmock_call_instance->Expected_me = (SmPseudoConditionalTest*)me;
  cmock_call_instance->Expected_pe = pe;
}

void smPCT_onEventA_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, SmPseudoConditionalTest* const me, RKH_EVT_T* pe, rbool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_smPCT_onEventA_CALL_INSTANCE));
  CMOCK_smPCT_onEventA_CALL_INSTANCE* cmock_call_instance = (CMOCK_smPCT_onEventA_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.smPCT_onEventA_CallInstance = CMock_Guts_MemChain(Mock.smPCT_onEventA_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_smPCT_onEventA(cmock_call_instance, me, pe);
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(rbool_t));
}

