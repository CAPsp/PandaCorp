#include "MainControll.h"

#include "DxLib.h"
#include "FPSManager.h"


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
