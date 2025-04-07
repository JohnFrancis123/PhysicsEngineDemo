#include "GameController.h"
#include "Renderer.h"
#include "TTFont.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "Timing.h"
#include "PhysicsController.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "RigidBody.h"
#include "Heroine.h"

GameController::GameController() {
	m_quit = false;
	m_sdlEvent = { };
	m_renderer = nullptr;
	m_fArial20 = nullptr;
	m_input = nullptr;
	m_timing = nullptr;
	m_physics = nullptr;
	m_heroine = nullptr;
}

GameController::~GameController() {
	ShutDown();
}//

void GameController::Initialize() {
	AssetController::Instance().Initialize(10000000); //Allocate 10MB
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>;
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>;

	m_renderer = &Renderer::Instance();
	m_renderer->Initialize();
	m_input = &InputController::Instance();
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_timing = &Timing::Instance();
	m_physics = &PhysicsController::Instance();
	m_heroine = new Heroine();
}

void GameController::ShutDown() {
	if (m_heroine != nullptr) {
		delete m_heroine;
		m_heroine = nullptr;
	}
	if (m_fArial20 != nullptr) {
		delete m_fArial20;
		m_fArial20 = nullptr;
	}

	if (SpriteAnim::Pool != nullptr) {
		delete SpriteAnim::Pool;
		SpriteAnim::Pool = nullptr;
	}

	if (SpriteSheet::Pool != nullptr) {
		delete SpriteSheet::Pool;
		SpriteSheet::Pool = nullptr;
	}
}

void GameController::HandleInput(SDL_Event _event) {
	if ((m_sdlEvent.type == SDL_QUIT) ||
		(m_input->KB()->KeyUp(m_sdlEvent, SDLK_ESCAPE))) {
		m_quit = true;
	}
	m_heroine->HandleInput(_event, m_timing->GetDeltaTime());
}

void GameController::RunGame() {
	Initialize();
	while (!m_quit) {
		m_timing->Tick();

		m_renderer->SetDrawColor(Color(255, 255, 255, 255));
		m_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}
		m_physics->Update(m_timing->GetDeltaTime());
		m_heroine->Update(m_timing->GetDeltaTime());
		
		m_heroine->Render(m_renderer);

		SDL_RenderPresent(m_renderer->GetRenderer());
	}
	ShutDown();
}