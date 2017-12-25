#include "StageEndProcess.h"
#include "DxLib.h"
#include "GlobalParam.h"


void procGameover(scene_sig&);
void procClear(scene_sig&);
void procReturnStageSelect(scene_sig&);


scene_sig StageEndProcess::update(){

	scene_sig rtn;
	rtn.next = scene_id::NONE;

	switch(mCurrentState){
		case GAME_OVER:
			procGameover(rtn);
			break;

		case CLEAR:
			procClear(rtn);
			break;

		case RETURN_SELECT:
			procReturnStageSelect(rtn);

	}

	return rtn;
}


// ��ʂɃG�t�F�N�g�������A���g���C���X�e�[�W�I���ɖ߂邩��I�΂���
void procGameover(scene_sig& signal){

	static int effectPal = 0;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, effectPal);
	DrawBox(0, 0, GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y, GetColor(255, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	effectPal += 2;
	if(effectPal >= 255){
		effectPal = 255;

		// �I�����E�B���h�E�̕\��
		signal.next = STAGE_SELECT;

	}

}


// �N���A���̃X�R�A��\�����A���ɐi�ނ��X�e�[�W�I���ɖ߂邩��I�΂���
void procClear(scene_sig& signal){

	static int effectPal = 0;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, effectPal);
	DrawBox(0, 0, GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	effectPal += 2;
	if(effectPal >= 255){
		effectPal = 255;

		// �I�����E�B���h�E�̕\��
		signal.next = STAGE_SELECT;

	}
	
}


// �{���ɖ߂邩�ǂ������m�F������ɂƂǂ܂邩�X�e�[�W�I���ɖ߂邩�����߂�
void procReturnStageSelect(scene_sig&){}
