#include "EnemyState.h"

#include <string>
#include "GlobalParam.h"
#include "DxLib.h"
#include "GraphManager.h"
#include "GameSceneParam.h"
#include "SoundManager.h"
#include "GameScene.h"


const std::string ENEMY_DIR_NAME = std::string(GRAPH_DIR_PATH) + "Enemy/";


// ------EnemyGlobalState�N���X�̎���------
void EnemyGlobalState::Execute(Enemy*){}



// ------EnemySearchState�N���X�̎���------
void EnemySearchState::Enter(Enemy* enemy){
	mAnimFrame = 0;
	char dir[4] = {GameObj::DIRECTON_UP, GameObj::DIRECTON_DOWN, GameObj::DIRECTON_RIGHT, GameObj::DIRECTON_LEFT};
	for(int d = 0; d < 4; d++){
		for(int i = 0;; i++){
			int id = GraphManager::getInstance().getDerivGraph(ENEMY_DIR_NAME + GRAPH_NAME + dir[d] + ".png", i, GameSceneParam::MASS_SIZE);
			if(id == -1){ break; }
			mKeepGraph[dir[d]].push_back(id);
		}
	}
	enemy->changeGraphic(mKeepGraph[enemy->checkDirection()][0]);
}


void EnemySearchState::Execute(Enemy* enemy){

	// �A�j���[�V�����J��
	mAnimFrame++;
	if((mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_NORMAL) >= mKeepGraph[enemy->checkDirection()].size()){ mAnimFrame = 0; }
	enemy->changeGraphic(mKeepGraph[enemy->checkDirection()][mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_NORMAL]);

	// ���������̂���������EnemyCautionState�ɕω�
	if(enemy->isFinding()){
		enemy->getStateMachine()->changeState(new EnemyCautionState());
	}

}


void EnemySearchState::Exit(Enemy*){
	for(auto itr = mKeepGraph.begin(); itr != mKeepGraph.end(); itr++){
		for(int id : itr->second){
			DeleteGraph(id);
		}
	}
}


// ------EnemyCautionState�N���X�̎���------
void EnemyCautionState::Enter(Enemy* enemy){
	mTimer = GameTimer(DELAY_FRAME);

	mKeepGraph = GraphManager::getInstance().getDerivGraph(ENEMY_DIR_NAME + GRAPH_NAME + enemy->checkDirection() + ".png", 0, GameSceneParam::MASS_SIZE);
	enemy->changeGraphic(mKeepGraph);
}


void EnemyCautionState::Execute(Enemy* enemy){

	// �ŏ��̉��t���[�����͊��m���Ȃ���Ԃ�����
	if(!mTimer.update()){
		if(!mDelayFinished){
			mTimer = GameTimer(CAUTION_FRAME);
			mDelayFinished = true;
		}
		else{
			enemy->getStateMachine()->changeState(new EnemySearchState());
			return;
		}
	}

	// ���������̂��݂����甭���X�e�[�g�Ɉڍs
	if(mDelayFinished && enemy->isFinding()){
		enemy->getStateMachine()->changeState(new EnemyFindState());
	}

}


void EnemyCautionState::Exit(Enemy*){
	DeleteGraph(mKeepGraph);
}


// ------EnemyDownState�N���X�̎���------
void EnemyDownState::Enter(Enemy*){}


void EnemyDownState::Execute(Enemy*){}


void EnemyDownState::Exit(Enemy*){}


// ------EnemyFindState�N���X�̎���------
void EnemyFindState::Enter(Enemy*){
	PlaySoundMem(SoundManager::getInstance().checkID("find.ogg"), DX_PLAYTYPE_BACK);
}


void EnemyFindState::Execute(Enemy*){
	if(!mDelayTimer.update()){
		GameScene::toGameOver();
	}
}


void EnemyFindState::Exit(Enemy*){}
