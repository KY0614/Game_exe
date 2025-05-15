#include <DxLib.h>
#include<cmath>
#include "../Manager/InputManager.h"
#include "../Object/Map.h"
#include "../Scene/SceneGame.h"
#include "../Common/Geometry.h"
#include "../Utility/AsoUtility.h"
#include "Player.h"

Player::Player(Map& map):map_(map)
{
	sceneGame_ = nullptr;

	mpos_ = { 0,0 };

	beansIn_ = false;
	beansStamp_ = false;
	beansBrew_ = false;
	beansDust_ = false;

	filterPos_ = {0,0};

	filter_ = FILTER::NONE;
	tamper_ = TAMPER::NONE;

	pushCnt_ = 0.0f;
}

Player::~Player(void)
{

}

bool Player::Init(SceneGame* parent)
{
	sceneGame_ = parent;

	LoadSounds();
	
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

	imgbeans_ = LoadGraph("Data/GameScene/CoffeeBeans.png");
	if (imgbeans_ == -1)
	{
		OutputDebugString("CoffeeBeans.png画像が見つからない");
		return false;
	}

	imgdust_ = LoadGraph("Data/GameScene/coffee_!.png");
	if (imgdust_ == -1)
	{
		OutputDebugString("coffee_!.png画像が見つからない");
		return false;
	}	
	
	// アイスディスペンサー
	imgIceDispenser_ = LoadGraph("Data/GameScene/ice dispenser.png");
	if (imgIceDispenser_ == -1)
	{
		OutputDebugString("ice dispenser.png画像が見つからない");
		return false;
	}
	
	imgfiltermat_ = LoadGraph("Data/GameScene/filtermat.png");
	if (imgfiltermat_ == -1)
	{
		OutputDebugString("milk pitcher.png画像が見つからない");
		return false;
	}

	imgEspresso_ = LoadGraph("Data/GameScene/espresso.png");
	if (imgEspresso_ == -1)
	{
		OutputDebugString("espresso.png画像が見つからない");
		return false;
	}	
	
	imgAmericano_ = LoadGraph("Data/GameScene/americano.png");
	if (imgAmericano_ == -1)
	{
		OutputDebugString("americano.png画像が見つからない");
		return false;
	}	
	
	imgLatte_ = LoadGraph("Data/GameScene/latte.png");
	if (imgLatte_ == -1)
	{
		OutputDebugString("latte.png画像が見つからない");
		return false;
	}	

	imgIce_Espresso_ = LoadGraph("Data/GameScene/ice_espresso.png");
	if (imgIce_Espresso_ == -1)
	{
		OutputDebugString("ice_espresso.png画像が見つからない");
		return false;
	}

	imgIce_Americano_ = LoadGraph("Data/GameScene/ice_americano.png");
	if (imgIce_Americano_ == -1)
	{
		OutputDebugString("ice_americano.png画像が見つからない");
		return false;
	}

	imgIce_Latte_ = LoadGraph("Data/GameScene/ice_latte.png");
	if (imgIce_Latte_ == -1)
	{
		OutputDebugString("ice_latte.png画像が見つからない");
		return false;
	}
	
	imgHotCupSet_ = LoadGraph("Data/GameScene/HotCupSet.png");
	if (imgHotCupSet_ == -1)
	{
		OutputDebugString("HotCupSet.png画像が見つからない");
		return false;
	}
		
	imgIceCupSet_ = LoadGraph("Data/GameScene/IceCupSet.png");
	if (imgIceCupSet_ == -1)
	{
		OutputDebugString("IceCupSet.png画像が見つからない");
		return false;
	}	
	
	imgMilk_ = LoadGraph("Data/GameScene/milk.png");
	if (imgMilk_ == -1)
	{
		OutputDebugString("milk.png画像が見つからない");
		return false;
	}	
	
	imgMachineMilk_ = LoadGraph("Data/GameScene/machine milk.png");
	if (imgMachineMilk_ == -1)
	{
		OutputDebugString("machine milk.png画像が見つからない");
		return false;
	}	
	
	imgPitcherSet_ = LoadGraph("Data/GameScene/pitcher_set.png");
	if (imgPitcherSet_ == -1)
	{
		OutputDebugString("pitcher_set.png画像が見つからない");
		return false;
	}

	// 画像の読み込み
	int ret;

	// 矢印画像の読み込み
	ret = LoadDivGraph(
		"Data/GameScene/milk pitcher.png",
		5,
		5,
		1,
		PITCHER_SIZE_X,
		PITCHER_SIZE_Y,
		&(imgsPitcher_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("milk pitcher.png画像が見つからない");
		return false;
	}	
	
	ret = LoadDivGraph(
		"Data/GameScene/refrigerator.png",
		MILK_NUM,
		MILK_NUM,
		1,
		REIZOU_SIZE_X,
		REIZOU_SIZE_Y,
		&(imgsReizou_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("refrigerator.png画像が見つからない");
		return false;
	}

	// 矢印画像の読み込み
	ret = LoadDivGraph(
		"Data/point.png",
		static_cast<int>(AsoUtility::DIR::MAX),
		static_cast<int>(AsoUtility::DIR::MAX),
		1,
		POINT_SIZE_X,
		POINT_SIZE_Y,
		&(imgsPoint_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("point.png画像が見つからない");
		return false;
	}

	// 下キー押下画像の読み込み
	ret = LoadDivGraph(
		"Data/Push Down.png",
		PUSHKEY_MAX_NUM * PUSHKEY_MAX_NUM,
		PUSHKEY_MAX_NUM,
		PUSHKEY_MAX_NUM,
		PUSHKEY_SIZE_X,
		PUSHKEY_SIZE_Y,
		&(imgsPushKey_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("Push Down.png画像が見つからない");
		return false;
	}

	// filterの読み込み
	ret = LoadDivGraph(
		"Data/GameScene/Filters.png",
		2 * FILTER_NUM,
		FILTER_NUM,
		2,
		FSIZE_X,
		FSIZE_Y,
		&(imgsfilter_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("Filters.png画像が見つからない");
		return false;
	}
	
	// tamperの読み込み
	ret = LoadDivGraph(
		"Data/GameScene/tamper.png",
		2 * TAMPER_NUM,
		TAMPER_NUM,
		2,
		TSIZE_X,
		TSIZE_Y,
		&(imgstamper_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("tamper.png画像が見つからない");
		return false;
	}

	// grinderの読み込み
	ret = LoadDivGraph(
		"Data/GameScene/coffee grinders.png",
		2,
		2,
		1,
		GSIZE_X,
		GSIZE_Y,
		&(imgsgrinder_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("coffee grinders.png画像が見つからない");
		return false;
	}

	// HotCupの読み込み
	ret = LoadDivGraph(
		"Data/GameScene/Cup.png",
		HOTCUP_NUM,
		HOTCUP_NUM,
		1,
		CUP_SIZE_X,
		CUP_SIZE_Y,
		&(imgsHotCup_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("Cup.png画像が見つからない");
		return false;
	}

	// IceCupの読み込み
	ret = LoadDivGraph(
		"Data/GameScene/IceCup.png",
		ICECUP_NUM,
		ICECUP_NUM,
		1,
		ICECUP_SIZE_X,
		ICECUP_SIZE_Y,
		&(imgsIceCup_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("IceCup.png画像が見つからない");
		return false;
	}

	// ボタンの読み込み
	ret = LoadDivGraph(
		"Data/GameScene/button.png",
		3,
		3,
		1,
		39,
		39,
		&(imgsButton_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("button.png画像が見つからない");
		return false;
	}

	// 初期化---------------------------------------------

	mpos_ = { 0,0 };
	pointPos_ = { 0,0 };
	pushPos_ = { 0,0 };

	dir_ = AsoUtility::DIR::DOWN;

	beansIn_ = false;
	beansStamp_ = false;
	beansBrew_ = false;
	beansDust_ = false;

	isPoint_ = true;
	isPushKey_ = false;	
	pushKey_ = 0;

	filterPos_ = { FILTER_POS_X,FILTER_POS_Y };
	tamperPos_ = { TAMPER_POS_X,TAMPER_POS_Y };

	filter_ = FILTER::NONE;
	tamper_ = TAMPER::NONE;
	cup_ = HOTCUP::NONE;
	iceCup_ = ICECUP::NONE;
	hotMenu_ = HOTMENU::NONE;
	iceMenu_ = ICEMENU::NONE;

	pitcher_ = PITCHER::NONE;
	milk_ = MILK::NONE;
	reizou_ = REIZOU::NONE;

	cpos = { GRINDER_POS_X ,615 };

	pushCnt_ = 3;

	boxPos_ = { 1510 /*- cameraPos.x*/, 728 /*- cameraPos.y */};

	isPlaySound_ = false;

	direction = 1;
	pointDirection_ = 1;

	flyPos_ = 35;

	isIce_ = false;

	isMilk_ = false;
	isFormer_ = false;

	cntAnim_ = 0;
	speedAnim_ = 0.05f;

	colorg = 0;
	colore = 0;
	colora = 0;
	colori = 0;
	colorm = 0;

	color_ = 0xFF0000;

	pitcherPos_ = { PITCHER_POS_X,PITCHER_POS_Y };

	SetPointPos({ FILTER_POS_X + FSIZE_X + 10, FILTER_POS_Y/* - (FSIZE_Y/2 + POINT_SIZE_Y)*/ }, AsoUtility::DIR::LEFT);

	return true;
}

void Player::Update(void)
{
	auto& ins = InputManager::GetInstance();

	SetMouseDispFlag(false);

	ins.GetMouse();
	mpos_ = ins.GetMousePos();

	CheckSounds();

	switch (sceneGame_->GetFase())
	{
	case SceneGame::FASE::TALK:
		UpdateTalk();
		break;

	case SceneGame::FASE::MAKE:
		UpdateMake();
		GetHotMenu();
		break;

	case SceneGame::FASE::DRINK:

		break;

	case SceneGame::FASE::TALK2:
		UpdateTalk2();
		break;

	default:
		break;
	}

}

void Player::UpdateTalk(void)
{

}

void Player::UpdateMake(void)
{
	cntAnim_++;

	auto& ins = InputManager::GetInstance();
	Vector2 cameraPos = sceneGame_->GetCameraPos();

	SetMouseDispFlag(false);

	ins.GetMouse();
	mpos_ = ins.GetMousePos();
	colorg = 0;
	colore = 0;
	colora = 0;
	colorm = 0;

	sceneGame_->Decelerate(SceneGame::MOVE_DEC);

	sceneGame_->Move(flyPos_);

	MoveCaution();
	MovePoint();

	if (sceneGame_->GetCustomer() == CustomerBase::CUSTOMER::ICECUP &&
		GetBeansBrew() == false)
	{
		IsPoint(false);
	}

	if (sceneGame_->GetCustomer() == CustomerBase::CUSTOMER::ICECUP &&
		GetBeansBrew() == false)
	{
		IsPoint(false);
	}


	switch (filter_)
	{
	case FILTER::NONE:
		// filter初期位置
		SetFilterPos({ FILTER_POS_X, FILTER_POS_Y });

		//StampFilter(false);
		BeansState(false, false, false, false);

		break;

	case FILTER::SELECT:

		BeansState(false, false, false, false);

		break;

	case FILTER::TAKE:
		if (GetBeansBrew() == true &&(GetHotMenu() == HOTMENU::NONE && GetIceMenu() == ICEMENU::NONE))
		{
			SetPointPos({ TAMPER_FPOS_X - 80, TAMPER_FPOS_Y }, AsoUtility::DIR::DOWN);
		}

		// beansが入っていないとき
		// カーソルの位置(filter位置)がfilterの初期位置よりgrinderに近かったら
		// filterの位置をgrinderに設定する
		if (GetBeansIn() == false &&
			((FILTER_GPOS_X - cameraPos.x) - mpos_.x) < (mpos_.x - (FILTER_POS_X - cameraPos.x))
			)
		{
			SetFilterPos(Vector2(FILTER_POS_X, FILTER_POS_Y));
		}
		else if (GetBeansIn() == false)
		{
			SetFilterPos(Vector2(FILTER_GPOS_X, FILTER_GPOS_Y));
		}

		if (GetBeansIn() == true &&
			GetBeansStamp() == false /*&& (GetHotMenu() == HOTMENU::NONE || GetIceMenu() == ICEMENU::NONE)*/)
		{
			SetFilterPos(Vector2(FILTER_TPOS_X, FILTER_TPOS_Y));

			// 矢印をtampermatの上部へ
			SetPointPos({ FILTER_TPOS_X, FILTER_TPOS_Y - 60 }, AsoUtility::DIR::DOWN);
		}
		else if (GetBeansIn() == true &&
			GetBeansStamp() == true /*&& (GetHotMenu() == HOTMENU::NONE || GetIceMenu() == ICEMENU::NONE)*/)
		{
			SetFilterPos(Vector2(FILTER_CPOS_X , FILTER_CPOS_Y));
		}

		// beansがtrueの時はfilterの位置をtampermatに設定する
		if (GetHotMenu() == HOTMENU::NONE)
		{
			if (GetBeansStamp() == true &&
				GetBeansBrew() == false)
			{
				// 矢印をマシンのセットする部分上部へ
				SetPointPos({ FILTER_CPOS_X , FILTER_CPOS_Y - 50 }, AsoUtility::DIR::DOWN);
			}
		}

		break;

	case FILTER::SELECT_G:

		break;

	case FILTER::SET_G:
		//if (GetBeansIn() == false)
		//{
		//	SetPointPos({ FILTER_GPOS_X, FILTER_GPOS_Y - 100 });
		//}
		//else
		//{
		//	SetPointPos({ FILTER_GPOS_X, FILTER_GPOS_Y - 60 });
		//}

		// grinderのボタンとカーソルの判定
		if (
			(mpos_.x - (cpos.x - cameraPos.x) <= 10) &&
			(mpos_.x - (cpos.x - cameraPos.x) >= -10) &&
			(mpos_.y - (cpos.y - cameraPos.y) <= 10) &&
			(mpos_.y - (cpos.y - cameraPos.y) >= -10)
			)
		{
			// マウスがボタンの位置に来ると色が変わる
			colorg = 1;

			if (GetFilter() == FILTER::SET_G &&
				GetBeansIn() == false &&
				ins.IsTrgMouseLeft() == true)
			{
				PlaySounds(grinderButton_,255);
				BeansState(true, false, false, false);

				// 矢印をgrinderのセットする部分の上部へ
				SetPointPos({ FILTER_GPOS_X, FILTER_GPOS_Y - 60 }, AsoUtility::DIR::DOWN);
			}
		}
		if (CheckSoundMem(grinderButton_) == 1)
		{
			colorg = 2;
		}

		break;

	case FILTER::SELECT_T:
		break;

	case FILTER::SET_T:
		// filterをmatに置いたとき矢印をtamper上部へ
		if (GetBeansStamp() == false)
		{
			SetPointPos({ TAMPER_POS_X, TAMPER_POS_Y - 70 }, AsoUtility::DIR::DOWN);
		}

		break;

	case FILTER::SELECT_M:
		if (GetBeansBrew() == true && !(GetHotMenu() == HOTMENU::NONE && GetIceMenu() == ICEMENU::NONE))
		{
			SetPointPos({ TAMPER_FPOS_X - 80, TAMPER_FPOS_Y }, AsoUtility::DIR::DOWN);
		}
		break;

	case FILTER::SET_M:
		// マシンの左から2番目のボタンとカーソルの判定
		if (/*
			 GetHotCup()==HOTCUP::SET_CENTER &&*/
			(mpos_.x - (929 - cameraPos.x) <= 18) &&
			(mpos_.x - (929 - cameraPos.x) >= -18)&&
			(mpos_.y - (592 - cameraPos.y) <= 18) &&
			(mpos_.y - (592 - cameraPos.y) >= -18)
			)
		{
			// マウスがボタンの位置に来ると色が変わる
			colore = 1;

			if (GetHotCup() == HOTCUP::SET_CENTER &&
				GetHotMenu() == HOTMENU::NONE &&
				GetBeansBrew() == false &&
				ins.IsTrgMouseLeft() == true)
			{
				PlaySounds(CupPourHotSound_, 255);
				BeansState(true, true, true, false);
				hotMenu_ = HOTMENU::ESPRESSO;
			}
			else if (GetIceCup() == ICECUP::SET_CENTER &&
				GetIceMenu() == ICEMENU::NONE &&
				isIce_ == true			&&
				GetBeansBrew() == false &&
				ins.IsTrgMouseLeft() == true)
			{
				PlaySounds(CupPourIceSound_, 255);
				BeansState(true, true, true, false);
				iceMenu_ = ICEMENU::ESPRESSO;
			}
		}

		if (
			(GetHotCup() == HOTCUP::SET_CENTER ||
				GetIceCup() == ICECUP::SET_CENTER) &&
			(CheckSoundMem(CupPourHotSound_) == 1	||
				CheckSoundMem(CupPourIceSound_) == 1)
			)
		{
			colore = 2;
		}

		if (
			(GetHotCup() == HOTCUP::SET_LEFT ||
				GetIceCup() == ICECUP::SET_LEFT)	&&
			(CheckSoundMem(CupPourHotSound_) == 1 ||
				CheckSoundMem(CupPourIceSound_) == 1)
			)
		{
			colora = 2;
		}

		if (sceneGame_->GetCustomer() == CustomerBase::CUSTOMER::ICECUP &&
			GetBeansBrew() == false)
		{
			IsPoint(false);
		}
		else if (isPlaySound_ && sceneGame_->GetCustomer() == CustomerBase::CUSTOMER::HOTCUP)
		{
			isPoint_ = false;
			return;
		}
		else if(isPlaySound_ == false&& sceneGame_->GetCustomer() == CustomerBase::CUSTOMER::HOTCUP)
		{
			isPoint_ = true;
		}

		if (GetBeansBrew() == true)
		{
			SetPointPos({ FILTER_CPOS_X + 35, FILTER_CPOS_Y }, AsoUtility::DIR::LEFT);
		}
		else if (GetHotCup() == HOTCUP::NONE)
		{
			SetPointPos({ HOTCUP_POS_X - 8, HOTCUP_POS_Y - 50 }, AsoUtility::DIR::DOWN);
		}
		else if (GetBeansBrew() == false &&
			GetHotCup() == HOTCUP::SET_LEFT)
		{
			SetPointPos({ LEFT_POS_X,  LEFT_POS_Y - 50 }, AsoUtility::DIR::DOWN);
		}
		else if (GetBeansBrew() == false &&
			GetHotCup() == HOTCUP::TAKE)
		{
			SetPointPos({ CENTER_POS_X - 5, CENTER_POS_Y - 30 }, AsoUtility::DIR::DOWN);
		}
		else if (GetHotMenu() == HOTMENU::NONE  &&
			GetHotCup() == HOTCUP::SET_CENTER)
		{
			SetPointPos({ 929, FILTER_CPOS_Y - 110 }, AsoUtility::DIR::DOWN);
		}

		break;

	default:
		break;
	}

	switch (tamper_)
	{
	case TAMPER::NONE:
		SetTamperPos(Vector2(TAMPER_POS_X, TAMPER_POS_Y));

		//if (GetBeansStamp() == true &&
		//	GetFilter() == FILTER::SET_T)
		//{
		//	// 矢印をtampermatの上部へ
		//	SetPointPos({ FILTER_TPOS_X, FILTER_TPOS_Y - 60 }, AsoUtility::DIR::DOWN);
		//}

		break;

	case TAMPER::SELECT:
		SetTamperPos(Vector2(TAMPER_POS_X, TAMPER_POS_Y));
		if (GetBeansStamp() == true &&
			GetFilter() == FILTER::SET_T)
		{
			// 矢印をtampermatの上部へ
			SetPointPos({ FILTER_TPOS_X, FILTER_TPOS_Y - 60 }, AsoUtility::DIR::DOWN);
		}
		break;

	case TAMPER::TAKE:
		// tamperの位置をgrinderに設定する
		if (/*GetBeansIn() == false &&*/
			((TAMPER_FPOS_X - cameraPos.x) - mpos_.x) < (mpos_.x - (TAMPER_POS_X - cameraPos.x))
			)
		{
			SetTamperPos(Vector2(TAMPER_POS_X, TAMPER_POS_Y));
		}
		else
		{
			SetTamperPos(Vector2(TAMPER_FPOS_X, TAMPER_FPOS_Y));
		}

		// beansがStampされていないとき
		if (GetBeansStamp() == false)
		{
			// 矢印をfilterの上部へ
			SetPointPos({ TAMPER_FPOS_X, TAMPER_FPOS_Y - 70 }, AsoUtility::DIR::DOWN);
		}
		else
		{
			// 矢印をtamper初期位置の上部へ
			SetPointPos({ TAMPER_POS_X, TAMPER_POS_Y - 70 }, AsoUtility::DIR::DOWN);
		}

		break;

	case TAMPER::SET_F:
		SetTamperPos(Vector2(TAMPER_FPOS_X, TAMPER_FPOS_Y));

		if (GetBeansStamp() == false)
		{
			// 矢印をfilterの上部へ
			SetPointPos({ TAMPER_FPOS_X, TAMPER_FPOS_Y - 70 }, AsoUtility::DIR::DOWN);
		}
		else
		{
			// 矢印をtamper初期位置の上部へ
			SetPointPos({ TAMPER_POS_X, TAMPER_POS_Y - 70 }, AsoUtility::DIR::DOWN);
		}		
		break;

	case TAMPER::STAMP:
		isPoint_ = false;
		isPushKey_ = true;
		pushPos_ = { TAMPER_FPOS_X, TAMPER_FPOS_Y - 65 };
		// 矢印をfilterの上部へ
		SetPointPos({ TAMPER_FPOS_X, TAMPER_FPOS_Y - 70 }, AsoUtility::DIR::DOWN);
		break;

	case TAMPER::FINISH:
		SetTamperPos(Vector2(TAMPER_FPOS_X, TAMPER_FPOS_Y));

		// 矢印をfilterの上部へ
		SetPointPos({ TAMPER_FPOS_X, TAMPER_FPOS_Y - 70 }, AsoUtility::DIR::DOWN);

		beansStamp_ = true;
		break;
	}

	// ホットのメニューがNONE以外かつ
	// ホットカップがマシーン中央にセットされていたら
	if (
		!(GetHotMenu() == HOTMENU::NONE) &&
		GetHotCup() == HOTCUP::SET_CENTER
		)
	{
		dir_ = AsoUtility::DIR::RIGHT;
		SetPointPos({ CENTER_POS_X - 65,CENTER_POS_Y }, AsoUtility::DIR::RIGHT);
	}
	else if (!(GetHotMenu() == HOTMENU::NONE) &&
		GetHotCup() == HOTCUP::SET_LEFT)
	{
		dir_ = AsoUtility::DIR::RIGHT;
		SetPointPos({ LEFT_POS_X + 65,LEFT_POS_Y }, AsoUtility::DIR::LEFT);
	}
	else if (	// ホットのメニューがNONE以外かつ
				// ホットカップがTAKE又はマシンチュウオウを選んでいる且つ
				// マップがキッチンだったら
		!(GetHotMenu() == HOTMENU::NONE) && 
		(GetHotCup() == HOTCUP::TAKE || GetHotCup() == HOTCUP::MACHINE_CENTER || GetHotCup() == HOTCUP::MACHINE_LEFT) &&
		map_.GetMapType() == Map::TYPE::COFFEE)
	{
		SetPointPos({ 1400 - 25,870 }, AsoUtility::DIR::RIGHT);
	}
	// ホットカップが提供部分に入っていたら
	else if (GetHotCup() == HOTCUP::FINISH )
	{
		SetPointPos({ 1293 - 60,425 }, AsoUtility::DIR::RIGHT);
	}
	// ホットかぷがTAKE且つマップが接客画面だったら
	else if (GetHotCup() == HOTCUP::TAKE &&
		map_.GetMapType() == Map::TYPE::TALK)
	{
		SetPointPos({ 1293 - 60,425 }, AsoUtility::DIR::RIGHT);

	}

	// カーソルとfilter(初期位置)の矩形判定
	if (
		mpos_.x > (FILTER_POS_X - (FSIZE_X / 2) - 5) - cameraPos.x &&
		mpos_.x < (FILTER_POS_X + (FSIZE_X / 2) + 5) - cameraPos.x &&
		mpos_.y >(FILTER_POS_Y - (FSIZE_Y / 2) - 5) - cameraPos.y &&
		mpos_.y < (FILTER_POS_Y + (FSIZE_Y / 2) + 5) - cameraPos.y
		)
	{
		if (GetFilter() == FILTER::NONE &&
			IsHolding() == false
			)
		{
			ChangeFilter(FILTER::SELECT);
		}
		if (GetFilter() == FILTER::SELECT &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(filterTakeSound_, 255);
			ChangeFilter(FILTER::TAKE);

			if (
				(!(GetHotCup() == HOTCUP::FINISH)||
				!(GetIceCup() == ICECUP::FINISH) ) &&
				GetHotMenu() == HOTMENU::NONE		)
			{
				// 矢印をgrinderのセットする部分の下部へ
				SetPointPos({ FILTER_GPOS_X, FILTER_GPOS_Y - 60 }, AsoUtility::DIR::DOWN);
			}
		
		}
		else if (
			GetFilter() == FILTER::TAKE &&
			beansIn_ == false &&
			ins.IsTrgMouseLeft() == true)
		{
			ChangeFilter(FILTER::SELECT);
			PlaySounds(filterTakeSound_, 255);

			if (GetHotMenu() == HOTMENU::NONE)
			{
				// 矢印をfilterの初期位置へ
				// SetPointPos({ FILTER_POS_X, FILTER_POS_Y - 90 }, AsoUtility::DIR::DOWN);
				SetPointPos({ FILTER_POS_X + FSIZE_X + 10, FILTER_POS_Y/* - (FSIZE_Y/2 + POINT_SIZE_Y)*/ }, AsoUtility::DIR::LEFT);

			}
			
		}
	}
	else if (GetFilter() == FILTER::SELECT)
	{
		ChangeFilter(FILTER::NONE);
	}

	// filterとgrinderの当たり判定（矩形）
	// filterとgrinderが近づいたとき吸い寄せられるように
	// fiterとgrinderが当たっているときにクリックすると設置する
	if (
		mpos_.x > 1100 - 5- cameraPos.x &&
		mpos_.x < 1150 + 5 - cameraPos.x &&
		mpos_.y > 655 - 5 - cameraPos.y &&
		mpos_.y < 675 + 5 - cameraPos.y &&
		!(GetBeansStamp())
		)
	{
		//if (!(GetFilter() == FILTER::NONE))
		//{
		//	// SetFilterPos(Vector2(FILTER_GPOS_X, FILTER_GPOS_Y));
		//}
		if (GetFilter() == FILTER::TAKE &&
			GetBeansIn() == false)
		{
			ChangeFilter(FILTER::SELECT_G);

			if (GetHotMenu() == HOTMENU::NONE)
			{
				// 矢印をgrinderのセットする部分の上部へ
				SetPointPos({ FILTER_GPOS_X, FILTER_GPOS_Y - 60 }, AsoUtility::DIR::DOWN);
			}
		}
		else if (GetFilter() == FILTER::SELECT_G &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(filterSetSound_, 255);
			ChangeFilter(FILTER::SET_G);
			if (GetHotMenu() == HOTMENU::NONE)
			{
				// 矢印をgrinderのボタン上部へ
				SetPointPos({ FILTER_GPOS_X, FILTER_GPOS_Y - 110 }, AsoUtility::DIR::DOWN);
			}
		}
		else if (GetFilter() == FILTER::SET_G &&
			IsHolding() == false			  &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(filterSetOutSound_, 255);
			ChangeFilter(FILTER::TAKE);

			if (GetHotMenu() == HOTMENU::NONE)
			{
				// 矢印をgrinderのセットする部分の上部へ
				SetPointPos({ FILTER_GPOS_X, FILTER_GPOS_Y - 60 }, AsoUtility::DIR::DOWN);
			}
		}
	}
	else if (GetFilter() == FILTER::SELECT_G)
	{
		ChangeFilter(FILTER::TAKE);
	}

	// filterとtampermatの当たり判定
	if (
		mpos_.x > 1490- 5  - cameraPos.x &&
		mpos_.x < 1530+ 5  - cameraPos.x &&
		mpos_.y > 717 - 5 - cameraPos.y &&
		mpos_.y < 744 + 5 - cameraPos.y &&
		GetBeansIn() == true  /*|| GetBeansStamp() == false */
		)
	{
		if (GetFilter() == FILTER::TAKE &&
			GetBeansStamp() == false)
		{
			ChangeFilter(FILTER::SELECT_T);
		}
		else if (GetFilter() == FILTER::SELECT_T &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(filterSetMatSound_, 255);
			ChangeFilter(FILTER::SET_T);
		}
		else if (GetFilter() == FILTER::SET_T && GetTamper() == TAMPER::NONE &&
			GetBeansStamp() == true &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(filterTakeSound_, 255);
			ChangeFilter(FILTER::TAKE);
		}
	}
	else if (GetFilter() == FILTER::SELECT_T)
	{
		ChangeFilter(FILTER::TAKE);
	}

	// カーソルとmat上のtamperの当たり判定
	// tamperがSTAMPの時も反応する
	if (
		(mpos_.x > (TAMPER_POS_X - (TSIZE_X / 2)- 5) - cameraPos.x) &&
		(mpos_.x < (TAMPER_POS_X + (TSIZE_X / 2)+ 5) - cameraPos.x) &&
		(mpos_.y > (TAMPER_POS_Y - (TSIZE_Y / 2)- 5) - cameraPos.y) &&
		(mpos_.y < (TAMPER_POS_Y + (TSIZE_Y / 2)+ 5) - cameraPos.y) &&
		GetFilter() == FILTER::SET_T && GetBeansIn() == true &&
		!(GetTamper() == TAMPER::STAMP /*|| GetTamper() == TAMPER::SELECT || GetTamper() == TAMPER::TAKE*/)
		)
	{
		// SetTamperPos(Vector2(TAMPER_POS_X, TAMPER_POS_Y));
		if (
			GetTamper() == TAMPER::NONE &&
			IsHolding() == false
			)
		{
			ChangeTamper(TAMPER::SELECT);
		}
		else if (GetTamper() == TAMPER::SELECT &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(filterTakeSound_, 255);
			// SELECTの時にtamperをクリックすると持つ
			ChangeTamper(TAMPER::TAKE);
		}
		else if (GetTamper() == TAMPER::TAKE &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(filterTakeSound_, 255);
			// 持っている状態でクリックすると置く
			ChangeTamper(TAMPER::SELECT);
		}
	}
	else if (GetTamper() == TAMPER::SELECT)
	{
		ChangeTamper(TAMPER::NONE);
	}

	// カーソルとfilter上部の接触判定
	if (
		(mpos_.x > (TAMPER_FPOS_X - (TSIZE_X / 2)- 5) - cameraPos.x) &&
		(mpos_.x < (TAMPER_FPOS_X + (TSIZE_X / 2)+ 5) - cameraPos.x) &&
		(mpos_.y > (TAMPER_FPOS_Y - (TSIZE_Y / 2)- 5) - cameraPos.y) &&
		(mpos_.y < (TAMPER_FPOS_Y + (TSIZE_Y / 2)+ 5) - cameraPos.y) &&
		GetTamper() == TAMPER::FINISH
		)
	{
		SetTamperPos(Vector2(TAMPER_FPOS_X, TAMPER_FPOS_Y));
		if (GetTamper() == TAMPER::FINISH &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(tamperSetSound_, 255);
			ChangeTamper(TAMPER::TAKE);
		}
	}

	// tamperとfilter上部の接触判定
	if (
		(mpos_.x > (TAMPER_FPOS_X - (TSIZE_X / 2)- 3) - cameraPos.x) &&
		(mpos_.x < (TAMPER_FPOS_X + (TSIZE_X / 2)+ 3) - cameraPos.x) &&
		(mpos_.y > (TAMPER_FPOS_Y - (TSIZE_Y / 2)- 3) - cameraPos.y) &&
		(mpos_.y < (TAMPER_FPOS_Y + (TSIZE_Y / 2)+ 3) - cameraPos.y) &&
		GetFilter() == FILTER::SET_T
		)
	{
		if (GetTamper() == TAMPER::TAKE)
		{
			ChangeTamper(TAMPER::SET_F);
		}
		else if (GetTamper() == TAMPER::SET_F &&
			GetBeansStamp() == false &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(tamperSetSound_, 255);
			ChangeTamper(TAMPER::STAMP);
		}
	}
	else if (GetTamper() == TAMPER::SET_F)
	{
		ChangeTamper(TAMPER::TAKE);
	}

	// tamperとBeansの矩形の押し出し処理
	if (GetTamper() == TAMPER::STAMP)
	{
		Rect pos = { 1510 - cameraPos.x,728 - cameraPos.y };
		Rect rcA = { {(tamperPos_.x - cameraPos.x),(tamperPos_.y - cameraPos.y)},{TSIZE_X,TSIZE_Y} };
		Rect rcB = { {(boxPos_.x - cameraPos.x),(boxPos_.y - cameraPos.y)} ,{39,12} };

		if (pushCnt_ < 40)
		{
			if (ins.IsNew(KEY_INPUT_DOWN) ||
				ins.IsNew(KEY_INPUT_S))
			{
				//rcA.pos.y += 2.0f;
				tamperPos_.y += 2.0f;
			}
			if (ins.IsNew(KEY_INPUT_UP)	||
				ins.IsNew(KEY_INPUT_W))
			{
				//rcA.pos.y -= 2.0f;
				tamperPos_.y -= 2.0f;
				if (tamperPos_.y < 640)
				{
					tamperPos_.y = 640;
				}
			}
		}
		else
		{
			pushKey_ = 1;
			color_ = 0x44FF44;
			if (ins.IsNew(KEY_INPUT_UP) ||
				ins.IsNew(KEY_INPUT_W))
			{
				PlaySounds(tamperPullupSound_, 255);
				ChangeTamper(TAMPER::FINISH);
				tamperPos_.y = TAMPER_FPOS_Y;
				isPushKey_ = false;
				if (sceneGame_->GetCustomer() == CustomerBase::CUSTOMER::HOTCUP)
				{
					isPoint_ = true;
				}
			}
		}

		if (IsHit(rcA, rcB))
		{
			if (pushCnt_ == MAX_COUNT)
			{
				beansStamp_ = true;
				return;
			}
			// 押し出し処理
			float weight = 0.1f;
			auto diffx = rcB.pos.x - rcA.pos.x;
			auto diffy = rcB.pos.y - rcA.pos.y;
			int signX = SignVal(diffx);
			int signY = SignVal(diffy);
			int overlapX = rcA.size.w / 2 + rcB.size.w / 2 - fabsf(diffx);
			int overlapY = rcA.size.h / 2 + rcB.size.h / 2 - fabsf(diffy);
			if (overlapX < overlapY)
			{
				tamperPos_.x += overlapX * -weight * signX;
				rcB.pos.x += overlapX * (1.0 - weight) * signX;
			}
			else
			{
				tamperPos_.y += overlapY * -weight * signY;
				rcB.pos.y += overlapY * (1.0 - weight) * signY;
			}
			if (tamperPos_.y - cameraPos.y >= 227)
			{
				pushCnt_++;
			}
		}
	}

	// filterを持っているカーソルとマシンの当たり判定
	if (
		mpos_.x > ((filterPos_.x - FSIZE_X / 2) - 5- cameraPos.x) &&
		mpos_.x < ((filterPos_.x + FSIZE_X / 2) + 5- cameraPos.x) &&
		mpos_.y > ((filterPos_.y - FSIZE_Y / 10)- 5 - cameraPos.y)&&
		mpos_.y < ((filterPos_.y + FSIZE_Y / 10)+ 5 - cameraPos.y)&&
		!(GetHotCup() == HOTCUP::TAKE) && GetBeansStamp()
		)
	{
		if (GetFilter() == FILTER::TAKE		&&
			GetBeansBrew() == false
			)
		{
			ChangeFilter(FILTER::SELECT_M);
		}
		else if (GetFilter() == FILTER::SELECT_M &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(filterSetSound_, 255);
			ChangeFilter(FILTER::SET_M);
		}
		else if (GetFilter() == FILTER::SET_M &&
			IsHolding() == false &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(filterSetOutSound_, 255);
			ChangeFilter(FILTER::TAKE);
		}
	}
	else if (GetBeansStamp() &&
		GetFilter() == FILTER::SELECT_M)
	{
		ChangeFilter(FILTER::TAKE);
	}

	// ホットカップとカーソルの接触判定
	if (
		mpos_.x > (817 - cameraPos.x) &&
		mpos_.x < (884 - cameraPos.x) &&
		mpos_.y > (917 - cameraPos.y)  &&
		mpos_.y < (960 - cameraPos.y)  
		)
	{
		if (IsHolding() == false &&
			GetHotCup() == HOTCUP::NONE)
		{
			ChangeHotCup(HOTCUP::SELECT);
		}
		else if (GetHotCup() == HOTCUP::SELECT &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupTakeSound_, 255);
			ChangeHotCup(HOTCUP::TAKE);
		}
		else if (GetHotCup() == HOTCUP::TAKE &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupSetSound_, 255);
			ChangeHotCup(HOTCUP::SELECT);
		}
	}
	else if(GetHotCup() == HOTCUP::SELECT)
	{
		ChangeHotCup(HOTCUP::NONE);
	}

	// アイスカップとカーソルの接触判定
	if (
		mpos_.x > ((ICECUP_POS_X - ICECUP_SIZE_X / 2) - cameraPos.x) &&
		mpos_.x < ((ICECUP_POS_X + ICECUP_SIZE_X / 2) - cameraPos.x) &&
		mpos_.y > ((ICECUP_POS_Y - ICECUP_SIZE_Y / 2) - cameraPos.y) &&
		mpos_.y < ((ICECUP_POS_Y + ICECUP_SIZE_Y / 2) - cameraPos.y)
		)
	{
		if (IsHolding() == false &&
			GetIceCup() == ICECUP::NONE)
		{
			ChangeIceCup(ICECUP::SELECT);
		}
		else if (GetIceCup() == ICECUP::SELECT &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupTakeSound_, 255);
			ChangeIceCup(ICECUP::TAKE);
		}
		else if (GetIceCup() == ICECUP::TAKE &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupSetSound_, 255);
			ChangeIceCup(ICECUP::SELECT);
		}
	}
	else if (GetIceCup() == ICECUP::SELECT)
	{
		ChangeIceCup(ICECUP::NONE);
	}

	// アイスカップを持っているとき
	// カーソルとアイスディスペンサーの矩形の接触判定
	if (
		mpos_.x > (1220 - cameraPos.x) &&
		mpos_.x < (1270 - cameraPos.x) &&
		mpos_.y >(655 - cameraPos.y) &&
		mpos_.y < (705 - cameraPos.y)
		)
	{
		if (GetIceCup() == ICECUP::TAKE)
		{
			ChangeIceCup(ICECUP::ICEDISPENSER);
		}
		else if (GetIceCup() == ICECUP::ICEDISPENSER &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupSetSound_, 255);
			ChangeIceCup(ICECUP::SET_ICE);
		}
		else if (GetIceCup() == ICECUP::SET_ICE &&
			IsHolding() == false &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupTakeSound_, 255);
			ChangeIceCup(ICECUP::ICEDISPENSER);
		}
	}
	else if (GetIceCup() == ICECUP::ICEDISPENSER)
	{
		ChangeIceCup(ICECUP::TAKE);
	}

	// アイスディスペンサーのボタンとカーソルの判定
	if (
		(mpos_.x - (1245 - cameraPos.x) <= 12) &&
		(mpos_.x - (1245 - cameraPos.x) >= -12)&&
		(mpos_.y - (600 - cameraPos.y) <= 12)  &&
		(mpos_.y - (600 - cameraPos.y) >= -12) &&
		isIce_ == false
		)
	{
		// マウスがボタンの位置に来ると色が変わる
		colori = 1;

		if (GetIceCup() == ICECUP::SET_ICE &&
			isIce_ == false &&
			ins.IsTrgMouseLeft() == true)
		{
			//PlaySounds(grinderButton_);
			PlaySounds(CupIceInSound_, 180);
			isIce_ = true;
			colori = 2;
		}
	}
	else
	{
		colori = 0;
	}

	if (GetIceCup() == ICECUP::SET_ICE &&
		CheckSoundMem(CupIceInSound_) != 0)
	{
		colori = 2;
	}


	// ホットカップを持っているとき
	// カーソルとマシン中央の矩形の接触判定
	if (
		mpos_.x > (900 - cameraPos.x) &&
		mpos_.x < (960 - cameraPos.x) &&
		mpos_.y > (668 - cameraPos.y) &&
		mpos_.y < (711 - cameraPos.y)
		)
	{
		if (IsSetMachineCenter() == false &&
			GetHotCup() == HOTCUP::TAKE)
		{
			ChangeHotCup(HOTCUP::MACHINE_CENTER);
		}
		else if (GetHotCup() == HOTCUP::MACHINE_CENTER &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupSetSound_, 255);
			ChangeHotCup(HOTCUP::SET_CENTER);
		}
		else if(GetHotCup() == HOTCUP::SET_CENTER &&
			IsHolding() == false &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupTakeSound_, 255);
			ChangeHotCup(HOTCUP::MACHINE_CENTER);
		}
	}
	else if (GetHotCup() == HOTCUP::MACHINE_CENTER)
	{
		ChangeHotCup(HOTCUP::TAKE);
	}

	// アイスカップを持っているとき
	// カーソルとマシン中央の矩形の接触判定
	if (
		mpos_.x > (900 - cameraPos.x) &&
		mpos_.x < (960 - cameraPos.x) &&
		mpos_.y > (668 - cameraPos.y) &&
		mpos_.y < (711 - cameraPos.y)
		)
	{
		if (IsSetMachineCenter() == false && 
			GetIceCup() == ICECUP::TAKE)
		{
			ChangeIceCup(ICECUP::MACHINE_CENTER);
		}
		else if (GetIceCup() == ICECUP::MACHINE_CENTER &&
			IsHolding() == false &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupSetSound_, 255);
			ChangeIceCup(ICECUP::SET_CENTER);
		}
		else if (GetIceCup() == ICECUP::SET_CENTER &&
			IsHolding() == false &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupTakeSound_, 255);
			ChangeIceCup(ICECUP::MACHINE_CENTER);
		}
	}
	else if (GetIceCup() == ICECUP::MACHINE_CENTER)
	{
		ChangeIceCup(ICECUP::TAKE);
	}

	// ホットカップを持っているとき
	// カーソルとマシン左の矩形の接触判定
	if (
		mpos_.x > (823 - cameraPos.x) &&
		mpos_.x < (880 - cameraPos.x) &&
		mpos_.y > (668 - cameraPos.y) &&
		mpos_.y < (711 - cameraPos.y)
		)
	{
		if (IsSetMachineLeft() == false &&
			GetHotCup() == HOTCUP::TAKE)
		{
			ChangeHotCup(HOTCUP::MACHINE_LEFT);
		}
		else if (GetHotCup() == HOTCUP::MACHINE_LEFT &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupSetSound_, 255);
			ChangeHotCup(HOTCUP::SET_LEFT);
		}
		else if (GetHotCup() == HOTCUP::SET_LEFT &&
			IsHolding() == false &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupTakeSound_, 255);
			ChangeHotCup(HOTCUP::MACHINE_LEFT);
		}
	}
	else if (GetHotCup() == HOTCUP::MACHINE_LEFT)
	{
		ChangeHotCup(HOTCUP::TAKE);
	}

	// アイスカップを持っているとき
	// カーソルとマシン左の矩形の接触判定
	if (
		mpos_.x > (823 - cameraPos.x) &&
		mpos_.x < (880 - cameraPos.x) &&
		mpos_.y >(668 - cameraPos.y) &&
		mpos_.y < (711 - cameraPos.y)
		)
	{
		if (IsSetMachineLeft() == false &&
			GetIceCup() == ICECUP::TAKE)
		{
			ChangeIceCup(ICECUP::MACHINE_LEFT);
		}
		else if (GetIceCup() == ICECUP::MACHINE_LEFT &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupSetSound_, 255);
			ChangeIceCup(ICECUP::SET_LEFT);
		}
		else if (GetIceCup() == ICECUP::SET_LEFT &&
			IsHolding() == false &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupTakeSound_, 255);
			ChangeIceCup(ICECUP::MACHINE_LEFT);
		}
	}
	else if (GetIceCup() == ICECUP::MACHINE_LEFT)
	{
		ChangeIceCup(ICECUP::TAKE);
	}

	// マシンの左端のボタンとカーソルの判定
	if (
		( GetHotCup()==HOTCUP::SET_LEFT || GetIceCup() == ICECUP::SET_LEFT) &&
		(mpos_.x - (840 - cameraPos.x) <= 18) &&
		(mpos_.x - (840 - cameraPos.x) >= -18) &&
		(mpos_.y - (597 - cameraPos.y) <= 18) &&
		(mpos_.y - (597 - cameraPos.y) >= -18)
		)
	{
		// マウスがボタンの位置に来ると色が変わる
		colora = 1;

		if (GetHotCup() == HOTCUP::SET_LEFT &&
			GetHotMenu() == HOTMENU::ESPRESSO &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupPourHotSound_, 240);
			hotMenu_ = HOTMENU::AMERICANO;
		}

		if (isIce_ == true	&&
			GetIceCup() == ICECUP::SET_LEFT &&
			GetIceMenu() == ICEMENU::ESPRESSO &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(CupPourIceSound_, 240);
			iceMenu_ = ICEMENU::AMERICANO;
		}
	}

	// ホットカップを持っているとき
	// カーソルと右下のBoxの接触判定
	if (
		mpos_.x > 600 &&
		mpos_.x < 790 &&
		mpos_.y > 310 &&
		mpos_.y < 450 &&
		!(GetFilter() == FILTER::TAKE)
		)
	{
		if (GetHotCup() == HOTCUP::TAKE &&
			!(GetHotMenu() == HOTMENU::NONE)&&
			ins.IsTrgMouseLeft() == true)
		{
			ChangeHotCup(HOTCUP::FINISH);
		}
		else if(GetHotCup() == HOTCUP::FINISH &&
			IsHolding() == false			&&
			ins.IsTrgMouseLeft() == true)
		{
			ChangeHotCup(HOTCUP::TAKE);
		}

		if (GetIceCup() == ICECUP::TAKE &&
			!(GetIceMenu() == ICEMENU::NONE) &&
			ins.IsTrgMouseLeft() == true)
		{
			ChangeIceCup(ICECUP::FINISH);
		}
		else if (GetIceCup() == ICECUP::FINISH &&
			IsHolding() == false &&
			ins.IsTrgMouseLeft() == true)
		{
			ChangeIceCup(ICECUP::TAKE);
		}
	}


	// マシンのボタンを押した後
	// filterをNockBoxへ持って行ったとき
	if (GetBeansBrew()&&
		mpos_.x > (1401 - cameraPos.x) &&
		mpos_.x < (1461 - cameraPos.x) &&
		mpos_.y > (700 - cameraPos.y)  &&
		mpos_.y < (752 - cameraPos.y)
		)
	{
		if (GetFilter()==FILTER::TAKE && 
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(beansDustSound_, 255);
			DustBeans();
			if (
				(GetHotCup() == HOTCUP::FINISH ||
				GetIceCup() == ICECUP::FINISH) &&
				sceneGame_->GetCustomer() == CustomerBase::CUSTOMER::ICECUP)
			{
				isPoint_ = false;
			}
		}
	}

	// マウスとピッチャーの当たり判定
	if (
		mpos_.x > (PITCHER_POS_X - PITCHER_SIZE_X / 2 - cameraPos.x) &&
		mpos_.x < (PITCHER_POS_X + PITCHER_SIZE_X / 2 - cameraPos.x) &&
		mpos_.y > (PITCHER_POS_Y - PITCHER_SIZE_Y / 2 - cameraPos.y) &&
		mpos_.y < (PITCHER_POS_Y + PITCHER_SIZE_Y / 2 - cameraPos.y) 
		)
	{
		if (GetPitcher() == PITCHER::NONE)
		{
			ChangePitcher(PITCHER::SELECT);
		}
		if (GetPitcher() == PITCHER::SELECT &&
			IsHolding() == false			&&
			ins.IsTrgMouseLeft() == true)
		{
			ChangePitcher(PITCHER::TAKE);
			PlaySounds(pitcherSound_, 255);
		}
		else if (GetPitcher() == PITCHER::TAKE &&
			ins.IsTrgMouseLeft() == true)
		{
			ChangePitcher(PITCHER::SELECT);
			PlaySounds(setPitcherSound_, 200);
		}
	}
	else if (GetPitcher() == PITCHER::SELECT)
	{
		ChangePitcher(PITCHER::NONE);
	}


	// 持っているピッチャーと机の当たり判定
	if (
		mpos_.x > (PITCHER_DESKPOS_X - PITCHER_SIZE_X / 2 )- cameraPos.x &&
		mpos_.x < (PITCHER_DESKPOS_X + PITCHER_SIZE_X / 2 )- cameraPos.x &&
		mpos_.y > (PITCHER_DESKPOS_Y - PITCHER_SIZE_Y / 2 )- cameraPos.y &&
		mpos_.y < (PITCHER_DESKPOS_Y + PITCHER_SIZE_Y / 2 )- cameraPos.y
		)
	{
		if (GetPitcher() == PITCHER::TAKE)
		{
			ChangePitcher(PITCHER::SELECT_DESK);
		}
		else if (GetPitcher() == PITCHER::SELECT_DESK &&
			ins.IsTrgMouseLeft() == true)
		{
			ChangePitcher(PITCHER::SET_DESK);
			PlaySounds(setPitcherSound_, 200);
		}
		else if (GetPitcher() == PITCHER::SET_DESK &&
			IsHolding() == false				   &&
			ins.IsTrgMouseLeft() == true)
		{
			ChangePitcher(PITCHER::TAKE);
			PlaySounds(pitcherSound_, 255);
		}
	}
	else if (GetPitcher() == PITCHER::SELECT_DESK)
	{
		ChangePitcher(PITCHER::TAKE);
	}


	// マウスと冷蔵庫の当たり判定
	if (
		mpos_.x > (1223 - 2 - cameraPos.x) &&
		mpos_.x < (1380 + 2 - cameraPos.x) &&
		mpos_.y > (782 - 2 - cameraPos.y)  &&
		mpos_.y < (960 + 2 - cameraPos.y)  
		)
	{
		if (IsHolding() == false &&
			reizou_ == REIZOU::NONE)
		{
			reizou_ = REIZOU::SELECT;
		}
		else if(reizou_ == REIZOU::SELECT	&&
			IsHolding() == false			&&
			ins.IsTrgMouseLeft() == true)
		{
			ChangeMilk(MILK::TAKE);
			PlaySounds(reizouCloseSound_, 255);
		}
		else if(reizou_ == REIZOU::SELECT &&
			GetMilk() == MILK::TAKE		&&
			ins.IsTrgMouseLeft() == true)
		{
			ChangeMilk(MILK::SELECT);
			PlaySounds(reizouOpenSound_, 255);
		}
		else if (GetMilk() == MILK::TAKE &&
			reizou_ == REIZOU::NONE)
		{
			reizou_ = REIZOU::SELECT;
		}
	}
	else if (reizou_ == REIZOU::SELECT)
	{
		reizou_ = REIZOU::NONE;
	}
	else if(GetMilk() == MILK::SELECT)
	{
		ChangeMilk(MILK::NONE);
	}

	// 机に置いたピッチャーと牛乳を持っているマウスの当たり判定
	if (
		mpos_.x > (PITCHER_DESKPOS_X - PITCHER_SIZE_X / 2) - cameraPos.x &&
		mpos_.x < (PITCHER_DESKPOS_X + PITCHER_SIZE_X / 2) - cameraPos.x &&
		mpos_.y > (PITCHER_DESKPOS_Y - PITCHER_SIZE_Y  - 30) - cameraPos.y &&
		mpos_.y < (PITCHER_DESKPOS_Y - PITCHER_SIZE_Y / 2 + 30) - cameraPos.y
		)
	{
		if (GetMilk() == MILK::TAKE	&&
			GetPitcher() == PITCHER::SET_DESK)
		{
			ChangeMilk(MILK::READY_POUR);
		}
		if (GetMilk() == MILK::READY_POUR &&
			isMilk_ == false		&&
			ins.IsTrgMouseLeft() == true)
		{
			isMilk_ = true;
			PlaySounds(pourMilkSound_, 255);
		}

	}
	else if (GetMilk() == MILK::READY_POUR)
	{
		ChangeMilk(MILK::TAKE);
	}

	// マシンにピッチャーをセットする部分とマウスの当たり判定
	if (
		mpos_.x > 1010 - cameraPos.x &&
		mpos_.x < 1070 - cameraPos.x &&
		mpos_.y > 638 - cameraPos.y &&
		mpos_.y < 710 - cameraPos.y
		)
	{
		if (GetPitcher() == PITCHER::TAKE &&
			isMilk_ == true)
		{
			ChangePitcher(PITCHER::SELECT_M);
		}
		else if(GetPitcher() == PITCHER::SELECT_M &&
			ins.IsTrgMouseLeft() == true)
		{
			ChangePitcher(PITCHER::SET_M);
			PlaySounds(pitcherSound_, 255);
		}
		else if (GetPitcher() == PITCHER::SET_M &&
			ins.IsTrgMouseLeft() == true)
		{
			ChangePitcher(PITCHER::SELECT_M);
			PlaySounds(pitcherSound_, 255);
		}
	}
	else if (GetPitcher() == PITCHER::SELECT_M)
	{
		ChangePitcher(PITCHER::TAKE);
	}

	if (
		(mpos_.x - (1005 - cameraPos.x) <= 18)	&&
		(mpos_.x - (1005 - cameraPos.x) >= -18) &&
		(mpos_.y - (592 - cameraPos.y) <= 18)	&&
		(mpos_.y - (592 - cameraPos.y) >= -18)
		)
	{
		colorm = 1;
		if (GetPitcher() == PITCHER::SET_M &&
			isMilk_ == true &&
			ins.IsTrgMouseLeft() == true)
		{
			colorm = 2;
			isFormer_ = true;
			PlaySounds(grinderButton_, 255);
		}
	}

	/*(890 - cameraPos.x,
		668 - PITCHER_SIZE_Y - cameraPos.y,
		970 - cameraPos.x,
		723 - PITCHER_SIZE_Y - cameraPos.y,*/

	// カップの上の当たり判定
	if (
		mpos_.x > 890 - cameraPos.x &&
		mpos_.x < 970 - cameraPos.x &&
		mpos_.y > (668 - PITCHER_SIZE_Y) - cameraPos.y &&
		mpos_.y < (723 - PITCHER_SIZE_Y) - cameraPos.y
		)
	{
		if (GetHotCup() == HOTCUP::SET_CENTER	&&
			GetHotMenu() == HOTMENU::ESPRESSO	&&
			GetPitcher() == PITCHER::TAKE		&&
			isFormer_ == true				)
		{
			ChangePitcher(PITCHER::READY_POUR);
			
		}
		if (GetHotCup() == HOTCUP::SET_CENTER &&
			GetPitcher() == PITCHER::READY_POUR &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(pourMilkSound_, 255);
			hotMenu_ = HOTMENU::LATTE;
			isFormer_ = false;
			isMilk_ = false;
		}

		if (GetIceCup() == ICECUP::SET_CENTER &&
			GetIceMenu() == ICEMENU::ESPRESSO &&
			GetPitcher() == PITCHER::TAKE &&
			isFormer_ == true)
		{
			ChangePitcher(PITCHER::READY_POUR);

		}
		if (GetIceCup() == ICECUP::SET_CENTER &&
			GetPitcher() == PITCHER::READY_POUR &&
			ins.IsTrgMouseLeft() == true)
		{
			PlaySounds(pourMilkSound_, 255);
			iceMenu_ = ICEMENU::LATTE;
			isFormer_ = false;
			isMilk_ = false;
		}
	}
	else if (GetPitcher() == PITCHER::READY_POUR)
	{
		ChangePitcher(PITCHER::TAKE);
	}

	// シンクとマウスの当たり判定
	if (
		mpos_.x > 560 - cameraPos.x &&
		mpos_.x < 770 - cameraPos.x &&
		mpos_.y > 665 - cameraPos.y &&
		mpos_.y < 745 - cameraPos.y
		)
	{
		if (GetHotCup() == HOTCUP::TAKE &&
			!(GetHotMenu() == HOTMENU::NONE) &&
			ins.IsTrgMouseLeft() == true)
		{
			hotMenu_ = HOTMENU::NONE;
		}

		if (GetIceCup() == ICECUP::TAKE &&
			!(GetIceMenu() == ICEMENU::NONE) &&
			ins.IsTrgMouseLeft() == true)
		{
			iceMenu_ = ICEMENU::NONE;
			isIce_ = false;
		}
	}
}

