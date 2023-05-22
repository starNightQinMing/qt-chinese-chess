#ifndef ILOCALPLAYER_H
#define ILOCALPLAYER_H

#include "irealplayer.h"

class ILocalPlayer : public IRealPlayer
{
    Q_OBJECT
public:
    explicit ILocalPlayer(QObject *parent = nullptr);
    virtual ~ILocalPlayer();

    virtual IPlayerType type() override;
    virtual void takePiece(const QPoint& pos) override;
    virtual void doMove() override;

signals:

};

#endif // ILOCALPLAYER_H
