#include "imainwidget.h"

#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>

#include <QtGui/qevent.h>

IMainWidget::IMainWidget(QWidget *parent)
    : QWidget(parent)
    , IMainWidgetUi()
{
    this->setupUi(this);
    this->loadQss();
}

IMainWidget::~IMainWidget()
{
}

void IMainWidget::changeEvent(QEvent *pEvent)
{
    if (pEvent->type() == QEvent::LanguageChange)
        this->retranslateUi(this);

    QWidget::changeEvent(pEvent);
}

void IMainWidget::loadQss()
{
    //:/ChineseChess/qss/imainwidget.qss
    QFile file(":/ChineseChess/qss/imainwidget.qss");
    QString stylesheet;
    if (file.open(QFile::ReadOnly))
    {
        qDebug() << "dd";
        stylesheet = file.readAll();
    }
    this->setStyleSheet(stylesheet);
    file.close();
}

