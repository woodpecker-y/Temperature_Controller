#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "sysparams.h"

// �豸ǩ��������ͷ���
u8 app_login_request(CJ188Pkg *pkg, const SysParams *sys_params, RunParams run_params);
u8 app_login_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params);

// ��ʱ�ϱ�������ͷ���
u8 app_report_request(CJ188Pkg *pkg, /*const*/ SysParams *sys_params, RunParams *run_params);
u8 app_report_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params, u8 *ack);

// ȷ�Ϸ���������ͷ���
u8 app_ack_request(CJ188Pkg *pkg, const SysParams *sys_params, RunParams run_params);
u8 app_normal_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params, u8 *ack);

// ����ǰ���ú���
u8 app_factory_request(CJ188Pkg *pkg, /*const*/ SysParams *sys_params, RunParams run_params);
u8 app_factory_report_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params, u8 *ack);
u8 app_factory_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params, u8 *ack);

u16 LittleANDBig_ModeCON2(u16*Input);
u32 LittleANDBig_ModeCON4(u32*Input);

#endif