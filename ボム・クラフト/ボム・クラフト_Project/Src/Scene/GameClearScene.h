//#pragma once
#include "SceneBase.h"

class Timer;

class GameClearScene : public SceneBase
{
public:

	// コンストラクタ
	GameClearScene(void);

	// デストラクタ
	~GameClearScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	int img_;
	int cat1Img_;
	int cat2Img_;
	int catImg_;
};

