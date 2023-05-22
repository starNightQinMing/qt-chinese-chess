#ifndef ISCENEWIDGET_H
#define ISCENEWIDGET_H

#include <QtWidgets/qwidget.h>

#include "ui/iscenewidgetui.h"

class IChessPlayer;
class IPiece;
class IStep;

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
    void initPlayer();

signals:

private slots:
    void onBoardWidgetPosClicked(const QPoint& pos);
    void onChessPlayerPieceTook(IPiece* pPiece);
    void onChessPlayerMoved(IStep* pStep);

private:
    IChessPlayer* m_pBlackPlayer;
    IChessPlayer* m_pRedPlayer;
    IChessPlayer* m_pCurrentPlayer;
};

#endif // ISCENEWIDGET_H
