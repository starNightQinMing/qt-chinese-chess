#include "isoundmanager.h"

ISoundManager::ISoundManager(QObject *parent)
    : QObject(parent)
{
}

ISoundManager::~ISoundManager()
{
}

void ISoundManager::playBackGroundSound()
{
    if (m_backGroundSoundPlayer.state() == QMediaPlayer::PlayingState)
        m_backGroundSoundPlayer.stop();

    QMediaPlaylist* playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/ChineseChess/sounds/ChineseChessBackgroundMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_backGroundSoundPlayer.setMedia(playlist);
    m_backGroundSoundPlayer.setVolume(90);

    m_backGroundSoundPlayer.play();
}

void ISoundManager::playMovePieceSound()
{
    playSound(m_otherSoundPlayer, "qrc:/ChineseChess/sounds/movePiece.mp3");
}

void ISoundManager::playSelectPieceSound()
{
    playSound(m_otherSoundPlayer, "qrc:/ChineseChess/sounds/selectPiece.mp3");
}

void ISoundManager::playEatPieceSound()
{
    playSound(m_eatSoundPlayer, "qrc:/ChineseChess/sounds/eatPiece.mp3");
}

void ISoundManager::playWinSound()
{
    playSound(m_winSoundPlayer, "qrc:/ChineseChess/sounds/fightWin.mp3");
}

void ISoundManager::playLoseSound()
{
    playSound(m_loseSoundPlayer, "qrc:/ChineseChess/sounds/fightLose.mp3");
}

void ISoundManager::playSound(QMediaPlayer& mdeiaPlayer, const QString& sound)
{
    if (mdeiaPlayer.state() == QMediaPlayer::PlayingState)
        mdeiaPlayer.stop();

    mdeiaPlayer.setMedia(QUrl(sound));
    mdeiaPlayer.setVolume(100);
    mdeiaPlayer.play();
}

