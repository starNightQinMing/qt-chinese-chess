#ifndef IOPERATIONWIDGET_H
#define IOPERATIONWIDGET_H

#include <QtWidgets/qwidget.h>

#include "ui/ioperationwidgetui.h"

class IOperationWidget
        : public QWidget
        , public IOperationWidgetUi
{
    Q_OBJECT
public:
    explicit IOperationWidget(QWidget *parent = nullptr);

protected:
    virtual void changeEvent(QEvent *pEvent) override;

signals:

private slots:
    void onStartButtonClicked();
    void onRestartButtonClicked();
    void onPromptButtonClicked();
    void onAdmitDefeatButtonClicked();
    void onDrawButtonClicked();
    void onHelpButtonClicked();
};

#endif // IOPERATIONWIDGET_H
