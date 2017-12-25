#include "ItemStock.h"

#include <algorithm>
#include "SpecialMassDef.h"
#include "GraphManager.h"
#include "ItemInfoDef.h"
#include "SoundManager.h"
#include "DxLib.h"


std::vector<Item*> ItemStock::sStockVec = std::vector<Item*>(0);


ItemStock::~ItemStock(){
	for(Item* item : sStockVec){
		delete item;
	}
	std::vector<Item*>().swap(sStockVec);
}


bool ItemStock::useItem(int elem){

	if(0 <= elem && elem < checkSize()){
		if(sStockVec.at(elem)->use()){
			PlaySoundMem(SoundManager::getInstance().checkID("selectse.ogg"), DX_PLAYTYPE_BACK);
			sStockVec.erase(sStockVec.begin() + elem);
			return true;
		}
		else{
			PlaySoundMem(SoundManager::getInstance().checkID("motu.ogg"), DX_PLAYTYPE_BACK);
			return false;
		}
	}

}


bool ItemStock::checkClearCurrentStock(Mass mass) const{

	// ÉhÉAÅ{åÆÇ†ÇÈÇ©
	for(Vec2D<int> p : SpecialMass::DOOR_GRAPH_POS){
		if(mass.checkGraphID() == GraphManager::getInstance().checkID(SpecialMass::DOOR_GRAPH_PATH, p)){
			for(Item* item : sStockVec){
				if(item->checkGID() == GraphManager::getInstance().checkID(ItemInfo::PATH, ItemInfo::KEY_POS)){
					return true;
				}
			}
		}
	}

	// ëãÇ©Ç«Ç§Ç©
	for(Vec2D<int> p : SpecialMass::WINDOW_GRAPH_POS){
		if(mass.checkGraphID() == GraphManager::getInstance().checkID(SpecialMass::WINDOW_GRAPH_PATH, p)){
			for(Item* item : sStockVec){
				if(item->checkGID() == GraphManager::getInstance().checkID(ItemInfo::PATH, ItemInfo::PARACHUTE_POS)){
					return true;
				}
			}
		}
	}

	return false;
}