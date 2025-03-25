#pragma once

#include "DxLib.h"
#include <memory>
#include <vector>
#include <string>

// 前方宣言
class Tetromino;
class Field;
class ScoreManager;
class SoundManager;

// ゲームの状態
enum class GameState {
    TITLE,
    PLAY,
    OVER
};

class Game {
public:
    Game();
    ~Game();

  
    bool Initialize();
    void Run();

private:
    
    void ProcessInput();
    void Update();
    void Render();

    // ゲーム状態の初期化
    void InitGame();

    // テトリミノ関連の処理
    void SpawnTetromino();
    void PlaceTetromino();

    // ゲームオーバー処理
    void GameOver();

    // ゲームの状態
    GameState m_gameState;

    // コンポーネント（今回はスマートポインタを使った。）
    std::unique_ptr<Field> m_field;
    std::unique_ptr<Tetromino> m_currentTetromino;
    std::unique_ptr<Tetromino> m_nextTetromino;
    std::unique_ptr<ScoreManager> m_scoreManager;
    std::unique_ptr<SoundManager> m_soundManager;

    // キー入力の遅延用カウンター
    int m_keyDelayCounter;

    // 落下用カウンター
    int m_fallCounter;

    // ゲーム設定
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 800;
    static constexpr int KEY_DELAY = 5;
};