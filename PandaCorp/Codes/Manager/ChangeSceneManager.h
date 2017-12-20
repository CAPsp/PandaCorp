//
// �V�[���J�ڏ�����S��
//

#pragma once


#include "BaseScene.h"


class ChangeSceneManager{

public:
	ChangeSceneManager(BaseScene** scene, scene_sig sig) :
		mScene(scene),
		mSignal(sig){}
	bool update();

private:
	BaseScene** mScene = nullptr;	// ���ݏ������Ă���V�[��(MainControll�N���X��������p��������)
	scene_sig mSignal;				// �O�V�[������킽���ꂽ�M��
	bool mIsEndBefore = false;		// �O�V�[���̏I���������I��������ǂ���

};