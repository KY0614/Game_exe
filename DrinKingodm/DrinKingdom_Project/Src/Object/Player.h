#pragma once

#include "../Common/Vector2.h"
#include "../Common/Geometry.h"
#include "../Utility/AsoUtility.h"

class Map;
class SceneGame;

class Player
{
public:
	
	static constexpr int POINT_SIZE_X = 54;
	static constexpr int POINT_SIZE_Y = 54;

	static constexpr int PUSHKEY_SIZE_X = 76;
	static constexpr int PUSHKEY_SIZE_Y = 69;

	static constexpr int PUSHKEY_MAX_NUM = 2;

#pragma region FILTER関連
	// filter関連
	// filterのサイズ
	static constexpr int FSIZE_X = 42;
	static constexpr int FSIZE_Y = 113;
	// beansのサイズ
	static constexpr int BSIZE_X = 39;
	static constexpr int BSIZE_Y = 6;

	// filterの初期位置
	static constexpr int FILTER_POS_X = 1431;
	static constexpr int FILTER_POS_Y = 585;
	
	// grinderの下の位置
	static constexpr int FILTER_GPOS_X = 1125;
	static constexpr int FILTER_GPOS_Y = 670;
	
	// tamperの隣の位置
	static constexpr int FILTER_TPOS_X = 1511;
	static constexpr int FILTER_TPOS_Y = 741;

	// マシンにセットする位置
	static constexpr int FILTER_CPOS_X = 927;
	static constexpr int FILTER_CPOS_Y = 642;

	// セットを確定させる時に増やす値
	static constexpr int SET_POS = 7;

	// filter画像の状態の数
	static constexpr int FILTER_NUM = 4;	// 将来的に５くらいほしい
									// (初期,選択時,take時,in時,カス時）

	// filterの状態
	enum class FILTER
	{
		NONE,			// 0
		SELECT,			// 1
		TAKE,			// 2
		SELECT_G,		// 3
		SET_G,			// 4  
		SELECT_T,		// 5
		SET_T,			// 6
		SELECT_M,		// 7
		SET_M,			// 8
		DUST
	};

#pragma endregion

#pragma region TAMPER関連
	// tamper関連
	// tamperのサイズ
	static constexpr int TSIZE_X = 39;
	static constexpr int TSIZE_Y = 52;

	// tamperの初期位置
	static constexpr int TAMPER_POS_X = 1570;
	static constexpr int TAMPER_POS_Y = 719;
	// tamperがfilter上部の位置
	static constexpr int TAMPER_FPOS_X = 1510;
	static constexpr int TAMPER_FPOS_Y = 680;	// 700

	// Stampするときのゲージの最大値
	static constexpr int MAX_COUNT = 40;

	// tamper画像の状態の数
	static constexpr int TAMPER_NUM = 2;	

	// tamperの状態
	enum class TAMPER
	{
		NONE,
		SELECT,
		TAKE,
		SET_F,
		STAMP,
		FINISH
	};

#pragma endregion

#pragma region GRINDER関連
	// grinder関連
	// grinderのサイズ
	static constexpr int GSIZE_X = 85;
	static constexpr int GSIZE_Y = 245;
	// grinderの初期位置
	static constexpr int GRINDER_POS_X = 1125/*1177*/;
	static constexpr int GRINDER_POS_Y = 629;

	static constexpr int GRINDER_NUM = 2;

	// grinderの状態
	enum class GRINDER
	{
		NONE,
		SELECT,
		TAKE,
		SET_G,
		INCOFFEE,
		SET_C
	};

#pragma endregion

#pragma region CUP関連

	// 画像サイズ
	static constexpr int CUP_SIZE_X = 65;
	static constexpr int CUP_SIZE_Y = 64;

	static constexpr int ICECUP_SIZE_X = 51;
	static constexpr int ICECUP_SIZE_Y = 66;

	// 初期位置
	// HotCup
	static constexpr int HOTCUP_POS_X = 850/*1293*/;
	static constexpr int HOTCUP_POS_Y = 928/*718*/;

	// IceCup
	static constexpr int ICECUP_POS_X = 925/*1293*/;
	static constexpr int ICECUP_POS_Y = 928/*718*/;