void Player::UpdateDrink(void)
{
	//商品提供後
}

void Player::UpdateTalk2(void)
{
	//商品提供後
}

void Player::Draw(void)
{
	auto& ins = InputManager::GetInstance();

	ins.GetMouse();
	mpos_ = ins.GetMousePos();
	Vector2 cameraPos = sceneGame_->GetCameraPos();

	switch (sceneGame_->GetFase())
	{
	case SceneGame::FASE::WAIT:
		DrawWait();
		break;

	case SceneGame::FASE::TALK:
		DrawTalk();
		break;

	case SceneGame::FASE::MAKE:
		DrawMake();
		break;

	case SceneGame::FASE::DRINK:
		DrawDrink();
		break;

	case SceneGame::FASE::TALK2:
		DrawTalk2();
		break;

	default:
		break;
	}
}

void Player::DrawWait(void)
{
}

void Player::DrawTalk(void)
{

}

void Player::DrawMake(void)
{
	Vector2 cameraPos = sceneGame_->GetCameraPos();

	// grinder描画
	DrawRotaGraph(GRINDER_POS_X - cameraPos.x,
		GRINDER_POS_Y - cameraPos.y,
		1.0f, 0.0f,
		imgsgrinder_[0][0],
		true);	
	
	// ice dispenser描画
	DrawRotaGraph((GRINDER_POS_X +120)  - cameraPos.x,
		GRINDER_POS_Y - cameraPos.y,
		1.0f, 0.0f,
		imgIceDispenser_,
		true);

	// grinderのボタン描画
	DrawRotaGraph(cpos.x - cameraPos.x,
		cpos.y - cameraPos.y,
		0.6f, 0.0f,
		imgsButton_[0][colorg],
		true);

	// マシン中央のボタン描画
	DrawRotaGraph(929 - cameraPos.x,
		592 - cameraPos.y,
		1.0f, 0.0f,
		imgsButton_[0][colore],
		true);

	// 左のボタン
	DrawRotaGraph(840 - cameraPos.x,
		592 - cameraPos.y,
		1.0f, 0.0f,
		imgsButton_[0][colora],
		true);

	// 一番右のボタン
	DrawRotaGraph(1005 - cameraPos.x,
		592 - cameraPos.y,
		1.0f, 0.0f,
		imgsButton_[0][colorm],
		true);

	// アイスディスペンサーのボタン
	DrawRotaGraph(1245 - cameraPos.x,
		600 - cameraPos.y,
		0.7f, 0.0f,
		imgsButton_[0][colori],
		true);

	// filter初期位置を示すマット
	DrawRotaGraph(FILTER_POS_X - cameraPos.x,
		FILTER_POS_Y - cameraPos.y,
		1.0f, 0.0f,
		imgfiltermat_,
		true);

	//　filterをtamperの横に設置したときのみ
	if (GetFilter()==FILTER::SET_T &&
		GetBeansStamp() == false)
	{
		// コーヒー豆単体の描画
		DrawRotaGraph(filterPos_.x - cameraPos.x,
			((filterPos_.y - (FSIZE_Y / 6 ) + 3) - cameraPos.y) + (pushCnt_ / 3),
			1.0f,
			0.0f,
			imgbeans_,
			true);
	}

	DrawRotaGraph(1302 - cameraPos.x,
		872 - cameraPos.y,
		1.0f,
		0.0f,
		imgsReizou_[0][static_cast<int>(reizou_)],
		true);

	switch (tamper_)
	{
	case TAMPER::NONE:
		// tamper仮置き
		DrawRotaGraph(tamperPos_.x - cameraPos.x,
			tamperPos_.y +1 - cameraPos.y,
			1.0f, 0.0f,
			imgstamper_[0][0],
			true);
		break;

	case TAMPER::SELECT:
		DrawRotaGraph(tamperPos_.x - cameraPos.x,
			tamperPos_.y -5- cameraPos.y,
			1.0f, 0.0f,
			imgstamper_[0][1],
			true);
		break;

	case TAMPER::TAKE:
		DrawRotaGraph(mpos_.x,
			mpos_.y,
			1.0f, 0.0f,
			imgstamper_[0][0],
			true);
		break;

	case TAMPER::SET_F:
		DrawRotaGraph(tamperPos_.x - cameraPos.x,
			tamperPos_.y - cameraPos.y,
			1.0f, 0.0f,
			imgstamper_[1][0],
			true);
		break;

	case TAMPER::STAMP:
		DrawRotaGraph(tamperPos_.x - cameraPos.x,
			tamperPos_.y - cameraPos.y,
			1.0f, 0.0f,
			imgstamper_[0][0],
			true);

		// ゲージ(灰色)
		DrawBox(1450 - cameraPos.x,
			700 - cameraPos.y,
			1470 - cameraPos.x,
			750 - cameraPos.y, 0x444444, true);	

		// ゲージ(赤)
		DrawBox(1450 - cameraPos.x,
			(740 - pushCnt_) - cameraPos.y,
			1470 - cameraPos.x,
			750 - cameraPos.y, color_, true);
		break;

	case TAMPER::FINISH:
		DrawRotaGraph(tamperPos_.x - cameraPos.x,
			tamperPos_.y - cameraPos.y,
			1.0f, 0.0f,
			imgstamper_[0][0],
			true);
		break;

	default:
		break;
	}

	switch (filter_)
	{
	case FILTER::NONE:
		DrawRotaGraph(filterPos_.x - cameraPos.x,
			filterPos_.y - cameraPos.y,
			1.0f,
			0.0f,
			imgsfilter_[0][0],
			true);
		break;	
	
	case FILTER::SELECT:
		DrawRotaGraph(filterPos_.x - cameraPos.x,
			filterPos_.y - cameraPos.y,
			1.0f,
			0.0f,
			imgsfilter_[0][1],
			true);
		break;	
	
	case FILTER::TAKE:
		if (!(GetBeansIn()) || GetBeansStamp())
		{
			DrawRotaGraph(mpos_.x, mpos_.y,
				1.0f,
				0.0f,
				imgsfilter_[0][2],
				true);
			if (GetBeansBrew() == true)
			{
				DrawRotaGraph(mpos_.x, mpos_.y - flyPos_,
					1.0f,
					0.0f,
					imgdust_,
					true);
			}
		}
		else if(GetBeansIn()== true)
		{
			DrawRotaGraph(mpos_.x, mpos_.y,
				1.0f,
				0.0f,
				imgsfilter_[0][3],
				true);
		}

		break;	

	case FILTER::SELECT_G:
		DrawRotaGraph(filterPos_.x - cameraPos.x,
			(filterPos_.y + SET_POS)- cameraPos.y,
			1.0f,
			0.0f,
			imgsfilter_[1][2],
			true);
		break;
	
	case FILTER::SET_G:
		if (beansIn_ == false)
		{
			DrawRotaGraph(filterPos_.x - cameraPos.x,
				filterPos_.y - cameraPos.y,
				1.0f,
				0.0f,
				imgsfilter_[0][2],
				true);
		}
		else
		{
			DrawRotaGraph(filterPos_.x - cameraPos.x,
				filterPos_.y - cameraPos.y,
				1.0f,
				0.0f,
				imgsfilter_[0][3],
				true);
		}
		break;	

	case FILTER::SELECT_T:
		DrawRotaGraph(filterPos_.x - cameraPos.x,
			(filterPos_.y - SET_POS) - cameraPos.y,
			1.0f,
			0.0f,
			imgsfilter_[1][3],
			true);
		break;

	case FILTER::SET_T:
		DrawRotaGraph(filterPos_.x - cameraPos.x,
			filterPos_.y +1- cameraPos.y,
			1.0f,
			0.0f,
			imgsfilter_[0][2],
			true);
		break;

	case FILTER::SELECT_M:
		DrawRotaGraph(filterPos_.x + 1 - cameraPos.x,
			filterPos_.y - cameraPos.y,
			1.0f,
			0.0f,
			imgsfilter_[1][2],
			true);

		if (GetBeansBrew())
		{
			DrawRotaGraph(filterPos_.x - cameraPos.x,
				(filterPos_.y - cameraPos.y) - flyPos_,
				1.0f,
				0.0f,
				imgdust_,
				true);
		}
		break;

	case FILTER::SET_M:
		DrawRotaGraph(filterPos_.x + 1 - cameraPos.x,
			(filterPos_.y - SET_POS) - cameraPos.y,
			1.0f,
			0.0f,
			imgsfilter_[0][2],
			true);

		if (GetBeansBrew())
		{
			DrawRotaGraph(filterPos_.x - cameraPos.x,
				(filterPos_.y - cameraPos.y) - flyPos_,
				1.0f,
				0.0f,
				imgdust_,
				true);
		}
		break;

	default:
		break;

	}
	
	DrawRotaGraph(HOTCUP_POS_X - cameraPos.x,
		HOTCUP_POS_Y - cameraPos.y,
		1.0f, 0.0f,
		imgHotCupSet_,
		true);	
	
	DrawRotaGraph(ICECUP_POS_X - cameraPos.x,
		ICECUP_POS_Y - cameraPos.y,
		1.0f, 0.0f,
		imgIceCupSet_,
		true);

	switch (cup_)
	{
	case HOTCUP::NONE:
		if (GetHotMenu() == HOTMENU::NONE)
		{
			DrawRotaGraph(HOTCUP_POS_X - cameraPos.x,
				HOTCUP_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][0],
				true);

		}
		else if (!(GetHotMenu() == HOTMENU::NONE))
		{
			DrawRotaGraph(HOTCUP_POS_X - cameraPos.x,
				HOTCUP_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][static_cast<int>(hotMenu_)],
				true);
		}
		break;

	case HOTCUP::SELECT:
		if (GetHotMenu() == HOTMENU::NONE)
		{
			DrawRotaGraph(HOTCUP_POS_X - cameraPos.x,
				HOTCUP_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][0],
				true);
		}
		else if (!(GetHotMenu() == HOTMENU::NONE)) 
		{
			DrawRotaGraph(HOTCUP_POS_X - cameraPos.x,
				HOTCUP_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][static_cast<int>(hotMenu_)],
				true);
		}
		break;

	case HOTCUP::MACHINE_CENTER:
		if (GetHotMenu() == HOTMENU::NONE)
		{
			DrawRotaGraph(CENTER_POS_X - cameraPos.x,
				(CENTER_POS_Y - SET_POS) - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][0],
				true);
		}
		else if (!(GetHotMenu() == HOTMENU::NONE))
		{
			DrawRotaGraph(CENTER_POS_X - cameraPos.x,
				(CENTER_POS_Y - SET_POS) - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][static_cast<int>(hotMenu_)],
				true);
		}
		break;

	case HOTCUP::MACHINE_LEFT:
		if (GetHotMenu() == HOTMENU::NONE)
		{
			DrawRotaGraph(LEFT_POS_X - cameraPos.x,
				(LEFT_POS_Y - SET_POS) - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][0],
				true);
		}
		else if (!(GetHotMenu() == HOTMENU::NONE)) 
		{
			DrawRotaGraph(LEFT_POS_X - cameraPos.x,
				(LEFT_POS_Y - SET_POS) - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][static_cast<int>(hotMenu_)],
				true);
		}
		break;

	case HOTCUP::SET_CENTER:
		if (GetHotMenu() == HOTMENU::NONE)
		{
			DrawRotaGraph(CENTER_POS_X - cameraPos.x,
				CENTER_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][0],
				true);
		}
		else if (!(GetHotMenu() == HOTMENU::NONE))
		{
			DrawRotaGraph(CENTER_POS_X - cameraPos.x,
				CENTER_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][static_cast<int>(hotMenu_)],
				true);
		}

		break;

	case HOTCUP::SET_LEFT:
		if (GetHotMenu() == HOTMENU::NONE)
		{
			DrawRotaGraph(LEFT_POS_X - cameraPos.x,
				LEFT_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][0],
				true);
		}
		else if (!(GetHotMenu() == HOTMENU::NONE)) 
		{
			DrawRotaGraph(LEFT_POS_X - cameraPos.x,
				LEFT_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsHotCup_[0][static_cast<int>(hotMenu_)],
				true);
		}
		break;

	default:
		break;
	}

	switch (iceCup_)
	{
	case ICECUP::NONE:
		if (GetIceMenu() == ICEMENU::NONE)
		{
			if (isIce_ == false)
			{
				DrawRotaGraph(ICECUP_POS_X - cameraPos.x,
					ICECUP_POS_Y - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][0],
					true);
			}
			else
			{
				DrawRotaGraph(ICECUP_POS_X - cameraPos.x,
					ICECUP_POS_Y - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][3],
					true);
			}
		}
		else 
		{
			DrawRotaGraph(ICECUP_POS_X - cameraPos.x,
				ICECUP_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsIceCup_[0][static_cast<int>(iceMenu_) + 3],
				true);
		}
		break;

	case ICECUP::SELECT:
		if (GetIceMenu() == ICEMENU::NONE)
		{
			if (isIce_ == false)
			{
				DrawRotaGraph(ICECUP_POS_X - cameraPos.x,
					ICECUP_POS_Y - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][1],
					true);
			}
			else
			{
				DrawRotaGraph(ICECUP_POS_X - cameraPos.x,
					ICECUP_POS_Y - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][3],
					true);
			}

		}
		else
		{
			DrawRotaGraph(ICECUP_POS_X - cameraPos.x,
				ICECUP_POS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsIceCup_[0][static_cast<int>(iceMenu_) + 3],
				true);
		}
		break;

	case ICECUP::ICEDISPENSER:		
	if (GetIceMenu() == ICEMENU::NONE)
	{
		if (isIce_ == false)
		{
			DrawRotaGraph(1245 - cameraPos.x,
				(679 - SET_POS) - cameraPos.y,
				1.0f, 0.0f,
				imgsIceCup_[0][2],
				true);
		}
		else
		{
			DrawRotaGraph(1245 - cameraPos.x,
				(679 - SET_POS) - cameraPos.y,
				1.0f, 0.0f,
				imgsIceCup_[0][3],
				true);
		}
	}
	else
	{
		DrawRotaGraph(1245 - cameraPos.x,
			(679 - SET_POS) - cameraPos.y,
			1.0f, 0.0f,
			imgsIceCup_[0][static_cast<int>(iceMenu_) + 3],
			true);
	}
		break;

	case ICECUP::SET_ICE:
		if (GetIceMenu() == ICEMENU::NONE)
		{
			if (isIce_ == false)
			{
				DrawRotaGraph(1245 - cameraPos.x,
					679 - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][2],
					true);
			}
			else
			{
				DrawRotaGraph(1245 - cameraPos.x,
					679 - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][3],
					true);
			}

		}
		else
		{
			DrawRotaGraph(1245 - cameraPos.x,
				679 - cameraPos.y,
				1.0f, 0.0f,
				imgsIceCup_[0][static_cast<int>(iceMenu_) + 3],
				true);
		}

		break;

	case ICECUP::MACHINE_CENTER:
		if (GetIceMenu() == ICEMENU::NONE)
		{
			if (isIce_ == false)
			{
				DrawRotaGraph(926 - cameraPos.x,
					(679 - SET_POS) - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][2],
					true);
			}
			else
			{
				DrawRotaGraph(926 - cameraPos.x,
					(679 - SET_POS) - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][3],
					true);
			}
		}
		else
		{
			DrawRotaGraph(926 - cameraPos.x,
				(679 - SET_POS) - cameraPos.y,
				1.0f, 0.0f,
				imgsIceCup_[0][static_cast<int>(iceMenu_) + 3],
				true);
		}

		break;

	case ICECUP::MACHINE_LEFT:
		if (GetIceMenu() == ICEMENU::NONE)
		{
			if (isIce_ == false)
			{
				DrawRotaGraph(851 - cameraPos.x,
					(679 - SET_POS) - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][2],
					true);
			}
			else
			{
				DrawRotaGraph(851 - cameraPos.x,
					(679 - SET_POS) - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][3],
					true);
			}
		}
		else
		{
			DrawRotaGraph(851 - cameraPos.x,
				(679 - SET_POS) - cameraPos.y,
				1.0f, 0.0f,
				imgsIceCup_[0][static_cast<int>(iceMenu_) + 3],
				true);
		}
		break;

	case ICECUP::SET_CENTER:
		if (GetIceMenu() == ICEMENU::NONE)
		{
			if (isIce_ == false)
			{
				DrawRotaGraph(926 - cameraPos.x,
					679 - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][2],
					true);
			}
			else
			{
				DrawRotaGraph(926 - cameraPos.x,
					679 - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][3],
					true);
			}
		}
		else 
		{
			DrawRotaGraph(926 - cameraPos.x,
				679 - cameraPos.y,
				1.0f, 0.0f,
				imgsIceCup_[0][static_cast<int>(iceMenu_) + 3],
				true);
		}

		break;

	case ICECUP::SET_LEFT:
		if (GetIceMenu() == ICEMENU::NONE)
		{
			if (isIce_ == false)
			{
				DrawRotaGraph(851 - cameraPos.x,
					679 - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][2],
					true);
			}
			else
			{
				DrawRotaGraph(851 - cameraPos.x,
					679 - cameraPos.y,
					1.0f, 0.0f,
					imgsIceCup_[0][3],
					true);
			}
		}
		else 
		{
			DrawRotaGraph(851 - cameraPos.x,
				679 - cameraPos.y,
				1.0f, 0.0f,
				imgsIceCup_[0][static_cast<int>(iceMenu_) + 3],
				true);
		}

		break;

	default:
		break;
	}

	switch (pitcher_)
	{
	case PITCHER::NONE:
		DrawRotaGraph(pitcherPos_.x - cameraPos.x,
			pitcherPos_.y - cameraPos.y,
			1.0f, 0.0f,
			imgPitcherSet_,
			true);
		if(!isMilk_)
		{
		DrawRotaGraph(pitcherPos_.x - cameraPos.x,
			pitcherPos_.y - cameraPos.y,
			1.0f, 0.0f,
			imgsPitcher_[0][0],
			true);
		}
		else
		{
			DrawRotaGraph(pitcherPos_.x - cameraPos.x,
				pitcherPos_.y - cameraPos.y,
				1.0f, 0.0f,
				imgsPitcher_[0][3],
				true);
			if (isFormer_)
			{
				DrawRotaGraph(pitcherPos_.x - cameraPos.x,
					pitcherPos_.y - cameraPos.y,
					1.0f, 0.0f,
					imgsPitcher_[0][4],
					true);
			}
		}
		break;

	case PITCHER::SELECT:
		DrawRotaGraph(pitcherPos_.x - cameraPos.x,
			pitcherPos_.y - cameraPos.y,
			1.0f, 0.0f,
			imgPitcherSet_,
			true);
		if(!isMilk_)
		{
		DrawRotaGraph(pitcherPos_.x - cameraPos.x,
			pitcherPos_.y - cameraPos.y,
			1.0f, 0.0f,
			imgsPitcher_[0][1],
			true);
		}
		else
		{
			DrawRotaGraph(pitcherPos_.x - cameraPos.x,
				pitcherPos_.y - cameraPos.y,
				1.0f, 0.0f,
				imgsPitcher_[0][3],
				true);
			if (isFormer_)
			{
				DrawRotaGraph(pitcherPos_.x - cameraPos.x,
					pitcherPos_.y - cameraPos.y,
					1.0f, 0.0f,
					imgsPitcher_[0][4],
					true);
			}
		}
		break;

	case PITCHER::TAKE:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawRotaGraph(pitcherPos_.x - cameraPos.x,
			pitcherPos_.y - cameraPos.y,
			1.0f, 0.0f,
			imgPitcherSet_,
			true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (!isMilk_)
		{
			DrawRotaGraph(PITCHER_DESKPOS_X - cameraPos.x,
				PITCHER_DESKPOS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgPitcherSet_,
				true);

			DrawRotaGraph(mpos_.x,
				mpos_.y,
				1.0f, 0.0f,
				imgsPitcher_[0][0],
				true);
		}
		else if (isMilk_ && !isFormer_)
		{
			DrawRotaGraph(1040 - cameraPos.x,
				664 - cameraPos.y,
				1.0f, (DX_PI_F / -6.0f),
				imgPitcherSet_,
				true);

			DrawRotaGraph(mpos_.x,
				mpos_.y,
				1.0f, 0.0f,
				imgsPitcher_[0][3],
				true);

		}
		else if (isMilk_ && isFormer_)
		{
			DrawRotaGraph(mpos_.x,
				mpos_.y,
				1.0f, 0.0f,
				imgsPitcher_[0][4],
				true);
		}
		break;

	case PITCHER::SELECT_DESK:
		if (!isMilk_) {

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawRotaGraph(PITCHER_DESKPOS_X - cameraPos.x,
				PITCHER_DESKPOS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgPitcherSet_,
				true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			DrawRotaGraph(PITCHER_DESKPOS_X - cameraPos.x,
				PITCHER_DESKPOS_Y - 10 - cameraPos.y,
				1.0f, 0.0f,
				imgsPitcher_[0][1],
				true);
		}
		else if(isMilk_ && !isFormer_)
		{ 
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawRotaGraph(1040 - cameraPos.x,
				664 - cameraPos.y,
				1.0f, (DX_PI_F / -6.0f),
				imgPitcherSet_,
				true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			DrawRotaGraph(PITCHER_DESKPOS_X - cameraPos.x,
				PITCHER_DESKPOS_Y - 10 - cameraPos.y,
				1.0f, 0.0f,
				imgsPitcher_[0][3],
				true);
		}
		else if (isMilk_ && isFormer_)
		{
			DrawRotaGraph(PITCHER_DESKPOS_X - cameraPos.x,
				PITCHER_DESKPOS_Y - 10 - cameraPos.y,
				1.0f, 0.0f,
				imgsPitcher_[0][4],
				true);
		}
		break;

	case PITCHER::SET_DESK:
		if(!isMilk_)
		{
		DrawRotaGraph(PITCHER_DESKPOS_X - cameraPos.x,
			PITCHER_DESKPOS_Y - cameraPos.y,
			1.0f, 0.0f,
			imgsPitcher_[0][2],
			true);
		}
		else if(isMilk_ && !isFormer_)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawRotaGraph(1040 - cameraPos.x,
				664 - cameraPos.y,
				1.0f, (DX_PI_F / -6.0f),
				imgPitcherSet_,
				true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			DrawRotaGraph(PITCHER_DESKPOS_X - cameraPos.x,
				PITCHER_DESKPOS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsPitcher_[0][3],
				true);
		}
		else if (isMilk_ && isFormer_)
		{
			DrawRotaGraph(PITCHER_DESKPOS_X - cameraPos.x,
				PITCHER_DESKPOS_Y - cameraPos.y,
				1.0f, 0.0f,
				imgsPitcher_[0][4],
				true);
		}
		break;

	case PITCHER::SELECT_M:
		if (isMilk_)
		{
			DrawRotaGraph(1040 - cameraPos.x,
				674 - cameraPos.y,
				1.0f, 0.0f,
				imgsPitcher_[0][3],
				true);
			if (isFormer_)
			{
				DrawRotaGraph(1040 - cameraPos.x,
					674 - cameraPos.y,
					1.0f, 0.0f,
					imgsPitcher_[0][4],
					true);
			}
		}
		break;

	case PITCHER::SET_M:
		if (isMilk_ && !isFormer_)
		{
			DrawRotaGraph(1040 - cameraPos.x,
				664 - cameraPos.y,
				1.0f, (DX_PI_F / -6.0f),
				imgsPitcher_[0][3],
				true);
		}
		else if (isMilk_ && isFormer_)
		{
			DrawRotaGraph(1040 - cameraPos.x,
				664 - cameraPos.y,
				1.0f, (DX_PI_F / -6.0f),
				imgsPitcher_[0][4],
				true);
		}
		break;

	case PITCHER::READY_POUR:
		if (isMilk_ && isFormer_)
		{
			if (mpos_.x > 933 - cameraPos.x)
			{
				DrawRotaGraph(mpos_.x + 15,
					mpos_.y + 15,
					1.0f, (DX_PI_F / -4.5f),
					imgsPitcher_[0][4],
					true);
			}
			else if (mpos_.x < 930 - 3 - cameraPos.x)
			{
				DrawRotaGraph(mpos_.x - 15,
					mpos_.y + 15,
					1.0f, (DX_PI_F / 4.5f),
					imgsPitcher_[0][4],
					true, true);
			}
			else {
				DrawRotaGraph(mpos_.x,
					mpos_.y + 10,
					1.0f, 0.0f,
					imgsPitcher_[0][4],
					true);
			}
		}
		else if (!isMilk_ && !isFormer_)
		{
			if (mpos_.x > 930 + 3 - cameraPos.x)
			{
				DrawRotaGraph(mpos_.x + 15,
					mpos_.y + 15,
					1.0f, (DX_PI_F / -4.5f),
					imgsPitcher_[0][2],
					true);
			}
			else if (mpos_.x < 930 - 3 - cameraPos.x)
			{
				DrawRotaGraph(mpos_.x - 15,
					mpos_.y + 15,
					1.0f, (DX_PI_F / 4.5f),
					imgsPitcher_[0][2],
					true, true);
			}
			else {
				DrawRotaGraph(mpos_.x,
					mpos_.y + 10,
					1.0f, 0.0f,
					imgsPitcher_[0][2],
					true);
			}
		}
		break;

	case PITCHER::POUR:
		break;
	default:
		break;
	}

	DrawGraph(995 - cameraPos.x, 622 - cameraPos.y, imgMachineMilk_, true);

	switch (milk_)
	{

	case MILK::TAKE:
		DrawRotaGraph(mpos_.x,
			mpos_.y ,
			1.0f, 0.0f,
			imgMilk_,
			true);

		break;

	case MILK::READY_POUR:
		if (mpos_.x > PITCHER_DESKPOS_X + 8 - cameraPos.x)
		{
			DrawRotaGraph(mpos_.x + 15,
				mpos_.y + 15,
				1.0f, (DX_PI_F / -4.5f),
				imgMilk_,
				true);
		}
		else if (mpos_.x < PITCHER_DESKPOS_X - 8 - cameraPos.x)
		{
			DrawRotaGraph(mpos_.x - 15,
				mpos_.y + 15,
				1.0f, (DX_PI_F / 4.5f),
				imgMilk_,
				true);
		}
		else {
			DrawRotaGraph(mpos_.x,
				mpos_.y + 10,
				1.0f, 0.0f,
				imgMilk_,
				true);
		}
		break;

	case MILK::POUR:
		break;

	default:
		break;
	}

	// 提供するBox(右下)
	DrawBox(600/*1400 - cameraPos.x*/,
		310  /*810 - cameraPos.y*/,
		790 /*1590 - cameraPos.x*/,
		450 /*950 - cameraPos.y*/, 0x000000, true);

	if (GetIceCup() == ICECUP::TAKE)
	{
		if (GetIceMenu() == ICEMENU::NONE)
		{
			if (isIce_ == false)
			{
				DrawRotaGraph(mpos_.x,
					mpos_.y,
					1.0f, 0.0f,
					imgsIceCup_[0][2],
					true);
			}
			else
			{
				DrawRotaGraph(mpos_.x,
					mpos_.y,
					1.0f, 0.0f,
					imgsIceCup_[0][3],
					true);
			}
		}
		else
		{
			DrawRotaGraph(mpos_.x,
				mpos_.y,
				1.0f, 0.0f,
				imgsIceCup_[0][static_cast<int>(iceMenu_) + 3],
				true);
		}

	}

	if (GetHotCup() == HOTCUP::TAKE)
	{
		if (GetHotMenu() == HOTMENU::NONE)
		{
			DrawRotaGraph(mpos_.x,
				mpos_.y,
				1.0f, 0.0f,
				imgsHotCup_[0][0],
				true);
		}
		else if (!(GetHotMenu() == HOTMENU::NONE)) {
			DrawRotaGraph(mpos_.x,
				mpos_.y,
				1.0f, 0.0f,
				imgsHotCup_[0][static_cast<int>(hotMenu_)],
				true);
		}
	}

	if (GetHotCup() == HOTCUP::FINISH)
	{	
		if (GetHotMenu() == HOTMENU::ESPRESSO)
		{
			DrawRotaGraph(695/*926 - cameraPos.x*/,
				380/*679 - cameraPos.y*/,
				1.0f, 0.0f,
				imgEspresso_,
				true);
		}
		else if (GetHotMenu() == HOTMENU::AMERICANO)
		{
			DrawRotaGraph(695/*926 - cameraPos.x*/,
				380/*679 - cameraPos.y*/,
				1.0f, 0.0f,
				imgAmericano_,
				true);
		}
		else
		{
			DrawRotaGraph(695/*926 - cameraPos.x*/,
				380/*679 - cameraPos.y*/,
				1.0f, 0.0f,
				imgLatte_,
				true);
		}
	}

	if (GetIceCup() == ICECUP::FINISH)
	{
		if (GetIceMenu() == ICEMENU::ESPRESSO)
		{
			DrawRotaGraph(695/*926 - cameraPos.x*/,
				380/*679 - cameraPos.y*/,
				1.0f, 0.0f,
				imgIce_Espresso_,
				true);
		}
		else if (GetIceMenu() == ICEMENU::AMERICANO)
		{
			DrawRotaGraph(695/*926 - cameraPos.x*/,
				380/*679 - cameraPos.y*/,
				1.0f, 0.0f,
				imgIce_Americano_,
				true);
		}
		else
		{
			DrawRotaGraph(695/*926 - cameraPos.x*/,
				380/*679 - cameraPos.y*/,
				1.0f, 0.0f,
				imgIce_Latte_,
				true);
		}
	}

	if (isPoint_ == true)
	{
		DrawRotaGraph((pointPos_.x + pointMove_.x) - cameraPos.x,
			(pointPos_.y + pointMove_.y) - cameraPos.y,
			1.0f, 0.0f,
			imgsPoint_[0][static_cast<int>(dir_)],
			true);
	}

	int animNum = static_cast<int>(
		static_cast<float>(cntAnim_) * speedAnim_)
		% PUSHKEY_MAX_NUM;

	if (isPushKey_ == true)
	{
		DrawRotaGraph(pushPos_.x - cameraPos.x,
			pushPos_.y - cameraPos.y,
			1.0f, 0.0f,
			imgsPushKey_[pushKey_][animNum],
			true);
	}
}

void Player::DrawDrink(void)
{

}

void Player::DrawTalk2(void)
{

}

bool Player::Release(void)
{

	for (int x = 0; x < 3; x++)
	{
		DeleteGraph(imgsButton_[0][x]);
	}

	DeleteGraph(imgPitcherSet_);
	DeleteGraph(imgMachineMilk_);
	DeleteGraph(imgMilk_);
	
	for (int x = 0; x < PITCHER_NUM; x++)
	{
		DeleteGraph(imgsPitcher_[0][x]);
	}	
	
	for (int x = 0; x < MILK_NUM; x++)
	{
		DeleteGraph(imgsReizou_[0][x]);
	}

	// grinder画像の解放
	for (int x = 0; x < GRINDER_NUM; x++)
		{
			DeleteGraph(imgsgrinder_[0][x]);
		}

	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < TAMPER_NUM; x++)
		{
			DeleteGraph(imgstamper_[y][x]);
		}
	}

	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < FILTER_NUM; x++)
		{
			DeleteGraph(imgsfilter_[y][x]);
		}
	}

	DeleteGraph(imgfiltermat_);
	DeleteGraph(messagecursorImage_);
	DeleteGraph(cursorImage_);

	DeleteSoundMem(filterTakeSound_);
	DeleteSoundMem(filterSetOutSound_);
	DeleteSoundMem(filterSetSound_);
	DeleteSoundMem(filterSetMatSound_);
	DeleteSoundMem(grinderButton_);
	DeleteSoundMem(CupTakeSound_);
	DeleteSoundMem(CupSetSound_);
	DeleteSoundMem(tamperPullupSound_);

	return false;
}

