#include "EnemyState.h"

#include <string>
#include "GlobalParam.h"
#include "DxLib.h"
#include "GraphManager.h"
#include "GameSceneParam.h"


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

}


void EnemySearchState::Exit(Enemy*){
	for(auto itr = mKeepGraph.begin(); itr != mKeepGraph.end(); itr++){
		for(int id : itr->second){
			DeleteGraph(id);
		}
	}
}


// ------EnemyCautionState�N���X�̎���------
void EnemyCautionState::Enter(Enemy*){}


void EnemyCautionState::Execute(Enemy*){}


void EnemyCautionState::Exit(Enemy*){}


// ------EnemyDownState�N���X�̎���------
void EnemyDownState::Enter(Enemy*){}


void EnemyDownState::Execute(Enemy*){}


void EnemyDownState::Exit(Enemy*){}


// ------EnemyFindState�N���X�̎���------
void EnemyFindState::Enter(Enemy*){}


void EnemyFindState::Execute(Enemy*){}


void EnemyFindState::Exit(Enemy*){}
