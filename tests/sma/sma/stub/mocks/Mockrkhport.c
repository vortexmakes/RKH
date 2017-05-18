/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "Mockrkhport.h"

typedef struct _CMOCK_rkh_enter_critical_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;

} CMOCK_rkh_enter_critical_CALL_INSTANCE;

typedef struct _CMOCK_rkh_exit_critical_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;

} CMOCK_rkh_exit_critical_CALL_INSTANCE;

typedef struct _CMOCK_rkh_set_tickrate_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  rui32_t Expected_tick_rate_hz;

} CMOCK_rkh_set_tickrate_CALL_INSTANCE;

typedef struct _CMOCK_rkh_get_port_version_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  char* ReturnVal;

} CMOCK_rkh_get_port_version_CALL_INSTANCE;

typedef struct _CMOCK_rkh_get_port_desc_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  char* ReturnVal;

} CMOCK_rkh_get_port_desc_CALL_INSTANCE;

static struct MockrkhportInstance
{
  CMOCK_MEM_INDEX_TYPE rkh_enter_critical_CallInstance;
  CMOCK_MEM_INDEX_TYPE rkh_exit_critical_CallInstance;
  CMOCK_MEM_INDEX_TYPE rkh_set_tickrate_CallInstance;
  CMOCK_MEM_INDEX_TYPE rkh_get_port_version_CallInstance;
  CMOCK_MEM_INDEX_TYPE rkh_get_port_desc_CallInstance;
} Mock;

extern jmp_buf AbortFrame;

void Mockrkhport_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_enter_critical_CallInstance, cmock_line, "Function 'rkh_enter_critical' called less times than expected.");
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_exit_critical_CallInstance, cmock_line, "Function 'rkh_exit_critical' called less times than expected.");
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_set_tickrate_CallInstance, cmock_line, "Function 'rkh_set_tickrate' called less times than expected.");
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_get_port_version_CallInstance, cmock_line, "Function 'rkh_get_port_version' called less times than expected.");
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_get_port_desc_CallInstance, cmock_line, "Function 'rkh_get_port_desc' called less times than expected.");
}

void Mockrkhport_Init(void)
{
  Mockrkhport_Destroy();
}

void Mockrkhport_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

void rkh_enter_critical(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_enter_critical_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_enter_critical_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_enter_critical_CallInstance);
  Mock.rkh_enter_critical_CallInstance = CMock_Guts_MemNext(Mock.rkh_enter_critical_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'rkh_enter_critical' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
}

void rkh_enter_critical_CMockExpect(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_enter_critical_CALL_INSTANCE));
  CMOCK_rkh_enter_critical_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_enter_critical_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_enter_critical_CallInstance = CMock_Guts_MemChain(Mock.rkh_enter_critical_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
}

void rkh_exit_critical(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_exit_critical_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_exit_critical_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_exit_critical_CallInstance);
  Mock.rkh_exit_critical_CallInstance = CMock_Guts_MemNext(Mock.rkh_exit_critical_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'rkh_exit_critical' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
}

void rkh_exit_critical_CMockExpect(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_exit_critical_CALL_INSTANCE));
  CMOCK_rkh_exit_critical_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_exit_critical_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_exit_critical_CallInstance = CMock_Guts_MemChain(Mock.rkh_exit_critical_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
}

void rkh_set_tickrate(rui32_t tick_rate_hz)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_set_tickrate_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_set_tickrate_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_set_tickrate_CallInstance);
  Mock.rkh_set_tickrate_CallInstance = CMock_Guts_MemNext(Mock.rkh_set_tickrate_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'rkh_set_tickrate' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_tick_rate_hz), (void*)(&tick_rate_hz), sizeof(rui32_t), cmock_line, "Function 'rkh_set_tickrate' called with unexpected value for argument 'tick_rate_hz'.");
  }
}

void CMockExpectParameters_rkh_set_tickrate(CMOCK_rkh_set_tickrate_CALL_INSTANCE* cmock_call_instance, rui32_t tick_rate_hz)
{
  memcpy(&cmock_call_instance->Expected_tick_rate_hz, &tick_rate_hz, sizeof(rui32_t));
}

void rkh_set_tickrate_CMockExpect(UNITY_LINE_TYPE cmock_line, rui32_t tick_rate_hz)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_set_tickrate_CALL_INSTANCE));
  CMOCK_rkh_set_tickrate_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_set_tickrate_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_set_tickrate_CallInstance = CMock_Guts_MemChain(Mock.rkh_set_tickrate_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_rkh_set_tickrate(cmock_call_instance, tick_rate_hz);
}

const char* rkh_get_port_version(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_get_port_version_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_get_port_version_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_get_port_version_CallInstance);
  Mock.rkh_get_port_version_CallInstance = CMock_Guts_MemNext(Mock.rkh_get_port_version_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'rkh_get_port_version' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
  return (const char*)cmock_call_instance->ReturnVal;
}

void rkh_get_port_version_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, char* cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_get_port_version_CALL_INSTANCE));
  CMOCK_rkh_get_port_version_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_get_port_version_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_get_port_version_CallInstance = CMock_Guts_MemChain(Mock.rkh_get_port_version_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = (char*)cmock_to_return;
}

const char* rkh_get_port_desc(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_get_port_desc_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_get_port_desc_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_get_port_desc_CallInstance);
  Mock.rkh_get_port_desc_CallInstance = CMock_Guts_MemNext(Mock.rkh_get_port_desc_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'rkh_get_port_desc' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
  return (const char*)cmock_call_instance->ReturnVal;
}

void rkh_get_port_desc_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, char* cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_get_port_desc_CALL_INSTANCE));
  CMOCK_rkh_get_port_desc_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_get_port_desc_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_get_port_desc_CallInstance = CMock_Guts_MemChain(Mock.rkh_get_port_desc_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = (char*)cmock_to_return;
}
