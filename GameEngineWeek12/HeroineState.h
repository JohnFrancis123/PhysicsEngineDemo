#ifndef HEROINE_STATE_H
#define HEROINE_STATE_H

#include "StandardIncludes.h"

//NOTE: These are NOT pointers. We didnt do this, but the class knows what they are upon first compilation
//the reason we do this is because they don't need to be pointers, since they are defined in the header.
class Heroine; 
class StandingState;
class DuckingState;
class JumpingState;
class DivingState;

class HeroineState
{
public:
	//Constructors/Destructors
	HeroineState() { } 
	virtual ~HeroineState() { }

	//Accessors
	static StandingState* GetStandingState() { return &m_standing; }
	static DuckingState* GetDuckingState() { return &m_ducking; }
	static JumpingState* GetJumpingState() { return &m_jumping; }
	static DivingState* GetDivingState() { return &m_diving; }

	//Methods
	//NOTE: These are pure virtual, meaning derived classes MUST implement them.
	virtual void HandleInput(Heroine* _heroine, SDL_Event _event) = 0;
	virtual void Update(Heroine* _heroine, float _deltaTime) = 0;

private:
	//Members
	static StandingState m_standing;
	static DuckingState m_ducking;
	static JumpingState m_jumping;
	static DivingState m_diving;
};

class StandingState : public HeroineState {
public:
	StandingState() { } 
	virtual ~StandingState() { }

	//Methods
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};

class DuckingState : public HeroineState {
public:
	 //Constructors/Destructors
	DuckingState() { }
	virtual ~DuckingState() { }

	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};

class JumpingState : public HeroineState {
public:
	JumpingState() { }
	virtual ~JumpingState() { };
	//Methods
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};

class DivingState : public HeroineState {
public:
	DivingState() { }
	virtual ~DivingState() { };
	//Methods
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};


#endif // HEROINE_STATE_H