void Player::SetPointPos(Vector2 pos, AsoUtility::DIR dir)
{
	pointPos_ = pos;
	dir_ = dir;
}

// 矢印を動かす量
void Player:: MovePoint(void)
{
	int maxY = 10;
	int minY = -10;

	int maxX = 10;
	int minX = -10;

	if (dir_ == AsoUtility::DIR::DOWN ||
		dir_ == AsoUtility::DIR::UP)
	{
		if (pointMove_.y > maxY || pointMove_.y < minY)
		{
			pointDirection_ *= -1;	//方向反転
		}
		pointMove_.x = 0;
		pointMove_.y += pointDirection_;
	}
	else if (dir_ == AsoUtility::DIR::RIGHT ||
		dir_ == AsoUtility::DIR::LEFT)
	{
		if (pointMove_.x > maxX || pointMove_.x < minX)
		{
			pointDirection_ *= -1;	//方向反転
		}
		pointMove_.x += pointDirection_;
		pointMove_.y = 0;
	}
}

bool Player::LoadSounds(void)
{

	// filter用
	filterTakeSound_ = LoadSoundMem("Data/Sound/take filter.mp3");
	filterSetMatSound_ = LoadSoundMem("Data/Sound/filter set mat.mp3");
	filterSetSound_ = LoadSoundMem("Data/Sound/filter set.mp3");
	filterSetOutSound_ = LoadSoundMem("Data/Sound/filter set out.mp3");
	beansDustSound_ = LoadSoundMem("Data/Sound/nockbox.mp3");

	// tamper用
	tamperPullupSound_ = LoadSoundMem("Data/Sound/tamper pullup.mp3");
	tamperSetSound_ = LoadSoundMem("Data/Sound/tamper set.mp3");

	// cup用
	CupTakeSound_ = LoadSoundMem("Data/Sound/take cup.mp3");
	CupSetSound_ = LoadSoundMem("Data/Sound/cup set.mp3");
	CupIceInSound_ = LoadSoundMem("Data/Sound/ice in.mp3");
	CupPourHotSound_ = LoadSoundMem("Data/Sound/pour coffee.mp3");
	CupPourIceSound_ = LoadSoundMem("Data/Sound/pour ice coffee.mp3");

	// grinder用
	grinderButton_ = LoadSoundMem("Data/Sound/button.mp3");

	// milk用
	pourMilkSound_ = LoadSoundMem("Data/Sound/pour milk.mp3");
					
	// pitcher用	
	pitcherSound_ = LoadSoundMem("Data/Sound/pitcher.mp3");
	setPitcherSound_ = LoadSoundMem("Data/Sound/set pitcher.mp3");
					 
	// 冷蔵庫用		
	reizouOpenSound_ = LoadSoundMem("Data/Sound/open reizou.mp3");
	reizouCloseSound_ = LoadSoundMem("Data/Sound/close reizou.mp3");

	return true;
}

