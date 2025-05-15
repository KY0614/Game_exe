#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ResourceManager.h"
#include "BlockBase.h"

BlockBase::BlockBase(Vector2 startPos, int img):pos_(startPos),img_(img),rotate_(0)
{
	// ランダムに初期角度を設定
	int randomAngle = GetRand(3) * 90; // 0, 1, 2, 3 のいずれかを生成し、×90度にする
	rotate_ = randomAngle;
	//UpdateConnections();

	// 初期出口の座標を設定
	int halfSize = 320 / 2 * 0.5;
	//exits[0] = { 0, 0 }; // 当たり判定のサイズを設定
	//exits[1] = { 0, 0 }; // 当たり判定のサイズを設定
	goalExits[0] = { -halfSize, 0 };
	startExits[0] = { halfSize, 0 };

	startPos_ = { -80,0 };
	goalPos_ = { 80,0 };
	
}


void BlockBase::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	SetParam();

	//画像読み込み

	int ret;
	ret = img_;

	//img_ = res.Load(ResourceManager::SRC::BLOCK).handleId_;
	//if (img_ == -1)
	//{
	//	return;
	//}

}

void BlockBase::Update(void)
{
	auto& ins = InputManager::GetInstance();
}

void BlockBase::Draw(void)
{

	// ブロックを描画
	if (hasElectricity) {
		// 電気が通っている場合の表示
		//DrawBox(pos_.x - 40, pos_.y - 40, pos_.x + 40, pos_.y + 40, GetColor(0, 255, 0), TRUE);
		DrawBox(pos_.x - 80, pos_.y - 80,
			pos_.x + 80, pos_.y + 80,
			0xFFFF00, true);
	}
	else {
		DrawBox(pos_.x - 80, pos_.y - 80,
			pos_.x + 80, pos_.y + 80,
			0xFF0000, true);
	}

	DrawRotaGraph(pos_.x, pos_.y,
		0.5f, rotate_ * DX_PI_F / 180, img_, true, false);
}

void BlockBase::Release(void)
{
	DeleteGraph(img_);
}

void BlockBase::UIDraw(void)
{
	DrawRotaGraph(pos_.x, pos_.y,
		0.3f, rotate_ * DX_PI_F / 180, img_, true, false);
}

int BlockBase::GetX(void) const
{
	return pos_.x;
}

int BlockBase::GetY(void) const
{
	return pos_.y;
}

void BlockBase::RightRotate(void)
{
	rotate_ = (rotate_ + 90+ 360) % 360;

	switch (type_)
	{
	case BlockBase::TYPE::LSHAPE:
		UpdateLShapeExits();
		break;
	case BlockBase::TYPE::PLUS:
		UpdatePlusExits();
		break;
	case BlockBase::TYPE::STRAIGHT:
		UpdateStraightExits();
		break;
	case BlockBase::TYPE::TO:
		UpdateToExits();
		break;
	case BlockBase::TYPE::PREVENT:
		UpdateExitsPre();
		break;
	case BlockBase::TYPE::GOAL:
		break;
	default:
		break;
	}

}

void BlockBase::LeftRotate(void)
{
	rotate_ = (rotate_ - 90 + 360) % 360;

	switch (type_)
	{
	case BlockBase::TYPE::LSHAPE:
		UpdateLShapeExits();
		break;
	case BlockBase::TYPE::PLUS:
		UpdatePlusExits();
		break;
	case BlockBase::TYPE::STRAIGHT:
		UpdateStraightExits();
		break;
	case BlockBase::TYPE::TO:
		UpdateToExits();
		break;
	case BlockBase::TYPE::PREVENT:
		UpdateExitsPre();
		break;
	case BlockBase::TYPE::GOAL:
		break;
	default:
		break;
	}
}

const std::vector<std::pair<int, int>>& BlockBase::GetConnections() const
{
	return connections;
}

void BlockBase::SnapToGrid(int gridSize, int startX, int startY)
{
	pos_.x = ((pos_.x - startX) / gridSize) * gridSize + gridSize / 2 + startX;
	pos_.y = ((pos_.y - startY) / gridSize) * gridSize + gridSize / 2 + startY;
}

const BlockBase::Exit* BlockBase::GetExits() const
{
	return exits;
}

bool BlockBase::HasElectricity() const
{
	return hasElectricity;
}

void BlockBase::SetElectricity(bool state)
{
	hasElectricity = state;
}

bool BlockBase::IsConnected(const BlockBase* otherBlock) const
{
	for (int i = 0; i < 2; ++i) {
		int exitX1 = pos_.x + exits[i].x;
		int exitY1 = pos_.y + exits[i].y;
		for (int j = 0; j < 2; ++j) {
			int exitX2 = otherBlock->GetX() + otherBlock->GetExits()[j].x;
			int exitY2 = otherBlock->GetY() + otherBlock->GetExits()[j].y;
			if (exitX1 == exitX2 && exitY1 == exitY2) {
				return true;
			}
		}
	}
	return false;
}

void BlockBase::SetConnection(TYPE type)
{
	type_ = type;

	switch (type)
	{
	case BlockBase::TYPE::LSHAPE:
		UpdateLShapeExits();
		break;
	case BlockBase::TYPE::PLUS:
		UpdatePlusExits();
		break;
	case BlockBase::TYPE::STRAIGHT:
		UpdateStraightExits();
		break;	
	
	case BlockBase::TYPE::TO:
		UpdateToExits();
		break;
	case BlockBase::TYPE::ONE:
		UpdateExitsOne();
		break;

	case BlockBase::TYPE::PREVENT:
		UpdateExitsPre();
		break;
	default:
		break;
	}
}

