#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle(void)
{
	bgm_ = -1;
	buttonSelectSound_ = -1;
	buttonPushSound_ = -1;

	titleImage_ = -1;
	backImage_ = -1;

	crownImage_ = -1;

	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < FACE_ANIM_NUM; x++)
		{
			faceImgs_[y][x] = -1;
		}
	}
	bodyImage_ = -1;

	selectImage_ = -1;
	select_onImage_ = -1;
	start_onImage_ = -1;
	start_offImage_ = -1;
	story_onImage_ = -1;
	story_offImage_ = -1;

	cursorImage_ = -1;

	isSelect_ = false;
	wasSelect_ = false;

	pos_ = { 0,0 };

	mpos_ = { 0,0 };

	crownPos_ = { 0,0 };
	crownMove_ = { 0,0 };
	facePos_ = { 0,0 };
	faceMove_ = { 0,0 };

	animNum_ = -1;
	blink_ = -1;

	blinkNum_ = BLINK::NONE;
	blinkPersent_ = -1;
	isBlink_ = false;

	crownDirection = -1;
	faceDirection = -1;

	select_ =SELECT::MAX;

	button_ = BUTTON::OFF;

	cntAnim_ = -1;
	cntMove_ = -1;
	moveDelay_ = - 1.0f;
	speedAnim_ = -1.0f;

	startTime = -1;
	elapsedTime = -1;
}

// デストラクタ
SceneTitle::~SceneTitle(void)
{

}


// 初期化処理
bool SceneTitle::Init(void)
{
	bgm_ = LoadSoundMem("Data/Title.mp3");
	buttonSelectSound_ = LoadSoundMem("Data/Sound//Title_button.mp3");
	buttonPushSound_ = LoadSoundMem("Data/Sound//Title_button_push.mp3");
	// 読みこんだ音を再生
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(180, bgm_);
	ChangeVolumeSoundMem(230, buttonSelectSound_);
	ChangeVolumeSoundMem(180, buttonPushSound_);

	// 顔の画像
	int ret;
	ret = LoadDivGraph(
		"Data/GameOver/wink.png",
		FACE_ANIM_NUM,
		FACE_ANIM_NUM,
		1,
		FACE_SIZE_WIDTH,
		FACE_SIZE_HEIGHT,
		&(faceImgs_[0][0])
	);
	if (ret == -1)
	{
		OutputDebugString("wink.png画像が見つからない");
		return false;
	}

	titleImage_ = LoadGraph("Data/Title/test.png");
	if (titleImage_ == -1)
	{
		OutputDebugString("Title.png画像が見つからない");
		return false;
	}

	backImage_ = LoadGraph("Data/Title/back.png");
	if (backImage_ == -1)
	{
		OutputDebugString("back.png画像が見つからない");
		return false;
	}

	selectImage_ = LoadGraph("Data/Title/select.png");
	if (selectImage_ == -1)
	{
		OutputDebugString("select.png画像が見つからない");
		return false;
	}		
	
	select_onImage_ = LoadGraph("Data/Title/select_on.png");
	if (select_onImage_ == -1)
	{
		OutputDebugString("select_on.png画像が見つからない");
		return false;
	}	
	
	start_onImage_ = LoadGraph("Data/Title/Start_on.png");
	if (start_onImage_ == -1)
	{
		OutputDebugString("Start_on.png画像が見つからない");
		return false;
	}

	start_offImage_ = LoadGraph("Data/Title/Start_off.png");
	if (start_offImage_ == -1)
	{
		OutputDebugString("Start_off.png画像が見つからない");
		return false;
	}	
	
	story_onImage_ = LoadGraph("Data/Title/Story_on.png");
	if (story_onImage_ == -1)
	{
		OutputDebugString("Story_on.png画像が見つからない");
		return false;
	}

	story_offImage_ = LoadGraph("Data/Title/Story_off.png");
	if (story_offImage_ == -1)
	{
		OutputDebugString("Story_off.png画像が見つからない");
		return false;
	}

	crownImage_ = LoadGraph("Data/Title/crown.png");
	if (crownImage_ == -1)
	{
		OutputDebugString("Image.png画像が見つからない");
		return false;
	}

	bodyImage_ = LoadGraph("Data/Title/body.png");
	if (bodyImage_ == -1)
	{
		OutputDebugString("Image.png画像が見つからない");
		return false;
	}

	cursorImage_ = LoadGraph("Data/cursor.png");	
	if (cursorImage_ == -1)
	{
		OutputDebugString("cursor.png画像が見つからない");
		return false;
	}

	SetBackgroundColor(245, 222, 179);

	isSelect_ = false;

	pos_ = { 500,250 };
	mpos_ = { 0,0 };
	select_ = SELECT::START;
	button_ = BUTTON::OFF;
	speedAnim_ = 0.2f;
	cntMove_ = 0;
	moveDelay_ = 0.7f;

	crownPos_ = { TITLE_SIZE_WIDTH / 2,TITLE_SIZE_HEIGHT / 2 - 5 };
	crownMove_ = { 0,0 };
	facePos_ = { 166,TITLE_SIZE_HEIGHT / 2 };
	faceMove_ = { 0,0 };

	animNum_ = 0;
	blink_ = 0;
	blinkPersent_ = 0;

	blinkNum_ = BLINK::NONE;

	isBlink_ = false;

	crownDirection = 1;
	faceDirection =  1;

	startTime = 0;
	elapsedTime = 0;

	return true;
}