// 読み込んだ音を再生する
void Player::PlaySounds(int SoundName, int Vol)
{
	soundMem_ = SoundName;
	// 音が再生中でなければ再生開始
	if (!isPlaySound_)
	{
		ChangeVolumeSoundMem(Vol, soundMem_);
		PlaySoundMem(soundMem_, DX_PLAYTYPE_BACK);
		isPlaySound_ = true;
	}// 再生が終わったか確認する
}

void Player::CheckSounds(void)
{	
	// 再生が終わったか確認する
	if (isPlaySound_ && CheckSoundMem(soundMem_) == 0)
	{
		isPlaySound_ = false; // 再生が終わった
	}
}

void Player::BeansState(bool In, bool Stamp, bool Brew, bool Dust)
{
	beansIn_ = In;
	beansStamp_ = Stamp;
	beansBrew_ = Brew;
	beansDust_ = Dust;
}

void Player::DustBeans(void)
{
	pushKey_ = 0;

	//return Reset();
	beansIn_ = false;
	beansStamp_ = false;
	beansBrew_ = false;
	pushCnt_ = 3;
	color_ = 0xFF0000;
}

// プレイヤーが手にアイテムを持っているか(true:持っている)
bool Player::IsHolding(void)
{
	if (
		!(GetFilter() == FILTER::TAKE) &&
		!(GetTamper() == TAMPER::TAKE) &&
		!(GetHotCup() == HOTCUP::TAKE) &&
		!(GetIceCup() == ICECUP::TAKE) &&
		!(GetPitcher() == PITCHER::TAKE)&&
		!(GetMilk() == MILK::TAKE )		&&
		!( GetMilk() == MILK::READY_POUR)&&
		!(GetPitcher() == PITCHER::READY_POUR)
		)
	{
		// 何も持っていない時はfalse
		return false;
	}

	// 持っている
	return true;
}

