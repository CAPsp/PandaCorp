//
// 各ゲームシーンを管理するSceneクラスの親クラス
//

#pragma once


enum scene_id{
	NONE,
	TITLE,
	STAGE_SELECT,
	GAME
};

typedef struct{
	int meta		= 0;
	scene_id next	= scene_id::NONE;
}scene_sig;



class BaseScene{

public:
	BaseScene() = default;
	virtual ~BaseScene() = default;

	// シーン開始の処理
	// trueを返すまでは処理が終わったことにならない
	virtual bool begin() = 0;

	// 1フレーム毎の更新処理をここでやる。
	// 戻り値によって他のシーンに遷移するかどうかが分かる
	virtual scene_sig update() = 0;
	
	// シーン終了時の処理
	// trueを返すまでは処理が終わったことにならない
	virtual bool end() = 0;

};