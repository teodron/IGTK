#pragma once
#include <functional>
#include "ITransitionAction.h"

using ActionFunctor = std::function<bool(const EventArgsPtr&)>;

template <class TWrappedClass>
class ActionDelegate
{
	using MethodPointer = bool (TWrappedClass::*)(const EventArgsPtr&);

public:
	ActionDelegate() = delete;
	ActionDelegate(TWrappedClass* iWrappableInstance, MethodPointer iMethodPointer) :
		m_wrappedInstance(iWrappableInstance),
		m_methodPointer(iMethodPointer)
	{
	}

	bool operator()(const EventArgsPtr& iEventArgs)
	{
		if (m_wrappedInstance == nullptr || m_methodPointer == nullptr)
		{
			return false;
		}
		return (m_wrappedInstance->*m_methodPointer)(iEventArgs);
	}
private:
	TWrappedClass*	m_wrappedInstance;
	MethodPointer	m_methodPointer;

};
/// This class is able to wrap function pointers, std::functions and lambda expressions
template <class TFunction>
class GenericTransitionAction :
	public ITransitionAction
{
public:
	GenericTransitionAction(TFunction iFunctor) :
		m_functor(iFunctor)
	{
	}

	
	~GenericTransitionAction() = default;

	bool operator()(const EventArgsPtr& iEventArgs)
	{
		return m_functor(iEventArgs);
	}

private:
	TFunction m_functor;
};

