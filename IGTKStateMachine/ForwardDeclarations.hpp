#pragma once
#include <memory>
class ITransitionAction;
class IEventArgs;
class State;
class Transition;
using TransitionActionPtr = std::shared_ptr<ITransitionAction>;
using EventArgsPtr = std::shared_ptr<IEventArgs>;
using StatePtr = std::shared_ptr<State>;
using TransitionPtr = std::shared_ptr<Transition>;