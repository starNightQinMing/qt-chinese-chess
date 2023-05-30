#ifndef IPERSONALWIDGET_H
#define IPERSONALWIDGET_H

#include <QtWidgets/qwidget.h>

#include "ui/ipersonalwidgetui.h"

#include <QtCore/qtimer.h>

class IPersonalWidget
        : public QWidget
        , public IPersonalWidgetUi
{
    Q_OBJECT
public:
    explicit IPersonalWidget(QWidget *parent = nullptr);
    virtual ~IPersonalWidget();

    void setImage(const QString& imageUrl);
    void setName(const QString& name);
    void setBureauTime(const QString& time);
    void setReflectTime(const QString& time);


public slots:
    void onTimerTimeout();
    void retime();
    void startTime();
    void stopTime();

private:
    QTimer m_timer;
};

#endif // IPERSONALWIDGET_H
