// #pragma once
#include "./CustomerBase.h"

class SceneGame;
class Camera;
class Player;

class IceCup : public CustomerBase
{
public:
	IceCup(Player* player, Camera* camera);
	~IceCup(void);

	void Update(void) override;
	void UpdateHot(void) override;
	void UpdateIce(void) override;

	void Draw(void) override;


	// パラメータ設定
	void SetParam(void) override;

protected:
	Camera* camera_;

	// プレイヤーのポインタ
	Player* player_;

};

