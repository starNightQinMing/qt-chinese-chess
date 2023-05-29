#include "icomputerplayer.h"

#include "engine/ialphabeta.h"
#include "engine/iaspirationsearch.h"
#include "engine/ifailsoftalphabeta.h"
#include "engine/iminimax.h"
#include "engine/iminiwindowsearch.h"
#include "engine/inegamax.h"

#include "iglobal.h"

IComputerPlayer::IComputerPlayer(QObject *parent)
    : IChessPlayer(parent)
{
    m_camp = IPieceCamp::Black;
    m_pSearchEngine = new IAlphaBeta();
    m_pSearchEngine->setSearchDepth(4);
}

IComputerPlayer::~IComputerPlayer()
{
    delete m_pSearchEngine;
}

IPlayerType IComputerPlayer::type()
{
    return IPlayerType::Computer;
}

void IComputerPlayer::toActivity()
{
    setActivity(true);
    //
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
    IStep* pStep = m_pSearchEngine->bestStep(IGlobal::global().pieceList());
    if (pStep != nullptr)
    {
        m_stepList.append(pStep);
        pStep->execute();
        m_pCurrentPiece = nullptr;//走完一步就不记录棋子
        emit moved(pStep);
    }
}

ISearchEngine *IComputerPlayer::searchEngine() const
{
    return m_pSearchEngine;
}

void IComputerPlayer::setSearchEngine(ISearchEngine *pSearchEngine)
{
    m_pSearchEngine = pSearchEngine;
}