	static constexpr int CENTER_POS_X = 933;
	static constexpr int CENTER_POS_Y = 679;

	static constexpr int LEFT_POS_X = 856;
	static constexpr int LEFT_POS_Y = 679;

	static constexpr int HOTCUP_NUM = 4;
	static constexpr int ICECUP_NUM = 7;

	enum class HOTCUP
	{
		NONE,
		SELECT,
		TAKE,
		MACHINE_CENTER,		//
		MACHINE_LEFT,		//
		SET_CENTER,				//
		SET_LEFT,				//
		FINISH
	};

	enum class ICECUP
	{
		NONE,
		SELECT,
		TAKE,
		ICEDISPENSER,
		SET_ICE,
		MACHINE_CENTER,		//
		MACHINE_LEFT,		//
		SET_CENTER,				//
		SET_LEFT,				//
		FINISH
	};

#pragma endregion

#pragma region MILK & PITCHER
	// サイズ
	static constexpr int PITCHER_SIZE_X = 80;
	static constexpr int PITCHER_SIZE_Y = 62;	
	
	static constexpr int REIZOU_SIZE_X = 159;
	static constexpr int REIZOU_SIZE_Y = 179;

	// 初期位置
	static constexpr int PITCHER_POS_X = ICECUP_POS_X + PITCHER_SIZE_X;
	static constexpr int PITCHER_POS_Y = ICECUP_POS_Y + 2;

	static constexpr int PITCHER_DESKPOS_X = 1359;
	static constexpr int PITCHER_DESKPOS_Y = 720;

	// 状態の種類
	static constexpr int PITCHER_NUM = 5;
	static constexpr int MILK_NUM = 2;

	// ピッチャーの状態
	enum class PITCHER
	{
		NONE,			// 
		SELECT,			// 選んでいる状態
		TAKE,			// 持っている状態
		SELECT_DESK,
		SET_DESK,
		SELECT_M,		// マシンを選んでいる状態
		SET_M,			// マシンにセットしている状態
		READY_POUR,		// カップ上部で注ぐ準備をしている状態
		POUR			// カップに注いでいる状態
	};

	// 牛乳の状態
	enum class MILK
	{
		NONE,			//
		SELECT,			// 選んでいる状態
		TAKE,			// 持っている状態
		READY_POUR,		// ピッチャー上部で注ぐ準備をしている状態
		POUR			// ピッチャーに注いでいる状態
	};

	// 冷蔵庫の状態
	enum class REIZOU
	{
		NONE,			//
		SELECT			// 選んでいる状態
	};
#pragma endregion


	// 作ったもの（ホットメニュー）
	enum class HOTMENU
	{
		NONE,		// 作っていない（できていない）
		ESPRESSO,	// エスプレッソ
		AMERICANO,	// アメリカ―ノ
		LATTE,		// ラテ
		MOCA,		// モカ
		MACCHIATO	// マキアート
	};

	// 作ったもの（アイスメニュー）
	enum class ICEMENU
	{
		NONE,		// 作っていない（できていない）
		ESPRESSO,	// エスプレッソ
		AMERICANO,	// アメリカ―ノ
		LATTE,		// ラテ
		MOCA,		// モカ
		MACCHIATO	// マキアート
	};

	// マウスのカーソル画像のサイズ
	static constexpr int CURSOR_SIZE_X = 20;
	static constexpr int CURSOR_SIZE_Y = 22;

	Player(Map& map);			// コンストラクタ
	~Player(void);				// デストラクタ

	bool Init(SceneGame* parent);		// 初期化処理

	void Update(void);			// 更新処理	
	void UpdateTalk(void);		// TALK
	void UpdateMake(void);		// MAKE	
	void UpdateDrink(void);		// DRINK
	void UpdateTalk2(void);		// TALK2

	void Draw(void);			// 描画処理
	void DrawWait(void);
	void DrawTalk(void);
	void DrawMake(void);
	void DrawDrink(void);
	void DrawTalk2(void);

	bool Release(void);		// 解放処理

