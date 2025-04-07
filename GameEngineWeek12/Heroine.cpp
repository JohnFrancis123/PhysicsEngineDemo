#include "Heroine.h"
#include "SpriteSheet.h"
#include "Renderer.h"
#include "PhysicsController.h"

Heroine::Heroine() {
	m_state = HeroineState::GetStandingState();

	m_rigidBody = PhysicsController::Instance().AddRigidBody(glm::vec2{ 100, 200 }, glm::vec2(0, 0), 40);
	m_animations = SpriteSheet::Pool->GetResource();
	m_animations->Load("../Assets/Textures/Warrior.tga");
	m_animations->SetSize(17, 6, 69, 44);
	m_animations->AddAnimation(EN_AN_IDLE, 0, 6, 10.0f);
	m_animations->AddAnimation(EN_AN_JUMP_UP_FALL, 41, 8, 4.0f);
	m_animations->AddAnimation(EN_AN_CROUCH, 64, 4, 8.0f);
	m_animations->SetBlendMode(SDL_BLENDMODE_BLEND);
}

Heroine::~Heroine() 
{
}

void Heroine::HandleInput(SDL_Event _event, float _deltaTime) {
	m_state->HandleInput(this, _event);
}

void Heroine::Update(float _deltaTime) {
	m_state->Update(this, _deltaTime);
}

void Heroine::Render(Renderer* _renderer) {
	glm::vec2 p = m_rigidBody->GetPosition();
	Rect destRect = Rect(p.x, p.y, p.x + 69 * 2, p.y + 44 * 2);
	_renderer->RenderTexture(m_animations, m_srcRect, destRect);
}