#pragma once
#include "BlockBase.h"

class ToBlock : public  BlockBase
{
public:
	static constexpr int BLOCK_SIZE = 320;

	//コンストラクタ	
	ToBlock(Vector2 pos, int img);

	//デストラクタ
	~ToBlock(void) = default;

protected:

	void SetParam(void)override;

private:

};

