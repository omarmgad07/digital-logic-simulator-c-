#include "XOR32.h"

XOR32::XOR32(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XOR32::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();
	STATUS in3 = m_InputPins[2].getStatus();

	int countHigh = 0;

	if (in1 == HIGH) countHigh++;
	if (in2 == HIGH) countHigh++;
	if (in3 == HIGH) countHigh++;

	if (countHigh % 2 == 1)        
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);

}



void XOR32::Draw(Output* pOut)
{
	pOut->DrawXOR32(m_GfxInfo, selected);
	pOut->DrawComponentLabel(m_GfxInfo, GetLabel());
}

int XOR32::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


int XOR32::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	
}

void XOR32::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
Component* XOR32::Clone(const GraphicsInfo& newGfx) const
{
	return new XOR32(newGfx, AND2_FANOUT);

}