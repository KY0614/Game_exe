// ---------------------------------------
// ゲーム制作	 :DrinKingdom(仮)
// 氏名			 :2316032	善原敬子
// ---------------------------------------

#include <DxLib.h>		// DXライブラリを使用する
#include "Application.h"

// WinMain関数
// -----------------
int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR IpCmdLine, int nCmdShow)
{
	Application::CreateInstance();

	Application::GetInstance().Run();

	Application::GetInstance().Release();

	return 0;				// システムの終了処理
}