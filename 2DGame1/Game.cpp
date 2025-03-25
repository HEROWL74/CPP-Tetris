#include "Game.h"
#include "Tetromino.h"
#include "Field.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include <ctime>

Game::Game()
    : m_gameState(GameState::TITLE)
    , m_keyDelayCounter(0)
    , m_fallCounter(0)
{
}

Game::~Game() {
    DxLib_End();
}

bool Game::Initialize() {
    // ウィンドウモードに設定
    ChangeWindowMode(TRUE);

    // ウィンドウサイズを設定
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

    // 背景色を設定
    SetBackgroundColor(32, 32, 64);

    // DXライブラリ初期化
    if (DxLib_Init() == -1) return false;

    // 描画先を裏画面に設定
    SetDrawScreen(DX_SCREEN_BACK);

    // 乱数の初期化
    srand(static_cast<unsigned int>(time(nullptr)));

    // コンポーネントの初期化
    m_field = std::make_unique<Field>();
    m_scoreManager = std::make_unique<ScoreManager>();
    m_soundManager = std::make_unique<SoundManager>();

    // サウンドのロード
    if (!m_soundManager->LoadSounds()) {
        // サウンドロードが失敗しても続行（オプション）
        // return false;
    }

    // タイトル画面からスタート
    m_gameState = GameState::TITLE;

    return true;
}

void Game::Run() {
    // メインループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ProcessInput();
        Update();

        // 画面クリア
        ClearDrawScreen();

        Render();

        // 裏画面を表画面に反映
        ScreenFlip();

        // フレーム待機
        WaitTimer(16);  // 約60FPS
    }
}

void Game::ProcessInput() {
    // キー入力の遅延処理
    m_keyDelayCounter++;

    if (m_gameState == GameState::TITLE) {
        static bool spacePressed = false;
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            if (!spacePressed) {
                InitGame();
                m_gameState = GameState::PLAY;
                spacePressed = true;
            }
        }
        else {
            spacePressed = false;
        }
        return;
    }

    if (m_gameState == GameState::OVER) {
        static bool spacePressed = false;
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            if (!spacePressed) {
                InitGame();
                spacePressed = true;
            }
        }
        else {
            spacePressed = false;
        }
        return;
    }

    if (m_gameState != GameState::PLAY || !m_currentTetromino) return;

    if (m_keyDelayCounter >= KEY_DELAY) {
        m_keyDelayCounter = 0;

        // 左移動
        if (CheckHitKey(KEY_INPUT_LEFT)) {
            if (m_field->CanMove(m_currentTetromino.get(), -1, 0)) {
                m_currentTetromino->Move(-1, 0);
                m_soundManager->PlayMove();
            }
        }

        // 右移動
        if (CheckHitKey(KEY_INPUT_RIGHT)) {
            if (m_field->CanMove(m_currentTetromino.get(), 1, 0)) {
                m_currentTetromino->Move(1, 0);
                m_soundManager->PlayMove();
            }
        }

        // 下移動（ソフトドロップ）
        if (CheckHitKey(KEY_INPUT_DOWN)) {
            if (m_field->CanMove(m_currentTetromino.get(), 0, 1)) {
                m_currentTetromino->Move(0, 1);
                m_scoreManager->AddScore(1); // 追加スコア
            }
            else {
                PlaceTetromino();
            }
        }
    }

    // 回転（遅延なし）
    static bool upPressed = false;
    if (CheckHitKey(KEY_INPUT_UP)) {
        if (!upPressed) {
            if (m_field->CanRotate(m_currentTetromino.get())) {
                m_currentTetromino->Rotate();
                m_soundManager->PlayRotate();
            }
            upPressed = true;
        }
    }
    else {
        upPressed = false;
    }

    // ハードドロップ
    static bool spacePressed = false;
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        if (!spacePressed) {
            while (m_field->CanMove(m_currentTetromino.get(), 0, 1)) {
                m_currentTetromino->Move(0, 1);
                m_scoreManager->AddScore(2); // 追加スコア
            }
            PlaceTetromino();
            spacePressed = true;
        }
    }
    else {
        spacePressed = false;
    }
}

