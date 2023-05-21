#ifndef ICHESSSTEP_H
#define ICHESSSTEP_H

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>

class IAbstractChess;

class IChessStep : public QObject
{
    Q_OBJECT
public:
    explicit IChessStep(QObject *parent = nullptr);

    QPoint originalPos() const;
    void setOriginalPos(const QPoint &originalPos);

    QPoint newPos() const;
    void setNewPos(const QPoint &newPos);

    bool isExecuted() const;
    void setIsExecuted(bool isExecuted);

    bool isRevoked() const;
    void setIsRevoked(bool isRevoked);

    IAbstractChess *currentChess() const;
    void setCurrentChess(IAbstractChess *pCurrentChess);

    IAbstractChess *killChess() const;
    void setKillChess(IAbstractChess *pKillChess);

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
    IAbstractChess* m_pCurrentChess;
    IAbstractChess* m_pKillChess;
};

#endif // ICHESSSTEP_H
