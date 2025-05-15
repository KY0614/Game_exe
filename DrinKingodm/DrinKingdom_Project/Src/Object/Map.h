#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneGame;

class Map
{
public:
	// 定数
	// マップのサイズ
	static constexpr int SIZE_X = 2400;
	static constexpr int SIZE_Y = 960;

	// 各種マップの位置
	// マップ上部
	static constexpr int TALK_POS_X = 800;
	static constexpr int TALK_POS_Y = 0;

	// マップ下部右
	static constexpr int COFFEE_POS_X = 800;
	static constexpr int COFFEE_POS_Y = 480;

	// マップ下部左
	static constexpr int JUICE_POS_X = 0;
	static constexpr int JUICE_POS_Y = 480;

	// filter関連
	static constexpr int FILTER_POS_X = 1285;
	static constexpr int FILTER_POS_Y = 645;

	// マップタイプ
	enum class TYPE
	{
		NONE,
		TALK,
		COFFEE,
		JUICE
	};

	Map(void);
	~Map(void);

	bool Init(SceneGame* parent);
	void Update(void);
	void Draw(void);		// 描画処理
	bool Release(void);		// 解放処理

	// マップ種別を返す
	TYPE GetMapType(void);

	// マップ変更
	void ChangeMap(TYPE value);

	Vector2 GetMapPos(void);

private:
	int mapimg_;

	// 現在地
	Vector2 pos_;

	// 処理しているマップの種別 
	TYPE type_;

	SceneGame* sceneGame_;

};