// 更新処理
void SceneTitle::Update(void)
{
	auto& ins = InputManager::GetInstance();

	SetMouseDispFlag(false);

	ins.GetMouse();
	mpos_ = ins.GetMousePos();

	cntMove_++;

	// 瞬き処理
	Blink();
	// 王冠移動処理
	MoveCrown();
	// 顔移動処理
	MoveFace();

	//ボタン押下での選択処理
	if (ins.IsTrgDown(KEY_INPUT_DOWN)
		|| ins.IsTrgDown(KEY_INPUT_S))
	{
		pos_.y = STORY_BUTTON_Y;
		select_ = SELECT::SECRET;
		button_ = BUTTON::OFF;
		PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
	}
	else if (ins.IsTrgDown(KEY_INPUT_UP)
		|| ins.IsTrgDown(KEY_INPUT_W))
	{
		pos_.y = START_POS_Y;
		select_ = SELECT::START;
		button_ = BUTTON::OFF;
		PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
	}

	//ボタンとマウスカーソルの矩形の当たり判定
	if ((mpos_.x >= BUTTON_POS_X && mpos_.x <= BUTTON_POS_X + SIZE_WIDTH) &&
		(mpos_.y >= START_POS_Y && mpos_.y <= START_POS_Y + SIZE_HEIGHT)
		)
	{
		isSelect_ = true;
		select_ = SELECT::START;
		pos_.y = START_POS_Y;
		if (!wasSelect_)
		{
			PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
		}
		if (ins.IsTrgMouseLeft() == true)
		{
			button_ = BUTTON::ON;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::OPENING,
				true
			);
		}
	}
	else if ((mpos_.x >= BUTTON_POS_X && mpos_.x <= BUTTON_POS_X + SIZE_WIDTH) &&
		(mpos_.y >= STORY_BUTTON_Y && mpos_.y <= STORY_BUTTON_Y + SIZE_HEIGHT))
	{
		isSelect_ = true;
		select_ = SELECT::SECRET;
		pos_.y = STORY_BUTTON_Y;
		if (!wasSelect_)
		{
			PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
		}
		if (ins.IsTrgMouseLeft() == true)
		{
			button_ = BUTTON::ON;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);

			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::STORY,
				true
			);
		}
	}
	else
	{
		isSelect_ = false;
	}

	if (select_ == SELECT::START)
	{
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			button_ = BUTTON::ON;
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::OPENING,
				true
			);
		}
	}
	else
	{
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			button_ = BUTTON::ON;
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::STORY,
				true
			);
		}
	}

	// 最後に「今回の状態を保存」
	wasSelect_ = isSelect_;
}

