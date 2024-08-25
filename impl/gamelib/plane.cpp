
#include "plane.hpp"
#include "math_helper.hpp"

Plane::Plane(std::shared_ptr<jt::Box2DWorldInterface> world)
    : m_world { world }
{
}

void Plane::doCreate()
{
    m_animation = std::make_shared<jt::Animation>();
    m_animation->loadFromAseprite("assets/plane.aseprite", textureManager());
    m_animation->play("idle");
    m_animation->setOrigin(jt::OriginMode::CENTER);

    b2BodyDef bodyDef;
    bodyDef.position.x = 200;
    bodyDef.position.y = 200;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.fixedRotation = false;
    bodyDef.angularDamping = 0.0f;
    bodyDef.linearDamping = 4.0f;
    m_physicsObject = std::make_shared<jt::Box2DObject>(m_world, &bodyDef);
}

void Plane::doUpdate(float const elapsed)
{
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::W)) {
        m_physicsObject->addForceToCenter(500 * m_direction);
    }
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::D)) {
        m_direction = jt::MathHelper::rotateBy(m_direction, 180 * elapsed);
    }
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::A)) {
        m_direction = jt::MathHelper::rotateBy(m_direction, -180 * elapsed);
    }
    m_animation->setPosition(m_physicsObject->getPosition());
    m_animation->setRotation(-jt::MathHelper::angleOf(m_direction) + 90);
    m_animation->update(elapsed);
}

void Plane::doDraw() const { m_animation->draw(renderTarget()); }

jt::Vector2f Plane::getPosition() { return m_physicsObject->getPosition(); }
