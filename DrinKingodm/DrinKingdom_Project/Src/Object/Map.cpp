#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Scene/SceneGame.h"
#include "Map.h"

// デフォルトコンストラクタ
Map::Map(void)
{
	sceneGame_ = nullptr;

	mapimg_ = 0;

	pos_ = { 0,0 };

	type_ = TYPE::NONE;

	pos_ = { 0,0 };
}

// デストラクタ
Map::~Map(void)
{

}


bool Map::Init(SceneGame* parent)
{
	sceneGame_ = parent;
	
	mapimg_ = LoadGraph("Data/GameScene/Map_test.png");
	if (mapimg_ == -1)
	{
		OutputDebugString("map.png画像が見つからない");
		return false;
	}

	type_ = TYPE::TALK; 
	pos_ = { 0,0 };

	// 初期で使うマップを指定する
	ChangeMap(TYPE::TALK);

}

void Map::Update(void)
{

	// 現在のマップ種別を取得する
	Map::TYPE nowMapType = GetMapType();

	Vector2 cameraPos = sceneGame_->GetCameraPos();

	// マップタイプの判別
	if (cameraPos.x == TALK_POS_X && cameraPos.y == TALK_POS_Y)
	{
		type_ = TYPE::TALK;
	}
	else if (cameraPos.x == COFFEE_POS_X && cameraPos.y == COFFEE_POS_Y)
	{
		type_ = TYPE::COFFEE;
	}	
	else if (cameraPos.x == JUICE_POS_X && cameraPos.y == JUICE_POS_Y)
	{
		type_ = TYPE::JUICE;
	}
	else if (cameraPos.x == 0 && cameraPos.y == 0)
	{
		type_ = TYPE::NONE;
	}
}

void Map::Draw(void)
{
	Vector2 cameraPos = sceneGame_->GetCameraPos();

	DrawGraph(pos_.x - cameraPos.x,
		pos_.y - cameraPos.y,
		mapimg_, true);

}

bool Map::Release(void)
{
	DeleteGraph(mapimg_);

	return false;
}

// マップ種別を返す
Map::TYPE Map::GetMapType(void)
{
	return type_;
}

// マップ変更
void Map::ChangeMap(TYPE value)
{
	if (value == TYPE::TALK)
	{
		type_ = TYPE::TALK;		// 処理で利用するマップをTALKマップ
	}
	else if (value == TYPE::COFFEE)
	{
		type_ = TYPE::COFFEE;	// 処理で利用するマップをCOFFEEマップ
	}
	else if (value == TYPE::JUICE)
	{
		type_ = TYPE::JUICE;	// 処理で利用するマップをJUICEマップ
	}
}

Vector2 Map::GetMapPos(void)
{
	return pos_;
}
