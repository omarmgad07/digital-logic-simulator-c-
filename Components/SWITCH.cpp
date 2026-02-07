#include "SWITCH.h"

SWITCH::SWITCH(const GraphicsInfo& r_GfxInfo, int r_FanOut)
    : Gate(0, r_FanOut)        
{
    m_GfxInfo = r_GfxInfo;
    m_Status = LOW;
    m_OutputPin.setStatus(LOW);
}

void SWITCH::Operate()
{
    m_OutputPin.setStatus(m_Status);
}

void SWITCH::Draw(Output* pOut)
{
    pOut->DrawSWITCH(m_GfxInfo, (m_Status == HIGH));
    pOut->DrawComponentLabel(m_GfxInfo, GetLabel());
}

int SWITCH::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

int SWITCH::GetInputPinStatus(int n)
{
    return -1;
}

void SWITCH::setInputPinStatus(int n, STATUS s)
{
}

void SWITCH::SetStatus(STATUS s)
{
    m_Status = s;
    m_OutputPin.setStatus(s);
}

STATUS SWITCH::GetStatus() const
{
    return m_Status;
}

void SWITCH::Toggle()
{

    if (m_Status == LOW)
        m_Status = HIGH;
    else
        m_Status = LOW;

    m_OutputPin.setStatus(m_Status);
}

Component* SWITCH::Clone(const GraphicsInfo& newGfx) const
{
    return new SWITCH(newGfx, AND2_FANOUT);
}
