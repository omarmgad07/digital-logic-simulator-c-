#pragma once
#include "Gate.h"

class SWITCH : public Gate
{
    STATUS m_Status;   

public:
    SWITCH(const GraphicsInfo& r_GfxInfo, int r_FanOut);

    virtual void Operate();
    virtual void Draw(Output* pOut);

    virtual int GetOutPinStatus();
    virtual int GetInputPinStatus(int n);
    virtual void setInputPinStatus(int n, STATUS s);

    void SetStatus(STATUS s);
    STATUS GetStatus() const;
    void Toggle();
    virtual Component* Clone(const GraphicsInfo& newGfx) const override;
};
