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
    // �E�B���h�E���[�h�ɐݒ�
    ChangeWindowMode(TRUE);

    // �E�B���h�E�T�C�Y��ݒ�
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

    // �w�i�F��ݒ�
    SetBackgroundColor(32, 32, 64);

    // DX���C�u����������
    if (DxLib_Init() == -1) return false;

    // �`���𗠉�ʂɐݒ�
    SetDrawScreen(DX_SCREEN_BACK);

    // �����̏�����
    srand(static_cast<unsigned int>(time(nullptr)));

    // �R���|�[�l���g�̏�����
    m_field = std::make_unique<Field>();
    m_scoreManager = std::make_unique<ScoreManager>();
    m_soundManager = std::make_unique<SoundManager>();

    // �T�E���h�̃��[�h
    if (!m_soundManager->LoadSounds()) {
        // �T�E���h���[�h�����s���Ă����s�i�I�v�V�����j
        // return false;
    }

    // �^�C�g����ʂ���X�^�[�g
    m_gameState = GameState::TITLE;

    return true;
}

void Game::Run() {
    // ���C�����[�v
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ProcessInput();
        Update();

        // ��ʃN���A
        ClearDrawScreen();

        Render();

        // ����ʂ�\��ʂɔ��f
        ScreenFlip();

        // �t���[���ҋ@
        WaitTimer(16);  // ��60FPS
    }
}

void Game::ProcessInput() {
    // �L�[���͂̒x������
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

        // ���ړ�
        if (CheckHitKey(KEY_INPUT_LEFT)) {
            if (m_field->CanMove(m_currentTetromino.get(), -1, 0)) {
                m_currentTetromino->Move(-1, 0);
                m_soundManager->PlayMove();
            }
        }

        // �E�ړ�
        if (CheckHitKey(KEY_INPUT_RIGHT)) {
            if (m_field->CanMove(m_currentTetromino.get(), 1, 0)) {
                m_currentTetromino->Move(1, 0);
                m_soundManager->PlayMove();
            }
        }

        // ���ړ��i�\�t�g�h���b�v�j
        if (CheckHitKey(KEY_INPUT_DOWN)) {
            if (m_field->CanMove(m_currentTetromino.get(), 0, 1)) {
                m_currentTetromino->Move(0, 1);
                m_scoreManager->AddScore(1); // �ǉ��X�R�A
            }
            else {
                PlaceTetromino();
            }
        }
    }

    // ��]�i�x���Ȃ��j
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

    // �n�[�h�h���b�v
    static bool spacePressed = false;
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        if (!spacePressed) {
            while (m_field->CanMove(m_currentTetromino.get(), 0, 1)) {
                m_currentTetromino->Move(0, 1);
                m_scoreManager->AddScore(2); // �ǉ��X�R�A
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

    // �����J�E���^�[
    m_fallCounter++;
    if (m_fallCounter >= 60 / m_scoreManager->GetFallSpeed()) {
        // �e�g���~�m��1�}�X����
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
    // �w�i
    DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(32, 32, 64), TRUE);

    switch (m_gameState) {
    case GameState::TITLE:
        // �^�C�g�����
        DrawString(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 20, "TETRIS", GetColor(255, 255, 255));
        DrawString(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 20, "Press SPACE to start", GetColor(255, 255, 255));
        break;

    case GameState::PLAY:
    case GameState::OVER:
        // �t�B�[���h�̕`��
        m_field->Draw();

        // ���݂̃e�g���~�m�̕`��i�Q�[���I�[�o�[���͕\�����Ȃ��j
        if (m_gameState == GameState::PLAY && m_currentTetromino) {
            m_currentTetromino->Draw(m_field->GetFieldX(), m_field->GetFieldY());

            // ���̃e�g���~�m�̃v���r���[
            DrawBox(50, 50, 180, 180, GetColor(255, 255, 255), FALSE);
            DrawString(60, 30, "NEXT", GetColor(255, 255, 255));

            if (m_nextTetromino) {
                m_nextTetromino->DrawPreview(80, 80);
            }
        }

        // �X�R�A���\��
        m_scoreManager->Draw();

        // �������
        DrawString(450, 50, "����: Move", GetColor(200, 200, 200));
        DrawString(450, 70, "��: Rotate", GetColor(200, 200, 200));
        DrawString(450, 90, "��: Soft Drop", GetColor(200, 200, 200));
        DrawString(450, 110, "SPACE: Hard Drop", GetColor(200, 200, 200));
        DrawString(450, 130, "ESC: Exit", GetColor(200, 200, 200));

        // �Q�[���I�[�o�[�\��
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
    // �t�B�[���h�̏�����
    m_field->Clear();

    // �X�R�A�̏�����
    m_scoreManager->Reset();

    // �e�g���~�m�̏�����
    m_nextTetromino = std::make_unique<Tetromino>(rand() % Tetromino::NUM_TYPES);
    SpawnTetromino();

    // �Q�[����Ԃ��v���C���ɐݒ�
    m_gameState = GameState::PLAY;

    // �J�E���^�[�̃��Z�b�g
    m_keyDelayCounter = 0;
    m_fallCounter = 0;
}

void Game::SpawnTetromino() {
    m_currentTetromino = std::move(m_nextTetromino);
    m_nextTetromino = std::make_unique<Tetromino>(rand() % Tetromino::NUM_TYPES);

    // �����ʒu�̐ݒ�
    m_currentTetromino->SetPosition(m_field->GetWidth() / 2 - 2, 0);

    // �������ɏՓ˂�����Q�[���I�[�o�[
    if (!m_field->CanPlace(m_currentTetromino.get())) {
        GameOver();
    }
}

void Game::PlaceTetromino() {
    if (!m_currentTetromino) return;

    // �e�g���~�m���t�B�[���h�ɔz�u
    m_field->PlaceTetromino(m_currentTetromino.get());

    // ���ʉ��Đ�
    m_soundManager->PlayDrop();

    // ���C�������`�F�b�N
    int clearedLines = m_field->CheckLines();
    if (clearedLines > 0) {
        m_soundManager->PlayClear();
        m_scoreManager->AddLines(clearedLines);
    }

    // ���̃e�g���~�m�𐶐�
    SpawnTetromino();
}

void Game::GameOver() {
    m_gameState = GameState::OVER;
    m_soundManager->PlayGameover();
}

