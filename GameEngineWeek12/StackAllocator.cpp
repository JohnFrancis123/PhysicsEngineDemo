#include "StackAllocator.h"
#include "StandardIncludes.h"
StackAllocator::StackAllocator() {
	//note that FIRST you NEED to set stackStart to nullptr.
	ClearMemory();
}

StackAllocator::~StackAllocator() {
	//do the same as commented in constructor
	ClearMemory();
}

void StackAllocator::AllocateStack(unsigned int _stackSizeBytes) {
	//first check if null, which we didn't do. If stackStart is not null, we set it to null.
	m_stackStart = new unsigned char[_stackSizeBytes];
	memset(m_stackStart, 0, _stackSizeBytes);
	m_stackPosition = m_stackStart;
	m_stackEnd = m_stackStart + _stackSizeBytes;

}

unsigned char* StackAllocator::GetMemory(unsigned int _sizeBytes) {
	unsigned char* hold = m_stackPosition;
	if (m_stackPosition + _sizeBytes <= m_stackEnd) {
		m_stackPosition += _sizeBytes;
		return hold;
	}
	return nullptr;
}

void StackAllocator::Mark() {
	m_marker = m_stackPosition;
}

void StackAllocator::FreeToMarker() {
	m_stackPosition = m_marker;
	*m_stackPosition = 0; //you can also use memset to set it to zero, but it isn't necessary.
}

void StackAllocator::ClearMemory() {
	if (m_stackStart != nullptr) {
		delete m_stackStart; //also note that it is better to call delete[] rather than delete, since m_stackStart is an array.
	}
	m_marker = nullptr;
	m_stackStart = nullptr;
	m_stackPosition = nullptr;
	m_stackEnd = nullptr;
}