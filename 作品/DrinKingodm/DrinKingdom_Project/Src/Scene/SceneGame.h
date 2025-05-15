#pragma once
#include <vector>
#include "SceneBase.h"

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"
#include "../Object/CustomerBase.h"

// 前方宣言
class SceneManager;
class Fader;
class Camera;
class Map;
class Player;
class HotCup;
class IceCup;
class Message;
class CustomerBase;

class SceneGame : public SceneBase
{
public:
	// 定数
	static constexpr int UI_SIZE_X = 50;
	static constexpr int UI_SIZE_Y = 50;

	// カメラ関連
	static constexpr float CAMERA_MAX_WIDTH = 800.0f;	// カメラの幅の最大
	static constexpr float CAMERA_MIN_WIDTH = 0.0f;		// カメラの幅の最小
	static constexpr float CAMERA_MAX_HEIGHT = 480.0f;	// カメラの高さの最大
	static constexpr float CAMERA_MIN_HEIGHT = 0.0f;	// カメラの高さの最小

	// 最大移動速度(カメラの）
	static constexpr float MAX_MOVE_WSPEED = 15.0f;
	static constexpr float MAX_MOVE_HSPEED = 10.0f;

	// 加速度(accelerator)
	static constexpr float MOVE_ACC = 0.25f;

	// 減衰(decelerate)
	static constexpr float MOVE_DEC = 0.1f;

	static constexpr int ANIM_SIZE_X = 200;
	static constexpr int ANIM_SIZE_Y = 430;

	// フェーズ
	enum class FASE
	{
		NONE,
		WAIT,	// お客待ち
		TALK,	// お客と話す
		MAKE,	// 飲み物を作る
		DRINK,	// 飲み物を渡す
		TALK2	// 渡した後の会話	

	};

	// MODEは画面遷移中に何もできないようにしたい
	enum class MODE
	{
		NONE,
		CHANGE		// 画面遷移中
	};

	enum class PAGE
	{
		NONE,
		PAGE1,
		PAGE2
	};

	SceneGame(void);		// コンストラクタ
	~SceneGame(void);		// デストラクタ

	bool Init(void);		// 初期化処理
	void Update(void);		// 更新処理	
	void Draw(void);		// 描画処理
	void DrawCursor(void);
	bool Release(void);		// 解放処理

	// カメラの位置を返す
	Vector2 GetCameraPos(void);

	// 画面遷移時のモード
	//void ChangeMode(MODE value);

	// 現在のフェーズを返す
	FASE GetFase(void);

	// フェーズを変更する
	void ChangeFase(FASE value);

	//メッセージが表示中かどうか
	bool MesSwitch(void);

	bool GetIsMesCursor(void);

	// 経過時間を返す
	int GetTime(void);

	// フェードインしながら画像を表示
	void FadeInImage(int x, int y, int imageFile, int fadeInSpeed);

	// 次来るお客が誰かを返す
	CustomerBase::CUSTOMER GetCustomer(void);

	// お客の反応を返す
	CustomerBase::REACTION GetReaction(void);

	bool GetMessCursor(void);

	// 速度制御
	void Accele(float speed);

	// 減衰制御
	void Decelerate(float speed);

	// 移動制御
	void Move(int pos);


private:

	// シーンマネージャのポインタ格納領域
	SceneManager* sceneManager_;

	Camera* camera_;

	// プレイヤー
	Player* player_;

	// 客
	HotCup* hotCup_;
	IceCup* iceCup_;

	// マップ
	Map* map_;

	// メッセージ
	Message* message_;

	//客
	std::vector<CustomerBase*> customers_;

	// マウス画像
	int cursorImage_;
	// テキストボックスの中のカーソル画像
	int messagecursorImage_;

	bool isMessCursor_;

	int imgsUI_[1][2];
	int imgRecipe_[1][2];
	int imgBack_;
	int imgBacks_[1][2];
	int imgNext_[1][2];
	
	int bookCnt_;
	int ui_;
	bool isUI_;
	bool isBack_;

	PAGE page_;

	// マウスの位置
	Vector2 mpos_;

#pragma region enum class

	// フェーズ
	FASE fase_;

	// カメラのモード
	MODE mode_;

#pragma endregion

#pragma region カメラ関連
	// 画面が遷移するときの向き
	AsoUtility::DIR dir_;

	// カメラの位置
	Vector2 cameraPos_;

	// カメラの移動
	//void CameraMove(void);


	// 移動速度
	float moveSpeedH_;	// 縦移動速度
	float moveSpeedW_;	// 横移動速度

#pragma endregion

	// フェーズを流すためのカウンター
	int counter_;

	// デバック用の色
	int color;

	//客の数
	int cnt_;

	bool hot_;
	bool ice_;

	// 経過時間管理用
	int startTime;
	int elapsedTime;

	// フェードインさせるスピード
	int fadeInSpeed_;

	int cntA;

	int animImgs_[1][3];
	int animIceImgs_[1][3];

	// BGM用
	int bgm_;

	int openBookSound_;
	int closeBookSound_;
};