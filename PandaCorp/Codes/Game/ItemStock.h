//
// �擾�����A�C�e����ۑ����Ă�Ƃ���
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
	bool checkClearCurrentStock(Mass) const;	// �����ɓn���ꂽ�}�X�͌��݂̃A�C�e���X�g�b�N��ԂŃN���A�\�ɂȂ邩

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
	static std::vector<Item*> sStockVec;	// �F�X�ȂƂ�����̎Q�Ƃ��l���ĐÓI�ȕϐ��ɂ���

};
