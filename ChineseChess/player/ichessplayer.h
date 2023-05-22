#ifndef ICHESSPLAYER_H
#define ICHESSPLAYER_H

#include <QtCore/qobject.h>

#include "piece/ipiece.h"

enum class IPlayerType
{
    None = 0,
    Computer,
    Real,
    Local,
    Network
};

class IChessPlayer : public QObject
{
    Q_OBJECT
public:
    explicit IChessPlayer(QObject *parent = nullptr);
    virtual ~IChessPlayer();

    IPieceCamp camp() const;
    void setCamp(const IPieceCamp &camp);

    bool activity() const;
    void setActivity(bool activity);

    IPiece *pCurrentPiece() const;
    void setPCurrentPiece(IPiece *pCurrentPiece);

    QPoint currentPos() const;
    void setCurrentPos(const QPoint &currentPos);

    QList<IStep *> stepList() const;
    void setStepList(const QList<IStep *> &stepList);

    virtual void takePiece(const QPoint& pos);
    virtual IPlayerType type() = 0;
    virtual void toActivity() = 0;
    virtual void endActivity() = 0;
    virtual void doMove() = 0;

signals:
    void moved(IStep* pStep);
    void pieceTook(IPiece* pPiece);

protected:
    IPieceCamp m_camp;
    bool m_activity;
    IPiece* m_pCurrentPiece;
    QPoint m_currentPos;
    QList<IStep*> m_stepList;

};

#endif // ICHESSPLAYER_H
