#include "Component.h"

Component::Component()
{
    m_GfxInfo.x1 = m_GfxInfo.y1 = 0;
    m_GfxInfo.x2 = m_GfxInfo.y2 = 0;

    selected = false; 
}

Component::Component(const GraphicsInfo& r_GfxInfo)
{
    m_GfxInfo = r_GfxInfo;
    selected = false; 
}

Component::~Component()
{
}

GraphicsInfo Component::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

void Component::SetGraphicsInfo(GraphicsInfo r_GFX)
{
    m_GfxInfo = r_GFX;
}

bool Component::HitTest(int x, int y)
{
    return (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 &&
        y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2);
}
