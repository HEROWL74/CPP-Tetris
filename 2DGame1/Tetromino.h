#pragma once

#include "DxLib.h"

class Tetromino {
public:
    // �e�g���~�m�̎��
    static constexpr int NUM_TYPES = 7;
    static constexpr int NUM_ROTATIONS = 4;
    static constexpr int SIZE = 4; // �e�g���~�m�̃T�C�Y�i4x4�}�X�j

    // �R���X�g���N�^
    Tetromino(int type);

    // �ړ��Ɖ�]
    void Move(int dx, int dy);
    void Rotate();

    // �`��
    void Draw(int fieldX, int fieldY) const;
    void DrawPreview(int x, int y) const;

    // �Q�b�^�[
    int GetType() const { return m_type; }
    int GetRotation() const { return m_rotation; }
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }

    // �ʒu�̐ݒ�
    void SetPosition(int x, int y);

    // �u���b�N�̏�Ԃ��擾
    int GetBlock(int x, int y) const;

private:
    int m_type;      // �e�g���~�m�̎��
    int m_rotation;  // ���݂̉�]���
    int m_x;         // X���W
    int m_y;         // Y���W

    // �e�g���~�m�̐F
    static const int COLORS[8];

    // �e�g���~�m�̃u���b�N�z�u
    static const int BLOCKS[NUM_TYPES][NUM_ROTATIONS][SIZE][SIZE];
};