	void SetPointPos(Vector2 pos,AsoUtility::DIR dir);
	void IsPoint(bool value) { isPoint_ = value; }
	void MovePoint(void);

#pragma region FILTER関連の関数
	// filter関連の関数------------------------------------------------------------------------------
	void ChangeFilter(FILTER value) { filter_ = value; }	// FILTERのモードを変える
	FILTER GetFilter(void) { return filter_; }				// FITLERの現在のモードを取得する
	void SetFilterPos(Vector2 value) { filterPos_ = value; }	// FILTERの座標を設定する
	void StampFilter(bool value) { beansStamp_ = value; }		// FILTERの中をSTAMPしたか
	void BeansFilter(bool value) { beansIn_ = value; }		// FILTERの中にBEANSがあるかどうか
	void BeansState(bool In, bool Stamp, bool Brew, bool Dust);		// FILTERの中のBeansの状態を変更
	bool GetBeansIn(void) { return beansIn_; }				// beansInの状態を取得する
	bool GetBeansStamp(void) { return beansStamp_; }			// beansStampの状態を取得する
	bool GetBeansBrew(void) { return beansBrew_; }			// beansBrewの状態を取得する
	void DustBeans(void);				// beansの変数を初期化する
#pragma endregion

	//アイテムを今持っているかどうか----------------------------------------------------------------------
	bool IsHolding(void);				// プレイヤーが手に何か持っているか(true:持っている)
	bool IsSetMachineCenter(void);		// マシン中央に何かセットされているか
	bool IsSetMachineLeft(void);		// マシン左側に何かセットされているか

	// tamper関連の関数--------------------------------------------------------------------------------
	void ChangeTamper(TAMPER value) { tamper_ = value; }	// TAMPERのモードを変える
	TAMPER GetTamper(void) { return tamper_; }				// TAMPERの現在のモードを取得する
	void SetTamperPos(Vector2 value) { tamperPos_ = value; }	// TAMPERの座標を設定する

	// cup関連の関数--------------------------------------------------------------------------------
	void ChangeHotCup(HOTCUP value) { cup_ = value; }	// HOTCUPのモードを変える
	HOTCUP GetHotCup(void) { return cup_; }

	void ChangeIceCup(ICECUP value) { iceCup_ = value; }	// ICECUPのモードを変える
	ICECUP GetIceCup(void){ return iceCup_; }

	// 牛乳とピッチャー関連の関数--------------------------------------------------------------------
	void ChangePitcher(PITCHER value) { pitcher_ = value; }	// PITCHERのモードを変える
	PITCHER GetPitcher(void){ return pitcher_; }

	void ChangeMilk(MILK value) { milk_ = value; }	// PITCHERのモードを変える
	MILK GetMilk(void) { return milk_; }

	// メニュー関連の関数----------------------------------------------------------------------------
	HOTMENU GetHotMenu(void) { return hotMenu_; }				// ホットメニューを得る
	ICEMENU GetIceMenu(void) { return iceMenu_; }				// アイスメニューを得る
	void ResetHotMenu(void) { hotMenu_ = HOTMENU::NONE; }				// hotMenu_をリセット(NONE)にする
	void ResetIceMenu(void) { iceMenu_ = ICEMENU::NONE; }				// hotMenu_をリセット(NONE)にする

	void MoveCaution(void);

	void SetColor(int value){ color_ = value; }

	// 押し出し処理関連--------------------------------------------------------------

	int SignVal(float value);

	bool IsHit(const Rect& rcA, const Rect& rcB);

	// 音関連 -----------------------------------------------------------------------
	void PlaySounds(int SoundName, int Vol);	// 読み込んだ音を再生する用

private:
	Map& map_;

	Vector2 mpos_;

	SceneGame* sceneGame_;

	// お助け矢印関連の変数-----------------
	// 矢印の画像
	int imgsPoint_[1][static_cast<int>(AsoUtility::DIR::MAX)];
	// カーソル下キーを押す画像
	int imgsPushKey_[2][PUSHKEY_MAX_NUM];

	AsoUtility::DIR dir_;

	Vector2 pointPos_;
	Vector2 pointMove_;
	Vector2 pushPos_;

	bool isPoint_;
	bool isPushKey_;

	int pointDirection_;

	int pushKey_;	// 0:down , 1:up

	int cntAnim_;
	float speedAnim_;

	// ------------------------------------

