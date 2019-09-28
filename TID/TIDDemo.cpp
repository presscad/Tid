#include "stdafx.h"
#include "Buffer.h"
#include "LogFile.h"
//ͨ���ܵ�����TID.exe
BOOL CreateTIDProcess( HANDLE hClientPipeRead, HANDLE hClientPipeWrite )
{
	//step1:��ȡ���ؼ������·��
	TCHAR cmd_str[MAX_PATH]="E:\\Structure\\TID\\Debug\\";
#ifndef _DEBUG
	GetSysPath(cmd_str);
#endif
	strcat(cmd_str,"TID.exe -child");

	STARTUPINFO startInfo;
	memset( &startInfo, 0 , sizeof( STARTUPINFO ) );
	startInfo.cb= sizeof( STARTUPINFO );
	startInfo.dwFlags |= STARTF_USESTDHANDLES;
	startInfo.hStdError= 0;
	startInfo.hStdInput= hClientPipeRead;
	startInfo.hStdOutput= hClientPipeWrite;

	PROCESS_INFORMATION processInfo;
	memset( &processInfo, 0, sizeof(PROCESS_INFORMATION) );

	BOOL b=CreateProcess( NULL,cmd_str,
		NULL,NULL, TRUE,CREATE_NEW_CONSOLE, NULL, NULL,&startInfo,&processInfo);
	DWORD er=GetLastError();
	return b;

}
BOOL WriteToTIDClient(HANDLE hPipeWrite)
{
	if( hPipeWrite == INVALID_HANDLE_VALUE )
		return FALSE;
	//TODO:��Ҫ��ɲ�����Ҫ��TID�ļ�
	CString sFilePath="D:\\TID_FILE\\ZMC2.tid";
	CBuffer file_buffer(10000);
	file_buffer.WriteString(sFilePath);	//д��TID�ļ�·��
	//
	return file_buffer.WriteToPipe(hPipeWrite,1024);
}
void RunTIDProcess()
{
	//������һ���ܵ�: ���ڷ���������ͻ��˷�������
	SECURITY_ATTRIBUTES attrib;
	attrib.nLength = sizeof( SECURITY_ATTRIBUTES );
	attrib.bInheritHandle= true;
	attrib.lpSecurityDescriptor = NULL;
	HANDLE hPipeClientRead=NULL, hPipeSrcWrite=NULL;
	if(!CreatePipe( &hPipeClientRead, &hPipeSrcWrite, &attrib, 0 ) )
	{
		logerr.Log("���������ܵ�ʧ��!GetLastError= %d\n", GetLastError() );
		return;
	}
	HANDLE hPipeSrcWriteDup=NULL;
	if( !DuplicateHandle( GetCurrentProcess(), hPipeSrcWrite, GetCurrentProcess(), &hPipeSrcWriteDup, 0, false, DUPLICATE_SAME_ACCESS ) )
	{
		logerr.Log("���ƾ��ʧ��,GetLastError=%d\n", GetLastError() );
		return;
	}
	CloseHandle(hPipeSrcWrite);
	//�����ڶ����ܵ������ڿͻ�����������˷�������
	HANDLE hPipeClientWrite=NULL, hPipeSrcRead=NULL;
	if( !CreatePipe( &hPipeSrcRead, &hPipeClientWrite, &attrib, 0) )
	{
		logerr.Log("�����ڶ��������ܵ�ʧ��,GetLastError=%d\n", GetLastError() );
		return;
	}
	HANDLE hPipeSrcReadDup=NULL;
	if( !DuplicateHandle( GetCurrentProcess(), hPipeSrcRead, GetCurrentProcess(), &hPipeSrcReadDup, 0, false, DUPLICATE_SAME_ACCESS ) )
	{
		logerr.Log("���Ƶڶ������ʧ��,GetLastError=%d\n", GetLastError() );
		return;
	}
	CloseHandle(hPipeSrcRead );
	//�����ӽ���,
	if(!CreateTIDProcess(hPipeClientRead,hPipeClientWrite))
	{
		logerr.Log("�����ӽ���ʧ��\n" );
		return;
	}
	if(WriteToTIDClient(hPipeSrcWriteDup))
	{
		logerr.Log("���ݴ���ʧ��");
		return;
	}
	if(logerr.IsHasContents())
		logerr.ShowToScreen();
}