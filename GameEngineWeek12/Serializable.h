#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "StandardIncludes.h"

class Serializable {
public:
	//Constructors/Destructors
	Serializable() {}
	virtual ~Serializable() {}

	//Methods
	//these are passed by reference. Here, you receive the actual object instead of a pointer variable.
	//passing by value would send an error, since there is no copy constructor. This means compiler cannot copy istream or ostream.
	virtual void Serialize(std::ostream& _stream) = 0; //output/writing data
	virtual void Deserialize(std::istream& _stream) = 0; //input/read data and serializing
};

#endif //SERIALIZABLE_H