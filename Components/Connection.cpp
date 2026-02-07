#include "Connection.h"
#include "Gate.h"


Connection::Connection(const GraphicsInfo& r_GfxInfo,
    OutputPin* pSrcPin,
    InputPin* pDstPin)
    : Component(r_GfxInfo)
{
    SrcPin = pSrcPin;
    DstPin = pDstPin;

    if (DstPin)
        DstPin->setConnection(this);
}

void Connection::setSourcePin(OutputPin* pSrcPin)
{
    SrcPin = pSrcPin;
}

OutputPin* Connection::getSourcePin()
{
    return SrcPin;
}

void Connection::setDestPin(InputPin* pDstPin)
{
    DstPin = pDstPin;
}

InputPin* Connection::getDestPin()
{
    return DstPin;
}

void Connection::Operate()
{
    if (SrcPin && DstPin)
        DstPin->setStatus(SrcPin->getStatus());
}

void Connection::Draw(Output* pOut)
{
    pOut->DrawConnection(m_GfxInfo);
    pOut->DrawComponentLabel(m_GfxInfo, GetLabel());
}

int Connection::GetOutPinStatus()
{
    return SrcPin ? SrcPin->getStatus() : LOW;
}

int Connection::GetInputPinStatus(int n)
{
    return DstPin ? DstPin->getStatus() : LOW;
}

void Connection::setInputPinStatus(int n, STATUS s)
{
}

bool Connection::HitTest(int x, int y)
{
    int tol = 6;

    int x1 = m_GfxInfo.x1;
    int y1 = m_GfxInfo.y1;
    int x2 = m_GfxInfo.x2;
    int y2 = m_GfxInfo.y2;

    int midX = (x1 + x2) / 2;

    int diffY1 = y - y1;
    if (diffY1 < 0) diffY1 = -diffY1;

    int diffXMid = x - midX;
    if (diffXMid < 0) diffXMid = -diffXMid;

    int diffY2 = y - y2;
    if (diffY2 < 0) diffY2 = -diffY2;

    if (diffY1 <= tol && x >= x1 && x <= midX)
        return true;

    if (diffXMid <= tol &&
        ((y >= y1 && y <= y2) || (y >= y2 && y <= y1)))
        return true;

    if (diffY2 <= tol && x >= midX && x <= x2)
        return true;

    return false;
}

void Connection::UpdatePosition()
{
    if (!SrcPin || !DstPin) return;

    int xOut = 0, yOut = 0;
    int xIn = 0, yIn = 0;

    Component* srcComp = SrcPin->getComponent();
    if (srcComp)
    {
        Gate* gsrc = dynamic_cast<Gate*>(srcComp);
        if (gsrc)
        {
            gsrc->GetOutputPinPosition(xOut, yOut);
        }
        else
        {
            GraphicsInfo g = srcComp->GetGraphicsInfo();
            xOut = g.x2;
            yOut = (g.y1 + g.y2) / 2;
        }
    }

    Component* dstComp = DstPin->getComponent();
    if (dstComp)
    {
        Gate* gdst = dynamic_cast<Gate*>(dstComp);
        if (gdst)
        {
            int pinIndex = gdst->GetInputPinIndex(DstPin);
            if (pinIndex < 0) pinIndex = 0;
            gdst->GetInputPinPosition(pinIndex, xIn, yIn);
        }
        else
        {
            GraphicsInfo g = dstComp->GetGraphicsInfo();
            xIn = g.x1;
            yIn = (g.y1 + g.y2) / 2;
        }
    }

    if (xOut == 0 && yOut == 0 && srcComp)
    {
        GraphicsInfo g = srcComp->GetGraphicsInfo();
        xOut = (g.x1 + g.x2) / 2;
        yOut = (g.y1 + g.y2) / 2;
    }
    if (xIn == 0 && yIn == 0 && dstComp)
    {
        GraphicsInfo g = dstComp->GetGraphicsInfo();
        xIn = (g.x1 + g.x2) / 2;
        yIn = (g.y1 + g.y2) / 2;
    }

    m_GfxInfo.x1 = xOut;
    m_GfxInfo.y1 = yOut;
    m_GfxInfo.x2 = xIn;
    m_GfxInfo.y2 = yIn;
}

Component* Connection::Clone(const GraphicsInfo& gfx) const
{
    return new Connection(gfx, nullptr, nullptr);
}