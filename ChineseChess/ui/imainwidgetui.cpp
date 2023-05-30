#include "imainwidgetui.h"

#include <QtGui/qicon.h>

#include <QtWidgets/qboxlayout.h>

#include "widget/iscenewidget.h"

IMainWidgetUi::IMainWidgetUi()
    : IAbstractWidgetUi()
{
    m_pMainLayout = nullptr;
    m_pSceneWidget = nullptr;
}

IMainWidgetUi::~IMainWidgetUi()
{

}

bool IMainWidgetUi::instance(QWidget *pWidget)
{
    I_INSTANCE(m_pMainLayout, QHBoxLayout, nullptr);
    I_INSTANCE(m_pSceneWidget, ISceneWidget, pWidget);

    return true;
}

bool IMainWidgetUi::retranslateUi(QWidget *pWidget)
{
    if (m_pMainLayout == nullptr)
        return false;

    pWidget->setWindowTitle("中国象棋");

    return true;
}

void IMainWidgetUi::layout(QWidget *pWidget)
{
    m_pMainLayout->addWidget(m_pSceneWidget);
    pWidget->setLayout(m_pMainLayout);
}

bool IMainWidgetUi::connect(QWidget *pWidget)
{
    QMetaObject::Connection connection;
    bool result(true);

    Q_UNUSED(pWidget);

    return result;
}

void IMainWidgetUi::objectNameSetting(QWidget *pWidget)
{
    m_pMainLayout->setObjectName("MainLayout");
    m_pSceneWidget->setObjectName("SceneWidget");
    pWidget->setObjectName("MainWidget");
}

bool IMainWidgetUi::decorate(QWidget *pWidget)
{
    //m_pMainLayout = nullptr;
    //m_pSceneWidget = nullptr;

    pWidget->setAttribute(Qt::WA_StyledBackground);
    pWidget->setWindowIcon(QIcon(":/ChineseChess/images/ChineseChessIcon.png"));

    return true;
}

void IMainWidgetUi::release()
{
    I_RELEASE(m_pMainLayout);
    I_RELEASE(m_pSceneWidget);
}
