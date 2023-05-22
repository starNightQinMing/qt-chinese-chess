#include "iscenewidgetui.h"

#include <QtWidgets/qboxlayout.h>

#include "widget/iboardwidget.h"
#include "widget/ioperationwidget.h"

ISceneWidgetUi::ISceneWidgetUi()
    : IAbstractWidgetUi()
{
    m_pMainLayout = nullptr;
    m_pBoardWidget = nullptr;
    m_pOperationWidget = nullptr;
}

ISceneWidgetUi::~ISceneWidgetUi()
{

}

bool ISceneWidgetUi::instance(QWidget *pWidget)
{
    I_INSTANCE(m_pMainLayout, QHBoxLayout, nullptr);
    I_INSTANCE(m_pBoardWidget, IBoardWidget, pWidget);
    I_INSTANCE(m_pOperationWidget, IOperationWidget, pWidget);

    return true;
}

bool ISceneWidgetUi::retranslateUi(QWidget *pWidget)
{
    if (m_pMainLayout == nullptr)
        return false;

    pWidget->setWindowTitle(QObject::tr("中国象棋"));

    return true;
}

void ISceneWidgetUi::layout(QWidget *pWidget)
{
    m_pMainLayout->addWidget(m_pBoardWidget);
    m_pMainLayout->addWidget(m_pOperationWidget);
    pWidget->setLayout(m_pMainLayout);
}

bool ISceneWidgetUi::connect(QWidget *pWidget)
{
    QMetaObject::Connection connection;
    bool result = true;

    connection = pWidget->connect(m_pBoardWidget, SIGNAL(posClicked(const QPoint&))
                                  , pWidget, SLOT(onBoardWidgetPosClicked(const QPoint&)));
    result &= bool(connection);

    return result;
}

void ISceneWidgetUi::objectNameSetting(QWidget *pWidget)
{
    m_pMainLayout->setObjectName("MainLayout");
    m_pBoardWidget->setObjectName("BoardWidget");
    m_pOperationWidget->setObjectName("OperationWidget");
    pWidget->setObjectName("SceneWidget");
}

bool ISceneWidgetUi::decorate(QWidget *pWidget)
{
    m_pMainLayout->setStretch(0, 1);
    m_pBoardWidget->setFixedSize(760, 840);
    //m_pOperationWidget;

    pWidget->setAttribute(Qt::WA_StyledBackground);

    return true;
}

void ISceneWidgetUi::release()
{
    I_RELEASE(m_pMainLayout);
    I_RELEASE(m_pBoardWidget);
    I_RELEASE(m_pOperationWidget);
}
