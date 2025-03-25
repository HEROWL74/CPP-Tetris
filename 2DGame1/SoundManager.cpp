#include "SoundManager.h"

SoundManager::SoundManager()
    : m_soundMove(-1)
    , m_soundRotate(-1)
    , m_soundDrop(-1)
    , m_soundClear(-1)
    , m_soundGameover(-1)
{
}

SoundManager::~SoundManager() {
    // サウンドリソースの解放
    if (m_soundMove != -1) DeleteSoundMem(m_soundMove);
    if (m_soundRotate != -1) DeleteSoundMem(m_soundRotate);
    if (m_soundDrop != -1) DeleteSoundMem(m_soundDrop);
    if (m_soundClear != -1) DeleteSoundMem(m_soundClear);
    if (m_soundGameover != -1) DeleteSoundMem(m_soundGameover);
}

bool SoundManager::LoadSounds() {
    // 効果音の読み込み
    m_soundMove = LoadSoundMem(SOUND_MOVE);
    m_soundRotate = LoadSoundMem(SOUND_ROTATE);
    m_soundDrop = LoadSoundMem(SOUND_DROP);
    m_soundClear = LoadSoundMem(SOUND_CLEAR);
    m_soundGameover = LoadSoundMem(SOUND_GAMEOVER);

    // すべてのサウンドが正常にロードされたかチェック
    return m_soundMove != -1 && m_soundRotate != -1 &&
        m_soundDrop != -1 && m_soundClear != -1 &&
        m_soundGameover != -1;
}

void SoundManager::PlayMove() {
    if (m_soundMove != -1) {
        PlaySoundMem(m_soundMove, DX_PLAYTYPE_BACK);
    }
}

void SoundManager::PlayRotate() {
    if (m_soundRotate != -1) {
        PlaySoundMem(m_soundRotate, DX_PLAYTYPE_BACK);
    }
}

void SoundManager::PlayDrop() {
    if (m_soundDrop != -1) {
        PlaySoundMem(m_soundDrop, DX_PLAYTYPE_BACK);
    }
}

void SoundManager::PlayClear() {
    if (m_soundClear != -1) {
        PlaySoundMem(m_soundClear, DX_PLAYTYPE_BACK);
    }
}

void SoundManager::PlayGameover() {
    if (m_soundGameover != -1) {
        PlaySoundMem(m_soundGameover, DX_PLAYTYPE_BACK);
    }
}