//#pragma once
#include "BlockBase.h"

class Block : public  BlockBase
{
public:

	static constexpr int BLOCK_SIZE = 320;
	
	//コンストラクタ	
	Block(Vector2 pos,int img);

	//デストラクタ
	~Block(void) = default;

protected:

	void SetParam(void)override;

private:

};

