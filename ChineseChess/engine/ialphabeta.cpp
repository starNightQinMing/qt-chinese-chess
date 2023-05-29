#include "ialphabeta.h"

#include <QtCore/qdebug.h>

IAlphaBeta::IAlphaBeta(QObject *parent)
    : ISearchEngine(parent)
{
}

IAlphaBeta::~IAlphaBeta()
{
}

qint32 IAlphaBeta::alphaBeta(qint32 searchDepth, qint32 alpha, qint32 beta)
{
    //bool first = true;
    IStep* pStep = Q_NULLPTR;
    qint32 score(0);
    quint8 pieceStepCount(0);
    QList<IStep*> stepList;
    for (quint8 index(0);index < 16;index++)
    {
        if (m_operatePieceList[index]->isDead()) continue;

        stepList = m_operatePieceList[index]->allPossibleSteps();
        pieceStepCount = stepList.count();
        while (pieceStepCount--)
        {
            m_stepCount++;
            pStep = stepList[pieceStepCount];
            fakeMove(pStep);
            if (checkSelfGeneral())
            {
                unFakeMove(pStep);
                delete pStep;
                continue;
            }
            score = -this->beta(searchDepth - 1, -beta, -alpha);
            unFakeMove(pStep);

            if (score > alpha)
            {
                alpha = score;
                if (m_pBestStep != Q_NULLPTR) delete m_pBestStep;
                m_pBestStep = pStep;
            }
            else
            {
                delete pStep;
                pStep = Q_NULLPTR;
            }

            if (score >= beta)
            {
                while (pieceStepCount--)
                {
                    delete stepList[pieceStepCount];
                }
                stepList.clear();
                return score;
            }

        }
        stepList.clear();
    }

    return alpha;
}

qint32 IAlphaBeta::alpha(qint32 searchDepth, qint32 alpha, qint32 beta)
{
    if (searchDepth == 0 || fightOver())
        return calScore(m_camp);

    IStep* pStep = Q_NULLPTR;
    qint32 score(0);
    for(quint8 index(0);index < 16;index++)
    {
        if (m_operatePieceList[index]->isDead()) continue;

        QList<IStep*> chessStepList = m_operatePieceList[index]->allPossibleSteps();
        while (!chessStepList.isEmpty())
        {
            pStep = chessStepList.back();
            chessStepList.removeLast();

            fakeMove(pStep);
//            if (checkSelfGeneral())
//            {
//                unFakeMove(pStep);
//                delete pStep;
//                pStep = Q_NULLPTR;
//                continue;
//            }
            m_stepCount++;
            score = -this->beta(searchDepth - 1, -beta, -alpha);
            unFakeMove(pStep);

            delete pStep;
            pStep = Q_NULLPTR;

            if (score > alpha) alpha = score;

            if (score >= beta)
            {
                while (!chessStepList.isEmpty())
                {
                    pStep = chessStepList.back();
                    chessStepList.removeLast();
                    delete pStep;
                }
                return score;
            }
        }
    }

    return alpha;
}

qint32 IAlphaBeta::beta(qint32 searchDepth, qint32 alpha, qint32 beta)
{
    if (searchDepth == 0 || fightOver())
        return calScore(IPieceCamp::Red);

    IStep* pStep = Q_NULLPTR;
    qint32 score(0);
    for(quint8 index(16);index < 32;index++)
    {
        if (m_operatePieceList[index]->isDead()) continue;

        QList<IStep*> chessStepList = m_operatePieceList[index]->allPossibleSteps();
        while (!chessStepList.isEmpty())
        {
            pStep = chessStepList.back();
            chessStepList.removeLast();

            fakeMove(pStep);
//            if (checkCampGeneral(Camp::Red))
//            {
//                unFakeMove(pStep);
//                delete pStep;
//                pStep = Q_NULLPTR;
//                continue;
//            }
            m_stepCount++;
            score = -this->alpha(searchDepth - 1, -beta, -alpha);
            unFakeMove(pStep);

            delete pStep;
            pStep = Q_NULLPTR;

            if (score > alpha) alpha = score;

            if (score >= beta)
            {
                while (!chessStepList.isEmpty())
                {
                    pStep = chessStepList.back();
                    chessStepList.removeLast();
                    delete pStep;
                }
                return score;
            }
        }
    }

    return alpha;
}

void IAlphaBeta::search()
{
    alphaBeta(m_searchDepth, MINIMUM_VALUE, MAXIMUM_VALUE);
}
