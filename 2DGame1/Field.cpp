#include "Field.h"
#include "Tetromino.h"

// テトリミノの色
const int Field::COLORS[8] = {
    0x000000,  // 0: 空白
    0x00FFFF,  // 1: I（水色）
    0x0000FF,  // 2: J（青）
    0xFF8800,  // 3: L（オレンジ）
    0xFFFF00,  // 4: O（黄色）
    0x00FF00,  // 5: S（緑）
    0xFF00FF,  // 6: T（紫）
    0xFF0000   // 7: Z（赤）
};

Field::Field()
    : m_field(FIELD_HEIGHT, std::vector<int>(FIELD_WIDTH, 0))
{
    Clear();
}

void Field::Clear() {
    // フィールドの初期化
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

                // フィールド外に出る場合
                if (fieldX < 0 || fieldX >= FIELD_WIDTH || fieldY < 0 || fieldY >= FIELD_HEIGHT) {
                    return false;
                }

                // 既に配置されたブロックと衝突する場合
                if (m_field[fieldY][fieldX]) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Field::CanRotate(const Tetromino* tetromino) const {
    // テトリミノをコピーして回転させる
    Tetromino rotated = *tetromino;
    rotated.Rotate();

    // 回転後の位置が有効かチェック
    for (int y = 0; y < Tetromino::SIZE; y++) {
        for (int x = 0; x < Tetromino::SIZE; x++) {
            if (rotated.GetBlock(x, y)) {
                int fieldX = rotated.GetX() + x;
                int fieldY = rotated.GetY() + y;

                // フィールド外に出る場合
                if (fieldX < 0 || fieldX >= FIELD_WIDTH || fieldY < 0 || fieldY >= FIELD_HEIGHT) {
                    return false;
                }

                // 既に配置されたブロックと衝突する場合
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

            // ラインを消去して上のラインを一段下げる
            for (int ty = y; ty > 0; ty--) {
                for (int x = 0; x < FIELD_WIDTH; x++) {
                    m_field[ty][x] = m_field[ty - 1][x];
                }
            }

            // 最上段を空にする
            for (int x = 0; x < FIELD_WIDTH; x++) {
                m_field[0][x] = 0;
            }
        }
    }

    return clearedLines;
}

void Field::Draw() const {
    // フィールド枠
    DrawBox(FIELD_X - 2, FIELD_Y - 2,
        FIELD_X + FIELD_WIDTH * BLOCK_SIZE + 2,
        FIELD_Y + FIELD_HEIGHT * BLOCK_SIZE + 2,
        GetColor(180, 180, 180), FALSE);

    // フィールド背景
    DrawBox(FIELD_X, FIELD_Y,
        FIELD_X + FIELD_WIDTH * BLOCK_SIZE,
        FIELD_Y + FIELD_HEIGHT * BLOCK_SIZE,
        GetColor(0, 0, 0), TRUE);

    // 配置済みブロックの描画
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

                // ブロックの枠線
                DrawBox(FIELD_X + x * BLOCK_SIZE,
                    FIELD_Y + y * BLOCK_SIZE,
                    FIELD_X + (x + 1) * BLOCK_SIZE,
                    FIELD_Y + (y + 1) * BLOCK_SIZE,
                    GetColor(0, 0, 0), FALSE);
            }
        }
    }
}