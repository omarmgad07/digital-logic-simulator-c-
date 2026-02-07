#include "Gate.h"

Gate::Gate(int r_Inputs, int r_FanOut)
    : m_OutputPin(r_FanOut)          
{
    m_Inputs = r_Inputs;
    m_InputPins = new InputPin[r_Inputs];

    for (int i = 0; i < m_Inputs; i++)
        m_InputPins[i].setComponent(this);

    m_OutputPin.setComponent(this);
}

void Gate::GetInputPinPosition(int n, int& x, int& y)
{
    if (n < 0 || n >= m_Inputs)
    {
        x = 0;
        y = 0;
        return;
    }

    GraphicsInfo g = GetGraphicsInfo();
    int spacing = (g.y2 - g.y1) / (m_Inputs + 1);

    x = g.x1;                    
    y = g.y1 + spacing * (n + 1);
}

void Gate::GetOutputPinPosition(int& x, int& y)
{
    GraphicsInfo g = GetGraphicsInfo();
    x = g.x2;                   
    y = (g.y1 + g.y2) / 2;       
}

int Gate::GetInputPinIndex(InputPin* pin)
{
    for (int i = 0; i < m_Inputs; i++)
        if (&m_InputPins[i] == pin)
            return i;

    return -1;
}