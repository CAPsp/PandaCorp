#include "StateMachine.h"


template<class entity_type>
StateMachine<entity_type>::StateMachine(entity_type* ow, State<entity_type>* start, State<entity_type>* global)
	:mOwner(ow), mCurrentState(start), mGlobalState(global){}


template<class entity_type>
StateMachine<entity_type>::~StateMachine(){

	delete mCurrentState;
	delete mPreviousState;
	delete mGlobalState;
}


template<class entity_type>
void StateMachine<entity_type>::changeState(State<entity_type>* state){

	// 直前のステートの記録
	delete mPreviousState;
	mPreviousState = mCurrentState;

	mCurrentState->Exit(mOwner);

	delete mCurrentState;
	mCurrentState = state;

	mCurrentState->Enter(mOwner);

}


template<class entity_type>
void StateMachine<entity_type>::revertToPrevious(){
	changeState(mPreviousState);
}


// 更新の順番は グローバル→Current なことに注意
template<class entity_type>
void StateMachine<entity_type>::update(){
	if(mGlobalState != nullptr)		{ mGlobalState->Execute(mOwner); }
	if(mCurrentState != nullptr)	{ mCurrentState->Execute(mOwner); }
}
