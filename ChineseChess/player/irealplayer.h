#ifndef IREALPLAYER_H
#define IREALPLAYER_H

#include "ichessplayer.h"

class IRealPlayer : public IChessPlayer
{
    Q_OBJECT
public:
    explicit IRealPlayer(QObject *parent = nullptr);
    virtual ~IRealPlayer();

    virtual IPlayerType type() override;
    virtual void toActivity() override;
    virtual void endActivity() override;

private:

};

#endif // IREALPLAYER_H
