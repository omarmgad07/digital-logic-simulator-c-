#include "AND32.h"

AND32::AND32(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void AND32::Operate()
{
	//caclulate the output status as the ANDing of the two input pins

	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();

	if (in1 == HIGH && in2 == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);


}


// Function Draw
// Draws 2-input AND gate
void AND32::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawAND32(m_GfxInfo, selected);
	pOut->DrawComponentLabel(m_GfxInfo, GetLabel());
}

//returns status of outputpin
int AND32::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND32::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void AND32::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
Component* AND32::Clone(const GraphicsInfo& newGfx) const
{
	return new AND32(newGfx, AND2_FANOUT);

}