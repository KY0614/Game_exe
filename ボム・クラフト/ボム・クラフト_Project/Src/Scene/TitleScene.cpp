#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{
	DeleteSoundMem(bgmHandle_);
}

void TitleScene::Init(void)
{
	
	//サウンド読み込み
	bgmHandle_ = LoadSoundMem("Data/Sound/Bgm/maou_bgm_cyber41.mp3");

	InitSoundEffect();

	//音量調整
	ChangeVolumeSoundMem(255* 30 / 100,bgmHandle_);

	auto& res = ResourceManager::GetInstance();

	backImg_ = res.Load(ResourceManager::SRC::SELECT).handleId_;
	if (backImg_ == -1)
	{
		return;
	}

	//画像読み込み
	img_ = res.Load(ResourceManager::SRC::TITLE).handleId_;
	if (img_ == -1)
	{
		return;
	}
	//画像読み込み
	imgr_ = res.Load(ResourceManager::SRC::TITLER).handleId_;
	if (img_ == -1)
	{
		return;
	}
	imgBlock_ = res.Load(ResourceManager::SRC::BLOCK).handleId_;
	if (img_ == -1)
	{
		return;
	}
	rotate_ = 0.0f;
	loopCount = 0;//カウント
	cr_ = 0xFFFFFF;
	count_ = 0;
	moziFlag = true;//描画フラグ
	//BGMスタート
	PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);

}

void TitleScene::Update(void)
{

	rotate_ += 1 * DX_PI_F / 180;
	if (rotate_ >= 360 * DX_PI_F / 180)
	{
		rotate_ = 0.0;
	}


	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		//BGM停止
		StopSoundMem(bgmHandle_);

 		PlaySoundMem(seDecision_, DX_PLAYTYPE_BACK);

		//SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT);
	}
	if (moziFlag == true)
	{
		loopCount++;
		if (loopCount >= 120)
		{
			loopCount = 0;
			moziFlag = false;
		}
	}
	else if (moziFlag == false)
	{
		loopCount++;
		if (loopCount >= 60)
		{
			loopCount = 0;
			moziFlag = true;
		}
	}
}

void TitleScene::Draw(void)
{
	SetFontSize(16);

	DrawBox(0, 0, Application::SCREEN_SIZE_X/2,
		Application::SCREEN_SIZE_Y, cr_, true);

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f, backImg_, true, false);

	DrawBox(200, Application::SCREEN_SIZE_Y / 2 - 50, Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 + 160, cr_, true);

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f, img_, true, false);
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2-155,
		Application::SCREEN_SIZE_Y / 2+63,
		0.45f, rotate_, imgBlock_, true, false);
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f, imgr_, true, false);
	
	//DrawString(0, 0, "title", cr_);

	int StrLen;
	StrLen = strlen("スペースを押して次へ");
	if (moziFlag == true)
	{
		SetFontSize(64);
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("スペースを押して次へ", StrLen)) / 2, Application::SCREEN_SIZE_Y / 2 + 180, "スペースを押して次へ", cr_);
	}
	SetFontSize(16);

	
}

void TitleScene::InitSoundEffect()
{
	seDecision_ = LoadSoundMem("Data/Sound/SE/se_decision.mp3");
	//音量調整
	ChangeVolumeSoundMem(255 * 30 / 100, seDecision_);
}
