#include "Particle.h"

ObjectPool<Particle>* Particle::Pool;

Particle::Particle() {
	m_currentTime = 0;
	m_lifeTime = 0;
}

void Particle::Update(float _deltaTime, glm::vec2 _force) {
	
	RigidBody::Update(_deltaTime, _force);

	m_currentTime += _deltaTime;
	if (m_currentTime > m_lifeTime) {
		SetDead(true);
	}
}