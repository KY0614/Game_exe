#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "SceneBase.h"

// 前方宣言
class Fader;

class SceneOpening :public SceneBase
{
public:
	//スペースキー押下画像サイズ
	static constexpr int SPACE_SIZE_WIDTH = 89;
	static constexpr int SPACE_SIZE_HEIGHT = 56;

	//スペースキー押下画像座標
	static constexpr int SPACE_IMAGE_POS_X = 700;
	static constexpr int SPACE_IMAGE_POS_Y = 400;

	//最大アニメーション数
	static constexpr int MAX_ANIM_NUM = 2;

	//最大待機時間
	static constexpr int WAIT_INTERVAL = 5000;

	SceneOpening(void);			// コンストラクタ
	~SceneOpening(void);		// デストラクタ

	bool Init(void) override;		// 初期化処理
	void Update(void) override;		// 更新処理	
	void Draw(void) override;		// 描画処理
	bool Release(void) override;	// 解放処理

private:
	// メンバー変数
	// 画像関連
	int operateImg_;
	int imgsSpace_[1][MAX_ANIM_NUM];

	// 音関連
	int bgm_;

	//　アニメーション関連
	int cntAnim_;
	float speedAnim_;

	//タイマー関連
	int startTime;
	int elapsedTime;

};
