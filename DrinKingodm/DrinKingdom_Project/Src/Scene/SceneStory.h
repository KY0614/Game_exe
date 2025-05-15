#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "SceneBase.h"

// 前方宣言
class Fader;

class SceneStory :public SceneBase
{
public:
	// ボタンのサイズ
	static constexpr int SIZE_WIDTH = 120;		// 横
	static constexpr int SIZE_HEIGHT = 70;		// 縦

	// ボタンの位置
	static constexpr int BUTTON_POS_X = 550;	//X座標はそろえるので一緒

	// タイトルボタンの位置
	static constexpr int TITLEBUTTON_POS_X = 50;
	static constexpr int TITLEBUTTON_POS_Y = 410;

	static constexpr int PLAYBUTTON_POS_X = 220;
	static constexpr int SELECT_IMG_POS_X = 170;

	SceneStory(void);			// コンストラクタ
	~SceneStory(void);			// デストラクタ

	bool Init(void) override;		// 初期化処理
	void Update(void) override;		// 更新処理	
	void Draw(void) override;		// 描画処理
	bool Release(void) override;	// 解放処理

private:
	// メンバー変数
	//サウンド関連
	int bgm_;
	int buttonSelectSound_;
	int buttonPushSound_;

	//画像関連
	int storyImg_;
	int cursorImage_;

	int selectImage_;
	int select_onImage_;

	int title_pushImage_;
	int titleImage_;
	int start_onImage_;
	int start_offImage_;

	// マウスの位置
	Vector2 mpos_;
	// 選択位置がわかる画像の位置
	Vector2 spos_;

	bool isTitle_;
	bool isPlay_;

	bool isSelect_;
	bool wasSelect_;
};
