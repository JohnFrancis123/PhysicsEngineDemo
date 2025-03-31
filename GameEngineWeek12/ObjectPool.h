#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "StandardIncludes.h"

template <class T>
class ObjectPool //object pools will handle deletion. If I manually delete stuff, it will cause errors. Just need to set to nullptrs if need be.
{
public:
	ObjectPool() {}
	~ObjectPool() {
		for (unsigned int count = 0; count < m_all.size(); count++) {
			cout << "Deleting pool object: " << typeid(T).name() << endl;
			delete m_all[count];
		}
		m_all.clear();
		m_available.clear();
	}

	T* GetResource() {
		if (m_available.empty()) {
			std::cout << "Creating new pool object: " << typeid(T).name() << endl;
			T* resource = new T();
			m_all.push_back(resource);
			return resource;
		}
		else {
			std::cout << "Reusing existing pool object: " << typeid(T).name() << endl;
			T* resource = m_available[0];
			m_available.erase(m_available.begin());
			return resource;
		}
	}

	void ReleaseResource(T* _object) {
		_object->Reset();
		m_available.push_back(_object);
	}

private:
	std::vector<T*> m_available;
	std::vector<T*> m_all;
};
#endif