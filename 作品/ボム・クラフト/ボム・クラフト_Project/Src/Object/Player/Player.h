//#pragma once
class Player
{

public:
	//定数
	
	//サイズ
	static constexpr int SIZE_X = 32;
	static constexpr int SIZE_Y = 32;

	//移動量
	static constexpr int MOVE_X = 32;
	static constexpr int MOVE_Y = 32;


private:
	//変数
	
	//
	int boxPosX_;
	int boxPosY_;

	//マウス座標保存用
	int mousePosX_;
	int mousePosY_;
	
	//デバッグ
	int count_;
	int cr_;

	//画像
	int img_;

	//クリック
	bool inputLFlag_;
	bool inputRFlag_;
public:
	//

	//初期化
	void Init(void);
	//アプデ
	void Updeta(void);
	//マウス移動
	void MoveMouseUpdeta(void);
	//キー移動
	void MoveKeyUpdata(void);
	//入力
	void InputUpdeta(void);
	//描画
	void Draw(void);
	//削除
	void Rerease(void);
	//クリック
	bool GetIsInputL(void);
	bool GetIsInputR(void);

};

