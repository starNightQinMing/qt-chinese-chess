#include "iscenewidget.h"

#include <QtGui/qevent.h>

#include <QtCore/qdebug.h>

#include "iboardwidget.h"

#include "iglobal.h"
#include "player/icomputerplayer.h"
#include "player/ilocalplayer.h"
#include "player/inetworkplayer.h"

ISceneWidget::ISceneWidget(QWidget *parent)
    : QWidget(parent)
    , ISceneWidgetUi()
    , m_pBlackPlayer(nullptr)
    , m_pRedPlayer(nullptr)
    , m_pCurrentPlayer(nullptr)
{
    this->setupUi(this);
    this->initPlayer();
}

ISceneWidget::~ISceneWidget()
{
    I_RELEASE(m_pBlackPlayer);
    I_RELEASE(m_pRedPlayer);
}

void ISceneWidget::changeEvent(QEvent *pEvent)
{
    if (pEvent->type() == QEvent::LanguageChange)
        this->retranslateUi(this);

    QWidget::changeEvent(pEvent);
}

void ISceneWidget::initPlayer()
{
    m_pBlackPlayer = new ILocalPlayer();
    m_pBlackPlayer->setCamp(IPieceCamp::Black);
    QWidget::connect(m_pBlackPlayer, &IChessPlayer::pieceTook,
                     this, &ISceneWidget::onChessPlayerPieceTook);
    QWidget::connect(m_pBlackPlayer, &IChessPlayer::moved,
                     this, &ISceneWidget::onChessPlayerMoved);

    m_pRedPlayer = new ILocalPlayer();
    m_pRedPlayer->setCamp(IPieceCamp::Red);
    QWidget::connect(m_pRedPlayer, &IChessPlayer::pieceTook,
                     this, &ISceneWidget::onChessPlayerPieceTook);
    QWidget::connect(m_pRedPlayer, &IChessPlayer::moved,
                     this, &ISceneWidget::onChessPlayerMoved);

    m_pCurrentPlayer = m_pRedPlayer;
}

void ISceneWidget::onBoardWidgetPosClicked(const QPoint &pos)
{
    m_pCurrentPlayer->takePiece(pos);
}

void ISceneWidget::onChessPlayerPieceTook(IPiece *pPiece)
{
    m_pBoardWidget->setCurrentPiece(pPiece);
    m_pBoardWidget->setCurrentStep(nullptr);
    m_pBoardWidget->update();
}

void ISceneWidget::onChessPlayerMoved(IStep *pStep)
{
    m_pBoardWidget->setCurrentPiece(nullptr);
    m_pBoardWidget->setCurrentStep(pStep);
    m_pBoardWidget->update();
    m_pCurrentPlayer = (m_pCurrentPlayer == m_pBlackPlayer) ? m_pRedPlayer : m_pBlackPlayer;

    IPiece* pPiece = pStep->killPiece();
    if (pPiece != nullptr && pPiece->type() == IPieceType::General)
    {
        IGlobal::global().reset();
        m_pCurrentPlayer = m_pRedPlayer;
    }
}
