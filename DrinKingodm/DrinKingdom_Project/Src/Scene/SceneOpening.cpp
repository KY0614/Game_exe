#include <DxLib.h>
#include "../Application.h"
#include "../Common/Fader.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "SceneOpening.h"

// デフォルトコンストラクタ
SceneOpening::SceneOpening(void)
{
	operateImg_ = -1;

	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < MAX_ANIM_NUM; x++)
		{
			imgsSpace_[y][x] = -1;
		}
	}
	
	bgm_ = -1;

	cntAnim_ = -1;
	speedAnim_ = -1.0f;

	startTime = -1;
	elapsedTime = -1;
}

// デストラクタ
SceneOpening::~SceneOpening(void)
{

}


// 初期化処理
bool SceneOpening::Init(void)
{
	bgm_ = LoadSoundMem("Data/Opening.mp3");
	// 読みこんだ音を再生
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(180, bgm_);

	operateImg_ = LoadGraph("Data/Opening/sousa.png");
	if (operateImg_ == -1)
	{
		OutputDebugString("sousa.png画像が見つからない");
		return false;
	}

	// スペースキー押下画像の読み込み
	int ret;
	ret = LoadDivGraph(
		"Data/Push Space.png",
		1 * MAX_ANIM_NUM,
		MAX_ANIM_NUM,
		MAX_ANIM_NUM,
		SPACE_SIZE_WIDTH,
		SPACE_SIZE_HEIGHT,
		&(imgsSpace_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("Push Space.png画像が見つからない");
		return false;
	}

	startTime = GetNowCount();
	cntAnim_ = 0;
	speedAnim_ = 0.05f;
	elapsedTime = 0;

	return true;
}

// 更新処理
void SceneOpening::Update(void)
{
	elapsedTime = (GetNowCount() - startTime);

	cntAnim_++;

	if (elapsedTime > WAIT_INTERVAL)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::GAME,
				true
			);
		}
	}
}

// 描画処理
void SceneOpening::Draw(void)
{
	DrawGraph(0, 0, operateImg_, true);

	int animNum = static_cast<int>(
		static_cast<float>(cntAnim_) * speedAnim_)
		% MAX_ANIM_NUM;

	if (elapsedTime > WAIT_INTERVAL)
	{
		DrawRotaGraph(SPACE_IMAGE_POS_X,
			SPACE_IMAGE_POS_Y,
			1.0f, 0.0f,
			imgsSpace_[0][animNum],
			true);
	}
}

// 解放処理
bool SceneOpening::Release(void)
{

	DeleteGraph(operateImg_);
	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < MAX_ANIM_NUM; x++)
		{
			DeleteGraph(imgsSpace_[y][x]);
		}
	}

	// サウンドハンドルの削除
	DeleteSoundMem(bgm_);

	return true;
}
