#include "NOR32.h"

NOR32::NOR32(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NOR32::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();
	STATUS in3 = m_InputPins[2].getStatus();

	if (in1 == LOW && in2 == LOW && in3 == LOW)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);



}

void NOR32::Draw(Output* pOut)
{
	pOut->DrawNOR32(m_GfxInfo, selected);
	pOut->DrawComponentLabel(m_GfxInfo, GetLabel());
}

int NOR32::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


int NOR32::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	
}

void NOR32::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
Component* NOR32::Clone(const GraphicsInfo& newGfx) const
{
	return new NOR32(newGfx, AND2_FANOUT);

}