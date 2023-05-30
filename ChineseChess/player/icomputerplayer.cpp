#include "icomputerplayer.h"

#include "engine/ialphabeta.h"
#include "engine/iaspirationsearch.h"
#include "engine/ifailsoftalphabeta.h"
#include "engine/iminimax.h"
#include "engine/iminiwindowsearch.h"
#include "engine/inegamax.h"

#include "iglobal.h"

#include <QtCore/qthread.h>

IComputerPlayer::IComputerPlayer(QObject *parent)
    : IChessPlayer(parent)
{
    m_camp = IPieceCamp::Black;
    m_pSearchEngine = new IAlphaBeta();
    m_pSearchEngine->setSearchDepth(5);
    m_pSearchEngine->setCamp(m_camp);

    QObject::connect(this, &IComputerPlayer::needSearch
                     , m_pSearchEngine, &ISearchEngine::startSearch);
    QObject::connect(m_pSearchEngine, &ISearchEngine::searchEnd
                     , this, &IComputerPlayer::onSearchEngineSearchEnd);

    m_pEngineThread = new QThread();
    m_pSearchEngine->moveToThread(m_pEngineThread);
    m_pEngineThread->start();
}

IComputerPlayer::~IComputerPlayer()
{
    delete m_pSearchEngine;

    if (m_pEngineThread->isRunning())
        m_pEngineThread->terminate();
    delete m_pEngineThread;
}

IPlayerType IComputerPlayer::type()
{
    return IPlayerType::Computer;
}

void IComputerPlayer::toActivity()
{
    setActivity(true);
    emit needSearch();
}

void IComputerPlayer::endActivity()
{
    setActivity(false);
    //查看搜索引擎情况
}

void IComputerPlayer::doMove()
{
    //使用搜索引擎
    IStep* pStep = m_pSearchEngine->bestStep();
    if (pStep == nullptr)
    {
        emit admitDefeat();
        return;
    }

    m_stepList.append(pStep);
    pStep->execute();
    m_pCurrentPiece = nullptr;//走完一步就不记录棋子
    emit moved(pStep);
}

ISearchEngine *IComputerPlayer::searchEngine() const
{
    return m_pSearchEngine;
}

void IComputerPlayer::setSearchEngine(ISearchEngine *pSearchEngine)
{
    m_pSearchEngine = pSearchEngine;
}

void IComputerPlayer::onSearchEngineSearchEnd()
{
    doMove();
}
