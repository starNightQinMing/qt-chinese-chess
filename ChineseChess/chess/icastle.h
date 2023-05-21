#ifndef ICAR_H
#define ICAR_H

#include "iabstractchess.h"

class ICastle : public IAbstractChess
{
    Q_OBJECT
public:
    explicit ICastle(QObject *parent = nullptr);
    virtual ~ICastle();

    virtual IChessType type() override;
    virtual QList<IChessStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // ICAR_H
