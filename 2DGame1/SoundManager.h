#pragma once

#include "DxLib.h"
#include <string>
#include <unordered_map>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    // サウンドのロード
    bool LoadSounds();

    // サウンド再生
    void PlayMove();
    void PlayRotate();
    void PlayDrop();
    void PlayClear();
    void PlayGameover();

private:
    // サウンドハンドル
    int m_soundMove;
    int m_soundRotate;
    int m_soundDrop;
    int m_soundClear;
    int m_soundGameover;


    static constexpr const char* SOUND_MOVE = "sounds/move.wav";
    static constexpr const char* SOUND_ROTATE = "sounds/rotate.wav";
    static constexpr const char* SOUND_DROP = "sounds/drop.wav";
    static constexpr const char* SOUND_CLEAR = "sounds/clear.wav";
    static constexpr const char* SOUND_GAMEOVER = "sounds/gameover.wav";
};