	// カーソル画像
	int cursorImage_;
	// テキストボックスの中のカーソル画像
	int messagecursorImage_;

#pragma region filter関連
	// fitler画像
	int imgsfilter_[2][FILTER_NUM];
	// beans単体画像
	int imgbeans_;
	// コーヒー豆を捨てるように出る警告画像
	int imgdust_;

	int imgfiltermat_;

	// 方向転換するための変数
	int direction;

	int flyPos_;

	// filterにbeansが入っているかどうか(true;入っている）
	bool beansIn_;

	// filterの上にあるbeansを押したかどうか（true:押した）
	bool beansStamp_;

	// filterに入っているbeansを淹れたかどうか(true：淹れた）
	bool beansBrew_;

	// filterに入っている淹れた後のbeansを捨てたかどうか
	bool beansDust_;

	// filterの場所
	Vector2 filterPos_;

	// filterの状態
	FILTER filter_;

#pragma endregion

#pragma region grinderとice dispenser関連

	int imgsgrinder_[1][2];

	Vector2 grinderPos_;

	int imgIceDispenser_;

#pragma endregion


#pragma region tamper関連
	// tamper画像
	int imgstamper_[2][TAMPER_NUM];

	// tamperの場所
	Vector2 tamperPos_;

	TAMPER tamper_;

	int pushCnt_;


#pragma endregion

#pragma region cup関連
	// cup画像
	int imgsHotCup_[1][HOTCUP_NUM];
	int imgsIceCup_[1][ICECUP_NUM];

	int imgEspresso_;
	int imgAmericano_;
	int imgLatte_;	
	
	int imgIce_Espresso_;
	int imgIce_Americano_;
	int imgIce_Latte_;

	// カップ初期位置を示す画像
	int imgHotCupSet_;
	int imgIceCupSet_;

	// cupの場所
	Vector2 cupPos_;

	// cupの状態
	HOTCUP cup_;

	// icecupの状態
	ICECUP iceCup_;

	bool isIce_;

#pragma endregion

#pragma region Milk関連

	int imgsPitcher_[1][PITCHER_NUM];
	int imgsReizou_[1][MILK_NUM];
	int imgMilk_;
	int imgMachineMilk_;
	int imgPitcherSet_;

	PITCHER pitcher_;
	MILK milk_;
	REIZOU reizou_;

	Vector2 pitcherPos_;
	Vector2 milkPos_;

	bool isMilk_;
	bool isFormer_;

#pragma endregion

	HOTMENU hotMenu_;
	ICEMENU iceMenu_;

	int imgsButton_[1][3];

	Vector2 cpos;
	int colorg;
	int colore;
	int colora;
	int colori;
	int colorm;

	int color_;

	Vector2 boxPos_;

	// サウンド用--------------------------------------------------------------------------
	// 変数

	// filter用
	int filterTakeSound_;			// filterを持つ時の音	
	int filterSetMatSound_;			// matにセットするときの音
	int filterSetSound_;			// マシーンにセットするときの音
	int filterSetOutSound_;			// マシーンから外すときの音
	int beansDustSound_;			// ボックスに捨てるときの音

	// tamper用
	int tamperPullupSound_;			// tamperを引き上げた時の音
	int tamperSetSound_;			// tamperを引き上げた時の音

	// cup用
	int CupTakeSound_;				// Cupを持つ時の音
	int CupSetSound_;				// Cupをマシーンにセットするときの音
	int CupIceInSound_;				// Cupに氷を淹れるときの音
	int CupPourIceSound_;			// Cupにアイスコーヒーを淹れるときの音
	int CupPourHotSound_;			// Cupにホットコーヒーを淹れるときの音

	// grinder用
	int grinderButton_;				// grinderのボタンを押したときの音

	// milk用
	int pourMilkSound_;

	// pitcher用
	int pitcherSound_;
	int setPitcherSound_;
	
	// 冷蔵庫用
	int reizouOpenSound_;
	int reizouCloseSound_;

	bool isPlaySound_;				// 今音を再生中かどうか

	int soundMem_;

	// サウンド用関数
	bool LoadSounds(void);			// 読み込み用

	void CheckSounds(void);			// 現在音を再生中かどうか判断する用

};

