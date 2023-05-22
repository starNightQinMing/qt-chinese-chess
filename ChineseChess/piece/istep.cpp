#include "istep.h"

#include "iglobal.h"

IStep::IStep(QObject *parent)
    : QObject(parent)
    , m_originalPos(QPoint(-1, -1))
    , m_newPos(QPoint(-1, -1))
    , m_isExecuted(false)
    , m_isRevoked(false)
    , m_pCurrentPiece(nullptr)
    , m_pKillPiece(nullptr)
{

}

QPoint IStep::originalPos() const
{
    return m_originalPos;
}

void IStep::setOriginalPos(const QPoint &originalPos)
{
    m_originalPos = originalPos;
}

QPoint IStep::newPos() const
{
    return m_newPos;
}

void IStep::setNewPos(const QPoint &newPos)
{
    m_newPos = newPos;
}

bool IStep::isExecuted() const
{
    return m_isExecuted;
}

void IStep::setIsExecuted(bool isExecuted)
{
    m_isExecuted = isExecuted;
}

bool IStep::isRevoked() const
{
    return m_isRevoked;
}

void IStep::setIsRevoked(bool isRevoked)
{
    m_isRevoked = isRevoked;
}

IPiece *IStep::currentPiece() const
{
    return m_pCurrentPiece;
}

void IStep::setCurrentPiece(IPiece *pCurrentPiece)
{
    m_pCurrentPiece = pCurrentPiece;
}

IPiece *IStep::killPiece() const
{
    return m_pKillPiece;
}

void IStep::setKillPiece(IPiece *pKillPiece)
{
    m_pKillPiece = pKillPiece;
}

bool IStep::execute()
{
    if (m_pCurrentPiece == nullptr)
        return false;

    if (m_pKillPiece != nullptr)
        m_pKillPiece->setIsDead(true);

    m_pCurrentPiece->moveTo(m_newPos);
    m_isExecuted = true;
    m_isRevoked = false;
    emit executed();
    return true;
}

bool IStep::revoke()
{
    if (m_pCurrentPiece == nullptr)
        return false;

    if (m_pKillPiece != nullptr)
        m_pKillPiece->setIsDead(false);

    m_pCurrentPiece->moveTo(m_originalPos);
    m_isExecuted = false;
    m_isRevoked = true;
    emit revoked();
    return true;
}
