#include <DxLib.h>
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"
#include "Application.h"

// フルスクリーンとウィンドウをF11で切り替えれるようにしたい

// シングルトン化
// ----------------
// instance_の初期化
Application* Application::instance_ = nullptr;

// デフォルトコンストラクタ
Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
	screen_ = false;
	currentTime = 0;
	lastFrameTime = 0;
	frameCnt = 0;
	updateFrameRateTime = 0;
	frameRate = 0.0f;
	isDone_ = false;
}

// デストラクタ
Application::~Application(void)
{
}


// 初期化処理
bool Application::Init(void)
{
	// システム処理
	// -------------
	SetWindowText("DrinKingdom");		// ゲームウィンドウのタイトル
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);				// ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);					// ゲームウィンドウの表示方法（false:フルスクリーン)
	isInitFail_ = true;
	if (DxLib_Init() == -1)					// DXライブラリの初期化処理
	{
		OutputDebugString("DXLibの初期化失敗");
		return false;							// DXライブラリの初期化失敗のためシステム終了
	}
	// 乱数の初期値を設定する
	SRand(100);		// 乱数の一定化

	// インスタンスを生成する
	// ---------------------------
	// キー制御初期化
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();

	
	// シーンマネージャ(シングルトン）
	SceneManager::CreateInstance();

	currentTime = 0;
	lastFrameTime = 0;

	frameCnt = 0;

	updateFrameRateTime = 0;

	frameRate = 0.0f;

	isDone_ = false;

	return true;
}

void Application::Update(void)
{

}

// ゲームループ処理
void Application::Run(void)
{
	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

	// ゲームループ
	// ------------------
	while (ProcessMessage() == 0 && (CheckHitKey(KEY_INPUT_ESCAPE) == 0 || isDone_ == false))
	{
		Sleep(1);		// システムに処理を返す

		// 現在の時刻を取得
		currentTime = GetNowCount();

		// 原罪の時刻が、前回のフレーム時より
		// 1/60秒経過していたら処理を実行する
		if (currentTime - lastFrameTime >= FRAME_RATE)
		{
			// フレーム実行時の時間を更新
			lastFrameTime = currentTime;

			// フレームをカウント
			frameCnt++;

			// エスケープが推されたらゲーム終了
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || isDone_ == true)
			{
				return;
			}

			// フレームレート計算
			CalcFrameRate();



			// ゲームのメイン処理
			// ------------------
			Update();
			inputManager.Update();
			sceneManager.Update();

			// 描画処理
			// ------------------
			SetDrawScreen(DX_SCREEN_BACK);		// 描画する画面を裏の画面に設定
			ClearDrawScreen();					// 描画する画面の内容を消去

			sceneManager.Draw();

			ScreenFlip();						// 裏の画面を表の画面に瞬間コピー
		}
	}
}

// 解放処理
bool Application::Release(void)
{
	// 管理マネージャーの解放処理
	// シーン管理用
	SceneManager::GetInstance().Release();

	// シングルトン化
	// ------------------------
	Destory();

	// システム終了処理
	// ----------------------
	DxLib_End();			// DXライブラリの終了処理


	return true;			// ゲームの終了
}	

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}

void Application::Screen(void)
{

}

// シングルトン化
// -----------------

// インスタンスの生成
// 外部から静的にインスタンスを生成する
void Application::CreateInstance(void)
{
	// instance_ が nullptr の場合は、初期化されたのち生成されていないので、生成処理を行う
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}

	instance_->Init();
}

// 外部でインスタンスを利用可能とするために
// インスタンスを返す関数を用意する
// 参照型にしているがポインタ型でもよい
Application& Application::GetInstance(void)
{
	return *instance_;
}

// インスタンスの破棄
void Application::Destory(void)
{
	delete instance_;		// インスタンスを削除
	instance_ = nullptr;	// インスタンス格納領域を初期化
}

void Application::CalcFrameRate(void)
{
	int nDifTime = currentTime - updateFrameRateTime;

	if (nDifTime > 1000)
	{
		float fFrameCnt = (float)(frameCnt * 1000);

		frameRate = fFrameCnt / nDifTime;

		frameCnt = 0;

		updateFrameRateTime = currentTime;
	}
}

void Application::SetIsDone(bool value)
{
	isDone_ = value;
}