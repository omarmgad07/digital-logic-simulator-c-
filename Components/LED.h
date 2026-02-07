#pragma once

#include "Gate.h"

class LED : public Gate
{
    bool m_IsOn;

public:
    LED(const GraphicsInfo& r_GfxInfo);

    virtual void Operate() override;
    virtual void Draw(Output* pOut) override;

    virtual int GetOutPinStatus() override;
    virtual int GetInputPinStatus(int n) override;
    virtual void setInputPinStatus(int n, STATUS s) override;

    virtual Component* Clone(const GraphicsInfo& gfx) const override;
};
