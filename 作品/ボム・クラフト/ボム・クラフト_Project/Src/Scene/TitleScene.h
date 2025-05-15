#pragma once

#include "SceneBase.h"


class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	
	int img_;//画像
	int backImg_;//画像
	int imgr_;
	int imgBlock_;
	float rotate_;	//角度
	int count_;
	int cr_;
	int loopCount;						//文字カウント
	int FontHandle;
	int StrLen;
	bool moziFlag;						//文字フラグ

	int bgmHandle_;						//BGM
	int seDecision_;					//決定音

	void InitSoundEffect();

};
