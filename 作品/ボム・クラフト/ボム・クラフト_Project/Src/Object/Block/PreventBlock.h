#pragma once
#include "BlockBase.h"

class PreventBlock : public  BlockBase
{
public:
	static constexpr int BLOCK_SIZE = 320;

	//コンストラクタ	
	PreventBlock(Vector2 pos, int img);

	//デストラクタ
	~PreventBlock(void) = default;

protected:

	void SetParam(void)override;

private:
};

