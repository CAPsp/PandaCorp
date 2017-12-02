#include "DxLib.h"

#include <string>
#include "Param.h"
#include "MainControll.h"
#include "GraphManager.h"


std::string init(){

	setlocale(LC_ALL, "japanese");	//���P�[���ݒ�(���C�h�����g�p�̂��ߕK�v)

	SetOutApplicationLogValidFlag(false);	// ���O�o�͂��s��Ȃ�

	// �E�B���h�E�T�C�Y�ƃJ���[�r�b�g����ύX����
	if(SetGraphMode(Param::WINDOW_SIZE.x, Param::WINDOW_SIZE.y, Param::COLOR_BIT_NUM) != DX_CHANGESCREEN_OK){
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

	SetMainWindowText("�ς񂾂I: Stage Editor");	// �E�B���h�E�̖��O��ύX

	SetFontSize(Param::FONT_SIZE);	// �t�H���g�T�C�Y�ύX

	GraphManager::getInstance().load(); // ���\�[�X�ǂݍ���

	return "";
}


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	// ���������� (���s�����烁�b�Z�[�W��\�����ďI������)
	std::string msg = init();
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "�G���[", MB_OK);
		return -1;
	}

	// ���C�����[�v�J�n
	MainControll::getInstance().doLoop();


	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

