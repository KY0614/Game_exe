#include <DxLib.h>
#include "BlockBase.h"
#include "StraightBlock.h"

StraightBlock::StraightBlock(Vector2 pos, int img) :BlockBase(pos, img)
{
	UpdateStraightExits();
}

void StraightBlock::SetParam(void)
{
	img_ = LoadGraph("Data/Image/LineBlock.png");

	SetConnection(TYPE::STRAIGHT);
	type_ = TYPE::STRAIGHT;
	UpdateStraightExits();
}
