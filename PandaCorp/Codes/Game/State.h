//
// �S�ẴX�e�[�g�̐e�N���X
//

#pragma once


template <class entity_type>
class State{

public:
	virtual ~State(){}

	virtual void Enter(entity_type*) = 0;		// ���̃X�e�[�g�ɓ������Ƃ��̏���

	virtual void Execute(entity_type*) = 0;		// ���̃X�e�[�g���̏���

	virtual void Exit(entity_type*) = 0;		// ���̃X�e�[�g����o��Ƃ��̏���

};