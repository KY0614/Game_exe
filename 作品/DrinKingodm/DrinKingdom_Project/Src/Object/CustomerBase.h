#pragma once
#include <DxLib.h>

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneGame;

class CustomerBase
{
public:
	// 画像サイズ
	static constexpr int SIZE_X = 214/*320*/;	
	static constexpr int SIZE_Y = 380;

	static constexpr int ICESIZE_X = 204;
	static constexpr int ICESIZE_Y = 400;

	static constexpr int POS_X = 1300;
	static constexpr int POS_Y = 202;

	// アニメーション数
	static constexpr int NUM_ANIM = 7;

	// お客の順番
	enum class CUSTOMER
	{
		NONE,
		HOTCUP,	  // 1人目
		ICECUP,	  // 2人目
		THREE	  // 3人目
	};

	// 客の反応（分岐要素）
	enum class REACTION
	{
		NONE,	 // まだ受け取っていない
		HAPPY,	 // 希望する通りの商品
		NORMAL,	 // 希望したものと少し違うもの
		BAD		 // 全く違うもの
	};

	enum class WINK
	{
		NONE,
		ONCE,
		TWICE
	};

	CustomerBase(void);
	virtual ~CustomerBase(void);

	bool Init(SceneGame*scenegame);		// 初期化処理

	virtual void Update(void);			// 更新処理	

	virtual void UpdateTalk(void);		// 更新処理	
	virtual void UpdateHot(void);
	virtual void UpdateIce(void);

	virtual void UpdateMake(void);		// 更新処理	
	virtual void UpdateDrink(void);		// 更新処理	
	virtual void UpdateTalk2(void);		// 更新処理	


	virtual void Draw(void);			// 描画処理
	bool Release(void);					// 解放処理

	virtual void SetParam(void) = 0;	// 固有の機能を設定する関数

	void Wink(void);

	CUSTOMER GetCustomer(void);			// customer_の状態を得る
	REACTION GetReaction(void);			// 客がどの反応をしているか

	void SetDrink(int value);

protected:

	// 画像ファイル名
	std::string imgFileName;

	// 表示座標
	Vector2 pos_;

	// サイズ
	Vector2 size_;

	// 
	int numY;

	int drink_;

	// お客の順番
	CUSTOMER customer_;

	// お客の反応
	REACTION reaction_;

	// ------------------------------------------

	// シーンゲームのポインタ格納領域
	SceneGame* sceneGame_;

	int image_;
	int imgs_[5][NUM_ANIM];

	// 向き
	AsoUtility::DIR dir_;

	// アニメーションカウンタ
	int cntAnim_;

	// アニメーション速度
	float speedAnim_;

	int animNum_;
	bool increasing;

	float time;


	int blink_;

	WINK wink_;
	int rand_;
	bool winkRand_;
};

