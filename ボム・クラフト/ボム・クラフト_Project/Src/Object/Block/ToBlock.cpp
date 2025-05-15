#include <DxLib.h>
#include "../../Manager/ResourceManager.h"
#include "BlockBase.h"
#include "ToBlock.h"

ToBlock::ToBlock(Vector2 pos, int img) :BlockBase(pos, img)
{
	UpdateToExits();
}

void ToBlock::SetParam(void)
{
	img_ = LoadGraph("Data/Image/ToBlock.png");

	SetConnection(TYPE::TO);
	type_ = TYPE::TO;
	UpdateToExits();
}
