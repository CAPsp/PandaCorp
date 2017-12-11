//
// �e�Q�[���V�[�����Ǘ�����Scene�N���X�̐e�N���X
//

#pragma once


enum scene_id{
	NONE,
	TITLE,
	STAGE_SELECT,
	GAME
};

typedef struct{
	int meta		= 0;
	scene_id next	= scene_id::NONE;
}scene_sig;



class BaseScene{

public:
	BaseScene() = default;
	virtual ~BaseScene() = default;

	// �V�[���J�n�̏���
	// true��Ԃ��܂ł͏������I��������ƂɂȂ�Ȃ�
	virtual bool begin() = 0;

	// 1�t���[�����̍X�V�����������ł��B
	// �߂�l�ɂ���đ��̃V�[���ɑJ�ڂ��邩�ǂ�����������
	virtual scene_sig update() = 0;
	
	// �V�[���I�����̏���
	// true��Ԃ��܂ł͏������I��������ƂɂȂ�Ȃ�
	virtual bool end() = 0;

};