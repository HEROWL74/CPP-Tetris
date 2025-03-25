#pragma once

#include "DxLib.h"

class ScoreManager {
public:
    ScoreManager();

    // スコア管理
    void Reset();
    void AddScore(int points);
    void AddLines(int lines);

    // ゲッター
    int GetScore() const { return m_score; }
    int GetLevel() const { return m_level; }
    int GetLines() const { return m_lines; }
    double GetFallSpeed() const { return m_fallSpeed; }

    // 描画
    void Draw() const;

private:
    int m_score;       // スコア
    int m_level;       // レベル
    int m_lines;       // 消去ライン数
    double m_fallSpeed; // 落下速度
};