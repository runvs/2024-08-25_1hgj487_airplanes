#ifndef PLANE_HPP
#define PLANE_HPP

#include "game_interface.hpp"
#include <animation.hpp>
#include <box2dwrapper/box2d_object.hpp>
#include <game_object.hpp>

class Plane : public jt::GameObject {
public:
    explicit Plane(std::shared_ptr<jt::Box2DWorldInterface> world);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::shared_ptr<jt::Animation> m_animation;

    std::shared_ptr<jt::Box2DObject> m_physicsObject;

    std::shared_ptr<jt::Box2DWorldInterface> m_world;

    jt::Vector2f m_direction { 0, -1 };
};

#endif // PLANE_HPP
