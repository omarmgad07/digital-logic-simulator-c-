#include "LED.h"
#include "../GUI/Output.h"



extern UI_Info UI;

LED::LED(const GraphicsInfo& r_GfxInfo)
    : Gate(1, 0)
{
    m_GfxInfo = r_GfxInfo;
    m_IsOn = false;
}

void LED::Operate()
{
   
    STATUS in = m_InputPins[0].getStatus();

    if (in == HIGH)
        m_IsOn = true;
    else
        m_IsOn = false;
}

void LED::Draw(Output* pOut)
{
    

    if (UI.AppMode == SIMULATION && m_IsOn)
    {
        pOut->DrawLED(m_GfxInfo, true); 
    }
    else
    {
        pOut->DrawLED(m_GfxInfo, false); 
    }

    pOut->DrawComponentLabel(m_GfxInfo, GetLabel());
}

int LED::GetOutPinStatus()
{
    return -1;
}

int LED::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();
}

void LED::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}

Component* LED::Clone(const GraphicsInfo& gfx) const
{
    return new LED(gfx);
}
