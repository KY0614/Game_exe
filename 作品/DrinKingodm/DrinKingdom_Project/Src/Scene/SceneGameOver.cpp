#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "SceneGameOver.h"

SceneGameOver::SceneGameOver(void)
{
	bgm_ = -1;
	buttonSelectSound_ = -1;
	buttonPushSound_ = -1;

	backImage_ = -1;
	thankImage_ = -1;
	playImage_ = -1;

	title_pushImage_ = -1;
	titleImage_ = -1;
	exitImage_ = -1;
	exit_pushImage_ = -1;

	selectImage_ = -1;
	select_onImage_ = -1;

	crownImage_ = -1;
	faceImage_ = -1;

	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < FACEANIM_NUM; x++)
		{
			faceImgs_[y][x] = -1;
		}
	}
	bodyImage_ = -1;
	armImage_ = -1;

	cursorImage_ = -1;

	isTitle_ = false;
	isExit_ = false;

	mpos_ = { 0,0 };

	spos_ = { 0,0 };

	crownPos_ = { 0,0 };
	crownMove_ = { 0,0 };

	facePos_ = { 0,0 };
	faceMove_ = { 0,0 };

	crownDirection = -1;
	faceDirection = -1;
	armDirection = -1;

	cntAnim_ = -1;
	cntMove_ = -1;
	moveDelay_ = -1.0f;
	speedAnim_ = -1.0f;

	moveArm_ = -1.0f;
	armAngle_ = -1.0f;
	moveHand_ = -1.0f;

	animNum_ = -1;
	blink_ = -1;

	blinkNum_ = BLINK::NONE;
	blinkPersent_ = -1;
	isBlink_ = false;

	startTime = -1;
	elapsedTime = -1;

	cnt_ = -1;
}

SceneGameOver::~SceneGameOver(void)
{
}

