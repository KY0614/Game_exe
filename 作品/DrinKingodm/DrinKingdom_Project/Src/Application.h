#pragma once
#include <string>

class SceneManager;

class Application
{
public:
	// ウィンドウサイズ (横幅)
	static constexpr int SCREEN_SIZE_X = 800;

	// ウィンドウサイズ (縦幅)
	static constexpr int SCREEN_SIZE_Y = 480;

	// フレームレート (60FPSに設定)
	static constexpr float FRAME_RATE = (1000 / 60);
	
	bool Init(void);		// 初期化処理
	void Update(void);		// 更新処理
	void Run(void);			// ゲームループ処理
	bool Release(void);		// 解放処理

	// 初期化成功／失敗の判定
	bool IsInitFail(void) const;

	// 解放成功／失敗の判定
	bool IsReleaseFail(void) const;

	void Screen(void);

	// シングルトン化
	// -------------------

	// インスタンスの生成
	// 外部から静的にインスタンスを生成する
	static void CreateInstance(void);

	// 外部でインスタンスを利用可能とするために
	// インスタンスを返す関数を用意する
	// 参照型にしているがポインタ型でもよい
	static Application& GetInstance(void);

	void SetIsDone(bool value);

private:
	// メンバー変数

	// シングルトン化
	// -------------------
	Application(void);		// コンストラクタ
	~Application(void);	// デストラクタ

	// コピーコンストラクタを利用できなくする
	Application(const Application& ins);

	// インスタンスの破棄
	void Destory(void);

	// 静的なインスタンス格納領域
	static Application* instance_;

	bool isInitFail_;       // 初期化失敗フラグ
	bool isReleaseFail_;    // 解放失敗フラグ
	bool isDone_;           // ゲーム終了フラグ
	bool screen_;           // スクリーンの状態

	int currentTime;        // 現在の時間 (ミリ秒)
	int lastFrameTime;      // 前回フレームの時間 (ミリ秒)

	int frameCnt;           // フレームカウンター
	int updateFrameRateTime;// フレームレート計算用の時間 (ミリ秒)

	float frameRate;        // フレームレート値 (FPS)


	void CalcFrameRate(void);// フレームレート計算処理
};