#ifndef ISCENEWIDGETUI_H
#define ISCENEWIDGETUI_H

#include "iabstractwidgetui.h"

class IBoardWidget;
class IOperationWidget;

class ISceneWidgetUi : public IAbstractWidgetUi
{
public:
    ISceneWidgetUi();
    virtual ~ISceneWidgetUi();

protected:
    virtual bool instance(QWidget* pWidget) override;
    virtual bool retranslateUi(QWidget* pWidget) override;
    virtual void layout(QWidget* pWidget) override;
    virtual bool connect(QWidget* pWidget) override;
    virtual void objectNameSetting(QWidget* pWidget) override;
    virtual bool decorate(QWidget* pWidget) override;
    virtual void release() override;

protected:
    QHBoxLayout* m_pMainLayout;
    IBoardWidget* m_pBoardWidget;
    IOperationWidget* m_pOperationWidget;
};

#endif // ISCENEWIDGETUI_H
