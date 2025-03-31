#include "Particle.h"

ObjectPool<Particle>* Particle::Pool;

Particle::Particle() {
	Reset();
}

void Particle::Reset() {
	m_currentTime = 0;
	m_lifeTime = 0;
	m_startSize = 0;
	m_endSize = 1;
	m_currentSize = 0;
	RigidBody::Reset();
}

void Particle::Update(float _deltaTime, glm::vec2 _force) {
	
	RigidBody::Update(_deltaTime, _force);

	float sizePerc = m_currentTime / m_lifeTime;
	m_currentSize = m_startSize + ((m_endSize - m_startSize) * sizePerc);

	m_currentTime += _deltaTime;
	if (m_currentTime > m_lifeTime) {
		SetDead(true);
	}
}