// èâä˙âªèàóù
bool SceneGameOver::Init(void)
{
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	bgm_ = LoadSoundMem("Data/GameClear.mp3");
	buttonSelectSound_ = LoadSoundMem("Data/Sound//Title_button.mp3");
	buttonPushSound_ = LoadSoundMem("Data/Sound//Title_button_push.mp3");
	// ì«Ç›Ç±ÇÒÇæâπÇçƒê∂
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(BGM_VOLUME, bgm_);
	ChangeVolumeSoundMem(BUTTON_SELECT_VOLUME, buttonSelectSound_);
	ChangeVolumeSoundMem(BUTTON_PUSH_VOLUME, buttonPushSound_);

	backImage_ = LoadGraph("Data/Title/back.png");
	if (backImage_ == -1)
	{
		OutputDebugString("back.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	thankImage_ = LoadGraph("Data/GameOver/Thank You.png");
	if (thankImage_ == -1)
	{
		OutputDebugString("Thank.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	playImage_ = LoadGraph("Data/GameOver/For Playing.png");
	if (playImage_ == -1)
	{
		OutputDebugString("For Playing.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	titleImage_ = LoadGraph("Data/GameOver/Title.png");
	title_pushImage_ = LoadGraph("Data/GameOver/Title_push.png");
	exitImage_ = LoadGraph("Data/GameOver/Exit.png");
	exit_pushImage_ = LoadGraph("Data/GameOver/Exit_push.png");
	if (titleImage_ == -1)
	{
		OutputDebugString("Thank.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}	
	if (title_pushImage_ == -1)
	{
		OutputDebugString("Thank.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}	
	if (exitImage_ == -1)
	{
		OutputDebugString("Thank.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}	
	if (exit_pushImage_ == -1)
	{
		OutputDebugString("Thank.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	crownImage_ = LoadGraph("Data/GameOver/crown.png");
	if (crownImage_ == -1)
	{
		OutputDebugString("Image.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	faceImage_ = LoadGraph("Data/GameOver/face.png");
	if (faceImage_ == -1)
	{
		OutputDebugString("Image.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	armImage_ = LoadGraph("Data/GameOver/arm.png");
	if (armImage_ == -1)
	{
		OutputDebugString("Image.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}	
	
	bodyImage_ = LoadGraph("Data/GameOver/body.png");
	if (bodyImage_ == -1)
	{
		OutputDebugString("Image.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	cursorImage_ = LoadGraph("Data/cursor.png");
	if (cursorImage_ == -1)
	{
		OutputDebugString("cursor.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	selectImage_ = LoadGraph("Data/Title/select.png");
	if (selectImage_ == -1)
	{
		OutputDebugString("select.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	select_onImage_ = LoadGraph("Data/Title/select_on.png");
	if (select_onImage_ == -1)
	{
		OutputDebugString("select_on.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	// äÁÇÃâÊëú
	int ret;
	ret = LoadDivGraph(
		"Data/GameOver/wink.png",
		FACEANIM_NUM,
		FACEANIM_NUM,
		1,
		FACE_SIZE_WIDTH,
		FACE_SIZE_HEIGHT,
		&(faceImgs_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("wink.pngâÊëúÇ™å©Ç¬Ç©ÇÁÇ»Ç¢");
		return false;
	}

	mpos_ = { 0,0 };
	spos_ = { SELECT_POS_X,TITLE_POS_Y };
	cntMove_ = 0;
	moveDelay_ = 0.7f;
	moveArm_ = 0.1f;
	moveHand_ = 0.1f;

	crownPos_ = { Application::SCREEN_SIZE_X - FACE_SIZE_WIDTH / 2,FACE_SIZE_HEIGHT / 2 - 5 };
	crownMove_ = { 0,0 };
	facePos_ = { Application::SCREEN_SIZE_X - FACE_SIZE_WIDTH / 2,FACE_SIZE_HEIGHT / 2 };
	faceMove_ = { 0,0 };

	crownDirection = 1;
	faceDirection = 1;
	armDirection = 1;

	speedAnim_ = 0.2f;

	armAngle_ = 0.0f;

	animNum_ = 0;
	blink_ = 0;
	blinkNum_ = BLINK::NONE;
	blinkPersent_ = 0;
	isBlink_ = false;

	isTitle_ = false;
	isExit_ = false;
	
	return true;
}

// çXêVèàóù
void SceneGameOver::Update(void)
{
	auto& ins = InputManager::GetInstance();

	SetMouseDispFlag(false);

	ins.GetMouse();
	mpos_ = ins.GetMousePos();

	cntMove_++;

	Blink();
	MoveCrown();
	MoveFace();
	MoveArm();

	isTitle_ = false;
	isExit_ = false;

	if (ins.IsTrgDown(KEY_INPUT_DOWN)
		|| ins.IsTrgDown(KEY_INPUT_S))
	{
		spos_.y = EXIT_POS_Y;
		PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
	}
	else if (ins.IsTrgDown(KEY_INPUT_UP)
		|| ins.IsTrgDown(KEY_INPUT_W))
	{
		spos_.y = TITLE_POS_Y;
		PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
	}

	if (spos_.y == EXIT_POS_Y)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			isExit_ = true;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			DxLib_End();
		}
	}
	else
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			isTitle_ = true;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::TITLE,
				true
			);
		}
	}

	if (
		mpos_.x > BUTTON_POS_X &&
		mpos_.x < BUTTON_POS_X + BUTTON_SIZE_WIDTH &&
		mpos_.y > TITLE_POS_Y &&
		mpos_.y < TITLE_POS_Y + BUTTON_SIZE_HEIGHT
		)
	{
		cnt_++;
		spos_.y = TITLE_POS_Y;
		if (ins.IsTrgMouseLeft() == true)
		{
			isTitle_ = true;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::TITLE,
				true
			);
		}
	}
	else if (
		mpos_.x > BUTTON_POS_X &&
		mpos_.x < BUTTON_POS_X + BUTTON_SIZE_WIDTH &&
		mpos_.y > EXIT_POS_Y &&
		mpos_.y < EXIT_POS_Y + BUTTON_SIZE_HEIGHT
		)
	{
		cnt_++;
		spos_.y = EXIT_POS_Y;
		if (ins.IsTrgMouseLeft() == true)
		{
			isExit_ = true;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			DxLib_End();
		}
	}
	else
	{
		cnt_ = 0;
	}

	if (cnt_ == 1)
	{
		PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
	}
}

// ï`âÊèàóù
void SceneGameOver::Draw(void)
{
	auto& ins = InputManager::GetInstance();

	DrawGraph(0, 0, backImage_, true);	// îwåi

	DrawGraph(45, 50, thankImage_, true);	// îwåi

	DrawGraph(50, 150, playImage_, true);	// îwåi

	int animNum = static_cast<int>(
		static_cast<float>(cntMove_) * speedAnim_)
		% FACEANIM_NUM;

	// âÊëúÇÃç∂è„Ç≈ÇÕÇ»Ç≠íÜêSç¿ïW
	DrawRotaGraph(
		facePos_.x,
		facePos_.y + faceMove_.y,
		1.0f,		// ägëÂ
		0.0f,		// âÒì]
		faceImgs_[0][animNum_],
		true,
		false);

	DrawRotaGraph(
		Application::SCREEN_SIZE_X - FACE_SIZE_WIDTH / 2,
		FACE_SIZE_HEIGHT / 2,
		1.0f,		// ägëÂ
		0.0f,		// âÒì]
		bodyImage_,
		true,
		false);

	DrawRotaGraph2(
		Application::SCREEN_SIZE_X - FACE_SIZE_WIDTH / 2 - SELECT_POS_X,
		FACE_SIZE_HEIGHT + 30,
		145,
		FACE_SIZE_HEIGHT,
		1.0f,		// ägëÂ
		armAngle_,		// âÒì]
		armImage_,
		true,
		false);	

	DrawRotaGraph(
		crownPos_.x,
		crownPos_.y + crownMove_.y,
		1.0f,		// ägëÂ
		0.0f,		// âÒì]
		crownImage_,
		true,
		false);

	DrawGraph(spos_.x, spos_.y, selectImage_, true);

	if (isTitle_ == false)
	{
		DrawGraph(BUTTON_POS_X, TITLE_POS_Y, titleImage_, true);	// É^ÉCÉgÉãÇ÷
	}
	else
	{
		DrawGraph(BUTTON_POS_X, TITLE_POS_Y, title_pushImage_, true);	// É^ÉCÉgÉãÇ÷
		DrawGraph(SELECT_POS_X, TITLE_POS_Y, select_onImage_, true);
	}

	if (isExit_ == false)
	{
		DrawGraph(BUTTON_POS_X, EXIT_POS_Y, exitImage_, true);
	}
	else
	{
		DrawGraph(BUTTON_POS_X, EXIT_POS_Y, exit_pushImage_, true);
		DrawGraph(SELECT_POS_X, EXIT_POS_Y, select_onImage_, true);
	}
	
	DrawGraph(mpos_.x, mpos_.y, cursorImage_, true);
}

// âï˙èàóù
bool SceneGameOver::Release(void)
{
	DeleteGraph(crownImage_);
	DeleteGraph(armImage_);

	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < FACEANIM_NUM; x++)
		{
			DeleteGraph(faceImgs_[y][x]);
		}
	}

	DeleteGraph(bodyImage_);
	DeleteGraph(faceImage_);
	DeleteGraph(cursorImage_);
	DeleteGraph(exit_pushImage_);
	DeleteGraph(exitImage_);
	DeleteGraph(title_pushImage_);
	DeleteGraph(titleImage_);
	DeleteGraph(playImage_);
	DeleteGraph(thankImage_);
	DeleteGraph(backImage_);


	// ÉTÉEÉìÉhÉnÉìÉhÉãÇÃçÌèú
	DeleteSoundMem(bgm_);

	return true;
}

void SceneGameOver::MoveCrown(void)
{
	int maxY = 0;
	int minY = -5;
	int animSpeed = 3;

	int animNum = static_cast<int>(
		static_cast<float>(cntMove_) * moveDelay_)
		% animSpeed;

	//è„â∫Ç≥ÇπÇÈ
	if (animNum == 0)
	{
		crownMove_.y += crownDirection;
	}

	if (crownMove_.y > maxY || crownMove_.y < minY)
	{
		crownDirection *= -1;	//ï˚å¸îΩì]
	}
}

void SceneGameOver::MoveFace(void)
{
	int maxY = 0;
	int minY = -2;
	int animSpeed = 9;

	int animNum = static_cast<int>(
		static_cast<float>(cntMove_) * moveDelay_)
		% animSpeed;

	//è„â∫Ç≥ÇπÇÈ
	if (animNum == 0)
	{
		faceMove_.y += faceDirection;
	}

	if (faceMove_.y > maxY || faceMove_.y < minY)
	{
		faceDirection *= -1;	//ï˚å¸îΩì]
	}
}

void SceneGameOver::MoveArm(void)
{
	float max = ARM_ANGLE_MAX;
	float min = ARM_ANGLE_MIN;

	armAngle_ += ARM_ANGLE_SPEED * armDirection;

	if (armAngle_ > max || armAngle_ < min)
	{
		armDirection *= -1;	//ï˚å¸îΩì]
	}
}

void SceneGameOver::Blink(void)
{
	int time = GetTime();
	int timePersent = 5;
	int animSpeed = 7;
	int maxRandNum = 100;

	if ((time / 1000) % timePersent == 0)
	{
		//ÉEÉBÉìÉNÇµÇƒÇ¢Ç»Ç¢Ç∆Ç´ÉâÉìÉ_ÉÄÇ≈ÉEÉBÉìÉNÇ∑ÇÈÇÊÇ§Ç…
		if (!isBlink_)
		{
			blinkPersent_ = GetRand(maxRandNum);
		}
		isBlink_ = true;
	}
	else
	{
		isBlink_ = false;
	}

	if (blinkPersent_ > BLINK_RANDOM_THRESHOLD_NONE)
	{
		blinkNum_ = BLINK::NONE;
	}
	else if (blinkPersent_ > BLINK_RANDOM_THRESHOLD_ONCE)
	{
		blinkNum_ = BLINK::ONCE;
	}
	else
	{
		blinkNum_ = BLINK::TWICE;
	}

	switch (blinkNum_)
	{
	case BLINK::NONE:
		animNum_ = 0;
		blink_ = 0;
		cntAnim_ = 0;
		break;

	case BLINK::ONCE:
		cntAnim_++;

		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% animSpeed;

		if (animNum_ > BLINK_ONCE_ANIM_NUM)
		{
			blinkPersent_ = maxRandNum;
			blinkNum_ = BLINK::NONE;
		}

		break;

	case BLINK::TWICE:
		cntAnim_++;

		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% animSpeed;

		if (animNum_ == 0)
		{
			blink_++;
		}
		if (blink_ > BLINK_TWICE_ANIM_NUM && animNum_ == BLINK_TWICE_IMAGE_NUM)
		{
			blinkPersent_ = maxRandNum;
			blinkNum_ = BLINK::NONE;
		}

		break;

	default:
		break;
	}
}

// åoâﬂéûä‘Çï‘Ç∑
int SceneGameOver::GetTime(void)
{
	elapsedTime = (GetNowCount() - startTime);

	return elapsedTime;
}