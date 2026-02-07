#include "NOT2.h"

NOT2::NOT2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NOT2::Operate()
{
	STATUS in = m_InputPins[0].getStatus(); // only the first input
	m_OutputPin.setStatus(in == HIGH ? LOW : HIGH); // invert
}



// Function Draw
// Draws 2-input AND gate
void NOT2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOT2(m_GfxInfo, selected);
	pOut->DrawComponentLabel(m_GfxInfo, GetLabel());
}

//returns status of outputpin
int NOT2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOT2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOT2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
Component* NOT2::Clone(const GraphicsInfo& newGfx) const
{
	return new NOT2(newGfx, AND2_FANOUT);

}