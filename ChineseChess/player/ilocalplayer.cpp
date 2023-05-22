#include "ilocalplayer.h"

#include "iglobal.h"

ILocalPlayer::ILocalPlayer(QObject *parent)
    : IRealPlayer(parent)
{

}

ILocalPlayer::~ILocalPlayer()
{

}

IPlayerType ILocalPlayer::type()
{
    return IPlayerType::Local;
}

void ILocalPlayer::takePiece(const QPoint &pos)
{
    IPiece* pPiece = IGlobal::global().findPiece(pos);
    /*处理逻辑：按照是否已经选择了一颗棋子进行处理
    */
    //如果点击的位置有棋子而且是己方棋子，则更改选择棋子
    if (pPiece != nullptr && pPiece->camp() == m_camp)
    {
        m_pCurrentPiece = pPiece;
        m_currentPos = pos;
        emit pieceTook(m_pCurrentPiece);
        return;
    }

    //如果没有选择棋子，则不处理
    if (m_pCurrentPiece == nullptr)
        return;

    //看看棋子是否可以走到该位置
    m_currentPos = pos;
    doMove();
}

void ILocalPlayer::doMove()
{
    IStep* pStep = m_pCurrentPiece->canMoveTo(m_currentPos);
    if (pStep != nullptr)
    {
        pStep->execute();
        m_pCurrentPiece = nullptr;//走完一步就不记录棋子
        emit moved(pStep);
    }
}
