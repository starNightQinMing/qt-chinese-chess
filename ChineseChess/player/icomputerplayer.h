#ifndef ICOMPUTERPLAYER_H
#define ICOMPUTERPLAYER_H

#include "ichessplayer.h"

class IComputerPlayer : public IChessPlayer
{
    Q_OBJECT
public:
    explicit IComputerPlayer(QObject *parent = nullptr);
    virtual ~IComputerPlayer();

    virtual IPlayerType type() override;
    virtual void toActivity() override;
    virtual void endActivity() override;
    virtual void doMove() override;

signals:

private:
    //搜索引擎
};

#endif // ICOMPUTERPLAYER_H
