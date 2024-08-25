#include "state_game.hpp"

#include "math_helper.hpp"
#include "random/random.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <color/color.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <state_menu.hpp>

void StateGame::replaceTarget()
{
    m_target->setPosition(jt::Random::getRandomPointIn(
        { 32, 32, GP::GetScreenSize().x - 64, GP::GetScreenSize().y - 64 }));
}

void StateGame::onCreate()
{
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });

    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    createPlayer();

    m_target = std::make_shared<Target>();
    add(m_target);
    replaceTarget();

    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);
    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::onEnter() { }

void StateGame::createPlayer()
{
    m_plane = std::make_shared<Plane>(m_world);
    add(m_plane);
}

void StateGame::onUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        m_hud->getObserverScoreP2()->notify(static_cast<int>(getAge() * 10));

        auto const tp = m_target->getPosition();
        auto const pp = m_plane->getPosition();

        auto distance = jt::MathHelper::distanceBetween(tp, pp);

        if (distance < 16) {
            m_scoreP1++;
            m_hud->getObserverScoreP1()->notify(m_scoreP1);
            replaceTarget();
            if (m_scoreP1 >= 15) {
                endGame();
            }
        }

        if (getGame()->input().keyboard()->pressed(jt::KeyCode::LShift)
            && getGame()->input().keyboard()->pressed(jt::KeyCode::Escape)) {
            endGame();
        }
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
}

void StateGame::onDraw() const
{
    m_background->draw(renderTarget());
    drawObjects();
    m_vignette->draw();
    m_hud->draw();
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    auto const newState = std::make_shared<StateMenu>();
    newState->setScore(getAge() * 10);
    getGame()->stateManager().switchState(newState);
}

std::string StateGame::getName() const { return "State Game"; }
