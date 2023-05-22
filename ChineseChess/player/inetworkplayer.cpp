#include "inetworkplayer.h"

#include "iglobal.h"

INetworkPlayer::INetworkPlayer(QObject *parent)
    : IRealPlayer(parent)
{

}

INetworkPlayer::~INetworkPlayer()
{

}

IPlayerType INetworkPlayer::type()
{
    return IPlayerType::Network;
}

void INetworkPlayer::doMove()
{
    IStep* pStep = m_pCurrentPiece->canMoveTo(m_currentPos);
    if (pStep != nullptr)
    {
        m_stepList.append(pStep);
        pStep->execute();
        m_pCurrentPiece = nullptr;//走完一步就不记录棋子
        emit moved(pStep);
    }
}

void INetworkPlayer::doNetwork(const QPoint &startPos, const QPoint &endPos)
{
    IPiece* pOriginalPiece = IGlobal::global().findPiece(startPos);
    if (pOriginalPiece == nullptr)
        return;

    m_pCurrentPiece = pOriginalPiece;
    m_currentPos = endPos;
    doMove();
}
