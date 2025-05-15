#include <chrono>
#include <DxLib.h>
#include "../Common/Fader.h"
#include "InputManager.h"
#include "../Scene/SceneTitle.h"
#include "../Scene/SceneStory.h"
#include "../Scene/SceneOpening.h"
#include "../Scene/SceneGame.h"
#include "../Scene/SceneGameOver.h"
#include "SceneManager.h"

// シングルトン化
// ----------------
// instance_の初期化
SceneManager* SceneManager::instance_ = nullptr;

// デフォルトコンストラクタ
SceneManager::SceneManager(void)
{
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::NONE;

	isSceneChanging_ = false;

	fader_ = nullptr;
	camera_ = nullptr;
	scene_ = nullptr;

}

// デストラクタ
SceneManager::~SceneManager(void)
{

}


// 初期化処理
bool SceneManager::Init(void)
{
	// フェード
	fader_ = new Fader();
	fader_->Init();

	// シーンの生成処理
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::TITLE;
	DoChangeScene();
	
	// タイトルをフェードインで表示する
	fader_->SetFade(Fader::STATE::FADE_IN);
	isSceneChanging_ = true;

	// インスタンスを生成する
	// ---------------------------

	//SetBackgroundColor(0, 130, 130);

	return true;
}

// 更新処理
void SceneManager::Update(void)
{
	if (scene_ == nullptr)
	{
		return;
	}

	// フェード処理※フェードが行われていない場合処理はなにもされない
	fader_->Update();
	
	if (isSceneChanging_ == true)
	{
		// フェード中
		Fade();
	}
	else	// フェード終了
	{
		// 各シーンの更新処理
		scene_->Update();
	}

}

// 描画処理
void SceneManager::Draw(void)
{
	scene_->Draw();

	// フェード
	fader_->Draw();
}

// 解放処理
bool SceneManager::Release(void)
{
	//  /シーンの解放処理
	ReleaseScene(sceneID_);

	// フェードの解放
	delete fader_;
	fader_ = new Fader();

	// シングルトン化
	// -------------------
	Destory();

	return true;
}

// シーン切り替えを依頼する関数
void SceneManager::ChangeScene(SCENE_ID nextID,bool isToFade)
{
	// フェード処理が終了後にシーンを遷移する場合もある為、
	// 遷移先シーンIDをメンバー変数に保持する
	waitSceneID_ = nextID;

	if (isToFade)
	{
		// フェードを実施し、シーン遷移する
		fader_->SetFade(Fader::STATE::FADE_OUT);
		isSceneChanging_ = true;
	}
	else
	{
		// フェードを実施せずにシーン遷移する
		DoChangeScene();
	}
}

// シーンを切り替える
void SceneManager::DoChangeScene(void)
{
	// 現在(sceneID_)のシーンを解放
	ReleaseScene(sceneID_);

	// 次に移動するシーン(waitSceneId_)が入っている
	sceneID_ = waitSceneID_;

	switch (sceneID_)
	{
	case SCENE_ID::TITLE:
		scene_ = new SceneTitle();
		break;

	case SCENE_ID::STORY:
		scene_ = new SceneStory();
		break;

	case SCENE_ID::OPENING:
		scene_ = new SceneOpening();
		break;

	case SCENE_ID::GAME:
		scene_ = new SceneGame();
		break;

	case SCENE_ID::GAMEOVER:
		scene_ = new SceneGameOver();
		break;

	default:
		break;
	}
	scene_->Init();

	// シーンの遷移が終了したので次のシーンをクリアする
	waitSceneID_ = SCENE_ID::NONE;

}

// フェードを実施用関数
void SceneManager::Fade(void)
{
	Fader::STATE fState = fader_->GetState();

	switch (fState)
	{
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd() == true)
		{
			// シーン切り替え
			DoChangeScene();

			// フェードで明るくしていく
			fader_->SetFade(Fader::STATE::FADE_IN);

		}
		break;

	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd() == true)
		{
			// フェードを終了する
			fader_->SetFade(Fader::STATE::NONE);

			// シーン切り替えの終了
			isSceneChanging_ = false;
		}
		break;
	}
}

// 指定したシーンの解放処理
void SceneManager::ReleaseScene(SCENE_ID iSceneID)
{
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
		scene_ = nullptr;
	}
}

// シングルトン化
// -----------------

// インスタンスの生成
// 外部から静的にインスタンスを生成する
void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

// 外部でインスタンスを利用可能とするために
// インスタンスを返す関数を用意する
// 参照型にしているがポインタ型でもよい
SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

// インスタンスの破棄
void SceneManager::Destory(void)
{
	delete instance_;		// インスタンスを削除
	instance_ = nullptr;	// インスタンス格納領域を初期化
}
