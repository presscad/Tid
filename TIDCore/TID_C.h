// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TIDCORE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TIDCORE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef TIDCORE_EXPORTS
#define TIDCORE_API __declspec(dllexport)
#else
#define TIDCORE_API __declspec(dllimport)
#endif

#pragma once
#include "XhLdsLm.h"
#include "Buffer.h"

GECS ModelCoordSystem();
//void EnumAssemblyFirst(char* );
//IAssembly *EnumAssemblyNext();
void InitTidModel(const char* src_buf,long buf_len);
