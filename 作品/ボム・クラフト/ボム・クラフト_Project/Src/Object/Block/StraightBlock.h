#pragma once
#include "BlockBase.h"

class StraightBlock : public  BlockBase
{
public:
	static constexpr int BLOCK_SIZE = 320;

	//コンストラクタ	
	StraightBlock(Vector2 pos, int img);

	//デストラクタ
	~StraightBlock(void) = default;

protected:

	void SetParam(void)override;

private:
};

