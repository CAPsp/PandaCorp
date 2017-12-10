//
// �X�e�[�g���Ǘ�����
// �e���v���[�g���g���Ă���̂Ŏ����̓w�b�_�[�ōs��
//

#pragma once

#include "State.h"


template <class entity_type>
class StateMachine{

public:
	// ���L�ҁA�n�߂̃X�e�[�g�A�K�v�Ȃ�΃O���[�o���X�e�[�g�𐶐����ɓn��
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

	// ���O�̃X�e�[�g�ɖ߂�
	void revertToPrevious(){
		changeState(mPreviousState);
	}

	void update(){
		if(mGlobalState != nullptr)		{ mGlobalState->Execute(mOwner); }
		if(mCurrentState != nullptr)	{ mCurrentState->Execute(mOwner); }
	}

private:
	entity_type* mOwner = nullptr;	// ���̃X�e�[�g�}�V�������L����I�u�W�F�N�g
	State<entity_type>* mCurrentState	= nullptr;
	State<entity_type>* mPreviousState	= nullptr;
	State<entity_type>* mGlobalState	= nullptr;

};