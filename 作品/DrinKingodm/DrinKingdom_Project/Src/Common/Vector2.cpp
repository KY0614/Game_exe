#include "DxLib.h"
#include "Vector2.h"
#include "Vector2F.h"

// デフォルトコンストラクタ
Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}

// コンストラクタ
Vector2::Vector2(int ix, int iy)
{
	x = ix;
	y = iy;
}

// デストラクタ
Vector2::~Vector2(void)
{
	OutputDebugString("Vector2　デストラクタ\n");
}

// Vector2Fへ変換
Vector2F Vector2::ToVector2F(void)
{
	Vector2F ret;
	ret.x = static_cast<float>(x);
	ret.y = static_cast<float>(y);
	return ret;
}