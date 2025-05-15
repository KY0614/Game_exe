#pragma once
#include "BlockBase.h"

class PlusBlock : public  BlockBase
{
public:
	static constexpr int BLOCK_SIZE = 320;

	//コンストラクタ	
	PlusBlock(Vector2 pos, int img);

	//デストラクタ
	~PlusBlock(void) = default;

protected:

	void SetParam(void)override;

private:

};

