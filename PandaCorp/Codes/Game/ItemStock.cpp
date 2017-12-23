#include "ItemStock.h"


std::vector<Item*> ItemStock::sStockVec = std::vector<Item*>(0);


ItemStock::~ItemStock(){
	for(Item* item : sStockVec){
		delete item;
	}
	std::vector<Item*>().swap(sStockVec);
}