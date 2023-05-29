#ifndef ICOMPUTERPLAYER_H
#define ICOMPUTERPLAYER_H

#include "ichessplayer.h"

class ISearchEngine;

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

    ISearchEngine *searchEngine() const;
    void setSearchEngine(ISearchEngine *pSearchEngine);

signals:

private:
    //搜索引擎
    ISearchEngine* m_pSearchEngine;
};

#endif // ICOMPUTERPLAYER_H
