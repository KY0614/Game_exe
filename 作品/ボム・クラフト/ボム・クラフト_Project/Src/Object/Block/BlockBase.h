#pragma once

#include <vector>
#include "../../Common/Vector2.h"

class BlockBase
{
public:
	static constexpr int IMAGE_SCALSE = 320;

	struct Exit {
		int x, y;
	};

	enum class TYPE
	{
		LSHAPE,
		PLUS,
		STRAIGHT,
		TO,
		ONE,
		GOAL,
		PREVENT
	};

	BlockBase(Vector2 startPos,int img);

	~BlockBase() = default;

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	void UIDraw(void);

	int GetX(void) const;
	int GetY(void) const;
	TYPE GetType(void) const{ return type_; }

	void SetPos(Vector2 pos) {pos_ = pos;}
	void SetRot(int rot) {rotate_ = rot;}
	Vector2 GetPos(void) { return pos_; }

	void RightRotate(void);
	void LeftRotate(void);

	const std::vector<std::pair<int, int>>& GetConnections() const;

	void SnapToGrid(int gridSize, int startX, int startY); // グリッドにスナップする関数
	
	const Exit* GetExits() const;
	const Exit* GetGoalExits() const { return goalExits; }
	const Exit* GetStartExits() const { return startExits; }
	bool HasElectricity() const;
	void SetElectricity(bool state);

	bool IsConnected(const BlockBase* otherBlock) const;

	void SetStartOrGoal(Vector2 pos) { exitsPos_[0] = pos; }
	void SetConnection(TYPE type);
	const Vector2* GetExitsPos() const { return exitsPos_; }

protected:

	int img_;		//画像
	int rotate_;	//角度
	Vector2 pos_;	//座標(int型)
	std::vector<std::pair<int, int>> connections; // 接続可能な方向
	Exit exits[4];			// 出口の座標の配列
	Exit goalExits[1];		// 出口
	Exit startExits[1];		// 起点
	bool hasElectricity;	// 電気が通っているかどうか

	TYPE type_;

	Vector2 exitsPos_[4];
	Vector2 startPos_;
	Vector2 goalPos_;

	virtual void SetParam(void) = 0;

	//void UpdateConnections(void); // 接続方向を更新する

	void UpdateLShapeExits(); // 出口の座標を更新する
	void UpdateStraightExits(); // 出口の座標を更新する
	void UpdatePlusExits(); // 出口の座標を更新する
	void UpdateToExits(); // 出口の座標を更新する
	void UpdateExitsOne();
	void UpdateExitsPre();

private:

};

