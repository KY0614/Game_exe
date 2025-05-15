#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneGame;

class Message
{
public:


	// フォントサイズ 
	static constexpr int FONT_SIZE = 20;

	// メッセージの最大文字数 
	static constexpr int MAX_LENGTH = 13;

	// メッセージの最大行数
	static constexpr int MAX_LINE = 10;

	// メッセージ描画位置 (X座標)
	static constexpr int MESSAGE_POS_X = 60;
	// メッセージ描画位置 (Y座標)
	static constexpr int MESSAGE_POS_Y = 60;

	// スペースアニメーションの横幅
	static constexpr int SPACE_SIZE_X = 89;

	// スペースアニメーションの縦幅 
	static constexpr int SPACE_SIZE_Y = 56;

	// アニメーションフレーム数
	static constexpr int MAX_ANIM_NUM = 2;

	// 仮想テキストバッファの横サイズ縦サイズ
	static constexpr int STRBUF_WIDTH = 24;
	static constexpr int STRBUF_HEIGHT = 20;

	// メッセージの空白表示時間 (ミリ秒)
	static constexpr int MESSAGE_DELAY_TIME = 3500;

	// メッセージ切り替え時間 (例: 1000ms)
	static constexpr int MESSAGE_SWITCH_TIME = 1000;

	// サウンドボリューム (標準設定)
	static constexpr int WAIT_SOUND_VOLUME = 130;
	static constexpr int ICE_SOUND_VOLUME = 120;
	static constexpr int HOT_SOUND_VOLUME = 200;


	Message(void);			// コンストラクタ
	~Message(void);			// デストラクタ

	bool Init(SceneGame* parent);	// 初期化処理

	void Update(void);			// 更新処理	

	void UpdateWait(void);		// Waitフェーズの更新処理	
	void UpdateTalk(void);		// Talkフェーズの更新処理	
	void UpdateTalk2(void);		// Talk2フェーズの更新処理	

	void Draw(void);			// 描画処理
	void DrawTalk(void);		// 描画処理
	void DrawTalk2(void);		// 描画処理

	void DrawMessage(void);	// メッセージ描画

	bool Release(void);		// 解放処理

	// 日本語かどうか判定
	int isJapaneseCharacter(unsigned char code);

	// messageで指定した文章をstartの位置からlen文字分表示する
	void WriteSubstring(char* message, int start, int len, int posX, int posY, int color, int bufferLine);

	// 描画したいメッセージをセットする
	void SetMessage(const char* message);

	// メッセージボックスの状態を返す
	bool Switch(void);

private:

	int imgMessageBox_;
	int imgMessageBox2_;
	int imgMessageBox3_;

	char message_[MAX_LENGTH * MAX_LINE] = "";

	char messageBuffer[MAX_LINE][MAX_LENGTH];

	int currentCursor;		// 今何文字目か
	int currentLineCursor;	// 今何行目の文字か

	int timeCnt_;				// 秒数管理用

	SceneGame* sceneGame_;

	int imgsSpace_[1][MAX_ANIM_NUM];
	int cntAnim_;
	float speedAnim_;

	int messCount_;

	// 今メッセージとメッセージボックスが表示中かどうか
	bool isMessage_;

	// 今メッセージを描画中（最後まで表示されてない）かどうか
	bool isWrite_;

	int hotSound_;
	int iceSound_;
	int waitSound_;
	int sound_;
};

