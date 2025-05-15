#pragma once
#include "../Common/Vector2.h"


// 2Dベクトル
struct Vector2D {
	float x;
	float y;
	Vector2D operator+(const Vector2D& vec)const 
	{
		return { x + vec.x,y + vec.y };
	}
	Vector2D operator-(const Vector2D& vec)const
	{
		return { x - vec.x,y - vec.y };
	}

	Vector2D operator*(float scale)const;

	void operator += (const Vector2D & vec);
	void operator -= (const Vector2D & vec);

	Vector2D operator-()const;

	float Length()const;		// ベクトルの大きさ（長さ）
	void Normalize();			// 正規化する
	Vector2D Normalized()const;	// 正規化ベクトルを返す
};

// ベクトルに対して、座標という別名を与えている
using Position2 = Vector2D;

// サイズ
struct Size {
	int w;	// 幅
	int h;	// 高さ
};

// 矩形（長方形）
struct Rect {
	Position2 pos;	// 矩形の中心
	Size size;		// 矩形の幅
	void Draw(unsigned int color);
	int Left()const {
		return pos.x - size.w / 2;
	}	
	int Right()const {
		return pos.x + size.w / 2;
	}	
	int Top()const {
		return pos.y - size.h / 2;
	}	
	int Bottom()const {
		return pos.y + size.h / 2;
	}

};

// 円 x²+y²=r²
// 中心P(a,b)のときは
// (x-a)²+(y-b)² = r
// となる
struct Circle {
	Vector2 pos;	// 座標

	float radius;	// 半径

	void Draw(unsigned int color = 0xffffff);

};