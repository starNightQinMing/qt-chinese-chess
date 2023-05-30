#ifndef IANIMATIONMANAGER_H
#define IANIMATIONMANAGER_H

#include <QtCore/qobject.h>
#include <QtCore/qpropertyanimation.h>
#include <QtCore/qtimer.h>
#include <QtCore/qdebug.h>

#include <QtGui/qfontmetrics.h>

#include <QtWidgets/qlabel.h>
#include <QtWidgets/qgraphicseffect.h>
#include <QtWidgets/qapplication.h>

class IAnimationManager : public QObject
{
    Q_OBJECT

public:
    IAnimationManager(QObject *parent = Q_NULLPTR);
    ~IAnimationManager();

    void displayAnimationImage(const QString& image);
    void displayAnimationText(const QString& text);

protected slots:
    void on_propertyAnimation_finished();
    void on_animationDisplayTimer_timeout();

private:
    QLabel* m_pAnimationLabel;
    QGraphicsOpacityEffect* m_pOpacityEffect;
    QPropertyAnimation* m_pPropertyAnimation;
    QTimer* m_pAnimationDisplayTimer;
    QWidget* m_pWidgetParent;
};

#endif // IANIMATIONMANAGER_H
