//
// ゲーム全体で扱う定数を定義する
//

#pragma once


#include "Vec2DUtils.h"


#define GAME_NAME "ぱんだつ！"
#define SOUND_DIR_PATH "Res/Sound/"
#define GRAPH_DIR_PATH "Res/Graph/"

namespace GlobalParam{

	const Vec2D<int> WINDOW_SIZE = {1280, 720};
	const int COLOR_BIT_NUM = 16;

	const int FPS = 60;

	const int FONT_SIZE = 20;	// デフォルトのフォントサイズ
};