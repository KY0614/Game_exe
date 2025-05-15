
#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/ResourceManager.h"
#include "Player.h"



void Player::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//画像読み込み
	img_ = res.Load(ResourceManager::SRC::PLAYER).handleId_;
	if (img_ == -1)
	{
		return;
	}
	boxPosX_ = 0;
	boxPosY_ = 0;
	mousePosX_ = 0;
	mousePosY_ = 0;
	count_ = 0;
	cr_ = 0x000000;
	//クリック
	inputLFlag_ = false;
	inputRFlag_ = false;
}
//プレイヤー全体更新
void Player::Updeta(void)
{
	MoveMouseUpdeta();
	MoveKeyUpdata();
	InputUpdeta();
}
//カーソル更新
void Player::MoveMouseUpdeta(void)
{
	SetMouseDispFlag(false);
	//マウス座標取得用
	int mousePosX, mousePosY;
	//マウス座標取得
	GetMousePoint(&mousePosX, &mousePosY);
	//座標保存
	mousePosX_ = mousePosX;
	mousePosY_ = mousePosY;
	//移動制限
	//左制限
	if (mousePosX_ < 0)
	{
		SetMousePoint(0, mousePosY);
	}
	//右制限
	if (mousePosX_ > Application::SCREEN_SIZE_X)
	{
		SetMousePoint(Application::SCREEN_SIZE_X, mousePosY);
	}
	//上
	if (mousePosY_ < 0)
	{
		SetMousePoint(mousePosX,0);
	}
	//下制限
	if (mousePosY_ > Application::SCREEN_SIZE_Y)
	{
		SetMousePoint(mousePosX, Application::SCREEN_SIZE_Y);
	}
}
//キー入力更新
void Player::MoveKeyUpdata(void)
{
	InputManager& ins = InputManager::GetInstance();

	//上移動
	if (ins.IsTrgDown(KEY_INPUT_W))
	{
		boxPosY_ -= MOVE_Y;
	}
	//下移動
	if (ins.IsTrgDown(KEY_INPUT_S))
	{
		boxPosY_ += MOVE_Y;
	}
	//右移動
	if (ins.IsTrgDown(KEY_INPUT_D))
	{
		boxPosX_ += MOVE_X;
	}
	//左移動
	if (ins.IsTrgDown(KEY_INPUT_A))
	{
		boxPosX_ -= MOVE_X;
	}


	//移動制限
	//右制限
	if (boxPosX_ > Application::SCREEN_SIZE_X - SIZE_X)
	{
		boxPosX_ = Application::SCREEN_SIZE_X - SIZE_X;
	}
	//左制限
	if (boxPosX_ < 0)
	{
		boxPosX_ = 0;
	}
	//上制限
	if (boxPosY_ < 0)
	{
		boxPosY_ = 0;
	}
	//下制限
	if (boxPosY_ > Application::SCREEN_SIZE_Y - SIZE_Y)
	{
		boxPosY_ = Application::SCREEN_SIZE_Y - SIZE_Y;
	}
}
//マウス入力更新
void Player::InputUpdeta(void)
{
	InputManager& ins = InputManager::GetInstance();
	//左クリック
	if (ins.IsTrgMouseLeft())
	{
		inputLFlag_ = true;
	}
	else
	{
		inputLFlag_ = false;
	}

	//右クリック
	if (ins.IsTrgMouseRight())
	{
		inputRFlag_ = true;
	}
	else
	{
		inputRFlag_ = false;
	}

}
//画像
void Player::Draw(void)
{
	//DrawBox(boxPosX_, boxPosY_, boxPosX_ + SIZE_X, boxPosY_ + SIZE_Y, 0x0000ff, false);
	DrawRotaGraph(mousePosX_+30,
		mousePosY_+30,
		1.0f, 0.0f, img_, true, false);


	////デバッグ
	/*DrawFormatString(0, 20, 0xffffff, "X%d", inputLFlag_);
	DrawFormatString(0, 40, 0xffffff, "Y%d", inputRFlag_);*/
	//DrawFormatString(0, 60, 0xffffff, "count%d", count_);
	//DrawBox(100, 100, 200, 200, cr_, true);
}
void Player::Rerease(void)
{

}
//ゲット・セット
bool Player::GetIsInputL(void)
{
	return inputLFlag_;
}

bool Player::GetIsInputR(void)
{
	return inputRFlag_;
}