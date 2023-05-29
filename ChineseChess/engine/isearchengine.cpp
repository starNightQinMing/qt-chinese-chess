#include "isearchengine.h"

#include "iglobal.h"

#include <QtCore/qdebug.h>
#include <QtCore/qdatetime.h>

ISearchEngine::ISearchEngine(QObject *parent)
    : QObject(parent)
    , m_searchDepth(DEFAULT_SEARCH_DEPTH)
    , m_camp(IPieceCamp::Black)
    , m_pBestStep(Q_NULLPTR)
    , m_pCheckGeneralStep(Q_NULLPTR)
    , m_stepCount(0)
    , m_firstStep(true)
{
}

ISearchEngine::~ISearchEngine()
{
}

void ISearchEngine::setSearchDepth(const qint32& searchDepth)
{
    m_searchDepth = searchDepth;
}

qint32 ISearchEngine::searchDepth() const
{
    return m_searchDepth;
}

void ISearchEngine::setCamp(IPieceCamp camp)
{
    m_camp = camp;
}

IPieceCamp ISearchEngine::camp() const
{
    return m_camp;
}

void ISearchEngine::setBestStep(IStep* pBestStep)
{
    m_pBestStep = pBestStep;
}

IStep* ISearchEngine::bestStep()
{
    return m_pBestStep;
}

void ISearchEngine::setOperatePieceList(QList<IPiece*>& pieceList)
{
    m_operatePieceList = pieceList;
}

QList<IPiece*>& ISearchEngine::operatePieceList()
{
    return m_operatePieceList;
}

void ISearchEngine::setStepCount(const quint64& count)
{
    m_stepCount = count;
}

quint64 ISearchEngine::stepCount() const
{
    return m_stepCount;
}

void ISearchEngine::setFirstStep(bool firstStep)
{
    m_firstStep = firstStep;
}

bool ISearchEngine::firstStep() const
{
    return m_firstStep;
}

bool ISearchEngine::fightOver()
{
    IPiece* pRedGeneral = IGlobal::global().findPiece(IPieceType::General, IPieceCamp::Red);
    if (pRedGeneral == nullptr)
        return true;

    IPiece* pBlackGeneral = IGlobal::global().findPiece(IPieceType::General, IPieceCamp::Black);
    if (pBlackGeneral == nullptr)
        return true;

    return false;
}

IStep* ISearchEngine::bestStep(const QList<IPiece*>& pieceList)
{
    m_stepCount = 0;
    m_operatePieceList = pieceList;
    m_pBestStep = Q_NULLPTR;
    m_pCheckGeneralStep = Q_NULLPTR;
    QTime startTime = QTime::currentTime();
    if (!checkEnemyGeneral()) search();//如果敌方已被将军，便不再判断，直接击杀
    QTime endTime = QTime::currentTime();
    qDebug() << startTime.msecsTo(endTime) << "ms, " << m_stepCount << "步";
    return m_pBestStep;
}

qint32 ISearchEngine::calScore(IPieceCamp camp)
{
    //车 马 相 士 将 炮 兵
    //车9分、炮4分半、马4分、过河兵2分、未过河兵1分、相2分、仕2分。
    qint32 chessScore[7] = { 90, 40, 10, 10, 2000, 50, 10 };//2520
    qint32 blackScore = 0;
    qint32 redScore = 0;
    for (IPiece* pPiece : m_operatePieceList)
    {
        if (pPiece->isDead())
        {
            if (pPiece->type() == IPieceType::General)
            {
                if (pPiece->camp() == IPieceCamp::Black)
                {
                    redScore = MAXIMUM_VALUE;
                    blackScore = MINIMUM_VALUE;
                }
                else
                {
                    redScore = MINIMUM_VALUE;
                    blackScore = MAXIMUM_VALUE;
                }
                break;
            }
            else
                continue;
        }

        /*QList<PieceStep*> chessStepList = pChess->allPossibleSteps(m_operatePieceList);
        for (PieceStep* pChessStep : chessStepList)
        {
            Piece* pKillChess = pChessStep->killChess();
            if (pKillChess != Q_NULLPTR)
            {
                if (pKillChess->camp() == PieceCamp::Black)
                    blackScore += -10;
                else
                    redScore += -10;
            }
            delete pChessStep;
        }*/

        if (pPiece->camp() == IPieceCamp::Black)
            blackScore += chessScore[qint32(pPiece->type())];// +chessStepList.count() * 2;
        else
            redScore += chessScore[qint32(pPiece->type())];// +chessStepList.count() * 2;
    }

    qint32 situationScore = (camp == IPieceCamp::Black) ? blackScore - redScore : redScore - blackScore;

    return situationScore;
}

void ISearchEngine::fakeMove(IStep* pStep)
{
    pStep->execute();
}

void ISearchEngine::unFakeMove(IStep* pStep)
{
    pStep->revoke();
}

IPieceCamp ISearchEngine::nextCamp(const IPieceCamp& currentCamp)
{
    IPieceCamp nextCamp = IPieceCamp::Black;
    if (currentCamp == IPieceCamp::Black)
    {
        nextCamp = IPieceCamp::Red;
    }

    return nextCamp;
}

bool ISearchEngine::checkEnemyGeneral()
{
    //获取敌方将军（元帅）的位置
    IPieceCamp enemyCamp = this->nextCamp(m_camp);
    IPiece* pEnemyGeneral = IGlobal::global().findPiece(IPieceType::General, enemyCamp);
    QPoint enemyGeneralPos = pEnemyGeneral->pos();

    //获取敌方所有棋子的初始位置和结束位置（是相连着的）
    quint8 beginIndex = IGlobal::global().campBeginIndex(enemyCamp);
    quint8 endIndex = IGlobal::global().campEndIndex(enemyCamp);

    //检查
    return checkGeneral(enemyGeneralPos, beginIndex, endIndex, true);
}

