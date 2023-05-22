#include "irealplayer.h"

#include "iglobal.h"

IRealPlayer::IRealPlayer(QObject *parent)
    : IChessPlayer(parent)
{

}

IRealPlayer::~IRealPlayer()
{

}

IPlayerType IRealPlayer::type()
{
    return IPlayerType::Real;
}

void IRealPlayer::toActivity()
{
    setActivity(true);
}

void IRealPlayer::endActivity()
{
    setActivity(false);
}
