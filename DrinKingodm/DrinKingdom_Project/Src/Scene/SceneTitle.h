// #pragma once


#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "SceneBase.h"

class SceneTitle :public SceneBase
{
public:
	// 定数の定義
	// ボタンのサイズ
	static constexpr int SIZE_WIDTH = 120;		// 横
	static constexpr int SIZE_HEIGHT = 70;		// 縦

	// ボタンの位置
	static constexpr int BUTTON_POS_X = 550;	//X座標はそろえるので一緒

	// startボタンの位置
	static constexpr int START_POS_Y = 250;		//Y座標	

	// storyボタンの位置
	static constexpr int STORY_BUTTON_Y = 350;

	// Titleロゴ画像のサイズ
	static constexpr int TITLE_SIZE_WIDTH = 402;
	static constexpr int TITLE_SIZE_HEIGHT = 480;
	//ロゴ画像の座標
	static constexpr int TITLE_IMAGE_X = 610;
	static constexpr int TITLE_IMAGE_Y = 120;

	// 顔画像のサイズ
	static constexpr int FACE_SIZE_WIDTH = 473;
	static constexpr int FACE_SIZE_HEIGHT = 480;

	//アニメーション関連
	static constexpr int FACE_ANIM_NUM = 7;	

	//乱数関連
	static constexpr int BLINK_RANDOM_THRESHOLD_NONE = 90;
	static constexpr int BLINK_RANDOM_THRESHOLD_ONCE = 50;
	static constexpr int BLINK_ONCE_ANIM_NUM = 5;
	static constexpr int BLINK_TWICE_ANIM_NUM = 4;
	static constexpr int BLINK_TWICE_IMAGE_NUM = 6;

	// 列挙型
	// ボタンの選択状態
	enum class SELECT
	{
		START,	// 未選択
		SECRET,	// 選択
		MAX
	};

	enum class BUTTON
	{
		OFF,
		ON
	};

	enum class BLINK
	{
		NONE,
		ONCE,
		TWICE
	};

	SceneTitle(void);			// コンストラクタ
	~SceneTitle(void);			// デストラクタ

	bool Init(void) override;		// 初期化処理
	void Update(void) override;		// 更新処理	
	void Draw(void) override;		// 描画処理
	bool Release(void) override;	// 解放処理

private:
	//メンバー変数

	//BGMやSE
	int bgm_;
	int buttonSelectSound_;
	int buttonPushSound_;

	//画像を格納する変数-----------------------
	int titleImage_;
	int backImage_;

	int crownImage_;
	int faceImgs_[1][FACE_ANIM_NUM];
	int bodyImage_;

	int selectImage_;
	int select_onImage_;
	int start_onImage_;
	int start_offImage_;
	int story_onImage_;
	int story_offImage_;

	int cursorImage_;

	// -----------------------------------

	bool isSelect_;
	bool wasSelect_;

	// 選択矢印の位置
	Vector2 pos_;

	// マウスの位置
	Vector2 mpos_;

	//上下に動かす画像用座標と移動量
	Vector2 crownPos_;	//王冠座標
	Vector2 crownMove_;	//王冠移動量
	Vector2 facePos_;	//顔座標
	Vector2 faceMove_;	//顔移動量

	int animNum_;
	int blink_;

	BLINK blinkNum_;
	int blinkPersent_;
	bool isBlink_;

	int crownDirection;
	int faceDirection;

	// 選択状態
	SELECT select_;

	//ボタンの状態
	BUTTON button_;

	int cntAnim_;
	int cntMove_;
	float moveDelay_;
	float speedAnim_;

	//タイマー関連
	int startTime;		//開始時間
	int elapsedTime;	//経過時間

	/// <summary>
	/// 王冠画像を動かす処理
	/// </summary>
	/// <param name="">上下に動かす処理</param>
	void MoveCrown(void);

	/// <summary>
	/// 顔画像を動かす処理
	/// </summary>
	/// <param name="">上下に動かす処理</param>
	void MoveFace(void);

	/// <summary>
	/// まばたき用の処理
	/// </summary>
	/// <param name="">瞬きしていなときはランダムでさせる</param>
	void Blink(void);

	/// <summary>
	/// 経過時間を返す
	/// </summary>
	/// <returns>経過時間</returns>
	int GetTime(void);
};