void Game::Update() {
    if (m_gameState != GameState::PLAY || !m_currentTetromino) return;

    // 落下カウンター
    m_fallCounter++;
    if (m_fallCounter >= 60 / m_scoreManager->GetFallSpeed()) {
        // テトリミノを1マス落下
        if (m_field->CanMove(m_currentTetromino.get(), 0, 1)) {
            m_currentTetromino->Move(0, 1);
        }
        else {
            PlaceTetromino();
        }
        m_fallCounter = 0;
    }
}

void Game::Render() {
    // 背景
    DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(32, 32, 64), TRUE);

    switch (m_gameState) {
    case GameState::TITLE:
        // タイトル画面
        DrawString(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 20, "TETRIS", GetColor(255, 255, 255));
        DrawString(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 20, "Press SPACE to start", GetColor(255, 255, 255));
        break;

    case GameState::PLAY:
    case GameState::OVER:
        // フィールドの描画
        m_field->Draw();

        // 現在のテトリミノの描画（ゲームオーバー時は表示しない）
        if (m_gameState == GameState::PLAY && m_currentTetromino) {
            m_currentTetromino->Draw(m_field->GetFieldX(), m_field->GetFieldY());

            // 次のテトリミノのプレビュー
            DrawBox(50, 50, 180, 180, GetColor(255, 255, 255), FALSE);
            DrawString(60, 30, "NEXT", GetColor(255, 255, 255));

            if (m_nextTetromino) {
                m_nextTetromino->DrawPreview(80, 80);
            }
        }

        // スコア情報表示
        m_scoreManager->Draw();

        // 操作説明
        DrawString(450, 50, "←→: Move", GetColor(200, 200, 200));
        DrawString(450, 70, "↑: Rotate", GetColor(200, 200, 200));
        DrawString(450, 90, "↓: Soft Drop", GetColor(200, 200, 200));
        DrawString(450, 110, "SPACE: Hard Drop", GetColor(200, 200, 200));
        DrawString(450, 130, "ESC: Exit", GetColor(200, 200, 200));

        // ゲームオーバー表示
        if (m_gameState == GameState::OVER) {
            const int fieldWidth = m_field->GetWidth() * Field::BLOCK_SIZE;
            const int fieldHeight = m_field->GetHeight() * Field::BLOCK_SIZE;
            const int fieldX = m_field->GetFieldX();
            const int fieldY = m_field->GetFieldY();

            DrawBox(fieldX, fieldY + fieldHeight / 3,
                fieldX + fieldWidth,
                fieldY + fieldHeight * 2 / 3,
                GetColor(0, 0, 0), TRUE);

            DrawString(fieldX + 30, fieldY + fieldHeight / 2 - 20,
                "GAME OVER", GetColor(255, 0, 0));

            DrawString(fieldX + 10, fieldY + fieldHeight / 2 + 10,
                "Press SPACE to retry", GetColor(255, 255, 255));
        }
        break;
    }
}

void Game::InitGame() {
    // フィールドの初期化
    m_field->Clear();

    // スコアの初期化
    m_scoreManager->Reset();

    // テトリミノの初期化
    m_nextTetromino = std::make_unique<Tetromino>(rand() % Tetromino::NUM_TYPES);
    SpawnTetromino();

    // ゲーム状態をプレイ中に設定
    m_gameState = GameState::PLAY;

    // カウンターのリセット
    m_keyDelayCounter = 0;
    m_fallCounter = 0;
}

void Game::SpawnTetromino() {
    m_currentTetromino = std::move(m_nextTetromino);
    m_nextTetromino = std::make_unique<Tetromino>(rand() % Tetromino::NUM_TYPES);

    // 初期位置の設定
    m_currentTetromino->SetPosition(m_field->GetWidth() / 2 - 2, 0);

    // 生成時に衝突したらゲームオーバー
    if (!m_field->CanPlace(m_currentTetromino.get())) {
        GameOver();
    }
}

void Game::PlaceTetromino() {
    if (!m_currentTetromino) return;

    // テトリミノをフィールドに配置
    m_field->PlaceTetromino(m_currentTetromino.get());

    // 効果音再生
    m_soundManager->PlayDrop();

    // ライン消去チェック
    int clearedLines = m_field->CheckLines();
    if (clearedLines > 0) {
        m_soundManager->PlayClear();
        m_scoreManager->AddLines(clearedLines);
    }

    // 次のテトリミノを生成
    SpawnTetromino();
}

void Game::GameOver() {
    m_gameState = GameState::OVER;
    m_soundManager->PlayGameover();
}

