#include "StageSelectScene.h"

#include"InputManager.h"
#include "DxLib.h"

#define StageNum 6 //�X�e�[�W��

//�O���[�o���ϐ��錾
int stage_select = 0;
int step = 0;
int select_decide = 0;

scene_sig StageSelectScene::update() {
	scene_sig rtn;

	int i;
	int go_next = 0;

	DrawFormatString(200, 600, GetColor(255, 255, 255), "stage_select: %d", stage_select);


	//�X�e�[�W�I���̕`�ʏ���
	//���X�e�[�W���ς���Ƃ��ɒ����K�{��
	for (i = 0; i < StageNum; i++) {
		if (i == stage_select) {
			DrawBox(150 + i * 170, 80, 150 + i * 170 + 130, 260, GetColor(255, 255, 255), TRUE);
		}
		else {
			DrawBox(150 + i * 170, 80, 150 + i * 170 + 130, 260, GetColor(128, 128, 128), TRUE);
		}
		DrawFormatString(150 + 65 + i * 170, 170, GetColor(0, 0, 0), "%d", i);
	}

	//�X�e�[�W�I���Ɋւ��鏈��
	if (step == 0) {

		//�X�e�[�W�I���J�[�\������
		//���L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) == 1) {
			if (stage_select > 0) {
				stage_select--;
			}
		}

		//�E�L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) == 1) {
			if (stage_select < StageNum - 1) {
				stage_select++;
			}
		}
		//�G���^�[�L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RETURN) == 1) {
			step = 1;
		}
	}

	//�I����@�m�F�̏���
	else if (step == 1) {

		//�m�F�{�^���̕`��
		DrawBox(246, 134, 1034, 586, GetColor(255, 255, 0), TRUE);
		DrawBox(256, 144, 1024, 576, GetColor(255, 255, 255), TRUE);
		DrawString(530, 204,"���̃X�e�[�W�ŗV�т܂����H", GetColor(0, 0, 0));
		DrawString(360, 404, "�͂�", GetColor(0, 0, 0));
		DrawString(830, 404, "������", GetColor(0, 0, 0));

		//�J�[�\���̕`��
		DrawString(340 + select_decide*470, 404, "��", GetColor(0, 0, 0));

		//�X�e�[�W�I���J�[�\������
		//���L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) == 1) {
			if (select_decide != 0) {
				select_decide = 0;
			}
		}

		//�E�L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) == 1) {
			if (select_decide != 1) {
				select_decide = 1;
			}
		}
		//�G���^�[�L�[�̏���
		//�͂���I�񂾂�X�e�[�W��ʂ֐i�ށ@��������I�񂾂�X�e�[�W�I���̏����֖߂�
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RETURN) == 1) {
			if (select_decide == 0) {
				go_next = 1;
			}
			else {
				step = 0;
				select_decide = 0;
			}
		}
	}

	if (go_next == 0) {
		rtn.next = scene_id::NONE;
	}
	else {
		rtn.next = scene_id::GAME;
		rtn.meta = stage_select+1; // 1 �` StageNum �̒l��Ԃ�
	}

	return rtn;
}


// true��Ԃ��܂� begin�̏������p������
bool StageSelectScene::begin() {

	return true;
}

// true��Ԃ��܂� begin�̏������p������
bool StageSelectScene::end() {
	return true;
}
