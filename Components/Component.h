#ifndef COMPONENT_H
#define COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include "InputPin.h"

class Component
{
protected:
    GraphicsInfo m_GfxInfo;
    string m_Label;

    bool selected;

public:
    Component();
    Component(const GraphicsInfo& r_GfxInfo);

    virtual void Operate() = 0;
    virtual void Draw(Output* pOut) = 0;

    virtual GraphicsInfo GetGraphicsInfo() const;
    virtual void SetGraphicsInfo(GraphicsInfo r_GFX);

    void SetSelected(bool s) { selected = s; }
    bool IsSelected() const { return selected; }

    virtual bool HitTest(int x, int y);

    virtual int GetOutPinStatus() = 0;
    virtual int GetInputPinStatus(int n) = 0;
    virtual void setInputPinStatus(int n, STATUS s) = 0;
    virtual Component* Clone(const GraphicsInfo& newGfx) const = 0;


    void SetLabel(const string& L) { m_Label = L; }
    string GetLabel() const { return m_Label; }

    virtual void GetInputPinPosition(int n, int& x, int& y) { x = y = 0; }
    virtual void GetOutputPinPosition(int& x, int& y) { x = y = 0; }
    virtual int GetInputPinIndex(InputPin* pin) { return -1; }

    

    virtual ~Component();
};

#endif
