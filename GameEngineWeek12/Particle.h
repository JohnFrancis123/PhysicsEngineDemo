#ifndef PARTICLE_H
#define PARTICLE_H

#include "RigidBody.h"
#include "ObjectPool.h"

class Particle : public RigidBody
{
public:
	//Constructors/Destructors
	Particle(); 
	virtual ~Particle(); 
};

#endif //PARTICLE_H