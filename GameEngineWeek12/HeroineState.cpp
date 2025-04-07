#include "HeroineState.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Heroine.h"
#include "SpriteSheet.h"

StandingState HeroineState::m_standing;
DuckingState HeroineState::m_ducking;
JumpingState HeroineState::m_jumping;
DivingState HeroineState::m_diving;

void StandingState::HandleInput(Heroine* _heroine, SDL_Event _event) {
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_b)) {
		_heroine->GetRigidBody()->SetBuoyancy(glm::vec2(0, 100));
		_heroine->GetRigidBody()->SetBuoyancyDecay(glm::vec2(0, 600));
		_heroine->SetState(HeroineState::GetJumpingState());
	}
	else if (InputController::Instance().KB()->KeyDown(_event, SDLK_DOWN)) {
		_heroine->SetState(HeroineState::GetDuckingState());
	}
}

void StandingState::Update(Heroine* _heroine, float _deltaTime) {
	_heroine->GetAnimations()->Update(EN_AN_IDLE, _deltaTime, _heroine->GetSrcRect());
}

void DuckingState::HandleInput(Heroine* _heroine, SDL_Event _event) {
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_DOWN))
	{
		_heroine->GetAnimations()->ResetCurrentClip(EN_AN_CROUCH);
		_heroine->SetState(HeroineState::GetStandingState());
	}
}

void DuckingState::Update(Heroine* _heroine, float _deltaTime) {
	_heroine->GetAnimations()->Update(EN_AN_CROUCH, _deltaTime, _heroine->GetSrcRect());
}

void JumpingState::HandleInput(Heroine* _heroine, SDL_Event _event) {
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_DOWN)) {
		_heroine->GetRigidBody()->SetRandomForce(glm::vec2(0, -100));
		_heroine->GetAnimations()->ResetCurrentClip(EN_AN_JUMP_UP_FALL);
		_heroine->SetState(HeroineState::GetDivingState());
	}
}

void JumpingState::Update(Heroine* _heroine, float _deltaTime) {
	_heroine->GetAnimations()->Update(EN_AN_JUMP_UP_FALL, _deltaTime, _heroine->GetSrcRect());
	if (_heroine->GetAnimations()->GetCurrentClip(EN_AN_JUMP_UP_FALL) >= 48.0f) {
		_heroine->GetAnimations()->ResetCurrentClip(EN_AN_JUMP_UP_FALL);
		_heroine->SetState(HeroineState::GetStandingState());
	}
}

void DivingState::HandleInput(Heroine* _heroine, SDL_Event _event) {

}

void DivingState::Update(Heroine* _heroine, float _deltaTime) {
	_heroine->GetAnimations()->Update(EN_AN_CROUCH, _deltaTime, _heroine->GetSrcRect());
	if (_heroine->GetAnimations()->GetCurrentClip(EN_AN_CROUCH) >= 66.0f) {
		_heroine->GetRigidBody()->SetRandomForce(glm::vec2(0, 0));
		_heroine->SetState(HeroineState::GetStandingState());
	}
}