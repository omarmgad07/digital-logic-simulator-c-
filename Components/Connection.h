#pragma once

#include "../Defs.h"
#include "Component.h"
#include "../GUI/Output.h"
#include "InputPin.h"
#include "OutputPin.h"

class Connection : public Component
{
private:
    OutputPin* SrcPin;
    InputPin* DstPin;

public:
    Connection(const GraphicsInfo& r_GfxInfo,
        OutputPin* pSrcPin,
        InputPin* pDstPin);

    void setSourcePin(OutputPin* pSrcPin);
    OutputPin* getSourcePin();

    void setDestPin(InputPin* pDstPin);
    InputPin* getDestPin();

    virtual void Operate() override;
    virtual void Draw(Output* pOut) override;

    virtual int GetOutPinStatus() override;
    virtual int GetInputPinStatus(int n) override;
    virtual void setInputPinStatus(int n, STATUS s) override;

    virtual bool HitTest(int x, int y) override;

    void UpdatePosition();

 
    virtual Component* Clone(const GraphicsInfo& gfx) const override;
};
