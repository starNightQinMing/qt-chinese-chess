#ifndef ISOLDIER_H
#define ISOLDIER_H

#include "ipiece.h"

class ISoldier : public IPiece
{
    Q_OBJECT
public:
    explicit ISoldier(QObject *parent = nullptr);
    virtual ~ISoldier();

    virtual IPieceType type() override;
    virtual QList<IStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // ISOLDIER_H
