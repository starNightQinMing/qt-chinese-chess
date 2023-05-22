#ifndef IGUARD_H
#define IGUARD_H

#include "ipiece.h"

class IGuard : public IPiece
{
    Q_OBJECT
public:
    explicit IGuard(QObject *parent = nullptr);
    virtual ~IGuard();

    virtual IPieceType type() override;
    virtual QList<IStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // IGUARD_H
