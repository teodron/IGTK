// IGTKStateMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Logger.h"
#include "StateMachine.h"
#include "ITransitionAction.h"
#include "StringEventArgs.h"
#include "GenericTransitionAction.h"

enum Events
{
	eAtoB,
	eAtoC,
	eBtoD,
	eCtoD,
	eDtoA
};
/*  Layout of a simple test state machine
		--->B---\
	   /		 \
   *A -				->D-----\
	 ^ \		 /			 \
	  \	--->C---/			  \
	   \______________________/

*/

class SuccessfulTransitionAction : public ITransitionAction
{
public:
	SuccessfulTransitionAction(const std::string& iTransitionString) :
		m_transitionString(iTransitionString)
	{
	}

	bool operator()(const EventArgsPtr& iEventArgs) override
	{
		IGTKLOG(m_transitionString);
		if (iEventArgs != nullptr)
		{
			IGTKLOG((std::string)(*static_cast<StringEventArgs*>(iEventArgs.get())));
		}
		else
		{
			IGTKLOG(" empty args ");
		}
		return true;
	}

private: 
	std::string m_transitionString;
};

struct OutgoingAction
{
	bool Pre(const EventArgsPtr& iEventArgs)
	{
		IGTKLOG(m_bundleName);
		if (iEventArgs != nullptr)
		{
			IGTKLOG((std::string)(*static_cast<StringEventArgs*>(iEventArgs.get())));
		}
		else
		{
			IGTKLOG(" Empty args. Failure. ");
			return false;
		}
		return true;
	}

	bool Post(const EventArgsPtr& iEventArgs)
	{
		IGTKLOG(m_bundleName);
		if (iEventArgs != nullptr)
		{
			return Pre(iEventArgs);
		}

		return Pre(std::make_shared<StringEventArgs>("Outgoing successful."));
	}
	std::string m_bundleName;
};

bool ActionFunction(const EventArgsPtr& iEventArgs)
{
	IGTKLOG(" Attempting transition function. ");
	if (iEventArgs != nullptr)
	{
		IGTKLOG((std::string)(*static_cast<StringEventArgs*>(iEventArgs.get())));
	}
	return true;
}

struct StaticStruct
{
	static bool Action(const EventArgsPtr& iEventArgs)
	{
		IGTKLOG(" Attempting transition function. ");
		return ActionFunction(iEventArgs);
	}
};

bool BindableActionFunction(const std::string& iTransitionName, const EventArgsPtr& iEventArgs)
{
	IGTKLOG(iTransitionName);
	return ActionFunction(iEventArgs);
}

int main()
{
	IGTKLOG("State machine test");
	std::string a_b = "a->b";
	std::string a_c = "a->c";
	std::string b_d = "b->d";
	std::string c_d = "c->d";
	std::string d_a = "d->a";
	EventArgsPtr a_b_str = std::make_shared<StringEventArgs>(a_b);
	EventArgsPtr a_c_str = std::make_shared<StringEventArgs>(a_c);
	EventArgsPtr c_d_str = std::make_shared<StringEventArgs>(c_d);
	EventArgsPtr b_d_str = std::make_shared<StringEventArgs>(b_d);
	EventArgsPtr d_a_str = std::make_shared<StringEventArgs>(d_a);

	StateMachine stateMachine({ "A", "B", "C", "D" });
	size_t a_id = State::Factory::GetByName("A")->GetId();
	size_t b_id = State::Factory::GetByName("B")->GetId();
	size_t c_id = State::Factory::GetByName("C")->GetId();
	size_t d_id = State::Factory::GetByName("D")->GetId();
	// a->b
	OutgoingAction action_a_b;
	action_a_b.m_bundleName = a_b;
	OutgoingAction action_a_c;
	action_a_c.m_bundleName = a_c;
	ActionDelegate<OutgoingAction> delegate_a_b_pre(&action_a_b, &OutgoingAction::Pre);
	ActionDelegate<OutgoingAction> delegate_a_b_post(&action_a_b, &OutgoingAction::Post);
	stateMachine.CreateTransition(eAtoB, a_id, b_id, CreateTransitionActionPtr(delegate_a_b_pre), CreateTransitionActionPtr(delegate_a_b_post));
	// a->c
	ActionDelegate<OutgoingAction> delegate_a_c_pre(&action_a_c, &OutgoingAction::Pre);
	ActionDelegate<OutgoingAction> delegate_a_c_post(&action_a_c, &OutgoingAction::Post);
	stateMachine.CreateTransition(eAtoC, a_id, c_id, CreateTransitionActionPtr(&action_a_c, &OutgoingAction::Pre), CreateTransitionActionPtr(delegate_a_c_post));
	// c->d
	auto action_c_d_pre = ActionFunctor(&ActionFunction);
	auto action_c_d_post = [](const EventArgsPtr& iArgs)->bool { IGTKLOG("c->d_post"); return true;};
	stateMachine.CreateTransition(eCtoD, c_id, d_id, CreateTransitionActionPtr(action_c_d_pre), CreateTransitionActionPtr(action_c_d_post));
	// b->d
	auto action_b_d = ActionFunctor(&ActionFunction);
	//stateMachine.CreateTransition(eBtoD, b_id, d_id, CreateTransitionActionPtr(&StaticStruct::Action), CreateTransitionActionPtr(&ActionFunction));
	stateMachine.CreateTransition(eBtoD, b_id, d_id, nullptr, CreateTransitionActionPtr(&ActionFunction));
	// d->a
	auto boundFunction2 = std::bind(BindableActionFunction, d_a, std::placeholders::_1);
	boundFunction2(d_a_str);
	auto boundFunction = std::bind(BindableActionFunction, d_a, std::placeholders::_1);
	auto action_d_a_pre = CreateTransitionActionPtr(boundFunction);
	stateMachine.CreateTransition(eDtoA, d_id, a_id, action_d_a_pre, CreateTransitionActionPtr(
		[&d_a_str](const EventArgsPtr& iArgs)
	{
		IGTKLOG(*(StringEventArgs*)(&*iArgs)); return false;
	}
	));

	// attempt transitions now
	
	stateMachine.OnEvent(eAtoB, a_b_str, a_b_str);  // go to b
	stateMachine.OnEvent(eAtoC, a_b_str, a_b_str);  // go to c
	stateMachine.OnEvent(eBtoD, b_d_str, b_d_str);  // go to d
	stateMachine.OnEvent(eDtoA, d_a_str, d_a_str);  // go to a
	stateMachine.OnEvent(eAtoC, a_c_str, a_c_str);  // go to c
	//stateMachine.OnEvent(eCtoD, c_d_str, c_d_str);  // go to d
	StateMachine::NotifyEvent(eCtoD, c_d_str, c_d_str);

	return 0;
}
