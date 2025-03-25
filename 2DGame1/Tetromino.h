#pragma once

#include "DxLib.h"

class Tetromino {
public:
    // テトリミノの種類
    static constexpr int NUM_TYPES = 7;
    static constexpr int NUM_ROTATIONS = 4;
    static constexpr int SIZE = 4; // テトリミノのサイズ（4x4マス）

    // コンストラクタ
    Tetromino(int type);

    // 移動と回転
    void Move(int dx, int dy);
    void Rotate();

    // 描画
    void Draw(int fieldX, int fieldY) const;
    void DrawPreview(int x, int y) const;

    // ゲッター
    int GetType() const { return m_type; }
    int GetRotation() const { return m_rotation; }
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }

    // 位置の設定
    void SetPosition(int x, int y);

    // ブロックの状態を取得
    int GetBlock(int x, int y) const;

private:
    int m_type;      // テトリミノの種類
    int m_rotation;  // 現在の回転状態
    int m_x;         // X座標
    int m_y;         // Y座標

    // テトリミノの色
    static const int COLORS[8];

    // テトリミノのブロック配置
    static const int BLOCKS[NUM_TYPES][NUM_ROTATIONS][SIZE][SIZE];
};