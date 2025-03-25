#pragma once

#include "DxLib.h"
#include <memory>
#include <vector>
#include <string>

// �O���錾
class Tetromino;
class Field;
class ScoreManager;
class SoundManager;

// �Q�[���̏��
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

    // �Q�[����Ԃ̏�����
    void InitGame();

    // �e�g���~�m�֘A�̏���
    void SpawnTetromino();
    void PlaceTetromino();

    // �Q�[���I�[�o�[����
    void GameOver();

    // �Q�[���̏��
    GameState m_gameState;

    // �R���|�[�l���g�i����̓X�}�[�g�|�C���^���g�����B�j
    std::unique_ptr<Field> m_field;
    std::unique_ptr<Tetromino> m_currentTetromino;
    std::unique_ptr<Tetromino> m_nextTetromino;
    std::unique_ptr<ScoreManager> m_scoreManager;
    std::unique_ptr<SoundManager> m_soundManager;

    // �L�[���͂̒x���p�J�E���^�[
    int m_keyDelayCounter;

    // �����p�J�E���^�[
    int m_fallCounter;

    // �Q�[���ݒ�
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 800;
    static constexpr int KEY_DELAY = 5;
};