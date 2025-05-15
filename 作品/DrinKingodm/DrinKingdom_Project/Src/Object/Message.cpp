#include <DxLib.h>
#include <string.h>
#include "../Manager/InputManager.h"
#include "../Scene/SceneGame.h"
#include "../Object/CustomerBase.h"
#include "Message.h"

Message::Message(void)
{
	currentCursor = 0;
	currentLineCursor = 0;
	timeCnt_ = 0;
	messCount_ = 0;
	isMessage_ = false;
	isWrite_ = false;
}

Message::~Message(void)
{
}

bool Message::Init(SceneGame* parent)
{
	sceneGame_ = parent;

	imgMessageBox_ = LoadGraph("Data/GameScene/message.png");
	if (imgMessageBox_ == -1)
	{
		OutputDebugString("message.png画像が見つからない");
		return false;
	}
	
	imgMessageBox2_ = LoadGraph("Data/GameScene/message2.png");
	if (imgMessageBox2_ == -1)
	{
		OutputDebugString("message2.png画像が見つからない");
		return false;
	}
	
	imgMessageBox3_ = LoadGraph("Data/GameScene/message3.png");
	if (imgMessageBox3_ == -1)
	{
		OutputDebugString("message3.png画像が見つからない");
		return false;
	}

	// スペースキー押下画像の読み込み
	int ret;
	ret = LoadDivGraph(
		"Data/Push Space.png",
		1 * MAX_ANIM_NUM,
		MAX_ANIM_NUM,
		MAX_ANIM_NUM,
		SPACE_SIZE_X,
		SPACE_SIZE_Y,
		&(imgsSpace_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("Push Space.png画像が見つからない");
		return false;
	}

	waitSound_ = LoadSoundMem("Data/Sound/HotCup_talk.mp3");
	iceSound_ = LoadSoundMem("Data/Sound/IceCup_talk.mp3");
	hotSound_ = LoadSoundMem("Data/Sound/wait.mp3");

	// 読みこんだ音の音量を調整
	ChangeVolumeSoundMem(WAIT_SOUND_VOLUME, waitSound_);
	ChangeVolumeSoundMem(ICE_SOUND_VOLUME, iceSound_);
	ChangeVolumeSoundMem(HOT_SOUND_VOLUME, hotSound_);


	SetFontSize(FONT_SIZE);

	messCount_ = -1;
	isMessage_ = false;
	isWrite_ = false;

	cntAnim_ = 0;
	speedAnim_ = 0.05f;

	return true;
}

void Message::Update(void)
{
	auto& ins = InputManager::GetInstance();

	timeCnt_++;
	cntAnim_++;

	if (sceneGame_->GetFase() == SceneGame::FASE::WAIT)
	{
		UpdateWait();
	}
	else if (sceneGame_->GetFase() == SceneGame::FASE::TALK)
	{
		UpdateTalk();
	}
	else if(sceneGame_->GetFase() == SceneGame::FASE::TALK2)
	{
		UpdateTalk2();
	}

}

void Message::UpdateWait(void)
{
	auto& ins = InputManager::GetInstance();

	// 経過時間
	int time = sceneGame_->GetTime();

	isWrite_ = true;

	// 最初は準備中の文字をセット
	// ２回目以降は入店待ちをセット
	if (messCount_ == -1)
	{
		sound_ = waitSound_;

		SetMessage("準備中......");

		messCount_ = 1;
	}
	else if ((messCount_ == 0))
	{
		sound_ = waitSound_;

		SetMessage("入店待ち......");
		messCount_++;
	}
	else if ((messCount_ > 0) && time > 3000 )
	{
		SetMessage("");
		sceneGame_->ChangeFase(SceneGame::FASE::TALK);
		isMessage_ = false;
		messCount_++;	// 2
	}
}

void Message::UpdateTalk(void)
{
	auto& ins = InputManager::GetInstance();
	int time = sceneGame_->GetTime();

	CustomerBase::CUSTOMER customer = sceneGame_->GetCustomer();

	bool messCursor = sceneGame_->GetMessCursor();

	switch (customer)
	{
	case CustomerBase::CUSTOMER::NONE:
		break;

	case CustomerBase::CUSTOMER::HOTCUP:
		sound_ = hotSound_;

		// 最初のメッセージは時間経過で表示される
		// メッセージが最後まで表示されたときにスペースイー押下で次のメッセージをセットする
		if (((messCount_ > 1) && (messCount_ < 3))		// 1 < messCount_ < 3
			&& time > MESSAGE_DELAY_TIME)
		{
			SetMessage("...どうも");
			messCount_++;	// 3
		}
		else if (((messCount_ > 2) && (messCount_ < 4)) && !(isWrite_) &&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
			(messCursor == true && ins.IsTrgMouseLeft() == true)
			))
		{
			SetMessage("こちらのお店には何がありますか？");

			messCount_++;	// 4
		}
		else if (((messCount_ > 3) && (messCount_ < 5)) && !(isWrite_) &&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage(".....といっても、私はコーヒーしか飲めないんですけどね。");
			messCount_++;	// 5
		}
		else if (((messCount_ > 4) && (messCount_ < 6)) && !(isWrite_) &&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("なるべく苦いコーヒーで温かいものをお願いします。");
			messCount_++;	// ６
		}
		else if (((messCount_ > 5) && (messCount_ < 7)) && !(isWrite_) &&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("");
			sceneGame_->ChangeFase(SceneGame::FASE::MAKE);
			isMessage_ = false;
			isWrite_ = true;
			messCount_++;	// 7
		}
		break;
	
	case CustomerBase::CUSTOMER::ICECUP:
		sound_ = iceSound_;

		// 最初のメッセージは時間経過で表示される
		// メッセージが最後まで表示されたときにスペースイー押下で次のメッセージをセットする
		if (((messCount_ > 1) && (messCount_ < 3)) 
			&& time > MESSAGE_DELAY_TIME)
		{
			SetMessage("こんにちは！オシャレなお店ね！");
			messCount_++;	// 3
		}
		else if (((messCount_ > 2) && (messCount_ < 4)) 
			&& !(isWrite_) 
			&&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("このお店は何があるの？");

			messCount_++;	// 4
		}
		else if (((messCount_ > 3) && (messCount_ < 5)) 
			&& !(isWrite_) 
			&&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("(...あなたはメニューを見せながら商品を紹介していく...）");
			messCount_++;	// 5
		}
		else if (((messCount_ > 4) && (messCount_ < 6)) 
			&& !(isWrite_)
			&&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("...う～んどれもよくわかんないや！冷たいものだったらなんでもいいよ！");
			messCount_++;	// ６
		}
		else if (((messCount_ > 5) && (messCount_ < 7)) 
			&& !(isWrite_) 
			&&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("");
			sceneGame_->ChangeFase(SceneGame::FASE::MAKE);
			isMessage_ = false;
			isWrite_ = true;
			messCount_++;	// 7
		}
		break;
	
	default:
		break;
	}

 }

