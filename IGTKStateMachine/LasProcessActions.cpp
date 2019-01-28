#include "stdafx.h"
#include "LasProcessActions.h"
#include "Logger.h"
#include <Windows.h>
#include <vector>

auto ConvertWString(const std::string& iString)
{

	// using vector, buffer is deallocated when function ends
	std::vector<WCHAR> widestr(iString.size() + 1);

	::MultiByteToWideChar(CP_ACP, 0, iString.c_str(), iString.size(), &widestr[0], iString.size());

	// Ensure wide string is null terminated
	widestr[iString.size()] = 0;
	return widestr;
}

void ExecuteProcessTransactionAction::ReadFromPipe()
{
	DWORD ReadCount = 0;
	char Buffer[1024] = { 0 };

	std::string data = std::string();

	while (true)
	{
		if (!ReadFile(m_stdOutReadPipe, Buffer, sizeof(Buffer) / sizeof(char), &ReadCount, 0))
			break;

		if (!ReadCount) break;

		Buffer[ReadCount] = '\0';
		data.append(&Buffer[0], ReadCount);
		
	}
	IGTKLOG(data);
}




bool ExecuteProcessTransactionAction::operator()(const EventArgsPtr& iEventArgs)
{

	ProcessArgs& processArgs = *static_cast<ProcessArgs*>(&(*iEventArgs));
	IGTKLOG("Invoking child process: " + processArgs.GetName() + " " + processArgs.GetArgs() + "\n");

	SECURITY_ATTRIBUTES saAttr;

	// Set the bInheritHandle flag so pipe handles are inherited. 

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	if (!CreatePipe(&m_stdOutReadPipe, &m_stdOutWritePipe, &saAttr, 0))
	{
		IGTKLOG("Failed to create pipes.");
		return false;
	}

	// Ensure the read handle to the pipe for STDOUT is not inherited.

	if (!SetHandleInformation(m_stdOutReadPipe, HANDLE_FLAG_INHERIT, 0))
	{
		IGTKLOG("Failed SetHandleInformation.");
		return false;
	}


	auto processName = ConvertWString(processArgs.GetName());
	auto processCmdLine = ConvertWString(processArgs.GetArgs());

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	
	ZeroMemory(&pi, sizeof(pi));

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.hStdError = m_stdOutWritePipe;
	si.hStdOutput = m_stdOutWritePipe;
	si.hStdInput = 0;
	si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	


	// Start the child process. 
	if (!CreateProcess(&processName[0],   // No module name (use command line)
						&processCmdLine[0],        // Command line
						NULL,           // Process handle not inheritable
						NULL,           // Thread handle not inheritable
						FALSE,          // Set handle inheritance to FALSE
						0,              // No creation flags
						NULL,           // Use parent's environment block
						NULL,           // Use parent's starting directory 
						&si,            // Pointer to STARTUPINFO structure
						&pi)           // Pointer to PROCESS_INFORMATION structure
						)
	{
		auto err = GetLastError();
		char errString[10];
		sprintf_s(errString, 10, "%d", err);
		IGTKLOG("CreateProcess failed. Error code = " + std::string( errString));
		return false;
	}
	
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	ReadFromPipe();
	return true;
}

ExecuteProcessTransactionAction::~ExecuteProcessTransactionAction()
{
	CloseHandle(m_stdOutReadPipe);
	CloseHandle(m_stdOutWritePipe);
}