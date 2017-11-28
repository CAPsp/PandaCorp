#include "DxLib.h"
#include <string>

#include "GlobalParam.h"
#include "MainControll.h"
#include "SoundManager.h"
#include "GraphManager.h"


std::string init();		// ������������S�� ���s�ŉ�������̕����񂪕Ԃ�
void end();				// �I��������S��


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	// ���������� (���s�����烁�b�Z�[�W��\�����ďI������)
	std::string msg = init();
	if(msg != ""){ 
		MessageBox(NULL, msg.c_str(), "�G���[", MB_OK);
		return -1;
	}

	// ���C�����[�v�J�n
	MainControll::getInstance().doMainLoop();

	end();	// �I������

	return 0;
}


std::string init(){

	setlocale(LC_ALL, "japanese");	//���P�[���ݒ�(���C�h�����g�p�̂��ߕK�v)

	// ���O�o�͂��s��Ȃ�
	SetOutApplicationLogValidFlag(false);

	// �E�B���h�E�T�C�Y�ƃJ���[�r�b�g����ύX����
	if(SetGraphMode(GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y, GlobalParam::COLOR_BIT_NUM) != DX_CHANGESCREEN_OK){
		return "�E�B���h�E�T�C�Y��ύX�ł��܂���ł���";
	}

	// �t���X�N���[�� �� �E�B���h�E
	if(ChangeWindowMode(true) != DX_CHANGESCREEN_OK){
		return "�E�B���h�E���[�h�ւ̈ڍs�Ɏ��s���܂���";
	}

	// DX���C�u��������������
	if(DxLib_Init() == -1){
		return "DX���C�u�����̏����������Ŏ��s���܂���";
	}

	SetDrawScreen(DX_SCREEN_BACK);	//�`���𗠉�ʂ�

	SetMainWindowText(GAME_NAME);	// �E�B���h�E�̖��O��ύX

	SetFontSize(GlobalParam::FONT_SIZE);	// �f�t�H���g�Ŏg���t�H���g�T�C�Y��ύX

	// ���\�[�X�̓ǂݍ���
	SoundManager::getInstance().load();
	GraphManager::getInstance().load();

	return "";
}


void end(){

	//�������ɓǂݍ��񂾃O���t�B�b�N�f�[�^�̊J��
	InitGraph();
	InitMask();

	InitSoundMem();	//�������ɓǂݍ��񂾃T�E���h�f�[�^�̊J��

	DxLib_End();
}