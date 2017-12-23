#include "ItemStock.h"

#include <algorithm>


std::vector<Item*> ItemStock::sStockVec = std::vector<Item*>(0);


ItemStock::~ItemStock(){
	for(Item* item : sStockVec){
		delete item;
	}
	std::vector<Item*>().swap(sStockVec);
}


void ItemStock::useItem(int elem){

	if(0 <= elem && elem < checkSize()){
		if(sStockVec.at(elem)->use()){
			sStockVec.erase(sStockVec.begin() + elem);
		}
	}

}