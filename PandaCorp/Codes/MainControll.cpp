#include "MainControll.h"

#include "DxLib.h"
#include "FPSManager.h"
#include "InputManager.h"
#include "DebugMsgData.h"
#include "GlobalParam.h"

#include "TitleScene.h"



MainControll::MainControll(){
	mScene = new TitleScene();
	mScene->begin();
}


MainControll::~MainControll(){
	delete mScene;			mScene = nullptr;
	delete mChangeSceneMan;	mChangeSceneMan = nullptr;
}


// �Q�[���̃��C�����[�v����
void MainControll::doMainLoop(){

	while(ScreenFlip() == 0 && ProcessMessage() != -1 && ClearDrawScreen() == 0){

		InputManager::getInstance().update();	// �v���C���[�̓��͂��X�V

		FPSManager::getInstance().adjustment();	// FPS����
		
		if(mChangeSceneMan == nullptr){
			
			scene_sig signal = mScene->update();
			if(signal.next == scene_id::END){
				break;
			}
			else if(signal.next != scene_id::NONE){
				mChangeSceneMan = new ChangeSceneManager(&mScene, signal);
			}
		}
		else{	// �V�[���J�ڒ�
			if(mChangeSceneMan->update()){
				delete mChangeSceneMan;
				mChangeSceneMan = nullptr;
			}
		}

		// ESC�L�[�������ꂽ�炢�ł��I������
		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_ESCAPE) == 1){ break; }

#ifdef _DEBUG
		std::vector<std::string> debugMsg = DebugMsgData::getInstance().getAllMsg();
		for(int i = 0; i < debugMsg.size(); i++){
			DrawString(0, i * GlobalParam::FONT_SIZE, debugMsg[i].c_str(), GetColor(255, 0, 0));
		}
#endif
	}

}
