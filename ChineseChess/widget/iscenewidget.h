#ifndef ISCENEWIDGET_H
#define ISCENEWIDGET_H

#include <QtWidgets/qwidget.h>

#include "ui/iscenewidgetui.h"

class IPiece;
class IStep;
enum class IPieceCamp;
class IChessPlayer;
class IAnimationManager;
class ISoundManager;

class ISceneWidget
        : public QWidget
        , public ISceneWidgetUi
{
    Q_OBJECT
public:
    explicit ISceneWidget(QWidget *parent = nullptr);
    virtual ~ISceneWidget();

protected:
    virtual void changeEvent(QEvent *pEvent) override;
    void initManager();
    void initPlayer();
    void gameOver();
    void fightOverHandle(const IPieceCamp& camp);

signals:

private slots:
    void onBoardWidgetPosClicked(const QPoint& pos);
    void onStartButtonClicked();
    void onRestartButtonClicked();
    void onPauseButtonClicked();
    void onEndButtonClicked();
    void onQuitButtonClicked();
    void onAboutButtonClicked();
    void onHelpButtonClicked();
    void onRepentanceButtonClicked();
    void onRequestButtonClicked();
    void onAdmitDefeatButtonClicked();
    void onPromptButtonClicked();
    void onChessPlayerPieceTook(IPiece* pPiece);
    void onChessPlayerMoved(IStep* pStep);
    void onChessPlayerAdmitDefeat();

private:
    ISoundManager* m_pSoundManager;//音效管理
    IAnimationManager* m_pAnimationManager;//提示管理
    IChessPlayer* m_pBlackPlayer;//黑方棋手
    IChessPlayer* m_pRedPlayer;//红方棋手
    IChessPlayer* m_pCurrentPlayer;//当前棋手
    bool m_beginFight;//开始对战
    bool m_pauseFight;//暂停对战
    bool m_fightOver;//对战结束
};

#endif // ISCENEWIDGET_H
