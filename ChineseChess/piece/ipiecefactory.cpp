#include "ipiecefactory.h"

IPieceFactory::IPieceFactory(QObject *parent)
    : QObject(parent)
{

}

IPiece *IPieceFactory::createPiece(const IPieceType &type)
{
    switch (type) {
    case IPieceType::Empty:
        return nullptr;
    case IPieceType::Guard:
        return new IGuard();
    case IPieceType::Horse:
        return new IHorse();
    case IPieceType::Cannon:
        return new ICannon();
    case IPieceType::Castle:
        return new ICastle();
    case IPieceType::General:
        return new IGeneral();
    case IPieceType::Soldier:
        return new ISoldier();
    case IPieceType::Elephant:
        return new IElephant();
    default:
        return nullptr;
    }
}

IPiece *IPieceFactory::createCannon()
{
    return new ICannon();
}

IPiece *IPieceFactory::createCastle()
{
    return new ICastle();
}

IPiece *IPieceFactory::createElephant()
{
    return new IElephant();
}

IPiece *IPieceFactory::createGeneral()
{
    return new IGeneral();
}

IPiece *IPieceFactory::createGuard()
{
    return new IGuard();
}

IPiece *IPieceFactory::createHorse()
{
    return new IHorse();
}

IPiece *IPieceFactory::createSoldier()
{
    return new ISoldier();
}
