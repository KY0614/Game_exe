#include <DxLib.h>
#include "BlockBase.h"
#include "PreventBlock.h"

PreventBlock::PreventBlock(Vector2 pos, int img) :BlockBase(pos, img)
{
	UpdateExitsPre();
}

void PreventBlock::SetParam(void)
{
	img_ = LoadGraph("Data/Image/PreventBlock.png");
	SetConnection(TYPE::PREVENT);
	type_ = TYPE::PREVENT;
	UpdateExitsPre();
}