// マシン中央に何かセットされているか
bool Player::IsSetMachineCenter(void)
{
	// 中央に何かセットされているか
	if (
		!(GetHotCup() == HOTCUP::SET_CENTER) &&
		!(GetIceCup() == ICECUP::SET_CENTER)
		)
	{
		// 何もセットされていない時はfalse
		return false;
	}

	// セットされている
	return true;
}

// マシン左側に何かセットされているか
bool Player::IsSetMachineLeft(void)
{
	// 中央に何かセットされているか
	if (
		!(GetHotCup() == HOTCUP::SET_LEFT) &&
		!(GetIceCup() == ICECUP::SET_LEFT)
		)
	{
		// 何もセットされていない時はfalse
		return false;
	}

	// 持っている
	return true;
}

void Player::MoveCaution(void)
{
	if (flyPos_ > 45 || flyPos_ < 30)
	{
		direction *= -1;	//方向反転
	}

	flyPos_ += direction;
}

// 押し出し処理関連の関数--------------------------------------------
int Player::SignVal(float value)
{
	return value < 0.0f ? -1 : 1;
}

bool Player::IsHit(const Rect& rcA, const Rect& rcB)
{
	// 当たらない条件
	auto diffx = rcA.pos.x - rcB.pos.x;	// 終点から始点を引く
	auto diffy = rcA.pos.y - rcB.pos.y;	// 終点から始点を引く
	if (fabsf(diffx) > rcA.size.w / 2 + rcB.size.w / 2 ||
		fabsf(diffy) > rcA.size.h / 2 + rcB.size.h / 2) {
		return false;
	}
	else 
	{
		return true;
	}
}