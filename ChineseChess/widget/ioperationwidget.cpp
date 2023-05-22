#include "ioperationwidget.h"

#include <QtGui/qevent.h>

IOperationWidget::IOperationWidget(QWidget *parent)
    : QWidget(parent)
    , IOperationWidgetUi()
{
    this->setupUi(this);
}

void IOperationWidget::changeEvent(QEvent *pEvent)
{
    if (pEvent->type() == QEvent::LanguageChange)
        this->retranslateUi(this);

    QWidget::changeEvent(pEvent);
}

void IOperationWidget::onStartButtonClicked()
{

}

void IOperationWidget::onRestartButtonClicked()
{

}

void IOperationWidget::onPromptButtonClicked()
{

}

void IOperationWidget::onAdmitDefeatButtonClicked()
{

}

void IOperationWidget::onDrawButtonClicked()
{

}

void IOperationWidget::onHelpButtonClicked()
{

}
