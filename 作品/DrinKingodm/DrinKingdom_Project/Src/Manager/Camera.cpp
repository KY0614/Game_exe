#include "../Application.h"
#include"../Manager/InputManager.h"
#include "../Object/Map.h"
#include "../Object/Player.h"
#include "../Scene/SceneGame.h"
#include "Camera.h"


// コンストラクタ
Camera::Camera(Map* map, Player* player)
{
	map_ = map;
	player_ = player;
	sceneGame_ = nullptr;

	mpos_ = { 0, 0 };

	cnt_ = -1;
	speedAnim_ = -1.0f;

	toggleW_ = W_TOGGLE::OFF;
	toggleS_ = S_TOGGLE::OFF;
	toggleA_ = A_TOGGLE::OFF;
	toggleD_ = D_TOGGLE::OFF;

	arrowWPos_ = { 0, 0 };
	arrowSPos_ = { 0, 0 };
	arrowAPos_ = { 0, 0 };
	arrowDPos_ = { 0, 0 };

	arrowMove_ = { 0, 0 };

	directionX = -1;
	directionY = -1;

	mode_ = MODE::NONE;
	dir_ = AsoUtility::DIR::MAX;

	cameraPos_ = { 0, 0 };

	moveSpeedH_ = -1.0f;
	moveSpeedW_ = -1.0f;

	for (int y = 0; y < 1; y++) {
		for (int x = 0; x < 2; x++) {
			imgsW_[y][x] = -1;
			imgsS_[y][x] = -1;
			imgsA_[y][x] = -1;
			imgsD_[y][x] = -1;
		}
	}
}

// デストラクタ
Camera::~Camera(void)
{

}

// 初期処理(基本的に最初の１回だけ実装)
bool Camera::Init(SceneGame* parent)
{
	sceneGame_ = parent;

	// 矢印画像の読み込み
	int ret;

	int xNum = 2;
	int yNum = 1;

	ret = LoadDivGraph(
		"Data/GameScene/Arrow_W.png",
		xNum * yNum,
		xNum,
		yNum,
		ARROW_SIZE_X,
		ARROW_SIZE_Y,
		&(imgsW_[0][0])
	);

	ret = LoadDivGraph(
		"Data/GameScene/Arrow_S.png",
		xNum * yNum,
		xNum,
		yNum,
		ARROW_SIZE_X,
		ARROW_SIZE_Y,
		&(imgsS_[0][0])
	);

	ret = LoadDivGraph(
		"Data/GameScene/Arrow_A.png",
		xNum * yNum,
		xNum,
		yNum,
		AD_SIZE_X,
		AD_SIZE_Y,
		&(imgsA_[0][0])
	);

	ret = LoadDivGraph(
		"Data/GameScene/Arrow_D.png",
		xNum * yNum,
		xNum,
		yNum,
		AD_SIZE_X,
		AD_SIZE_Y,
		&(imgsD_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("W.png画像が見つからない");
		return false;
	}

	directionY = 1;
	directionX = 1;

	// 矢印の位置設定
	arrowWPos_ = { ARROW_W_POS_X, ARROW_W_POS_Y };
	arrowSPos_ = { ARROW_S_POS_X, ARROW_S_POS_Y };
	arrowAPos_ = { ARROW_A_POS_X, ARROW_A_POS_Y };
	arrowDPos_ = { ARROW_D_POS_X, ARROW_D_POS_Y };

	arrowMove_ = { 0,0 };
	// トグルOFF初期化
	toggleW_ = W_TOGGLE::OFF;
	toggleS_ = S_TOGGLE::OFF;
	toggleA_ = A_TOGGLE::OFF;
	toggleD_ = D_TOGGLE::OFF;

	dir_ = AsoUtility::DIR::MAX;

	mode_ = MODE::NONE;

	cameraPos_ = { Application::SCREEN_SIZE_X,0 };

	moveSpeedH_ = 0.0f;

	moveSpeedW_ = 0.0f;
	cnt_ = 0;
	speedAnim_ = ANIMATION_SPEED;
}

// 更新処理(毎フレーム実行)
void Camera::Update(void)
{
	cnt_++;
	auto& ins = InputManager::GetInstance();
	SetMouseDispFlag(false);

	ins.GetMouse();
	mpos_ = ins.GetMousePos();

	SceneGame::FASE fase = sceneGame_->GetFase();
	MoveArrow();

	if (fase == SceneGame::FASE::MAKE)
	{
		// カメラが動いてるときにFASEを遷移しないように
		CameraMove();
	}
}

// 描画処理(毎フレーム実行)
void Camera::Draw(void)
{
	// W
	DrawRotaGraph(arrowWPos_.x - cameraPos_.x,
		(arrowWPos_.y + arrowMove_.y) - cameraPos_.y,
		1.0f,
		0.0f,
		imgsW_[0][static_cast<int>(toggleW_)],
		true);

	// S
	DrawRotaGraph(arrowSPos_.x - cameraPos_.x,
		(arrowSPos_.y + arrowMove_.y) - cameraPos_.y,
		1.0f,
		0.0f,
		imgsS_[0][static_cast<int>(toggleS_)],
		true);

	// A
	DrawRotaGraph((arrowAPos_.x + arrowMove_.x) - cameraPos_.x,
		arrowAPos_.y - cameraPos_.y,
		1.0f,
		0.0f,
		imgsA_[0][static_cast<int>(toggleA_)],
		true);
	
	// D
	DrawRotaGraph((arrowDPos_.x + arrowMove_.x) - cameraPos_.x,
		arrowDPos_.y  - cameraPos_.y,
		1.0f,
		0.0f,
		imgsD_[0][static_cast<int>(toggleD_)],
		true);
}

// 解放処理
void Camera::Release(void)
{
	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			DeleteGraph(imgsS_[y][x]);
			DeleteGraph(imgsW_[y][x]);
			DeleteGraph(imgsA_[y][x]);
			DeleteGraph(imgsD_[y][x]);
		}
	}

}

