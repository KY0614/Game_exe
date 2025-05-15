//#pragma once
class BlockManager
{
public:

	static constexpr int BLOCK_SIZE = 320;

	//コンストラクタ	
	BlockManager(void);

	//デストラクタ
	~BlockManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

};

