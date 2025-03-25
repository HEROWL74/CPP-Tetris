#pragma once

//GameSystemクラス
//・このゲームの土台となるクラス

class GameSystem
{
public:
	//このゲームの初期化を行う
	void Initialize();
	//このゲームの時間を進める
	void Execute();

//=========================================
// 今回このクラスも、どこからでもアクセスできるように
// シングルトンパターンにしておきます。
// ↓↓↓以下、シングルトンパターンのコード
//=========================================
private:
	//唯一のインスタンス用のポインタ
	static inline GameSystem* s_instance;
	//コンストラクタは、privateにする
	GameSystem() {}
public:

	//インスタンス作成
	static void CreateInstance()
	{
		DeleteInstance();

		s_instance = new GameSystem();
	}
	//インスタンス削除
	static void DeleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}
	//唯一のインスタンス取得
	static GameSystem& GetInstance()
	{
		
		return *s_instance;
	}
};
//GameSystemの唯一のインスタンスを簡単に取得するためのマクロを定義
#define GAMESYS GameSystem::GetInstance()
