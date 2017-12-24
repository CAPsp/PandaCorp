//
// 取得したアイテムを保存してるところ
//

#pragma once


#include "Item.h"
#include <vector>
#include "Mass.h"


class ItemStock{

public:
	ItemStock() = default;
	~ItemStock();
	void useItem(int);
	bool checkClearCurrentStock(Mass) const;	// 引数に渡されたマスは現在のアイテムストック状態でクリア可能になるか

public:
	inline int checkItemGID(int elem){
		return (0 <= elem && elem < sStockVec.size()) ? sStockVec.at(elem)->checkGID() : (-1);
	}
	inline static void addItem(Item* item){ 
		item->toVisible();
		sStockVec.push_back(item);
	}
	inline int checkSize(){ return (int)(sStockVec.size()); }

private:
	static std::vector<Item*> sStockVec;	// 色々なとこからの参照を考えて静的な変数にした

};
