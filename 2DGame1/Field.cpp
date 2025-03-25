#include "Field.h"
#include "Tetromino.h"

// �e�g���~�m�̐F
const int Field::COLORS[8] = {
    0x000000,  // 0: ��
    0x00FFFF,  // 1: I�i���F�j
    0x0000FF,  // 2: J�i�j
    0xFF8800,  // 3: L�i�I�����W�j
    0xFFFF00,  // 4: O�i���F�j
    0x00FF00,  // 5: S�i�΁j
    0xFF00FF,  // 6: T�i���j
    0xFF0000   // 7: Z�i�ԁj
};

Field::Field()
    : m_field(FIELD_HEIGHT, std::vector<int>(FIELD_WIDTH, 0))
{
    Clear();
}

void Field::Clear() {
    // �t�B�[���h�̏�����
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            m_field[y][x] = 0;
        }
    }
}

bool Field::CanMove(const Tetromino* tetromino, int dx, int dy) const {
    int newX = tetromino->GetX() + dx;
    int newY = tetromino->GetY() + dy;

    for (int y = 0; y < Tetromino::SIZE; y++) {
        for (int x = 0; x < Tetromino::SIZE; x++) {
            if (tetromino->GetBlock(x, y)) {
                int fieldX = newX + x;
                int fieldY = newY + y;

                // �t�B�[���h�O�ɏo��ꍇ
                if (fieldX < 0 || fieldX >= FIELD_WIDTH || fieldY < 0 || fieldY >= FIELD_HEIGHT) {
                    return false;
                }

                // ���ɔz�u���ꂽ�u���b�N�ƏՓ˂���ꍇ
                if (m_field[fieldY][fieldX]) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Field::CanRotate(const Tetromino* tetromino) const {
    // �e�g���~�m���R�s�[���ĉ�]������
    Tetromino rotated = *tetromino;
    rotated.Rotate();

    // ��]��̈ʒu���L�����`�F�b�N
    for (int y = 0; y < Tetromino::SIZE; y++) {
        for (int x = 0; x < Tetromino::SIZE; x++) {
            if (rotated.GetBlock(x, y)) {
                int fieldX = rotated.GetX() + x;
                int fieldY = rotated.GetY() + y;

                // �t�B�[���h�O�ɏo��ꍇ
                if (fieldX < 0 || fieldX >= FIELD_WIDTH || fieldY < 0 || fieldY >= FIELD_HEIGHT) {
                    return false;
                }

                // ���ɔz�u���ꂽ�u���b�N�ƏՓ˂���ꍇ
                if (m_field[fieldY][fieldX]) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Field::CanPlace(const Tetromino* tetromino) const {
    return CanMove(tetromino, 0, 0);
}

void Field::PlaceTetromino(const Tetromino* tetromino) {
    for (int y = 0; y < Tetromino::SIZE; y++) {
        for (int x = 0; x < Tetromino::SIZE; x++) {
            if (tetromino->GetBlock(x, y)) {
                int fieldX = tetromino->GetX() + x;
                int fieldY = tetromino->GetY() + y;

                if (fieldX >= 0 && fieldX < FIELD_WIDTH && fieldY >= 0 && fieldY < FIELD_HEIGHT) {
                    m_field[fieldY][fieldX] = tetromino->GetBlock(x, y);
                }
            }
        }
    }
}

int Field::CheckLines() {
    int clearedLines = 0;

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        bool lineFull = true;

        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (m_field[y][x] == 0) {
                lineFull = false;
                break;
            }
        }

        if (lineFull) {
            clearedLines++;

            // ���C�����������ď�̃��C������i������
            for (int ty = y; ty > 0; ty--) {
                for (int x = 0; x < FIELD_WIDTH; x++) {
                    m_field[ty][x] = m_field[ty - 1][x];
                }
            }

            // �ŏ�i����ɂ���
            for (int x = 0; x < FIELD_WIDTH; x++) {
                m_field[0][x] = 0;
            }
        }
    }

    return clearedLines;
}

void Field::Draw() const {
    // �t�B�[���h�g
    DrawBox(FIELD_X - 2, FIELD_Y - 2,
        FIELD_X + FIELD_WIDTH * BLOCK_SIZE + 2,
        FIELD_Y + FIELD_HEIGHT * BLOCK_SIZE + 2,
        GetColor(180, 180, 180), FALSE);

    // �t�B�[���h�w�i
    DrawBox(FIELD_X, FIELD_Y,
        FIELD_X + FIELD_WIDTH * BLOCK_SIZE,
        FIELD_Y + FIELD_HEIGHT * BLOCK_SIZE,
        GetColor(0, 0, 0), TRUE);

    // �z�u�ς݃u���b�N�̕`��
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (m_field[y][x]) {
                int blockType = m_field[y][x];
                int color = COLORS[blockType];

                DrawBox(FIELD_X + x * BLOCK_SIZE,
                    FIELD_Y + y * BLOCK_SIZE,
                    FIELD_X + (x + 1) * BLOCK_SIZE,
                    FIELD_Y + (y + 1) * BLOCK_SIZE,
                    color, TRUE);

                // �u���b�N�̘g��
                DrawBox(FIELD_X + x * BLOCK_SIZE,
                    FIELD_Y + y * BLOCK_SIZE,
                    FIELD_X + (x + 1) * BLOCK_SIZE,
                    FIELD_Y + (y + 1) * BLOCK_SIZE,
                    GetColor(0, 0, 0), FALSE);
            }
        }
    }
}