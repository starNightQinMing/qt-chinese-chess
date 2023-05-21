#ifndef IKING_H
#define IKING_H

#include "iabstractchess.h"

class IGeneral : public IAbstractChess
{
    Q_OBJECT
public:
    explicit IGeneral(QObject *parent = nullptr);
    virtual ~IGeneral();

    virtual IChessType type() override;
    virtual QList<IChessStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // IKING_H
