#pragma once
class Timer
{

public:

    // コンストラクタ
    Timer(void);

    // デストラクタ
    ~Timer(void);

    void Init(void);
    void Update(void);
    void Draw(void);

    int GetTime(void) { return count; }

private:

    //int i, a = 0;
    int White;

    int countTime;
    int count;

};

