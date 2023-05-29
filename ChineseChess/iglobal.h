#ifndef IGLOBAL_H
#define IGLOBAL_H

#include <QtCore/qobject.h>
#include <QtCore/qrect.h>

#include "piece/ipiece.h"

class IGlobal : public QObject
{
    Q_OBJECT
public:
    static IGlobal& global();
    void reset();

    QList<IPiece*> pieceList() const;
    quint8 campBeginIndex(const IPieceCamp& camp) const;
    quint8 campEndIndex(const IPieceCamp& camp) const;
    IPiece* findPiece(const IPieceType& type, const IPieceCamp& camp) const;
    IPiece* findPiece(const QPoint& pos) const;
    QRect bordRange() const;
    QRect pieceCampRange(const IPieceCamp& camp) const;
    QRect pieceCampJiuGongGeRange(const IPieceCamp& camp) const;

private:
    explicit IGlobal(QObject *parent = nullptr);
    void initPos();
    void initPiece();

signals:

private:
    QList<QPoint> m_blackPosList;
    QList<QPoint> m_redPosList;
    QList<IPiece*> m_pieceList;
};

#endif // IGLOBAL_H
