#include "StageSelectScene.h"

#include"InputManager.h"
#include "DxLib.h"
#include "SoundManager.h"

#define StageNum 6 //�X�e�[�W��
#define PI    3.1415926535897932384626433832795f

//�O���[�o���ϐ��錾
int stage_select = 1;
int step = 0;
int select_decide = 0;
int Fontstageselect; //�X�e�[�W�I���Ŏg���Ă���t�H���g
int Stageselect_Cursor;

//�Z�[�u�f�[�^����ǂݍ��񂾒l��ۑ�����ϐ�
FILE *fp_hiscore;
int hiscore[StageNum] = { 0, 0, 0, 0, 0, 0 };//�n�C�X�R�A�ۑ��p
int stageappear = 1;//���ݏo�����Ă���X�e�[�W�̐���ۑ�

//begin, end�֐��̑���̏��������邽�߂̕ϐ��@���ꂼ��ڐA������폜
int _begin = 0;
int _end = 0;


scene_sig StageSelectScene::update() {
	scene_sig rtn;

	int i;
	int go_next = 0;

	//begin�֐��̑��� �ڐA������폜
	if (_begin == 0) {

		//begin�֐��ɓ����\��̏���
		Fontstageselect = CreateFontToHandle(NULL, 40, 5, DX_FONTTYPE_NORMAL);
		SetTransColor(255, 255, 255);
		Stageselect_Cursor = LoadGraph("test_cursor.png");

		//�ȉ��f�[�^�ǂݍ��݂̃e�X�g�p�R�[�h

		//�e�X�g�@�f�[�^��������
		/*
		fopen_s(&fp_hiscore, "test_hi.dat", "wb");
		if (fp_hiscore == NULL)
		{
			for (i = 0; i < StageNum; i++) {
				hiscore[i] = 0;
			}
		}
		else {
			fwrite(&stageappear, sizeof(int), 1, fp_hiscore);
			for (i = 0; i < StageNum; i++) {
				fwrite(&hiscore[i], sizeof(int), 1, fp_hiscore);
			}
		}
		*/

		//�e�X�g�@�f�[�^�ǂݍ���

		fopen_s(&fp_hiscore, "test_hi.dat", "rb");

		if (fp_hiscore == NULL)
		{
			for (i = 0; i < StageNum; i++) {
				hiscore[i] = 0;
			}
		}
		else {
			fread(&stageappear, sizeof(int), 1, fp_hiscore);
			for (i = 0; i < StageNum; i++) {
				fread(&hiscore[i], sizeof(int), 1, fp_hiscore);
			}
		}

		fclose(fp_hiscore);

		//�������܂Ńe�X�g�p�R�[�h

		_begin = 1;
	}

	//�X�e�[�W�I���̕`�ʏ���

	//�㕔�̏���
	//���X�e�[�W���ς���Ƃ��ɒ����K�{��
	for (i = 1; i <= stageappear; i++) {
		if (i == stage_select) {
			DrawBox(150 + (i - 1) * 170, 80, 150 + (i - 1) * 170 + 130, 260, GetColor(255, 255, 255), TRUE);

			//�J�[�\���̕`��
			DrawGraph(150 + (i - 1) * 170 + 45, 30, Stageselect_Cursor, TRUE);
		}
		else {
			DrawBox(150 + (i - 1) * 170, 80, 150 + (i - 1) * 170 + 130, 260, GetColor(128, 128, 128), TRUE);
		}
		DrawFormatStringToHandle(150 + 55 + (i - 1) * 170, 160, GetColor(0, 0, 0), Fontstageselect, "%d", i);
	}

	//�����̏���
	DrawFormatStringToHandle(156, 520, GetColor(255, 255, 255), Fontstageselect, "Stage%d", stage_select);
	DrawStringToHandle(994, 492, "�n�C�X�R�A", GetColor(255, 255, 255), Fontstageselect);
	DrawFormatStringToHandle(1009, 566, GetColor(255, 255, 255), Fontstageselect, "%08d", hiscore[stage_select - 1]);

	DrawBox(346, 320, 934, 656, GetColor(255, 255, 255), TRUE);
	DrawStringToHandle(406, 420, "�}�b�v�S�̑��Ƃ�\n�X�e�[�W�̏���\n�\������Ƃ���", GetColor(0, 0, 0), Fontstageselect);

	//�X�e�[�W�I���Ɋւ��鏈��
	if (step == 0) {

		//�X�e�[�W�I���J�[�\������
		//���L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) == 1) {
			if (stage_select > 1) {
				stage_select--;
			}

			PlaySoundMem(SoundManager::getInstance().checkID("select02.ogg"), DX_PLAYTYPE_BACK);

		}

		//�E�L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) == 1) {
			if (stage_select < stageappear) {
				stage_select++;
			}

			PlaySoundMem(SoundManager::getInstance().checkID("select02.ogg"), DX_PLAYTYPE_BACK);
		}
		//�G���^�[�L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_Z) == 1) {
			step = 1;

			PlaySoundMem(SoundManager::getInstance().checkID("selectse.ogg"), DX_PLAYTYPE_BACK);
		}
	}

	//�I����@�m�F�̏���
	else if (step == 1) {

		//�m�F�{�^���̕`��
		DrawBox(246, 134, 1034, 586, GetColor(255, 255, 0), TRUE);
		DrawBox(256, 144, 1024, 576, GetColor(255, 255, 255), TRUE);
		DrawStringToHandle(380, 204, "���̃X�e�[�W�ŗV�т܂����H", GetColor(0, 0, 0), Fontstageselect);
		DrawStringToHandle(380, 484, "�͂�", GetColor(0, 0, 0), Fontstageselect);
		DrawStringToHandle(830, 484, "������", GetColor(0, 0, 0), Fontstageselect);

		//�J�[�\���̕`��
		DrawRotaGraph2(360 + select_decide * 450, 504, 20, 20, 1.0, 2 * PI * 3 / 4, Stageselect_Cursor, TRUE);

		//�X�e�[�W�I���J�[�\������
		//���L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) == 1) {
			if (select_decide != 0) {
				select_decide = 0;
			}

			PlaySoundMem(SoundManager::getInstance().checkID("select02.ogg"), DX_PLAYTYPE_BACK);
		}

		//�E�L�[�̏���
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) == 1) {
			if (select_decide != 1) {
				select_decide = 1;
			}

			PlaySoundMem(SoundManager::getInstance().checkID("select02.ogg"), DX_PLAYTYPE_BACK);
		}
		//�G���^�[�L�[�̏���
		//�͂���I�񂾂�X�e�[�W��ʂ֐i�ށ@��������I�񂾂�X�e�[�W�I���̏����֖߂�
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_Z) == 1) {
			if (select_decide == 0) {
				go_next = 1;

				PlaySoundMem(SoundManager::getInstance().checkID("selectse.ogg"), DX_PLAYTYPE_BACK);
			}
			else {
				step = 0;
				select_decide = 0;

				PlaySoundMem(SoundManager::getInstance().checkID("selectse.ogg"), DX_PLAYTYPE_BACK);
			}
		}
	}

	if (go_next == 0) {
		rtn.next = scene_id::NONE;
	}
	else
	{
		stage_select = 1;
		step = 0;
		select_decide = 0;
		rtn.next = scene_id::GAME;
		rtn.meta = stage_select; // 1 �` StageNum �̒l��Ԃ�
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
