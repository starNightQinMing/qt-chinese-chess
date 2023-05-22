#ifndef IOPERATIONWIDGETUI_H
#define IOPERATIONWIDGETUI_H

#include "iabstractwidgetui.h"

class QPushButton;

class IOperationWidgetUi : public IAbstractWidgetUi
{
public:
    IOperationWidgetUi();
    virtual ~IOperationWidgetUi();

protected:
    virtual bool instance(QWidget* pWidget) override;
    virtual bool retranslateUi(QWidget* pWidget) override;
    virtual void layout(QWidget* pWidget) override;
    virtual bool connect(QWidget* pWidget) override;
    virtual void objectNameSetting(QWidget* pWidget) override;
    virtual bool decorate(QWidget* pWidget) override;
    virtual void release() override;

protected:
    QVBoxLayout* m_pMainLayout;
    QSpacerItem* m_pLeftVerticalSpacer;
    QPushButton* m_pStartButton;
    QPushButton* m_pRestartButton;
    QPushButton* m_pPromptButton;
    QPushButton* m_pAdmitDefeatButton;
    QPushButton* m_pDrawButton;
    QPushButton* m_pHelpButton;
};

#endif // IOPERATIONWIDGETUI_H
