#ifndef IKING_H
#define IKING_H

#include "ipiece.h"

class IGeneral : public IPiece
{
    Q_OBJECT
public:
    explicit IGeneral(QObject *parent = nullptr);
    virtual ~IGeneral();

    virtual IPieceType type() override;
    virtual QList<IStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // IKING_H
