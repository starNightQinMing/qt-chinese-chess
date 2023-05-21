#include "ichessstep.h"

#include "iglobal.h"

IChessStep::IChessStep(QObject *parent)
    : QObject(parent)
    , m_originalPos(QPoint(-1, -1))
    , m_newPos(QPoint(-1, -1))
    , m_isExecuted(false)
    , m_isRevoked(false)
    , m_pCurrentChess(nullptr)
    , m_pKillChess(nullptr)
{

}

QPoint IChessStep::originalPos() const
{
    return m_originalPos;
}

void IChessStep::setOriginalPos(const QPoint &originalPos)
{
    m_originalPos = originalPos;
}

QPoint IChessStep::newPos() const
{
    return m_newPos;
}

void IChessStep::setNewPos(const QPoint &newPos)
{
    m_newPos = newPos;
}

bool IChessStep::isExecuted() const
{
    return m_isExecuted;
}

void IChessStep::setIsExecuted(bool isExecuted)
{
    m_isExecuted = isExecuted;
}

bool IChessStep::isRevoked() const
{
    return m_isRevoked;
}

void IChessStep::setIsRevoked(bool isRevoked)
{
    m_isRevoked = isRevoked;
}

IAbstractChess *IChessStep::currentChess() const
{
    return m_pCurrentChess;
}

void IChessStep::setCurrentChess(IAbstractChess *pCurrentChess)
{
    m_pCurrentChess = pCurrentChess;
}

IAbstractChess *IChessStep::killChess() const
{
    return m_pKillChess;
}

void IChessStep::setKillChess(IAbstractChess *pKillChess)
{
    m_pKillChess = pKillChess;
}

bool IChessStep::execute()
{
    if (m_pCurrentChess == nullptr)
        return false;

    if (m_pKillChess != nullptr)
        m_pKillChess->setIsDead(true);

    m_pCurrentChess->moveTo(m_newPos);
    m_isExecuted = true;
    m_isRevoked = false;
    emit executed();
    return true;
}

bool IChessStep::revoke()
{
    if (m_pCurrentChess == nullptr)
        return false;

    if (m_pKillChess != nullptr)
        m_pKillChess->setIsDead(false);

    m_pCurrentChess->moveTo(m_originalPos);
    m_isExecuted = false;
    m_isRevoked = true;
    emit revoked();
    return true;
}
