#ifndef IGLOBAL_H
#define IGLOBAL_H

#include <QtCore/qobject.h>
#include <QtCore/qrect.h>

#include "chess/iabstractchess.h"

class IGlobal : public QObject
{
    Q_OBJECT
public:
    static IGlobal& global();
    void reset();

    QList<IAbstractChess*> chessList() const;
    IAbstractChess* findChess(const IChessType& type, const IChessCamp& camp) const;
    IAbstractChess* findChess(const QPoint& pos) const;
    QRect bordRange() const;
    QRect chessCampRange(const IChessCamp& camp) const;
    QRect chessCampJiuGongGeRange(const IChessCamp& camp) const;

private:
    explicit IGlobal(QObject *parent = nullptr);
    void initPos();
    void initChess();

signals:

private:
    QList<QPoint> m_blackPosList;
    QList<QPoint> m_redPosList;
    QList<IAbstractChess*> m_chessList;
};

#endif // IGLOBAL_H