void Message::UpdateTalk2(void)
{
	auto& ins = InputManager::GetInstance();
	int time = sceneGame_->GetTime();

	CustomerBase::CUSTOMER customer = sceneGame_->GetCustomer();
	CustomerBase::REACTION reaction = sceneGame_->GetReaction();

	bool messCursor = sceneGame_->GetMessCursor();

	switch (customer)
	{
	case CustomerBase::CUSTOMER::NONE:
		break;

	case CustomerBase::CUSTOMER::HOTCUP:
		// 最初のメッセージは時間経過で表示される
		// メッセージが最後まで表示されたときにスペースイー押下で次のメッセージをセットする
		switch (reaction)
		{
		case CustomerBase::REACTION::HAPPY:
			// 希望通りの商品を渡したとき
			if (((messCount_ > 6) && (messCount_ < 8))		// 1 < messCount_ < 3
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("ありがとうございます。");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("とてもビターで濃厚ですね。私の好きなコーヒーです。");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("とても美味しかったです。妹も連れてまた来ますね。それでは。");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		case CustomerBase::REACTION::NORMAL:
			// 希望通りの商品に近いものを渡したとき
			if (((messCount_ > 6) && (messCount_ < 8))
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("ありがとうございます。");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("今まで色んなコーヒーを飲んできましたけど、ここのコーヒーも悪くないですね。");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("また飲みたくなったら足を運びますね。");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		case CustomerBase::REACTION::BAD:
			// 希望した商品と全く違うものを渡したとき
			if (((messCount_ > 6) && (messCount_ < 8))		// 1 < messCount_ < 3
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage(".....");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("...ここのお店のコーヒーはこんな感じなんですね。");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("少し...私の口には合わないかもしれませんが...このコーヒーが気に入る人もいるでしょう。");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}

			break;

		default:
			break;
		}

		break;

	case CustomerBase::CUSTOMER::ICECUP:
		switch (reaction)
		{
		case CustomerBase::REACTION::HAPPY:
			// 最初のメッセージは時間経過で表示される
			// メッセージが最後まで表示されたときにスペースイー押下で次のメッセージをセットする
			if (((messCount_ > 6) && (messCount_ < 8))
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("ありがと！");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("めちゃ美味しかった！やっぱり冷たい飲み物はさっぱりするね！");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("こんなにいいお店があるなんて知らなかった…。お兄ちゃんも連れてまた来るね！");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		case CustomerBase::REACTION::NORMAL:
			// 最初のメッセージは時間経過で表示される
			// メッセージが最後まで表示されたときにスペースイー押下で次のメッセージをセットする
			if (((messCount_ > 6) && (messCount_ < 8))
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("ありがとう！");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("結構苦めのコーヒーをだしてるんだね。でもおいしいよ！");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("今度は苦味が控え目だと嬉しいな～。また来るね！");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		case CustomerBase::REACTION::BAD:
			// 最初のメッセージは時間経過で表示される
			// メッセージが最後まで表示されたときにスペースイー押下で次のメッセージをセットする
			if (((messCount_ > 6) && (messCount_ < 8))
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("ありがとね");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("私にはちょっと...冷たいものが良かったかなぁ...");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("次は冷たい飲み物があるのを期待しとくね");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		default:
			break;
		}


		break;

	default:
		break;
	}

}

void Message::Draw(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 cameraPos = sceneGame_->GetCameraPos();

	// 文字が1文字もセットされてなかったらメッセージボックスを表示しない
	if (strnlen_s(message_, MAX_LENGTH * MAX_LINE) <= 0)
	{
		return;
	}
	
	int animNum = static_cast<int>(
		static_cast<float>(cntAnim_) * speedAnim_)
		% MAX_ANIM_NUM;

	DrawGraph(25, 25, imgMessageBox_, true);
	DrawGraph(300, 260, imgMessageBox2_, true);
	DrawGraph(370, 310, imgMessageBox3_, true);

	if (isWrite_ == false)
	{
		DrawRotaGraph(300,
			200,
			0.5f, 0.0f,
			imgsSpace_[0][animNum],
			true);
	}

	DrawMessage();
}

void Message::DrawTalk(void)
{

}

void Message::DrawTalk2(void)
{

}

// メッセージの描画
void Message::DrawMessage(void)
{
	auto& ins = InputManager::GetInstance();

	isMessage_ = true;


	if (timeCnt_ == 4)
	{
		// 1秒間たった時の処理
		if (message_[currentCursor] != '\0')
		{
			currentCursor++;
			isWrite_ = true;
			PlaySoundMem(sound_, DX_PLAYTYPE_BACK);
		}	
		else
		{
			isWrite_ = false;
		}

		
		// MESSAGE_MAX_LENGTHまで文字を描画したら段階を切り替える
		if (currentCursor % MAX_LENGTH == 0)
		{
			if (message_[currentCursor] != '\0')
			{
				currentLineCursor++;
			}
			else
			{
				isWrite_ = false;
			}
		}

		if (message_[currentCursor] == '\0')
		{
			StopSoundMem(sound_);
		}
		timeCnt_ = 0;
	}

	// メッセージ描画
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (i == currentLineCursor)
		{
			// サウンドノベルメッセージ風に表示
			WriteSubstring(message_, i * MAX_LENGTH,
				currentCursor - MAX_LENGTH * i,
				MESSAGE_POS_X , MESSAGE_POS_Y + FONT_SIZE * i ,
				0xffffff, i);
			break;
		}
		else
		{
			// メッセージをそのまま表示
 			WriteSubstring(message_, i * MAX_LENGTH,
				MAX_LENGTH, MESSAGE_POS_X,
				MESSAGE_POS_Y + FONT_SIZE * i,
				0xffffff, i);

			StopSoundMem(sound_);
		}
	}
}

bool Message::Release(void)
{
	return true;
}

// codeが日本語であるか判定する
// 戻り値が１：日本語　０：日本語ではない
int Message::isJapaneseCharacter(unsigned char code)
{
	if ((code >= 0x81 && code <= 0x9F) ||
		(code >= 0xE0 && code <= 0xFC))
	{
		return 1;
	}
	return 0;
}

// messageで指定した文章をstartの位置からlen文字分表示する
// 文字列左側の座標は(posX,posY)、文字の色をcolorとする
void Message::WriteSubstring(char* message, int start, int len, 
	int posX, int posY, int color, int bufferLine)
{
	int i;
	// 文字数
	int maxLen = strlen(message);

	// startの位置を変更する	
	// startの位置までに日本語が出てきていたら、1を足していく
	for (i = 0; i < start && message[i] != '\0';)
	{
		if (isJapaneseCharacter(message[i]))
		{
			// 日本語の場合2バイト分進める
			i += 2;

			// startに1バイト分足す
			start++;
		}
		else
		{
			// 半角文字の場合、１バイト分進める
			i++;
		}
	}

	// startの位置が表示したい最大文字数より大きい場合
	if (start >= maxLen)
	{
		return;
	}

	// 指定した位置からlen文字分表示する
	for (i = 0; i < len && message[start + i] != '\0';)
	{
		if (isJapaneseCharacter(message[start + i]))
		{
			// 日本語の場合、2文字分bufferにセットする
			messageBuffer[bufferLine][ i ] = message[start + i];
			messageBuffer[bufferLine][i + 1] = message[start + i + 1];
			// lenは日本語なので、１バイト分追加する
			len++;
			// 2バイト分進める
			i += 2;
		}
		else
		{
			// 半角文字1文字を表示
			// printf("%c", message[start + i]);
			messageBuffer[bufferLine][i] = message[start + i];
			// 1バイト分進める
			i++;
		}
	}
	messageBuffer[bufferLine][i] = '\0';

	// メッセージ描画
	DrawString(posX, posY, messageBuffer[bufferLine], color);
}

void Message::SetMessage(const char* message)
{
	// カーソルの初期化
	currentCursor = 0;
	currentLineCursor = 0;
	timeCnt_ = 0;

	// メッセージをコピー
	strncpy_s(message_, message, MAX_LENGTH * MAX_LINE);
}

bool Message::Switch(void)
{
	return isMessage_;
}