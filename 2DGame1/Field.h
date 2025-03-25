#pragma once

#include "DxLib.h"
#include <vector>

// �O���錾
class Tetromino;

class Field {
public:
    // �u���b�N�̃T�C�Y
    static constexpr int BLOCK_SIZE = 30;

    // �R���X�g���N�^
    Field();

    // �t�B�[���h�̏�����
    void Clear();

    // �e�g���~�m�̑���`�F�b�N
    bool CanMove(const Tetromino* tetromino, int dx, int dy) const;
    bool CanRotate(const Tetromino* tetromino) const;
    bool CanPlace(const Tetromino* tetromino) const;

    // �e�g���~�m�̔z�u
    void PlaceTetromino(const Tetromino* tetromino);

    // ���C�������`�F�b�N
    int CheckLines();

    // �`��
    void Draw() const;

    // �Q�b�^�[
    int GetWidth() const { return FIELD_WIDTH; }
    int GetHeight() const { return FIELD_HEIGHT; }
    int GetFieldX() const { return FIELD_X; }
    int GetFieldY() const { return FIELD_Y; }

private:
    // �t�B�[���h�̐ݒ�
    static constexpr int FIELD_WIDTH = 10;   // �t�B�[���h�̕�
    static constexpr int FIELD_HEIGHT = 20;  // �t�B�[���h�̍���
    static constexpr int FIELD_X = 220;      // �t�B�[���h��X���W
    static constexpr int FIELD_Y = 20;       // �t�B�[���h��Y���W

    // �t�B�[���h�f�[�^�i0: ��A1-7: �e�g���~�m�̃^�C�v�ɑΉ�����ԍ��ɂȂ�j
    std::vector<std::vector<int>> m_field;

    // �e�g���~�m�̐F
    static const int COLORS[8];
};