//void BlockBase::UpdateConnections(void)
//{
//	// 90度回転ごとに接続方向を更新
//	for (auto& conect : connections) {
//		int dx = conect.first;
//		int dy = conect.second;
//		conect.first = -dy;
//		conect.second = dx;
//	}
//}

void BlockBase::UpdateLShapeExits()
{
	exits[0] = { 0, 0 };
	exits[1] = { 0, 0 };
	exits[2] = { 0, 0 };
	exits[3] = { 0, 0 };

	int halfSize = 320 / 2 * 0.5; // 160 * 0.5 = 80

	switch (rotate_) {
	case 0:
		exits[0] = { -halfSize, 0 };  // 左
		exits[1] = { 0, -halfSize };  // 上

		break;
	case 90:
		exits[0] = { 0, -halfSize };  // 上
		exits[1] = { halfSize, 0 };   // 右

		break;
	case 180:
		exits[0] = { halfSize, 0 };   // 右
		exits[1] = { 0, halfSize };   // 下
		
		break;
	case 270:
		exits[0] = { 0, halfSize };   // 下
		exits[1] = { -halfSize, 0 };  // 左

		break;
	}
}

void BlockBase::UpdateStraightExits()
{
	exits[0] = { 0, 0 };
	exits[1] = { 0, 0 };
	exits[2] = { 0, 0 };
	exits[3] = { 0, 0 };

	int halfSize = 320 / 2 * 0.5; // 160 * 0.5 = 80

	switch (rotate_) {
	case 0:
		exits[0] = { -halfSize, 0 };	// 左
		exits[1] = { halfSize, 0 };		// 右

		break;
	case 90:
		exits[0] = { 0, -halfSize };  //上
		exits[1] = {0, halfSize };	  // 下

		break;
	case 180:
		exits[0] = { -halfSize, 0 };	// 左
		exits[1] = { halfSize, 0 };		// 右

		break;
	case 270:
		exits[0] = { 0, -halfSize };  //上
		exits[1] = { 0, halfSize };	  // 下

		break;
	}
}

void BlockBase::UpdatePlusExits()
{
	//exits[0] = { 0, 0 };
	//exits[1] = { 0, 0 };
	//exits[2] = { 0, 0 };
	//exits[3] = { 0, 0 };

	int halfSize = 320 / 2 * 0.5; // 160 * 0.5 = 80

	switch (rotate_) {
	case 0:
		exits[0] = { -halfSize, 0 };  // 左
		exits[1] = { 0, -halfSize };  // 上		
		exits[2] = { halfSize, 0 };  // 右
		exits[3] = { 0, halfSize };  // 下

		break;
	case 90:
		exits[0] = { 0, -halfSize };  // 左
		exits[1] = { halfSize, 0 };  // 上		
		exits[2] = { 0, halfSize };  // 右
		exits[3] = { -halfSize, 0 };  // 下

		break;
	case 180:
		exits[0] = { halfSize, 0 };  // 左
		exits[1] = { 0, halfSize };  // 上		
		exits[2] = { -halfSize, 0 };  // 右
		exits[3] = { 0, -halfSize };  // 下
		break;
	case 270:
		exits[0] = { 0, halfSize };  // 左
		exits[1] = { -halfSize, 0 };  // 上		
		exits[2] = { 0, -halfSize };  // 右
		exits[3] = { halfSize, 0 };  // 下

		break;
	}
}

void BlockBase::UpdateToExits()
{
	exits[0] = { 0, 0 };
	exits[1] = { 0, 0 };
	exits[2] = { 0, 0 };
	exits[3] = { 0, 0 };

	int halfSize = 320 / 2 * 0.5; // 160 * 0.5 = 80

	switch (rotate_) {
	case 0:
		exits[0] = { -halfSize, 0 };	// 左
		exits[1] = { 0, -halfSize };	// 上
		exits[2] = { halfSize, 0 };		// 右

		break;
	case 90:
		exits[0] = { 0, -halfSize };	// 上
		exits[1] = { halfSize, 0 };		// 右
		exits[2] = { 0, halfSize };		// 下

		break;
	case 180:
		exits[0] = { halfSize, 0 };		// 右
		exits[1] = { 0, halfSize };		// 下
		exits[2] = { -halfSize, 0 };	// 左

		break;
	case 270:
		exits[0] = { 0, halfSize };		// 下
		exits[1] = { -halfSize, 0 };	// 左
		exits[2] = { 0, -halfSize };	// 上

		break;
	}
}

void BlockBase::UpdateExitsOne()
{
	exits[0] = { 0, 0 };
	exits[1] = { 0, 0 };
	exits[2] = { 0, 0 };
	exits[3] = { 0, 0 };

	int halfSize = 320 / 2 * 0.5; // 160 * 0.5 = 80

	switch (rotate_) {
	case 0:
		exits[0] = { halfSize, 0 };   // 右

		//直接当たり判定する用
		exitsPos_[0] = { 80,0 };
		break;
	case 90:
		exits[0] = { 0, halfSize };   // 下

		//直接当たり判定する用
		exitsPos_[0] = { 0, 80 };
		break;
	case 180:
		exits[0] = { -halfSize, 0 };  // 左

		//直接当たり判定する用
		exitsPos_[0] = { -80, 0 };

		break;
	case 270:
		exits[0] = { 0, -halfSize };  // 上

		//直接当たり判定する用
		exitsPos_[0] = { 0,-80 };
		break;
	}
}

void BlockBase::UpdateExitsPre()
{
	exits[0] = { 0, 0 };
	exits[1] = { 0, 0 };
	exits[2] = { 0, 0 };
	exits[3] = { 0, 0 };
}
