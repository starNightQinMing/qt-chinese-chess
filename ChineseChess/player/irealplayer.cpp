#include "irealplayer.h"

#include "iglobal.h"

IRealPlayer::IRealPlayer(QObject *parent)
    : IChessPlayer(parent)
{

}

IRealPlayer::~IRealPlayer()
{

}

void IRealPlayer::toActivity()
{
    setActivity(true);
}

void IRealPlayer::endActivity()
{
    setActivity(false);
}
