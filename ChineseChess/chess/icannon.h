#ifndef ICANNON_H
#define ICANNON_H

#include "iabstractchess.h"

class ICannon : public IAbstractChess
{
    Q_OBJECT
public:
    explicit ICannon(QObject *parent = nullptr);
    virtual ~ICannon();

    virtual IChessType type() override;
    virtual QList<IChessStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // ICANNON_H
