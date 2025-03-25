#include "ScoreManager.h"

ScoreManager::ScoreManager()
    : m_score(0)
    , m_level(1)
    , m_lines(0)
    , m_fallSpeed(1.0)
{
}

void ScoreManager::Reset() {
    m_score = 0;
    m_level = 1;
    m_lines = 0;
    m_fallSpeed = 1.0;
}

void ScoreManager::AddScore(int points) {
    m_score += points;
}

void ScoreManager::AddLines(int lines) {
    if (lines <= 0) return;

    // �X�R�A���Z
    int linePoints[] = { 0, 100, 300, 500, 800 }; // 0, 1, 2, 3, 4���C�������̃|�C���g
    AddScore(linePoints[lines] * m_level);

    // �������C�������Z
    m_lines += lines;

    // ���x���A�b�v�i10���C���������Ɓj
    m_level = m_lines / 10 + 1;

    // �������x�̍X�V
    m_fallSpeed = 1.0 + (m_level - 1) * 0.1;
}

void ScoreManager::Draw() const {
    // �X�R�A���\��
    DrawBox(50, 200, 180, 350, GetColor(255, 255, 255), FALSE);

    DrawString(60, 210, "SCORE", GetColor(255, 255, 255));
    DrawFormatString(60, 230, GetColor(255, 255, 255), "%d", m_score);

    DrawString(60, 260, "LEVEL", GetColor(255, 255, 255));
    DrawFormatString(60, 280, GetColor(255, 255, 255), "%d", m_level);

    DrawString(60, 310, "LINES", GetColor(255, 255, 255));
    DrawFormatString(60, 330, GetColor(255, 255, 255), "%d", m_lines);
}