/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_RKHSMA_SYNC_H
#define _MOCK_RKHSMA_SYNC_H

#include "rkhsma_sync.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mock_rkhsma_sync_Init(void);
void Mock_rkhsma_sync_Destroy(void);
void Mock_rkhsma_sync_Verify(void);




#define rkh_sma_block_Ignore() rkh_sma_block_CMockIgnore()
void rkh_sma_block_CMockIgnore(void);
#define rkh_sma_block_Expect(me) rkh_sma_block_CMockExpect(__LINE__, me)
void rkh_sma_block_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* const me);
typedef void (* CMOCK_rkh_sma_block_CALLBACK)(RKH_SMA_T* const me, int cmock_num_calls);
void rkh_sma_block_StubWithCallback(CMOCK_rkh_sma_block_CALLBACK Callback);
#define rkh_sma_block_IgnoreArg_me() rkh_sma_block_CMockIgnoreArg_me(__LINE__)
void rkh_sma_block_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_setReady_Ignore() rkh_sma_setReady_CMockIgnore()
void rkh_sma_setReady_CMockIgnore(void);
#define rkh_sma_setReady_Expect(me) rkh_sma_setReady_CMockExpect(__LINE__, me)
void rkh_sma_setReady_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* const me);
typedef void (* CMOCK_rkh_sma_setReady_CALLBACK)(RKH_SMA_T* const me, int cmock_num_calls);
void rkh_sma_setReady_StubWithCallback(CMOCK_rkh_sma_setReady_CALLBACK Callback);
#define rkh_sma_setReady_IgnoreArg_me() rkh_sma_setReady_CMockIgnoreArg_me(__LINE__)
void rkh_sma_setReady_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_setUnready_Ignore() rkh_sma_setUnready_CMockIgnore()
void rkh_sma_setUnready_CMockIgnore(void);
#define rkh_sma_setUnready_Expect(me) rkh_sma_setUnready_CMockExpect(__LINE__, me)
void rkh_sma_setUnready_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* const me);
typedef void (* CMOCK_rkh_sma_setUnready_CALLBACK)(RKH_SMA_T* const me, int cmock_num_calls);
void rkh_sma_setUnready_StubWithCallback(CMOCK_rkh_sma_setUnready_CALLBACK Callback);
#define rkh_sma_setUnready_IgnoreArg_me() rkh_sma_setUnready_CMockIgnoreArg_me(__LINE__)
void rkh_sma_setUnready_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);

#endif