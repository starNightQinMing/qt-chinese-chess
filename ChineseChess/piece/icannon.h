#ifndef ICANNON_H
#define ICANNON_H

#include "ipiece.h"

class ICannon : public IPiece
{
    Q_OBJECT
public:
    explicit ICannon(QObject *parent = nullptr);
    virtual ~ICannon();

    virtual IPieceType type() override;
    virtual QList<IStep*> allPossibleSteps() override;

protected:
    virtual bool canMove(const QPoint& newPos) override;
};

#endif // ICANNON_H
