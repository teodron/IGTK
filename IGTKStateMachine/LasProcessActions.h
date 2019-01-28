#pragma once
#include "ITransitionAction.h"
#include "IEventArgs.h"
#include <string>
#include <Windows.h>

class ProcessArgs : public IEventArgs
{
public:
	ProcessArgs(const std::string& iProcessName,
		const std::string& iProcessArgs) :
		m_processName(iProcessName),
		m_processArgs(iProcessArgs)
	{
	}

	

	inline const std::string& GetName() const
	{
		return m_processName;
	}

	inline const std::string& GetArgs() const
	{
		return m_processArgs;
	}

private:
	std::string m_processName;
	std::string m_processArgs;
};

class ExecuteProcessTransactionAction :
	public ITransitionAction
{
public:
	ExecuteProcessTransactionAction() = default;
	~ExecuteProcessTransactionAction();

	bool operator()(const EventArgsPtr& iEventArgs) override;
private:
	void ReadFromPipe();

	HANDLE		m_stdOutWritePipe = 0;
	HANDLE		m_stdOutReadPipe = 0;
};

