#ifndef ICOMPUTERPLAYER_H
#define ICOMPUTERPLAYER_H

#include "ichessplayer.h"

class ISearchEngine;
class QThread;

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
    void needSearch();

private slots:
    void onSearchEngineSearchEnd();

private:
    //搜索引擎
    ISearchEngine* m_pSearchEngine;
    QThread* m_pEngineThread;
};

#endif // ICOMPUTERPLAYER_H
