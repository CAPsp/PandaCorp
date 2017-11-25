#include "MainControll.h"

#include "DxLib.h"
#include "FPSManager.h"

#include "GameScene.h"



MainControll::MainControll(){
	// �f�o�b�O�p
	mScene = new GameScene(0);
}


MainControll::~MainControll(){
	delete mScene;			mScene = nullptr;
	delete mChangeSceneMan;	mChangeSceneMan = nullptr;
}


// �Q�[���̃��C�����[�v����
void MainControll::doMainLoop(){

	while(ScreenFlip() == 0 && ProcessMessage() != -1 && ClearDrawScreen() == 0){

		FPSManager::getInstance().adjustment();	// FPS����
		
		if(mChangeSceneMan == nullptr){
			
			scene_sig signal = mScene->update();
			if(signal.next != scene_id::NONE){
				mChangeSceneMan = new ChangeSceneManager(mScene, signal);
			}
		}
		else{	// �V�[���J�ڒ�
			if(mChangeSceneMan->update()){
				delete mChangeSceneMan;
				mChangeSceneMan = nullptr;
			}
		}

#ifdef _DEBUG
		// ����Ɍ��݂�FPS��\��
		DrawFormatString(0, 0, GetColor(255, 0, 0), "%d", FPSManager::getInstance().getFrameNumInSec());
#endif
	}

}
