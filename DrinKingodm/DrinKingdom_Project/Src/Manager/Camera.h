#pragma once
#include <DxLib.h>

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class Map;
class Player;
class SceneGame;

class Camera
{
public:
	// 定数

	// 矢印関連
	static constexpr int ARROW_SIZE_X = 77;       // 矢印画像の横幅
	static constexpr int ARROW_SIZE_Y = 46;       // 矢印画像の縦幅
	static constexpr int AD_SIZE_X = 48;          // 左右矢印の横幅
	static constexpr int AD_SIZE_Y = 77;          // 左右矢印の縦幅

	// カメラ移動関連
	static constexpr float CAMERA_MOVE_SPEED_W = 15.0f; // 横移動速度
	static constexpr float CAMERA_MOVE_SPEED_H = 10.0f; // 縦移動速度
	static constexpr float CAMERA_MAX_WIDTH = 800.0f;   // カメラX最大
	static constexpr float CAMERA_MIN_WIDTH = 0.0f;     // カメラX最小
	static constexpr float CAMERA_MAX_HEIGHT = 480.0f;  // カメラY最大

	// アニメーション関連
	static constexpr int ANIMATION_INIT_COUNT = 0;      // アニメーション初期カウント
	static constexpr float ANIMATION_SPEED = 0.7f;      // アニメーション速度
	static constexpr int ARROW_MOVE_MIN = -2;           // 矢印移動最小値
	static constexpr int ARROW_MOVE_MAX = 0;            // 矢印移動最大値

	// UI座標関連
	static constexpr int ARROW_W_POS_X = 1200;          // W矢印X
	static constexpr int ARROW_W_POS_Y = 480 + ARROW_SIZE_Y / 2 + 8; // W矢印Y
	static constexpr int ARROW_S_POS_X = 1200;          // S矢印X
	static constexpr int ARROW_S_POS_Y = 450;           // S矢印Y
	static constexpr int ARROW_A_POS_X = 800 + AD_SIZE_X / 2 + 8;     // A矢印X
	static constexpr int ARROW_A_POS_Y = 780;           // A矢印Y
	static constexpr int ARROW_D_POS_X = 800 - AD_SIZE_X / 2 - 8;     // D矢印X
	static constexpr int ARROW_D_POS_Y = 780;           // D矢印Y

	// 矢印の状態
	// ON：マウスカーソルが矢印に合っている
	enum class W_TOGGLE
	{
		OFF,
		ON
	};

	enum class S_TOGGLE
	{
		OFF,
		ON
	};

	enum class A_TOGGLE
	{
		OFF,
		ON
	};

	enum class D_TOGGLE
	{
		OFF,
		ON
	};

	// カメラモード
	// MODEは画面遷移中に何もできないようにしたい
	enum class MODE
	{
		NONE,
		CHANGE		// 画面遷移中
	};

	// コンストラクタ
	Camera(Map* map, Player* player);
	// デストラクタ
	~Camera(void);

	// 初期処理(基本的に最初の１回だけ実装)
	bool Init(SceneGame* parent);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(基本的に最後の１回だけ実装)
	void Release(void);

	// カメラの位置を返す
	Vector2 GetCameraPos(void);

	// 画面遷移時のモード
	void ChangeMode(MODE value);

	void MoveArrow(void);

private:
	SceneGame* sceneGame_;       // 親シーンへのポインタ
	Map* map_;                   // マップオブジェクトへのポインタ
	Player* player_;             // プレイヤーオブジェクトへのポインタ

	Vector2 mpos_;               // マウスの現在位置
	int cnt_;                   // アニメーション用カウンタ
	float speedAnim_;           // アニメーション速度

	int imgsW_[1][2];           // W矢印画像のハンドル配列
	int imgsS_[1][2];           // S矢印画像のハンドル配列
	int imgsA_[1][2];           // A矢印画像のハンドル配列
	int imgsD_[1][2];           // D矢印画像のハンドル配列

	W_TOGGLE toggleW_;          // W矢印トグル状態
	S_TOGGLE toggleS_;          // S矢印トグル状態
	A_TOGGLE toggleA_;          // A矢印トグル状態
	D_TOGGLE toggleD_;          // D矢印トグル状態

	Vector2 arrowWPos_;         // W矢印の座標
	Vector2 arrowSPos_;         // S矢印の座標
	Vector2 arrowAPos_;         // A矢印の座標
	Vector2 arrowDPos_;         // D矢印の座標

	Vector2 arrowMove_;         // 矢印のアニメーション移動量

	int directionY;             // 矢印移動方向Y
	int directionX;             // 矢印移動方向X

	MODE mode_;                 // カメラの動作モード
	AsoUtility::DIR dir_;       // カメラの移動方向

	Vector2 cameraPos_;         // カメラの現在座標

	float moveSpeedH_;          // 縦方向のカメラ移動速度
	float moveSpeedW_;          // 横方向のカメラ移動速度

	// カメラの移動
	void CameraMove(void);
};

