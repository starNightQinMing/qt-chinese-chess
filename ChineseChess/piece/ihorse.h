#ifndef IHORSE_H
#define IHORSE_H

#include "ipiece.h"

class IHorse : public IPiece
{
    Q_OBJECT
public:
    explicit IHorse(QObject *parent = nullptr);
    virtual ~IHorse();

    virtual IPieceType type() override;
    virtual QList<IStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // IHORSE_H
