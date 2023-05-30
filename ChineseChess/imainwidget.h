#ifndef IMAINWIDGET_H
#define IMAINWIDGET_H

#include <QtWidgets/qwidget.h>

#include "ui/imainwidgetui.h"

class IMainWidget
        : public QWidget
        , public IMainWidgetUi
{
    Q_OBJECT

public:
    IMainWidget(QWidget *parent = nullptr);
    ~IMainWidget();

protected:
    virtual void changeEvent(QEvent *pEvent) override;
    void loadQss();
};

#endif // IMAINWIDGET_H
