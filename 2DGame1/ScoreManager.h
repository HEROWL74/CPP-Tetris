#pragma once

#include "DxLib.h"

class ScoreManager {
public:
    ScoreManager();

    // �X�R�A�Ǘ�
    void Reset();
    void AddScore(int points);
    void AddLines(int lines);

    // �Q�b�^�[
    int GetScore() const { return m_score; }
    int GetLevel() const { return m_level; }
    int GetLines() const { return m_lines; }
    double GetFallSpeed() const { return m_fallSpeed; }

    // �`��
    void Draw() const;

private:
    int m_score;       // �X�R�A
    int m_level;       // ���x��
    int m_lines;       // �������C����
    double m_fallSpeed; // �������x
};