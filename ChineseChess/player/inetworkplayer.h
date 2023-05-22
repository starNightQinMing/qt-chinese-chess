#ifndef INETWORKPLAYER_H
#define INETWORKPLAYER_H

#include "irealplayer.h"

class INetworkPlayer : public IRealPlayer
{
    Q_OBJECT
public:
    explicit INetworkPlayer(QObject *parent = nullptr);
    virtual ~INetworkPlayer();

    virtual IPlayerType type() override;
    virtual void doMove() override;

public:
    void doNetwork(const QPoint& startPos, const QPoint& endPos);
};

#endif // INETWORKPLAYER_H
