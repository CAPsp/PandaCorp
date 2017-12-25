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
		mKeepGraph[dir[d]] = GraphManager::getInstance().getGraphIDs(ENEMY_DIR_NAME + GRAPH_NAME + dir[d] + ".png");
	}
	enemy->changeGraphic(mKeepGraph[enemy->checkDirection()][0]);
}


void EnemySearchState::Execute(Enemy* enemy){

	// �p�g���[���n�_�Ɉ꒼���Ɍ����������B���x���W�����킹�悤�Ƃ���
	Vec2D<int> p = enemy->nextPatrolPoint();
	Vec2D<int> move;
	if(p.x > enemy->checkPos().x)		{ move.x = 1;	enemy->changeDirection(GameObj::DIRECTON_RIGHT);	}
	else if(p.x < enemy->checkPos().x)	{ move.x = -1;	enemy->changeDirection(GameObj::DIRECTON_LEFT);		}
	else if(p.y > enemy->checkPos().y)	{ move.y = 1;	enemy->changeDirection(GameObj::DIRECTON_DOWN);		}
	else if(p.y < enemy->checkPos().y)	{ move.y = -1;	enemy->changeDirection(GameObj::DIRECTON_UP);		}
	enemy->movePos(move);

	// �A�j���[�V�����J��
	mAnimFrame++;
	if((mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_NORMAL) >= mKeepGraph[enemy->checkDirection()].size()){
		mAnimFrame = 0;
	}
	enemy->changeGraphic(mKeepGraph[enemy->checkDirection()][mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_NORMAL]);

	// ���������̂���������EnemyCautionState�ɕω�
	if(enemy->isFinding()){
		enemy->getStateMachine()->changeState(new EnemyCautionState());
	}

}


void EnemySearchState::Exit(Enemy*){}


// ------EnemyCautionState�N���X�̎���------
void EnemyCautionState::Enter(Enemy* enemy){
	mTimer = GameTimer(DELAY_FRAME);

	mKeepGraph = (GraphManager::getInstance().getGraphIDs(ENEMY_DIR_NAME + GRAPH_NAME + enemy->checkDirection() + ".png"))[0];

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


void EnemyCautionState::Exit(Enemy*){}


// ------EnemyDownState�N���X�̎���------
void EnemyDownState::Enter(Enemy*){}


void EnemyDownState::Execute(Enemy*){}


void EnemyDownState::Exit(Enemy*){}


// ------EnemyFindState�N���X�̎���------
void EnemyFindState::Enter(Enemy* enemy){
	PlaySoundMem(SoundManager::getInstance().checkID("mitukaru.ogg"), DX_PLAYTYPE_BACK);

	int enemyG = (GraphManager::getInstance().getGraphIDs(ENEMY_DIR_NAME + GRAPH_NAME + enemy->checkDirection() + ".png"))[0];

	// �G�摜�ƃG�t�F�N�g�̃T�C�Y������
	Vec2D<int> enemySize;
	GetGraphSize(enemyG, &(enemySize.x), &(enemySize.y));
	int effectEdgeSize = enemySize.x;

	// �`��ΏۂƂȂ�O���t�B�b�N��V��������
	mKeepGraph = MakeScreen(enemySize.x, enemySize.y + effectEdgeSize, true);

	// �G�̓��Ƀr�b�N���}�[�N���ł�悤�ȃG�t�F�N�g�����������摜�����
	SetDrawScreen(mKeepGraph);
	DrawGraph(0, effectEdgeSize, enemyG, true);
	DrawCircle(effectEdgeSize / 2, effectEdgeSize / 2, effectEdgeSize / 2, GetColor(255, 255, 0), true);
	DrawCircle(effectEdgeSize / 2, effectEdgeSize / 4 * 3, effectEdgeSize / 8, GetColor(255, 0, 0), true);
	DrawOval(effectEdgeSize / 2, effectEdgeSize / 5, effectEdgeSize / 8, effectEdgeSize / 4, GetColor(255, 0, 0), true);
	SetDrawScreen(DX_SCREEN_BACK);

	enemy->changeGraphic(mKeepGraph);
}


void EnemyFindState::Execute(Enemy* enemy){
	if(!mDelayTimer.update()){
		enemy->getStateMachine()->changeState(new EnemyCautionState());
	}
}


void EnemyFindState::Exit(Enemy*){
	GameScene::toGameOver();
	DeleteGraph(mKeepGraph);
}
