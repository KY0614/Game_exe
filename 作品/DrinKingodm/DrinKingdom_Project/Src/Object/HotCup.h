#pragma once
#include "../Object/CustomerBase.h"

class SceneGame;
class Camera;
class Player;

class HotCup : public CustomerBase
{
public:

	HotCup(Player* player,Camera*camera);
	~HotCup(void);

	void Update(void) override;
	void UpdateHot(void) override;
	void UpdateIce(void) override;

	void Draw(void) override;

	// パラメータ設定
	void SetParam(void) override;

protected:
	// シーンゲームのポインタ格納領域
	SceneGame* sceneGame_;

	Camera* camera_;

	// プレイヤーのポインタ
	Player* player_;

};

