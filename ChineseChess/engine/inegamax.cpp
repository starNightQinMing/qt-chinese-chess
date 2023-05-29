#include "inegamax.h"

INegaMax::INegaMax(QObject *parent)
    : ISearchEngine(parent)
{
}

INegaMax::~INegaMax()
{
}

qint32 INegaMax::negaMax(qint32 searchDepth, IPieceCamp currentCamp)
{
    if (searchDepth == 0)
        return calScore(currentCamp);

    qint32 currentScore = MINIMUM_VALUE;
    for (IPiece* pPiece : m_operatePieceList)
    {
        if (pPiece->camp() != currentCamp || pPiece->isDead())
            continue;

        QList<IStep*> chessStepList = pPiece->allPossibleSteps();
        while(!chessStepList.isEmpty())
        {
            m_stepCount++;
            IStep* pChessStep = chessStepList.back();
            chessStepList.removeLast();

            fakeMove(pChessStep);
            qint32 score = -negaMax(searchDepth - 1, nextCamp(currentCamp));
            unFakeMove(pChessStep);

            bool condition = score > currentScore;
            if (condition) currentScore = score;

            if (condition && searchDepth == m_searchDepth)
            {
                if (m_pBestStep) delete m_pBestStep;
                m_pBestStep = pChessStep;
            }
            else
            {
                delete pChessStep;
            }
        }
    }

    return currentScore;
}

void INegaMax::search()
{
    negaMax(m_searchDepth, m_camp);
}
