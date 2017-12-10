//
// ステートを管理する
// テンプレートを使っているので実装はヘッダーで行う
//

#pragma once

#include "State.h"


template <class entity_type>
class StateMachine{

public:
	// 所有者、始めのステート、必要ならばグローバルステートを生成時に渡す
	StateMachine(entity_type* ow, State<entity_type>* start, State<entity_type>* global = nullptr)
		:mOwner(ow), mCurrentState(start), mGlobalState(global){}

	~StateMachine(){
		delete mCurrentState;
		delete mPreviousState;
		delete mGlobalState;
	}

	void changeState(State<entity_type>* state){
		delete mPreviousState;
		mPreviousState = mCurrentState;

		mCurrentState->Exit(mOwner);

		mCurrentState = state;

		mCurrentState->Enter(mOwner);
	}

	// 直前のステートに戻る
	void revertToPrevious(){
		changeState(mPreviousState);
	}

	void update(){
		if(mGlobalState != nullptr)		{ mGlobalState->Execute(mOwner); }
		if(mCurrentState != nullptr)	{ mCurrentState->Execute(mOwner); }
	}

private:
	entity_type* mOwner = nullptr;	// このステートマシンを所有するオブジェクト
	State<entity_type>* mCurrentState	= nullptr;
	State<entity_type>* mPreviousState	= nullptr;
	State<entity_type>* mGlobalState	= nullptr;

};