//
// ���C�����[�v�Ȃǂ𐧌�
//

#pragma once


// �V���O���g��
class MainControll{

private:
	MainControll() = default;
	~MainControll() = default;

public:
	MainControll& operator=(const MainControll&) = delete;
	MainControll(const MainControll&) = delete;
	MainControll& operator=(MainControll&&) = delete;
	MainControll(MainControll&&) = delete;

	static MainControll& getInstance(){
		static MainControll obj;
		return obj;
	}

	void doLoop();



};