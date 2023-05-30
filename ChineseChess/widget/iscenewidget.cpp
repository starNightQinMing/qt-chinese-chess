#include "iscenewidget.h"

#include <QtGui/qevent.h>

#include <QtCore/qdebug.h>

#include <QtWidgets/qpushbutton.h>

#include "iboardwidget.h"

#include "iglobal.h"
#include "player/icomputerplayer.h"
#include "player/ilocalplayer.h"
#include "player/inetworkplayer.h"

#include "util/ianimationmanager.h"
#include "util/isoundmanager.h"

ISceneWidget::ISceneWidget(QWidget *parent)
    : QWidget(parent)
    , ISceneWidgetUi()
    , m_pSoundManager(nullptr)
    , m_pAnimationManager(nullptr)
    , m_pBlackPlayer(nullptr)
    , m_pRedPlayer(nullptr)
    , m_pCurrentPlayer(nullptr)
    , m_beginFight(false)
    , m_pauseFight(false)
    , m_fightOver(false)
{
    this->setupUi(this);
    this->initManager();
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

void ISceneWidget::initManager()
{
    m_pSoundManager = new ISoundManager(this);
    m_pSoundManager->playBackGroundSound();
    m_pAnimationManager = new IAnimationManager(this);
}

void ISceneWidget::initPlayer()
{
    m_pBlackPlayer = new IComputerPlayer();
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
    m_pCurrentPlayer->toActivity();
}

void ISceneWidget::gameOver()
{
    IGlobal::global().reset();
    m_pCurrentPlayer = m_pRedPlayer;
    m_pBoardWidget->update();
}

void ISceneWidget::fightOverHandle(const IPieceCamp& camp)
{
    m_fightOver = true;
    if (camp == IPieceCamp::Black)
    {
        m_pSoundManager->playWinSound();
        m_pAnimationManager->displayAnimationImage(":/ChineseChess/images/redWin.png");
    }
    else
    {
        m_pSoundManager->playLoseSound();
        m_pAnimationManager->displayAnimationImage(":/ChineseChess/images/blackWin.png");
    }
}

void ISceneWidget::onBoardWidgetPosClicked(const QPoint &pos)
{
    if (!m_beginFight || m_pauseFight || m_fightOver)
    {
        m_pAnimationManager->displayAnimationText("请点击开始或者继续对战!");
        return;
    }

    m_pCurrentPlayer->takePiece(pos);
}

void ISceneWidget::onStartButtonClicked()
{
    if (m_beginFight)
    {
        m_pAnimationManager->displayAnimationText("已经开始对战！");
        return;
    }
    m_pAnimationManager->displayAnimationText("对战已经开始，谨慎行棋，稳定军心!");
    m_beginFight = true;
    //static_cast<ComputerPlayer*>(m_pBlackChessPlayer)->setSearchEngineFirstStep(true);
}

void ISceneWidget::onRestartButtonClicked()
{
    if (!m_beginFight)
    {
        m_pAnimationManager->displayAnimationText("未开始进行对战！");
        return;
    }

    onEndButtonClicked();
    //static_cast<ComputerPlayer*>(m_pBlackChessPlayer)->setSearchEngineFirstStep(true);
    m_beginFight = true;
}

void ISceneWidget::onPauseButtonClicked()
{
    if (!m_beginFight || m_fightOver)
    {
        m_pAnimationManager->displayAnimationText("未开始进行对战或对战已结束！");
        return;
    }

    if (!m_pauseFight)
        m_pPauseButton->setText("出兵再战");
    else
        m_pPauseButton->setText("鸣金收兵");

    m_pauseFight = !m_pauseFight;
}

void ISceneWidget::onEndButtonClicked()
{
    if (!m_beginFight)
    {
        m_pAnimationManager->displayAnimationText("未开始进行对战！");
        return;
    }

    m_beginFight = false;
    m_pauseFight = false;
    m_fightOver = false;
    IGlobal::global().reset();
    m_pCurrentPlayer = m_pRedPlayer;
    m_pBoardWidget->update();
}

void ISceneWidget::onQuitButtonClicked()
{
    this->close();
}

void ISceneWidget::onAboutButtonClicked()
{
    qDebug() << "将军百战死，壮士十年归";
}

void ISceneWidget::onHelpButtonClicked()
{
}

void ISceneWidget::onRepentanceButtonClicked()
{
}

void ISceneWidget::onRequestButtonClicked()
{
}

void ISceneWidget::onAdmitDefeatButtonClicked()
{
}

void ISceneWidget::onPromptButtonClicked()
{
}


void ISceneWidget::onChessPlayerPieceTook(IPiece *pPiece)
{
    m_pSoundManager->playSelectPieceSound();
    m_pBoardWidget->setCurrentPiece(pPiece);
    m_pBoardWidget->setCurrentStep(nullptr);
    m_pBoardWidget->update();
}

void ISceneWidget::onChessPlayerMoved(IStep *pStep)
{
    IPiece* pKillPiece = pStep->killPiece();
    if (pKillPiece != Q_NULLPTR)
    {
        if (pKillPiece->type() != IPieceType::General)
        {
            m_pSoundManager->playEatPieceSound();
            m_pAnimationManager->displayAnimationImage(":/ChineseChess/images/eatChess.png");
        }
        else
        {
            fightOverHandle(pKillPiece->camp());
        }
    }
    else
    {
        m_pSoundManager->playMovePieceSound();
    }

    m_pSoundManager->playMovePieceSound();
    m_pBoardWidget->setCurrentPiece(nullptr);
    m_pBoardWidget->setCurrentStep(pStep);
    m_pBoardWidget->update();
    m_pCurrentPlayer = (m_pCurrentPlayer == m_pBlackPlayer) ? m_pRedPlayer : m_pBlackPlayer;
    m_pCurrentPlayer->toActivity();
}

void ISceneWidget::onChessPlayerAdmitDefeat()
{
    //gameOver();
}
