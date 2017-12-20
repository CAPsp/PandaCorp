#include "ChangeSceneManager.h"

#include "DebugMsgData.h"

#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"


// return: 
//	true = �J�ڏ������I��������Ƃ�����
//	false = �J�ڏ������I����Ă��Ȃ�
bool ChangeSceneManager::update(){

	// �O�V�[���̏I������
	if(!mIsEndBefore){

		// �I���������I������玟�̃V�[���̃C���X�^���X�𐶐�
		if((*mScene)->end()){

			// �V�[���؂�ւ����Ƀf�o�b�O���b�Z�[�W������������
			DebugMsgData::getInstance().deleteData();

			delete *mScene;
			*mScene = nullptr;
			
			switch(mSignal.next){

				case scene_id::TITLE:
					*mScene = new TitleScene();
					break;

				case scene_id::STAGE_SELECT:
					*mScene = new StageSelectScene();
					break;

				case scene_id::GAME:
					*mScene = new GameScene(mSignal.meta);
					break;

				default:
					// TODO: ��O��������
					break;

			}

			mIsEndBefore = true;
		}
	}

	//  ���V�[���̊J�n����
	return (*mScene)->begin();
}