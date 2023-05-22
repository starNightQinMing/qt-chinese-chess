#include "icomputerplayer.h"

IComputerPlayer::IComputerPlayer(QObject *parent)
    : IChessPlayer(parent)
{

}

IComputerPlayer::~IComputerPlayer()
{

}

IPlayerType IComputerPlayer::type()
{
    return IPlayerType::Computer;
}

void IComputerPlayer::toActivity()
{
    setActivity(true);
    doMove();
}

void IComputerPlayer::endActivity()
{
    setActivity(false);
    //查看搜索引擎情况
}

void IComputerPlayer::doMove()
{
    //使用搜索引擎

}