// カメラの位置を返す
Vector2 Camera::GetCameraPos(void)
{
  	return cameraPos_;
}

// モードを変更する
void Camera::ChangeMode(MODE value)
{
	mode_ = value;
}

// カメラ移動と制御
void Camera::CameraMove(void)
{
	auto& ins = InputManager::GetInstance();

	//
	Vector2 mapPos = map_->GetMapPos();

	// 画面遷移中に遷移しないように制御
	if (
		(cameraPos_.x % Application::SCREEN_SIZE_X) == 0
		&& (cameraPos_.y % Application::SCREEN_SIZE_Y) == 0
		)
	{
		//tamperがセットされている又、押し出している時は
		//カーソルキー上を押しても画面遷移しないように制御
		if (player_->GetTamper() == Player::TAMPER::STAMP ||
			player_->GetTamper() == Player::TAMPER::SET_F ||
			player_->GetTamper() == Player::TAMPER::FINISH
			)
		{
			return;
		}

		// 画面遷移する方向
		if (ins.IsNew(KEY_INPUT_A) ||
			ins.IsNew(KEY_INPUT_LEFT)
			)
		{
			dir_ = AsoUtility::DIR::LEFT;
		}
		if (
			mpos_.x > (arrowAPos_.x + arrowMove_.x - AD_SIZE_X / 2) - cameraPos_.x &&
			mpos_.x < (arrowAPos_.x + arrowMove_.x + AD_SIZE_X / 2) - cameraPos_.x &&
			mpos_.y > (arrowAPos_.y - AD_SIZE_Y / 2) - cameraPos_.y &&
			mpos_.y < (arrowAPos_.y + AD_SIZE_Y / 2) - cameraPos_.y
			)
		{
			toggleA_ = A_TOGGLE::ON;

			if (ins.IsTrgMouseLeft() == true &&
				toggleA_ == A_TOGGLE::ON)
			{
				dir_ = AsoUtility::DIR::LEFT;
			}
		}
		else
		{
			toggleA_ = A_TOGGLE::OFF;
		}
		if (ins.IsNew(KEY_INPUT_D) ||
			ins.IsNew(KEY_INPUT_RIGHT)
			)
		{
			dir_ = AsoUtility::DIR::RIGHT;
		}
		if (
			mpos_.x > (arrowDPos_.x + arrowMove_.x - AD_SIZE_X / 2) - cameraPos_.x &&
			mpos_.x < (arrowDPos_.x + arrowMove_.x + AD_SIZE_X / 2) - cameraPos_.x &&
			mpos_.y >(arrowDPos_.y - AD_SIZE_Y / 2) - cameraPos_.y &&
			mpos_.y < (arrowDPos_.y + AD_SIZE_Y / 2) - cameraPos_.y
			)
		{
			toggleD_ = D_TOGGLE::ON;

			if (ins.IsTrgMouseLeft() == true &&
				toggleD_ == D_TOGGLE::ON)
			{
				dir_ = AsoUtility::DIR::RIGHT;
			}
		}
		else
		{
			toggleD_ = D_TOGGLE::OFF;
		}
		if (
			(ins.IsNew(KEY_INPUT_S) ||
			ins.IsNew(KEY_INPUT_DOWN)) 
			)
		{
			dir_ = AsoUtility::DIR::DOWN;
		}
		if (
			mpos_.x > (arrowSPos_.x - ARROW_SIZE_X / 2) - cameraPos_.x &&
			mpos_.x < (arrowSPos_.x + ARROW_SIZE_X / 2) - cameraPos_.x &&
			mpos_.y >((arrowSPos_.y + arrowMove_.y) - ARROW_SIZE_Y / 2) - cameraPos_.y &&
			mpos_.y < ((arrowSPos_.y + arrowMove_.y) + ARROW_SIZE_Y / 2) - cameraPos_.y
			)
		{
			toggleS_ = S_TOGGLE::ON;

			if (ins.IsTrgMouseLeft() == true	&&
				toggleS_ == S_TOGGLE::ON)
			{
				dir_ = AsoUtility::DIR::DOWN;
			}
		}
		else
		{
			toggleS_ = S_TOGGLE::OFF;
		}
		if (ins.IsNew(KEY_INPUT_W) ||
			ins.IsNew(KEY_INPUT_UP)
			)
		{
			dir_ = AsoUtility::DIR::UP;
		}
		if (
			mpos_.x > (arrowWPos_.x - ARROW_SIZE_X / 2) - cameraPos_.x &&
			mpos_.x < (arrowWPos_.x + ARROW_SIZE_X / 2) - cameraPos_.x &&
			mpos_.y >((arrowWPos_.y + arrowMove_.y) - ARROW_SIZE_Y / 2) - cameraPos_.y &&
			mpos_.y < ((arrowWPos_.y + arrowMove_.y) + ARROW_SIZE_Y / 2) - cameraPos_.y
			)
		{
			toggleW_ = W_TOGGLE::ON;

			if (ins.IsTrgMouseLeft() == true &&
				toggleW_ == W_TOGGLE::ON)
			{
				dir_ = AsoUtility::DIR::UP;
			}
		}
		else
		{
			toggleW_ = W_TOGGLE::OFF;
		}
	}

	//縦移動時のカメラスピード
	moveSpeedH_ = CAMERA_MOVE_SPEED_H;
	//横移動時のカメラスピード
	moveSpeedW_ = CAMERA_MOVE_SPEED_W;

	// キーを押したときの移動処理
	switch (dir_)
	{
	case AsoUtility::DIR::DOWN:		// 下へ移動する
		cameraPos_.y = cameraPos_.y + moveSpeedH_;
		ChangeMode(MODE::CHANGE);	// 画面遷移中
		toggleS_ = S_TOGGLE::ON;
		if (cameraPos_.y > CAMERA_MAX_HEIGHT)		// マップ画像より下に行かないよう且つカメラ遷移状態をNONEに	
		{
			cameraPos_.y = CAMERA_MAX_HEIGHT;
			ChangeMode(MODE::NONE);
			toggleS_ = S_TOGGLE::OFF;
		}
		break;

	case AsoUtility::DIR::UP:		// 上へ移動する
		cameraPos_.y -= moveSpeedH_;
		ChangeMode(MODE::CHANGE);	// 画面遷移中
		toggleW_ = W_TOGGLE::ON;
		if (cameraPos_.y < 0)
		{
			cameraPos_.y = 0;
			ChangeMode(MODE::NONE);
			toggleW_ = W_TOGGLE::OFF;
		}
		else if (map_->GetMapType() == Map::TYPE::JUICE &&		// JUICEの場所から上に行かないよう
			cameraPos_.y < CAMERA_MAX_HEIGHT)					// 且つカメラ遷移状態が変わらないよう
		{
			cameraPos_.y = CAMERA_MAX_HEIGHT;
			ChangeMode(MODE::NONE);
		}
		break;

	case AsoUtility::DIR::LEFT:		// 左へ移動する
		cameraPos_.x -= moveSpeedW_;
		ChangeMode(MODE::CHANGE);	// 画面遷移中
		toggleA_ = A_TOGGLE::ON;
		if (cameraPos_.x < CAMERA_MIN_WIDTH)
		{
			cameraPos_.x = CAMERA_MIN_WIDTH;
			ChangeMode(MODE::NONE);
			toggleA_ = A_TOGGLE::OFF;
		}
		else if (map_->GetMapType() == Map::TYPE::TALK &&
			cameraPos_.x < CAMERA_MAX_WIDTH)
		{
			cameraPos_.x = CAMERA_MAX_WIDTH;
			ChangeMode(MODE::NONE);
		}
		break;

	case AsoUtility::DIR::RIGHT:	// 右へ移動する
		cameraPos_.x += moveSpeedW_;
		ChangeMode(MODE::CHANGE);	// 画面遷移中
		toggleD_ = D_TOGGLE::ON;

		// 画面がマップ画像より右に行かないように
		// (何もないとこに行かないように）
		if (cameraPos_.x > CAMERA_MAX_WIDTH)
		{
			cameraPos_.x = CAMERA_MAX_WIDTH;
			ChangeMode(MODE::NONE);
			toggleD_ = D_TOGGLE::OFF;
		}
		break;
	}
}

void Camera::MoveArrow(void)
{
	int animNum = static_cast<int>(
		static_cast<float>(cnt_) * speedAnim_)
		% 3;

	int maxY = 0;
	int minY = -2;

	int maxX = 0;
	int minX = -2;

	if (animNum == 0)
	{
		arrowMove_.y += directionY;
		arrowMove_.x += directionX;
	}

	if (arrowMove_.y > maxY || arrowMove_.y < minY)
	{
		directionY *= -1;	//方向反転
	}

	if (arrowMove_.x > maxX || arrowMove_.x < minX)
	{
		directionX *= -1;	//方向反転
	}
}
