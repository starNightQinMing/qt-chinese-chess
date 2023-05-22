#ifndef IPieceSTEP_H
#define IPieceSTEP_H

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>

class IPiece;

class IStep : public QObject
{
    Q_OBJECT
public:
    explicit IStep(QObject *parent = nullptr);

    QPoint originalPos() const;
    void setOriginalPos(const QPoint &originalPos);

    QPoint newPos() const;
    void setNewPos(const QPoint &newPos);

    bool isExecuted() const;
    void setIsExecuted(bool isExecuted);

    bool isRevoked() const;
    void setIsRevoked(bool isRevoked);

    IPiece *currentPiece() const;
    void setCurrentPiece(IPiece *pCurrentPiece);

    IPiece *killPiece() const;
    void setKillPiece(IPiece *pKillPiece);

    bool execute();
    bool revoke();

signals:
    void executed();
    void revoked();

private:
    QPoint m_originalPos;
    QPoint m_newPos;
    bool m_isExecuted;
    bool m_isRevoked;
    IPiece* m_pCurrentPiece;
    IPiece* m_pKillPiece;
};

#endif // IPieceSTEP_H
