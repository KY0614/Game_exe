// #pragma once

#include "SceneBase.h"
#include "../Application.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneGame;

class SceneGameOver :public SceneBase
{
public:

	//画像関連

	//顔画像のサイズ
	static constexpr int FACE_SIZE_WIDTH = 473;
	static constexpr int FACE_SIZE_HEIGHT = 480;

	static constexpr int ANIM_NUM = 4;
	static constexpr int FACEANIM_NUM = 7;

	// ボタン関連
	static constexpr int BUTTON_SIZE_WIDTH = 120;	// ボタンの幅
	static constexpr int BUTTON_SIZE_HEIGHT = 70;	// ボタンの高さ
	static constexpr int BUTTON_POS_X = 140;		// ボタンのX座標
	static constexpr int TITLE_POS_Y = 300;			// タイトルボタンのY座標
	static constexpr int EXIT_POS_Y = 400;			// 終了ボタンのY座標
	static constexpr int SELECT_POS_X = 90;		// 選択している画像のX座標

	// 腕の動き関連
	static constexpr float ARM_ANGLE_MAX = 0.6f;     // 腕の回転最大角度
	static constexpr float ARM_ANGLE_MIN = -0.1f;    // 腕の回転最小角度
	static constexpr float ARM_ANGLE_SPEED = 0.01f;  // 腕の回転速度

	// 音量関連
	static constexpr int BGM_VOLUME = 140;            // BGMの音量
	static constexpr int BUTTON_SELECT_VOLUME = 230;   // ボタン選択音の音量
	static constexpr int BUTTON_PUSH_VOLUME = 180;     // ボタン押下音の音量

	//乱数tとまばたき関連
	static constexpr int BLINK_RANDOM_THRESHOLD_NONE = 90;
	static constexpr int BLINK_RANDOM_THRESHOLD_ONCE = 50;
	static constexpr int BLINK_ONCE_ANIM_NUM = 5;
	static constexpr int BLINK_TWICE_ANIM_NUM = 4;
	static constexpr int BLINK_TWICE_IMAGE_NUM = 6;

	enum class BLINK
	{
		NONE,
		ONCE,
		TWICE
	};

	SceneGameOver(void);			// コンストラクタ
	 ~SceneGameOver(void);			// デストラクタ

	bool Init(void) override;		// 初期化処理
	void Update(void) override;		// 更新処理	
	void Draw(void) override;		// 描画処理
	bool Release(void) override;	// 解放処理

private:
	// メンバー変数

	// BGM
	int bgm_;
	int buttonSelectSound_;
	int buttonPushSound_;

	// 画像
	int backImage_;
	int thankImage_;
	int playImage_;

	int title_pushImage_;
	int titleImage_;
	int exitImage_;
	int exit_pushImage_;

	int selectImage_;
	int select_onImage_;

	int crownImage_;
	int faceImage_;
	int faceImgs_[1][FACEANIM_NUM];
	int bodyImage_;
	int armImage_;

	int cursorImage_;

	bool isTitle_;
	bool isExit_;

	// マウスの位置
	Vector2 mpos_;

	Vector2 spos_;

	Vector2 crownPos_;
	Vector2 crownMove_;

	Vector2 facePos_;
	Vector2 faceMove_;

	int crownDirection;
	int faceDirection;
	int armDirection;

	int cntAnim_;
	int cntMove_;
	float moveDelay_;
	float speedAnim_;

	float moveArm_;
	float armAngle_;	
	float moveHand_;

	int animNum_;
	int blink_;

	BLINK blinkNum_;
	int blinkPersent_;
	bool isBlink_;

	int startTime;
	int elapsedTime;

	int cnt_;

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
	/// 腕を動かす処理
	/// </summary>
	/// <param name="">腕を回転させる</param>
	void MoveArm(void);

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