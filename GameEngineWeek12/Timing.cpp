#include "Timing.h"

Timing::Timing() {
	m_fpsCount = 0;
	m_fpsLast = 0;
	m_deltaTime = 0;
	m_currentTime = SDL_GetTicks(); //number of milliseconds since application start
	m_lastTime = m_currentTime;
	m_fpsStart = m_currentTime;
	SetFPS(60);
}

void Timing::Tick() { //calculate FPS
	m_currentTime = SDL_GetTicks(); //use this to calculate milliseconds passed since starting
	m_deltaTime = (float)(m_currentTime - m_lastTime) / 1000.0f; //delta time is time between frames
	if (m_fpsStart + 1000 <= m_currentTime) //checking if a second passed
	{
		m_fpsLast = m_fpsCount; //equate fpsLast to fpsCount
		m_fpsCount = 0; //reset fpsCount
		m_fpsStart = m_currentTime; //set fpsStart to currentTime
	}
	else {
		m_fpsCount++; //keep incrementing fpsCount (thousands of times per second)
	}
	m_lastTime = m_currentTime; //equate lastTime to currentTime for delta time calculation
}

void Timing::SetFPS(int _fps) {
	m_targetFPS = _fps;
	m_ticksPerFrame = 1000 / m_targetFPS;
}

void Timing::CapFPS() {
	unsigned int delta = SDL_GetTicks() - m_currentTime;
	if (delta < m_ticksPerFrame) {
		SDL_Delay(m_ticksPerFrame - delta);
	}
}