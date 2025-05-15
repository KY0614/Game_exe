#include <DxLib.h>
#include "../Application.h"
#include "../Common/Fader.h"
#include "../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/Camera.h"
#include "../Object/Map.h"
#include "../Object/Player.h"
#include "../Object/Message.h"
#include "../Object/CustomerBase.h"
#include "../Object/HotCup.h"
#include "../Object/IceCup.h"
#include "SceneGame.h"


// デフォルトコンストラクタ
SceneGame::SceneGame(void)
{
	map_ = nullptr;
	player_ = nullptr;
	message_ = nullptr;

	fase_ = FASE::NONE;

	mode_ = MODE::NONE;

	cameraPos_ = { 0,0 };

	dir_ = AsoUtility::DIR::MAX;

	moveSpeedH_ = 0.0f;

	moveSpeedW_ = 0.0f;

	counter_ = 0;
}

// デストラクタ
SceneGame::~SceneGame(void)
{

}


// 初期化処理
bool SceneGame::Init(void)
{
	cursorImage_ = LoadGraph("Data/cursor.png");
	if (cursorImage_ == -1)
	{
		OutputDebugString("cursor.png画像が見つからない");
		return false;
	}

	messagecursorImage_ = LoadGraph("Data/Messagecursor.png");
	if (messagecursorImage_ == -1)
	{
		OutputDebugString("Messagecursor.png画像が見つからない");
		return false;
	}

	imgBack_ = LoadGraph("Data/GameScene/back.png");
	if (imgBack_ == -1)
	{
		OutputDebugString("back.png画像が見つからない");
		return false;
	}

	bgm_ = LoadSoundMem("Data/Triple-Sec.mp3");
	openBookSound_ = LoadSoundMem("Data/Sound/open book.mp3");
	closeBookSound_ = LoadSoundMem("Data/Sound/close book.mp3");
	// 読みこんだ音を再生
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(140, bgm_);
	ChangeVolumeSoundMem(255,openBookSound_ );
	ChangeVolumeSoundMem(255,closeBookSound_);

	// Drinkフェーズの時に出す画像の読み込み
	int ret;
	ret = LoadDivGraph(
		"Data/GameScene/HotDrink.png",
		3,
		3,
		1,
		ANIM_SIZE_X,
		ANIM_SIZE_Y,
		&(animImgs_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("Drink.png画像が見つからない");
		return false;
	}

	ret = LoadDivGraph(
		"Data/GameScene/IceDrink.png",
		3,
		3,
		1,
		ANIM_SIZE_X,
		ANIM_SIZE_Y,
		&(animIceImgs_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("IceDrink.png画像が見つからない");
		return false;
	}

	// UI画像の読み込み
	ret = LoadDivGraph(
		"Data/GameScene/MENU.png",
		2,
		2,
		1,
		UI_SIZE_X,
		UI_SIZE_Y,
		&(imgsUI_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("MENU.png画像が見つからない");
		return false;
	}

	// recipi画像の読み込み
	ret = LoadDivGraph(
		"Data/GameScene/recipe.png",
		2,
		2,
		1,
		400,
		380,
		&(imgRecipe_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("recipe.png画像が見つからない");
		return false;
	}

	ret = LoadDivGraph(
		"Data/GameScene/backs.png",
		2,
		2,
		1,
		UI_SIZE_X + 5,
		UI_SIZE_Y + 5,
		&(imgBacks_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("backs.png画像が見つからない");
		return false;
	}
	
	ret = LoadDivGraph(
		"Data/GameScene/next.png",
		2,
		2,
		1,
		UI_SIZE_X + 5,
		UI_SIZE_Y + 5,
		&(imgNext_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("backs.png画像が見つからない");
		return false;
	}


	// マップ
	if (map_ == nullptr)
	{
		map_ = new Map();
	}
	map_->Init(this);
	
	// プレイヤー
	if (player_ == nullptr)
	{
		player_ = new Player(*map_);
	}
	player_->Init(this);	
	
	// メッセージ
	if (message_ == nullptr)
	{
		message_ = new Message();
	}
	message_->Init(this);

	camera_ = new Camera(map_,player_);
	camera_->Init(this);

	// 客 
	auto hotcup = new HotCup(player_, camera_);
	hotcup->Init(this);
	customers_.push_back(hotcup);

	auto iceCup = new IceCup(player_, camera_);
	iceCup->Init(this);
	customers_.push_back(iceCup);

	// 開始の状態を設定する
	// マップの選定
	map_->ChangeMap(Map::TYPE::TALK);

	dir_ = AsoUtility::DIR::MAX;

	fase_ = FASE::NONE;

	mode_ = MODE::NONE;

	page_ = PAGE::NONE;

	cameraPos_ = { Application::SCREEN_SIZE_X,0 };

	moveSpeedH_ = 0.0f;

	moveSpeedW_ = 0.0f;

	counter_ = 0;
	cnt_ = -1;

	hot_ = false;
	ice_ = false;
	isMessCursor_ = false;

	startTime = GetNowCount();
	 
	fadeInSpeed_ = 5;

	cntA = 0;

	isUI_ = false;
	isBack_ = false;

	ui_ = 0;

	bookCnt_ = 0;

	return true;
}

// 更新処理
void SceneGame::Update(void)
{
	auto& ins = InputManager::GetInstance();
	counter_++;

	ins.GetMouse();
	mpos_ = ins.GetMousePos();

	// 経過時間
	GetTime();

	// カメラ
	camera_->Update();

	size_t size = customers_.size();

	// お客が2人来て帰ったら終了画面へ
	if (cnt_ == 2)
	{
		SceneManager::GetInstance().ChangeScene(
			SceneManager::SCENE_ID::GAMEOVER,
			true
		);
	}

	for (auto customer : customers_)
	{
		customer->Update();
	}

	if (mpos_.x > 50 && mpos_.x < 380 &&
		mpos_.y >50 && mpos_.y < 250)
	{
		isMessCursor_ = true;
	}
	else
	{
		isMessCursor_ = false;
	}

	switch (fase_)
	{
	case FASE::NONE:
		if (counter_ > 10)
		{
			cnt_++;
			cntA = 0;
			// 経過時間をリセット
			startTime = GetNowCount();

			// 提供した物のメニューをリセット 
			if (hot_ == true)
			{
				player_->ResetHotMenu();
			}
			else if (ice_ == true)
			{
				player_->ResetIceMenu();
			}

			// WAITフェーズへ遷移
			fase_ = FASE::WAIT;
		}
		break;

	case FASE::WAIT:
		hot_ = false;
		ice_ = false;
		message_->Update();
		break;

	case FASE::TALK:
		message_->Update();
		break;

	case FASE::MAKE:
		ui_ = 0;
		bookCnt_++;
		if (mpos_.x > 770 - UI_SIZE_X / 2 &&
			mpos_.x < 770 + UI_SIZE_X / 2 &&
			mpos_.y > 30 - UI_SIZE_X / 2 &&
			mpos_.y < 30 + UI_SIZE_X / 2
			)
		{
			ui_ = 1;
			if (isUI_ == false &&
				ins.IsTrgMouseLeft() == true)
			{
				isUI_ = true;
				page_ = PAGE::PAGE1;
				player_->PlaySounds(openBookSound_, 255);
			}
			else if (isUI_ == true&&
				ins.IsTrgMouseLeft() == true)
			{
				isUI_ = false;
				PlaySoundMem(closeBookSound_, DX_PLAYTYPE_BACK);
			}
			
		}

		if (isUI_ == true &&
			page_ == PAGE::PAGE1		&&
			(mpos_.x > 570 - UI_SIZE_X / 2 &&
			mpos_.x < 570 + UI_SIZE_X / 2 &&
			mpos_.y > 400 - UI_SIZE_X / 2 &&
			mpos_.y < 400 + UI_SIZE_X / 2)
			)
		{
			if (ins.IsTrgMouseLeft() == true)
			{
				page_ = PAGE::PAGE2;
				player_->PlaySounds(openBookSound_, 255);
			}
		}
		else if (isUI_ == true &&
			page_ == PAGE::PAGE2 &&
			(mpos_.x > 570 - UI_SIZE_X / 2 &&
				mpos_.x < 570 + UI_SIZE_X / 2 &&
				mpos_.y > 400 - UI_SIZE_X / 2 &&
				mpos_.y < 400 + UI_SIZE_X / 2)
			)
		{
			if (ins.IsTrgMouseLeft() == true)
			{
				isUI_ = false;
				PlaySoundMem(closeBookSound_, DX_PLAYTYPE_BACK);
			}
		}

		if (isUI_ == true)
		{
			return;
		}

		//カメラ遷移中ではない時に
		//商品をお客の前に持って行くと提供画面へ遷移する
		if (mode_ == MODE::NONE && 
			mpos_.x > 460	&&
			mpos_.x < 527	&&
			mpos_.y > 380	&&
			mpos_.y < 460
			)
		{
			if (
				player_->GetHotCup() == Player::HOTCUP::TAKE  &&
				!(player_->GetHotMenu() == Player::HOTMENU::NONE)&&
				map_->GetMapType() == Map::TYPE::TALK &&
				ins.IsTrgMouseLeft() == true)
			{
				hot_ = true;
				// 提供フェーズへ
				fase_ = FASE::DRINK;
				// Cupを初期状態へ
				player_->ChangeHotCup(Player::HOTCUP::NONE);
				// 経過時間をリセット
				startTime = GetNowCount();
			}
			else if (player_->GetIceCup() == Player::ICECUP::TAKE &&
				!(player_->GetIceMenu() == Player::ICEMENU::NONE) &&
				map_->GetMapType() == Map::TYPE::TALK &&
				ins.IsTrgMouseLeft() == true)
			{
				ice_ = true;
				// 提供フェーズへ
				fase_ = FASE::DRINK;
				// Cupを初期状態へ
				player_->ChangeIceCup(Player::ICECUP::NONE);
				// 経過時間をリセット
				startTime = GetNowCount();
			}
		}
		break;

	case FASE::DRINK:
		for (auto customer : customers_)
		{
			customers_[cnt_]->SetDrink(1);
		}
		// 提供画面に遷移して6秒経つと会話画面へ遷移
		if (elapsedTime > 6000)
		{
			// 時間をリセット
			startTime = GetNowCount();

			// フェーズ遷移
			fase_ = FASE::TALK2;
		}

		break;

	case FASE::TALK2:
		//for (auto customer : customers_)
		//{
		//	customers_[cnt_]->SetDrink(0);
		//}
		message_->Update();

		// 受け取ったものによってリアクション変更する
		//	hotCup_->Update();

		if (hot_ == true)
		{
			for (auto customer : customers_)
			{
				customers_[cnt_]->UpdateHot();
			}
		}
		else if (ice_ == true)
		{
			for (auto customer : customers_)
			{
				customers_[cnt_]->UpdateIce();
			}
		}

		counter_ = 0;

		break;

	default:
		break;
	}

	map_->Update();
	player_->Update();
}

// 描画処理
void SceneGame::Draw(void)
{
	// マップ描画
	map_->Draw();

	if (cnt_ == 3)
	{
		return;
	}

	size_t size = customers_.size();

	switch (fase_)
	{
	case FASE::WAIT:
		if (cnt_ == 2)
		{
			return;
		}
		// メッセージの描画
		message_->Draw();
		break;

	case FASE::TALK:
		// メッセージの描画
		message_->Draw();

		for (auto customer : customers_)
		{
			customers_[cnt_]->Draw();
		}
		

		//if (cnt_ == 1)
		//{
		//	hotCup_->Draw();
		//}
		//else if(cnt_ == 2)
		//{
		//	iceCup_->Draw();
		//}

		break;

	case FASE::MAKE:
		for (auto customer : customers_)
		{
			customers_[cnt_]->Draw();
		}

		//if (cnt_ == 1)
		//{
		//	hotCup_->Draw();
		//}
		//else if (cnt_ == 2)
		//{
		//	iceCup_->Draw();
		//}

		break;

	case FASE::DRINK:
		for (auto customer : customers_)
		{
			customers_[cnt_]->Draw();
		}

		if (cnt_ == 0)
		{
			// 提供する時に出す画像をフェードインしながら表示
			if (cntA == 0)
			{
				FadeInImage(50, 30, animImgs_[0][0], 0);
			}
			else if (cntA == 1)
			{
				DrawGraph(50, 30, animImgs_[0][0], true);
				FadeInImage(300, 30, animImgs_[0][1], 0);
			}
			else if (cntA == 2)
			{
				DrawGraph(50, 30, animImgs_[0][0], true);
				DrawGraph(300, 30, animImgs_[0][1], true);
				FadeInImage(550, 30, animImgs_[0][2], 0);
			}
			else
			{
				DrawGraph(50, 30, animImgs_[0][0], true);
				DrawGraph(300, 30, animImgs_[0][1], true);
				DrawGraph(550, 30, animImgs_[0][2], true);
			}
		}
		else 
		{
			// 提供する時に出す画像をフェードインしながら表示
			if (cntA == 0)
			{
				FadeInImage(50, 30, animIceImgs_[0][0], 0);
			}
			else if (cntA == 1)
			{
				DrawGraph(50, 30, animIceImgs_[0][0], true);
				FadeInImage(300, 30, animIceImgs_[0][1], 0);
			}
			else if (cntA == 2)
			{
				DrawGraph(50, 30, animIceImgs_[0][0], true);
				DrawGraph(300, 30, animIceImgs_[0][1], true);
				FadeInImage(550, 30, animIceImgs_[0][2], 0);
			}
			else
			{
				DrawGraph(50, 30, animIceImgs_[0][0], true);
				DrawGraph(300, 30, animIceImgs_[0][1], true);
				DrawGraph(550, 30, animIceImgs_[0][2], true);
			}
		}
		break;

	case FASE::TALK2:

		for (auto customer : customers_)
		{
			customers_[cnt_]->Draw();
		}

		// メッセージの描画
		message_->Draw();
			
			break;

	default:
		break;
	}

	player_->Draw();
	camera_->Draw();

	DrawRotaGraph(770,
		30,
		1.0f, 0.0f,
		imgsUI_[0][ui_],
		true);

	if (isUI_ == true && page_ == PAGE::PAGE1)
	{
		DrawRotaGraph(400,
			240,
			1.0f, 0.0f,
			imgRecipe_[0][0],
			true);	

		// アニメーションスピード
		int animNum = static_cast<int>(
			static_cast<float>(bookCnt_) * 0.02f)
			% 2;

		DrawRotaGraph(570,
			400,
			1.0f, 0.0f,
			imgNext_[0][animNum],
			true);

	}
	else if (isUI_ == true && page_ == PAGE::PAGE2)
	{
		DrawRotaGraph(400,
			240,
			1.0f, 0.0f,
			imgRecipe_[0][1],
			true);

		// アニメーションスピード
		int animNum = static_cast<int>(
			static_cast<float>(bookCnt_) * 0.02f)
			% 2;

		DrawRotaGraph(570,
			400,
			1.0f, 0.0f,
			imgBacks_[0][animNum],
			true);
	}

	DrawCursor();


	Vector2 cameraPos_ = camera_->GetCameraPos();

}

void SceneGame::DrawCursor(void)
{
	if (MesSwitch() == true)
	{
		if (mpos_.x > 50 && mpos_.x < 380 &&
			mpos_.y >50 && mpos_.y < 250)
		{
			isMessCursor_ = true;
			DrawGraph(mpos_.x, mpos_.y, messagecursorImage_, true);
		}
		else
		{
			DrawGraph(mpos_.x, mpos_.y, cursorImage_, true);
		}
	}
	else
	{
		isMessCursor_ = false;
		DrawGraph(mpos_.x, mpos_.y, cursorImage_, true);
	}
}

// 解放処理
bool SceneGame::Release(void)
{
	// サウンドハンドルの削除
	DeleteSoundMem(bgm_);

	// マップの解放
	map_->Release();		// マップ内の素材解放
	delete map_;			// インスタンスの削除
	map_ = nullptr;			// ポインタ変数を初期化
	
	message_->Release();	// メッセージ内の素材解放	
	delete message_;		// インスタンスの削除	
	message_ = nullptr;		// ポインタ変数を初期化	

	player_->Release();		// プレイヤー内の素材解放
	delete player_;			// インスタンスの削除
	player_ = nullptr;		// ポインタ変数を初期化

	
	DeleteGraph(cursorImage_);
	DeleteGraph(animImgs_[0][0]);

	return true;
}

// カメラの位置を返す
Vector2 SceneGame::GetCameraPos(void)
{
	return camera_->GetCameraPos();
}

// 現在のフェーズを取得する
SceneGame::FASE SceneGame::GetFase(void)
{
	return fase_;
}

// フェーズを変更する
void SceneGame::ChangeFase(FASE value)
{
	fase_ = value;
}

// 現在メッセージが表示中かどうか
bool SceneGame::MesSwitch(void)
{
	return message_->Switch();
}

bool SceneGame::GetIsMesCursor(void)
{
	return isMessCursor_;
}

// 経過時間を返す
int SceneGame::GetTime(void)
{
	elapsedTime = (GetNowCount() - startTime);

	return elapsedTime;
}

void SceneGame::FadeInImage(int x1, int y1, int imageFile, int fadeInSpeed)
{
	fadeInSpeed_ += 3;

	if (fadeInSpeed_ > 255)
	{
		fadeInSpeed_ = 0;

		cntA++;
		DrawGraph(x1, y1, imageFile, true);
	}

	if (cntA == 3)
	{
		return;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeInSpeed_);
	DrawGraph(x1, y1, imageFile, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

CustomerBase::CUSTOMER SceneGame::GetCustomer(void)
{
	return customers_[cnt_]->GetCustomer();
}

CustomerBase::REACTION SceneGame::GetReaction(void)
{
	size_t size = customers_.size();
	for (auto customer : customers_)
	{
		return customers_[cnt_]->GetReaction();
	}
}

bool SceneGame::GetMessCursor(void)
{
	return isMessCursor_;
}

void SceneGame::Accele(float speed)
{
	moveSpeedW_ += speed;
	moveSpeedH_ += speed;

	// 右移動の速度制限
	if (moveSpeedW_ > MAX_MOVE_WSPEED)
	{
		moveSpeedW_ = MAX_MOVE_WSPEED;
	}

	// 左移動の速度制限
	if (moveSpeedW_ < -MAX_MOVE_WSPEED)
	{
		moveSpeedW_ = -MAX_MOVE_WSPEED;
	}

	// 上移動の速度制限
	if (moveSpeedH_ < -MAX_MOVE_HSPEED)
	{
		moveSpeedH_ = -MAX_MOVE_HSPEED;
	}

	// 下移動の速度制限
	if (moveSpeedH_ > MAX_MOVE_HSPEED)
	{
		moveSpeedH_ = MAX_MOVE_HSPEED;
	}

}

// 減衰
void SceneGame::Decelerate(float speed)
{
	// 移動方向：右
	if (moveSpeedW_ > 0.0f)
	{
		moveSpeedW_ -= speed;
		if (moveSpeedW_ < 0.0f)
		{
			moveSpeedW_ = 0.0f;
		}
	}
	// 移動方向：左
	else if (moveSpeedW_ < 0.0f)
	{
		moveSpeedW_ += speed;
		if (moveSpeedW_ > 0.0f)
		{
			moveSpeedW_ = 0.0f;
		}
	}

	// 移動方向：上
	if(moveSpeedH_ < 0.0f)
	{
		moveSpeedH_ += speed;
		if (moveSpeedH_ > 0.0f)
		{
			moveSpeedH_ = 0.0f;
		}
	}
	// 移動方向：下
	else if (moveSpeedH_ > 0.0f)
	{
		moveSpeedH_ -= speed;
		if (moveSpeedH_ < 0.0f)
		{
			moveSpeedH_ = 0.0f;
		}
	}
}

void SceneGame::Move(int pos)
{
	pos += moveSpeedH_;
}