bool ISearchEngine::checkSelfGeneral()
{
    //获取己方将军（元帅）的位置
    IPieceCamp selfCamp = m_camp;
    IPiece* pSelefGeneral = IGlobal::global().findPiece(IPieceType::General, selfCamp);
    QPoint selfGeneralPos = pSelefGeneral->pos();

    //获取己方所有棋子的初始位置和结束位置（是相连着的）
    quint8 beginIndex = IGlobal::global().campBeginIndex(selfCamp);
    quint8 endIndex = IGlobal::global().campEndIndex(selfCamp);

    //检查
    return checkGeneral(selfGeneralPos, beginIndex, endIndex);
}

bool ISearchEngine::checkCampGeneral(const IPieceCamp &camp)
{
    //获取将军（元帅）的位置
    IPiece* pGeneral = IGlobal::global().findPiece(IPieceType::General, camp);
    QPoint generalPos = pGeneral->pos();

    //获取所有棋子的初始位置和结束位置（是相连着的）
    quint8 beginIndex = IGlobal::global().campBeginIndex(camp);
    quint8 endIndex = IGlobal::global().campEndIndex(camp);

    //检查
    return checkGeneral(generalPos, beginIndex, endIndex);
}

bool ISearchEngine::checkGeneral(const QPoint& enemyGeneralPos, quint8 beginIndex, quint8 endIndex, bool need)
{
    IStep* pStep = Q_NULLPTR;
    for (quint8 index(beginIndex); index <= endIndex; index++)
    {
        if(m_operatePieceList[index]->isDead()) continue;

        pStep = m_operatePieceList[index]->canMoveTo(enemyGeneralPos);
        if(pStep != Q_NULLPTR)
        {
            if (need)
                m_pBestStep = pStep;
            else
                delete pStep;

            return true;
        }
    }

    return false;
}

IStep* ISearchEngine::escapeCheck(QList<IPiece*>& pieceList)
{
    for (qint8 index(14); index >= 0; index--)
    {
        if (pieceList[index]->isDead()) continue;

        QList<IStep*> stepList = pieceList[index]->allPossibleSteps();
        while (!stepList.isEmpty())
        {
            IStep* pStep = stepList.back();
            stepList.removeLast();
            fakeMove(pStep);
            if (!checkSelfGeneral())
            {
                unFakeMove(pStep);
                while (!stepList.isEmpty())
                {
                    IStep* pPieceStep2 = stepList.back();
                    stepList.removeLast();
                    delete pPieceStep2;
                    pPieceStep2 = Q_NULLPTR;
                }
                return pStep;
            }
            unFakeMove(pStep);
            delete pStep;
            pStep = Q_NULLPTR;
        }
    }

    QList<IStep*> stepList = pieceList[15]->allPossibleSteps();
    while (!stepList.isEmpty())
    {
        IStep* pPieceStep = stepList.back();
        stepList.removeLast();
        fakeMove(pPieceStep);
        if (!checkSelfGeneral())
        {
            unFakeMove(pPieceStep);
            while (!stepList.isEmpty())
            {
                IStep* pPieceStep2 = stepList.back();
                stepList.removeLast();
                delete pPieceStep2;
                pPieceStep2 = Q_NULLPTR;
            }
            return pPieceStep;
        }
        unFakeMove(pPieceStep);
        delete pPieceStep;
        pPieceStep = Q_NULLPTR;
    }

    return Q_NULLPTR;
}

void ISearchEngine::getFirstStep()
{
    m_firstStep = false;
    if(IGlobal::global().findPiece(IPieceType::Cannon, IPieceCamp::Red)->pos() == QPoint(4, 7)
            || IGlobal::global().findPiece(IPieceType::Cannon, IPieceCamp::Red)->pos() == QPoint(4, 7))
    {
        IPiece* pPiece = IGlobal::global().findPiece(IPieceType::Horse, IPieceCamp::Black);
        m_pBestStep = pPiece->canMoveTo(QPoint(2, 2));
        return;
    }

    quint8 index = 16;
    do {
        qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
        index = qrand() % 16;
        if(index < 2 || index == 6 || index == 8 || index == 10 || index == 11)
            index = 16;
    } while(index == 16);

    IPiece* pPiece = m_operatePieceList[index];
    if (pPiece->type() == IPieceType::Horse)
    {
        //左边的马
        if (pPiece->pos().x() == 1)
        {
            m_pBestStep = pPiece->canMoveTo(QPoint(2, 2));
            return;
        }

        //右边的马
        m_pBestStep = pPiece->canMoveTo(QPoint(6, 2));
        return;
    }

    //炮
    if (pPiece->type() == IPieceType::Cannon)
    {
        m_pBestStep = pPiece->canMoveTo(QPoint(4, 2));
        return;
    }

    //象
    if (pPiece->type() == IPieceType::Elephant)
    {
        m_pBestStep = pPiece->canMoveTo(QPoint(4, 2));
        return;
    }

    //士
    if (pPiece->type() == IPieceType::Guard)
    {
        m_pBestStep = pPiece->canMoveTo(QPoint(4, 1));
        return;
    }

    //兵
    if (pPiece->type() == IPieceType::Soldier)
    {
        m_pBestStep = pPiece->canMoveTo(QPoint(pPiece->x(), pPiece->y() + 1));
        return;
    }
}

