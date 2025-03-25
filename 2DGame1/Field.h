#pragma once

#include "DxLib.h"
#include <vector>

// 前方宣言
class Tetromino;

class Field {
public:
    // ブロックのサイズ
    static constexpr int BLOCK_SIZE = 30;

    // コンストラクタ
    Field();

    // フィールドの初期化
    void Clear();

    // テトリミノの操作チェック
    bool CanMove(const Tetromino* tetromino, int dx, int dy) const;
    bool CanRotate(const Tetromino* tetromino) const;
    bool CanPlace(const Tetromino* tetromino) const;

    // テトリミノの配置
    void PlaceTetromino(const Tetromino* tetromino);

    // ライン消去チェック
    int CheckLines();

    // 描画
    void Draw() const;

    // ゲッター
    int GetWidth() const { return FIELD_WIDTH; }
    int GetHeight() const { return FIELD_HEIGHT; }
    int GetFieldX() const { return FIELD_X; }
    int GetFieldY() const { return FIELD_Y; }

private:
    // フィールドの設定
    static constexpr int FIELD_WIDTH = 10;   // フィールドの幅
    static constexpr int FIELD_HEIGHT = 20;  // フィールドの高さ
    static constexpr int FIELD_X = 220;      // フィールドのX座標
    static constexpr int FIELD_Y = 20;       // フィールドのY座標

    // フィールドデータ（0: 空、1-7: テトリミノのタイプに対応する番号になる）
    std::vector<std::vector<int>> m_field;

    // テトリミノの色
    static const int COLORS[8];
};