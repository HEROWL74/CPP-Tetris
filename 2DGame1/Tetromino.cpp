#include "Tetromino.h"
#include "Field.h"

// テトリミノの色
const int Tetromino::COLORS[8] = {
    0x000000,  // 0: 空白
    0x00FFFF,  // 1: I（水色）
    0x0000FF,  // 2: J（青）
    0xFF8800,  // 3: L（オレンジ）
    0xFFFF00,  // 4: O（黄色）
    0x00FF00,  // 5: S（緑）
    0xFF00FF,  // 6: T（紫）
    0xFF0000   // 7: Z（赤）
};

// テトリミノのブロック配置
const int Tetromino::BLOCKS[NUM_TYPES][NUM_ROTATIONS][SIZE][SIZE] = {
    // I
    {
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }
    },
    // J
    {
        {
            {2, 0, 0, 0},
            {2, 2, 2, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 2, 2, 0},
            {0, 2, 0, 0},
            {0, 2, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {2, 2, 2, 0},
            {0, 0, 2, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 2, 0, 0},
            {0, 2, 0, 0},
            {2, 2, 0, 0},
            {0, 0, 0, 0}
        }
    },
    // L
    {
        {
            {0, 0, 3, 0},
            {3, 3, 3, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 3, 0, 0},
            {0, 3, 0, 0},
            {0, 3, 3, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {3, 3, 3, 0},
            {3, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {3, 3, 0, 0},
            {0, 3, 0, 0},
            {0, 3, 0, 0},
            {0, 0, 0, 0}
        }
    },
    // O
    {
        {
            {0, 4, 4, 0},
            {0, 4, 4, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 4, 4, 0},
            {0, 4, 4, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 4, 4, 0},
            {0, 4, 4, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 4, 4, 0},
            {0, 4, 4, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    // S
    {
        {
            {0, 5, 5, 0},
            {5, 5, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 5, 0, 0},
            {0, 5, 5, 0},
            {0, 0, 5, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 5, 5, 0},
            {5, 5, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {5, 0, 0, 0},
            {5, 5, 0, 0},
            {0, 5, 0, 0},
            {0, 0, 0, 0}
        }
    },
    // T
    {
        {
            {0, 6, 0, 0},
            {6, 6, 6, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 6, 0, 0},
            {0, 6, 6, 0},
            {0, 6, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {6, 6, 6, 0},
            {0, 6, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 6, 0, 0},
            {6, 6, 0, 0},
            {0, 6, 0, 0},
            {0, 0, 0, 0}
        }
    },
    // Z
    {
        {
            {7, 7, 0, 0},
            {0, 7, 7, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 7, 0},
            {0, 7, 7, 0},
            {0, 7, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {7, 7, 0, 0},
            {0, 7, 7, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 7, 0, 0},
            {7, 7, 0, 0},
            {7, 0, 0, 0},
            {0, 0, 0, 0}
        }
    }
};

Tetromino::Tetromino(int type)
    : m_type(type)
    , m_rotation(0)
    , m_x(0)
    , m_y(0)
{
}

void Tetromino::Move(int dx, int dy) {
    m_x += dx;
    m_y += dy;
}

void Tetromino::Rotate() {
    m_rotation = (m_rotation + 1) % NUM_ROTATIONS;
}

void Tetromino::Draw(int fieldX, int fieldY) const {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (GetBlock(x, y)) {
                int blockType = GetBlock(x, y);
                int color = COLORS[blockType];

                int screenX = fieldX + (m_x + x) * Field::BLOCK_SIZE;
                int screenY = fieldY + (m_y + y) * Field::BLOCK_SIZE;

                DrawBox(screenX, screenY,
                    screenX + Field::BLOCK_SIZE,
                    screenY + Field::BLOCK_SIZE,
                    color, TRUE);

                // ブロックの枠線
                DrawBox(screenX, screenY,
                    screenX + Field::BLOCK_SIZE,
                    screenY + Field::BLOCK_SIZE,
                    GetColor(0, 0, 0), FALSE);
            }
        }
    }
}

void Tetromino::DrawPreview(int x, int y) const {
    for (int py = 0; py < SIZE; py++) {
        for (int px = 0; px < SIZE; px++) {
            if (BLOCKS[m_type][0][py][px]) {
                int blockType = BLOCKS[m_type][0][py][px];
                int color = COLORS[blockType];

                DrawBox(x + px * Field::BLOCK_SIZE,
                    y + py * Field::BLOCK_SIZE,
                    x + (px + 1) * Field::BLOCK_SIZE,
                    y + (py + 1) * Field::BLOCK_SIZE,
                    color, TRUE);

                // ブロックの枠線
                DrawBox(x + px * Field::BLOCK_SIZE,
                    y + py * Field::BLOCK_SIZE,
                    x + (px + 1) * Field::BLOCK_SIZE,
                    y + (py + 1) * Field::BLOCK_SIZE,
                    GetColor(0, 0, 0), FALSE);
            }
        }
    }
}

void Tetromino::SetPosition(int x, int y) {
    m_x = x;
    m_y = y;
}

int Tetromino::GetBlock(int x, int y) const {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        return 0;
    }
    return BLOCKS[m_type][m_rotation][y][x];
}