//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>


class Player;
class BlockBase;
class Timer;

class HardGameScene : public SceneBase
{
public:

	static constexpr int BLOCK_NUM_X = 5;
	static constexpr int BLOCK_NUM_Y = 4;

	// コンストラクタ
	HardGameScene(void);

	// デストラクタ
	~HardGameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	Player* player_;
	Timer* timer_;

	//サウンド
	int bgmHandle_;		//BGM

	std::vector<BlockBase*> blocks;
	BlockBase* startBlock;
	BlockBase* goalBlock;
	BlockBase* UIBlock1;
	BlockBase* UIBlock2;
	int gridSize_;
	int startX_;
	int startY_;

	int img_;

	int seTouch_;					//ブロック触ったとき
	int seRotate_;					//回転

	Vector2 highlightPos_;			//ハイライト座標
	BlockBase* highlightBlock;		//ハイライトをつけるブロック
	BlockBase* preHighlightBlock;	//

	int replaceCount;

	void InitBlock(void);
	void AddBlock(BlockBase* block);

	void BlockProcess(Vector2 pos);	//ブロックの操作処理
	bool AreBlocksConnected(const BlockBase* block1, const BlockBase* block2) const;
	BlockBase* GetBlockAtPosition(int x, int y) const; // マウス位置にあるブロックを取得する
	void UpdateElectricity(BlockBase* block);
	void ClearElectricity();	//電気の状態を全部リセット
	void PropagateElectricity(BlockBase* block); // 電気を伝播させる
	void ReplaceBlockWithPlusBlock();

	void HighlightUpdate();
	void HighlightDraw();

	void InitSoundEffect();
	void PlaySoundEffect();
};