#ifndef ISOUNDMANAGER_H
#define ISOUNDMANAGER_H

#include <QtCore/qobject.h>

#include <QtMultimedia/qmediaplayer.h>
#include <QtMultimedia/qmediaplaylist.h>

class ISoundManager : public QObject
{
    Q_OBJECT

public:
    ISoundManager(QObject *parent = Q_NULLPTR);
    ~ISoundManager();

public slots:
    void playBackGroundSound();
    void playMovePieceSound();
    void playSelectPieceSound();
    void playEatPieceSound();
    void playWinSound();
    void playLoseSound();

    void playSound(QMediaPlayer& mdeiaPlayer, const QString& sound);

private:
    QMediaPlayer m_backGroundSoundPlayer;
    QMediaPlayer m_eatSoundPlayer;
    QMediaPlayer m_otherSoundPlayer;
    QMediaPlayer m_winSoundPlayer;
    QMediaPlayer m_loseSoundPlayer;
};

#endif // ISOUNDMANAGER_H
