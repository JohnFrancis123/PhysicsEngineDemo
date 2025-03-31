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

GameController::GameController() {
	m_quit = false;
	m_sdlEvent = { };
	m_renderer = nullptr;
	m_fArial20 = nullptr;
	m_input = nullptr;
	m_timing = nullptr;
	m_physics = nullptr;
	m_circle = nullptr;
}

GameController::~GameController() {
	ShutDown();
}

void GameController::Initialize() {
	AssetController::Instance().Initialize(10000000); //Allocate 10MB
	m_renderer = &Renderer::Instance();
	m_renderer->Initialize();
	m_input = &InputController::Instance();
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_timing = &Timing::Instance();
	m_physics = &PhysicsController::Instance();

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	m_circle = SpriteSheet::Pool->GetResource();
	m_circle->Load("../Assets/Textures/Circle.tga");
	m_circle ->SetSize(1, 1, 32, 32);
	m_circle->AddAnimation(EN_AN_IDLE, 0, 1, 0.0f);
	m_circle->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void GameController::ShutDown() {
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
	else if (m_input->KB()->KeyUp(m_sdlEvent, SDLK_a)) {
		glm::vec2 pos = glm::vec2{ 16 + rand() % ( 1920 - 32 ), 16 + rand() % (1080 - 32) };
		glm::vec2 dest = glm::vec2{ rand() % 1920, rand() % 1080 };
		glm::vec2 dir = dest - pos;
		dir = glm::normalize(dir) * 200.0f;
		m_physics->AddRigidBody(pos, dir, rand() % 128);
	}

	m_input->MS()->ProcessButtons(_event);
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

		Rect r = m_circle->Update(EN_AN_IDLE, m_timing->GetDeltaTime());
		for (RigidBody* b : m_physics->GetBodies()) {
			auto pos = b->GetPosition();
			m_renderer->RenderTexture(m_circle, r, Rect(pos.x - 16, pos.y - 16, pos.x + 16, pos.y + 16),  b->GetMass() + 127);
		}

		m_fArial20->Write(m_renderer->GetRenderer(), ("FPS: " + to_string(m_timing->GetFPS())).c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 10, 10 });
		m_fArial20->Write(m_renderer->GetRenderer(), m_physics->ToString().c_str(), SDL_Color{0, 0, 255}, SDL_Point{110, 10});



		SDL_RenderPresent(m_renderer->GetRenderer());
	}
}