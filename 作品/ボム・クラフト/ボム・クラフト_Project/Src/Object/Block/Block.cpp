#include <DxLib.h>
#include "../../Manager/ResourceManager.h"
#include "BlockBase.h"
#include "Block.h"

Block::Block(Vector2 pos, int img):BlockBase(pos,img)
{	
	//exits[0] = { -80, 0 }; // ç∂
	//exits[1] = { 0, -80 }; // è„

	UpdateLShapeExits();
}

void Block::SetParam(void)
{
	img_ = LoadGraph("Data/Image/LBlock.png");

	SetConnection(TYPE::LSHAPE);
	type_ = TYPE::LSHAPE;
	UpdatePlusExits();

}
