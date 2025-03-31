#include "Controller.h"

Controller::Controller() {
}

Controller::~Controller() {
}

void Controller::DetectControllers() { //called once on startup
	m_controllers.clear();
	int numControllers = SDL_NumJoysticks(); //if no joysticks, return
	if (numControllers == 0) return;
	for (int count = 0; count < numControllers; count++) { //otherwise add controllers using the Add() method
		if (!SDL_IsGameController(count)) continue; //if not a game controller, just reiterate without adding a controller
		Add(SDL_GameControllerOpen(count), count); //if it is a controller, call the Add() method with its Controller pointer and ID (as count)
		//with the above, this is a little bit redundant
	}
}

void Controller::Add(SDL_GameController* _controller, int _controllerID) { //opens a connection to your controller internally. Uses a pointer to controller.
	if (_controller == nullptr) return; //normally there should be an error message for this check, but for this class, we just return.

	SDL_Joystick* j = SDL_GameControllerGetJoystick(_controller); //Grabbing the joystick pointer 
	SDL_JoystickID jID = SDL_JoystickInstanceID(j); //_controllerID is not to be used as a unique ID
	for (ControllerInfo c : m_controllers) {
		if (c.ID == jID) return; //checking if we already have the joystick ID, then returning if so
	}
	//if not,
	ControllerInfo c = ControllerInfo(); //assigning ControllerInfo as c and giving it the Controller, Name, ID, and pushes back the array of controllers.
	c.Controller = _controller;
	c.Name = string(SDL_GameControllerName(_controller));
	c.ID = jID;
	m_controllers.push_back(c);
}

bool Controller::Added(SDL_Event _event) { //checking if the controller was added
	if (_event.type != SDL_CONTROLLERDEVICEADDED) return false; //SDL_CONTROLLERDEVICEADDED event happens when we add a controller

	//if it was added, we call the Add() method with the controller ID (being _event.cdevice.which)
	if (SDL_IsGameController(_event.cdevice.which)) {
		SDL_GameController* controller = SDL_GameControllerOpen(_event.cdevice.which);
		Add(controller, _event.cdevice.which); //extracting the joystick ID and adding the controller.
	}

	return true;
}

bool Controller::Removed(SDL_Event _event) { //checking if the controller was removed
	if (_event.type != SDL_CONTROLLERDEVICEREMOVED) return false;

	for (unsigned int count = 0; count < m_controllers.size(); count++) {
		if (m_controllers[count].ID != _event.cdevice.which) continue; //checking if we have the right controller. If not, ignore.
		m_controllers.erase(m_controllers.begin() + count); //If we do have the right controller, erasing the item starting at the beginning + the count, so we remove the right controller from the list. Unfortunately we can't pass the index just like that for erase.
		break; //since there cannot be two controllers removed at the same time, we just break here.
	}

	return true;
}

bool Controller::ProcessButtons(SDL_Event _event) {
	if (_event.type == SDL_CONTROLLERBUTTONDOWN) { //checks if the event is a CONTROLLERBUTTONDOWN event
		for (unsigned int count = 0; count < m_controllers.size(); count++) {
			if (m_controllers[count].ID != _event.cdevice.which) continue; //if not the controller with the controller button down, ignore below and repeat.
			//since v is not a member variable, we cannot push_back, so we have to copy it.
			auto v = m_controllers[count].Buttons; //if it is, add a button to the vector of Buttons, stored in the local variable v.
			if (std::find(v.begin(), v.end(), _event.cbutton.button) == v.end()) { //find the button, then add to the list.
				m_controllers[count].Buttons.push_back(SDL_GameControllerButton(_event.cbutton.button)); //push back to the list of Buttons. We would also be able to use v.push_back if we were to use auto v = &m_controllers[count].Begin; instead.
			}
			break; //break after finding the button
		}
		return true;
	}
	else if (_event.type == SDL_CONTROLLERBUTTONUP) {
		for (unsigned int count = 0; count < m_controllers.size(); count++) {
			if (m_controllers[count].ID != _event.cdevice.which) continue; //REMEMBER WE NEEDED TO ADD THIS LINE. DO NOT RUN PREVIOUS ITERATIONS.
			vector<SDL_GameControllerButton>* v = &m_controllers[count].Buttons; //equating v to its buttons using the address of operator (&)
			for (unsigned int button = 0; button < v->size(); button++) {
				if ((*v)[button] == _event.cbutton.button) {
					v->erase(v->begin() + button);
					break;
				}
			}
		}
		return true;
	}
	return false;
}

bool Controller::ProcessMotion(SDL_Event _event) {
	if (_event.type != SDL_CONTROLLERAXISMOTION) return false; //return false we did not move the sticks.

	for (unsigned int count = 0; count < m_controllers.size(); count++) {
		if (m_controllers[count].ID != _event.cdevice.which) continue;

		//Left Analog Stick
		if (_event.caxis.axis == 0) { //X axis motion. _event.caxis.axis checks the axis.
			m_controllers[count].LeftAxis.X = _event.caxis.value; //can go up to the max or min of a 16-bit int (or short int) (-32768 to 32767)
		} //note: it would be a good idea to add a tolerance threshold for stick drift in a real game.
		else if (_event.caxis.axis == 1) { //Y axis motion
			m_controllers[count].LeftAxis.Y = _event.caxis.value;
		}

		//Right Analog Stick
		if (_event.caxis.axis == 2) { //X axis motion
			m_controllers[count].RightAxis.X = _event.caxis.value;
		}
		else if (_event.caxis.axis == 3) { //Y axis motion
			m_controllers[count].RightAxis.Y = _event.caxis.value;
		}
	} //ideally we'd want to have a break to break out of the loop assuming we get what we want, since this works for one controller at a time.
}


string Controller::ToString() {
	int cc = 0;
	string s = "Controllers: ";
	for (ControllerInfo c : m_controllers) {
		cc++;
		s += to_string(cc) + " - " + c.Name + ": ";
		s += c.ToString();
	}
	return s;
}