// 描画処理
void SceneTitle::Draw(void)
{
	DrawGraph(0, 0, backImage_, true);	// 背景

	DrawGraph(pos_.x, pos_.y, selectImage_, true);	// startのoffボタン


	// startボタン
	if (select_ == SELECT::START)
	{
		DrawGraph(BUTTON_POS_X, START_POS_Y, start_offImage_, true);	// startのoffボタン
		if (button_ == BUTTON::ON)
		{
			DrawGraph(BUTTON_POS_X, START_POS_Y, start_onImage_, true);	// startのonボタン
			DrawGraph(pos_.x, pos_.y, select_onImage_, true);	// startのoffボタン
		}

		DrawGraph(BUTTON_POS_X, STORY_BUTTON_Y, story_offImage_, true);

	}
	else if(select_ == SELECT::SECRET)
	{
		DrawGraph(BUTTON_POS_X, START_POS_Y, start_offImage_, true);	// startはoff
		DrawGraph(BUTTON_POS_X, STORY_BUTTON_Y, story_offImage_, true);

		if (button_ == BUTTON::ON)
		{
			DrawGraph(BUTTON_POS_X, STORY_BUTTON_Y, story_onImage_, true);
			DrawGraph(pos_.x, pos_.y, select_onImage_, true);	// startのoffボタン
		}
	}

	int animNum = static_cast<int>(
		static_cast<float>(cntMove_) * speedAnim_)
		% FACE_ANIM_NUM;

	// 画像の左上ではなく中心座標
	DrawRotaGraph(
		facePos_.x,
		facePos_.y + faceMove_.y,
		1.0f,		// 拡大
		0.0f,		// 回転
		faceImgs_[0][animNum_],
		true,
		false);

	DrawRotaGraph(
		TITLE_SIZE_WIDTH / 2,
		TITLE_SIZE_HEIGHT / 2,
		1.0f,		// 拡大
		0.0f,		// 回転
		bodyImage_,
		true,
		false);

	DrawRotaGraph(
		crownPos_.x,
		crownPos_.y + crownMove_.y,
		1.0f,		// 拡大
		0.0f,		// 回転
		crownImage_,
		true,
		false);

	DrawRotaGraph(
		TITLE_IMAGE_X,
		TITLE_IMAGE_Y,
		1.0f,		// 拡大
		0.0f,		// 回転
		titleImage_,
		true,
		false);

	DrawGraph(mpos_.x, mpos_.y, cursorImage_, true);

}

// 解放処理
bool SceneTitle::Release(void)
{
	DeleteGraph(crownImage_);
	DeleteGraph(bodyImage_);

	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < FACE_ANIM_NUM; x++)
		{
			DeleteGraph(faceImgs_[y][x]);
		}
	}

	//画像削除
	DeleteGraph(story_offImage_);
	DeleteGraph(story_onImage_);
	DeleteGraph(start_offImage_);
	DeleteGraph(start_onImage_);
	DeleteGraph(select_onImage_);
	DeleteGraph(selectImage_);
	DeleteGraph(cursorImage_);
	DeleteGraph(backImage_);
	DeleteGraph(titleImage_);

	// サウンドハンドルの削除
	DeleteSoundMem(bgm_);
	DeleteSoundMem(buttonSelectSound_);
	DeleteSoundMem(buttonPushSound_);

	return true;
}

void SceneTitle::MoveCrown(void)
{
	int maxY = 0;
	int minY = -5;
	int animSpeed = 3;

	int animNum = static_cast<int>(
		static_cast<float>(cntMove_) * moveDelay_)
		% animSpeed;

	if (animNum == 0)
	{
		crownMove_.y += crownDirection;
	}

	if (crownMove_.y > maxY || crownMove_.y < minY)
	{
		crownDirection *= -1;	//方向反転
	}
}

void SceneTitle::MoveFace(void)
{
	int maxY = 0;
	int minY = -2;
	int animSpeed = 9;

	int animNum = static_cast<int>(
		static_cast<float>(cntMove_) * moveDelay_)
		% animSpeed;

	if (animNum == 0)
	{
		faceMove_.y += faceDirection;
	}

	if (faceMove_.y > maxY || faceMove_.y < minY)
	{
		faceDirection *= -1;	//方向反転
	}
}

void SceneTitle::Blink(void)
{
	int time = GetTime();
	int timePersent = 5;
	int animSpeed = 7;
	int maxRandNum = 100;

	if ((time / 1000) % timePersent == 0)
	{
		//ウィンクしていないときランダムでウィンクするように
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

// 経過時間を返す
int SceneTitle::GetTime(void)
{
	elapsedTime = (GetNowCount() - startTime);

	return elapsedTime;
}