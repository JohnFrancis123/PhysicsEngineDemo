#ifndef TIMING_H
#define TIMING_H

#include "StandardIncludes.h"

class Timing : public Singleton<Timing> //created as a singleton. We don't need multiple.
{
public:
	// Constructors/Destructors
	Timing();
	virtual ~Timing() { }

	// Accessors
	unsigned int GetFPS() { return m_fpsLast; }
	float GetDeltaTime() { return m_deltaTime; }
	void SetFPS(int _fps);
	void CapFPS();

	// Methods
	void Tick();

private: //
	//Members
	unsigned int m_currentTime;
	unsigned int m_lastTime;
	unsigned int m_fpsStart;
	unsigned int m_fpsCount;
	unsigned int m_fpsLast;
	float m_deltaTime;
	unsigned int m_targetFPS;
	unsigned int m_ticksPerFrame;
};

#endif // TIMING_H