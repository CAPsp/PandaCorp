//
// 2次元ベクトルの定義と様々な操作
//

#pragma once


template<typename T>
class Vec2D{
	
public:
	T x, y;

	Vec2D(T x = (T)0, T y = (T)0) :x(x), y(y){}

	Vec2D operator-(){
		return Vec2D{this->x * (T)(-1), this->y * (T)(-1)};
	}

	bool operator==(Vec2D& other){
		return (this->x == other.x) && (this->y == other.y);
	}

	Vec2D& operator=(const Vec2D& other){
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	Vec2D operator*(const T coef){
		Vec2D tmp;
		tmp.x = this->x * coef;
		tmp.y = this->y * coef;
		return tmp;
	}

	Vec2D operator+(const Vec2D other){
		Vec2D tmp;
		tmp.x = this->x + other.x;
		tmp.y = this->y + other.y;
		return tmp;
	}

	Vec2D operator-(const Vec2D other){
		Vec2D tmp;
		tmp.x = (*this).x - other.x;
		tmp.y = (*this).y - other.y;
		return tmp;
	}

	Vec2D& operator*=(const T coef){
		(*this) = (*this) * coef;
		return (*this);
	}

	Vec2D& operator+=(const Vec2D other){
		(*this) = (*this) + other;
		return (*this);
	}

	Vec2D& operator-=(const Vec2D other){
		(*this) = (*this) - other;
		return (*this);
	}

};
