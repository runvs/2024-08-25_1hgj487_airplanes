#ifndef TARGET_HPP
#define TARGET_HPP

#include "shape.hpp"
#include <game_object.hpp>

class Target : public jt::GameObject {

public:
    std::shared_ptr<jt::Shape> m_shape;

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    jt::Vector2f m_position;

public:
    [[nodiscard]] jt::Vector2f getPosition() const { return m_position; }

    void setPosition(jt::Vector2f const& position) { m_position = position; }
};

#endif // TARGET_HPP
