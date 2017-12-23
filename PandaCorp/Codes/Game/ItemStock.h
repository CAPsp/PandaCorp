//
// 取得したアイテムを保存してるところ
//

#pragma once


#include "Item.h"
#include <vector>


class ItemStock{

public:
	ItemStock() = default;
	~ItemStock();

	inline int checkItemGID(int elem){
		return (0 <= elem && elem < sStockVec.size()) ? sStockVec.at(elem)->checkGID() : (-1);
	}
	inline static void addItem(Item* item){ sStockVec.push_back(item); }


private:
	static std::vector<Item*> sStockVec;	// 色々なとこからの参照を考えて静的な変数にした

};
