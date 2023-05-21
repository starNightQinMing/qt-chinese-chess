#include "ichessfactory.h"

IChessFactory::IChessFactory(QObject *parent)
    : QObject(parent)
{

}

IAbstractChess *IChessFactory::createChess(const IChessType &type)
{
    switch (type) {
    case IChessType::Empty:
        return nullptr;
    case IChessType::Guard:
        return new IGuard();
    case IChessType::Horse:
        return new IHorse();
    case IChessType::Cannon:
        return new ICannon();
    case IChessType::Castle:
        return new ICastle();
    case IChessType::General:
        return new IGeneral();
    case IChessType::Soldier:
        return new ISoldier();
    case IChessType::Elephant:
        return new IElephant();
    default:
        return nullptr;
    }
}

IAbstractChess *IChessFactory::createCannon()
{
    return new ICannon();
}

IAbstractChess *IChessFactory::createCastle()
{
    return new ICastle();
}

IAbstractChess *IChessFactory::createElephant()
{
    return new IElephant();
}

IAbstractChess *IChessFactory::createGeneral()
{
    return new IGeneral();
}

IAbstractChess *IChessFactory::createGuard()
{
    return new IGuard();
}

IAbstractChess *IChessFactory::createHorse()
{
    return new IHorse();
}

IAbstractChess *IChessFactory::createSoldier()
{
    return new ISoldier();
}
