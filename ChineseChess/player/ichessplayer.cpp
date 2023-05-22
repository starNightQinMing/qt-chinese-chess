#include "ichessplayer.h"

IChessPlayer::IChessPlayer(QObject *parent)
    : QObject(parent)
    , m_camp(IPieceCamp::None)
    , m_activity(false)
    , m_pCurrentPiece(nullptr)
    , m_currentPos(QPoint(-1, -1))
{

}

IChessPlayer::~IChessPlayer()
{

}

IPieceCamp IChessPlayer::camp() const
{
    return m_camp;
}

void IChessPlayer::setCamp(const IPieceCamp &camp)
{
    m_camp = camp;
}

bool IChessPlayer::activity() const
{
    return m_activity;
}

void IChessPlayer::setActivity(bool activity)
{
    m_activity = activity;
}

IPiece *IChessPlayer::pCurrentPiece() const
{
    return m_pCurrentPiece;
}

void IChessPlayer::setPCurrentPiece(IPiece *pCurrentPiece)
{
    m_pCurrentPiece = pCurrentPiece;
}

QPoint IChessPlayer::currentPos() const
{
    return m_currentPos;
}

void IChessPlayer::setCurrentPos(const QPoint &currentPos)
{
    m_currentPos = currentPos;
}

QList<IStep *> IChessPlayer::stepList() const
{
    return m_stepList;
}

void IChessPlayer::setStepList(const QList<IStep *> &stepList)
{
    m_stepList = stepList;
}

void IChessPlayer::takePiece(const QPoint &pos)
{
    Q_UNUSED(pos);
}
