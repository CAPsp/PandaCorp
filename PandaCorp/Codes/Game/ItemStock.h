//
// �擾�����A�C�e����ۑ����Ă�Ƃ���
//

#pragma once


#include "Item.h"
#include <vector>


class ItemStock{

public:
	ItemStock() = default;
	~ItemStock();
	void useItem(int);

	inline int checkItemGID(int elem){
		return (0 <= elem && elem < sStockVec.size()) ? sStockVec.at(elem)->checkGID() : (-1);
	}
	inline static void addItem(Item* item){ sStockVec.push_back(item); }
	inline int checkSize(){ return (int)(sStockVec.size()); }

private:
	static std::vector<Item*> sStockVec;	// �F�X�ȂƂ�����̎Q�Ƃ��l���ĐÓI�ȕϐ��ɂ���

};
