#ifndef _GATE_H
#define _GATE_H

#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate : public Component
{
protected:
    InputPin* m_InputPins;  
    OutputPin m_OutputPin;  
    int m_Inputs;           

public:
    Gate(int r_Inputs, int r_FanOut);

    OutputPin* GetOutputPin()
    {
        return &m_OutputPin;
    }

    InputPin* GetInputPin(int n)
    {
        if (n >= 1 && n <= m_Inputs)
            return &m_InputPins[n - 1];
        else
            return nullptr;
    }

    int GetInputCount() const
    {
        return m_Inputs;
    }


    void GetInputPinPosition(int n, int& x, int& y) override;
    void GetOutputPinPosition(int& x, int& y) override;
    int GetInputPinIndex(InputPin* pin) override;
};

#endif
