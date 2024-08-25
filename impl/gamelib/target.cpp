#include "target.hpp"
#include <drawable_helpers.hpp>

void Target::doCreate()
{
    m_shape = jt::dh::createShapeCircle(8, jt::colors::Gray, textureManager());
    m_shape->setOrigin(jt::OriginMode::CENTER);
}

void Target::doUpdate(float const elapsed)
{
    m_shape->setPosition(m_position);
    m_shape->update(elapsed);
}

void Target::doDraw() const { m_shape->draw(renderTarget()); }
