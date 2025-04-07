#include "SpriteSheet.h"

ObjectPool<SpriteSheet>* SpriteSheet::Pool;

SpriteSheet::SpriteSheet() {
	m_rows = 0;
	m_columns = 0;
	m_clipSizeX = 0;
	m_clipSizeY = 0;
}

SpriteSheet::~SpriteSheet() {
	m_animations.clear();
}

void SpriteSheet::SetSize(byte _rows, byte _columns, byte _clipSizeX, byte _clipSizeY) {
	m_rows = _rows;
	m_columns = _columns;
	m_clipSizeX = _clipSizeX;
	m_clipSizeY = _clipSizeY;
}

void SpriteSheet::AddAnimation(AnimationNames _name, short _clipStart, short  _clipCount, float _clipSpeed) {
	SpriteAnim* anim = SpriteAnim::Pool->GetResource();
	anim->Create(_clipStart, _clipCount, _clipSpeed);
	m_animations[_name] = anim;
}

Rect SpriteSheet::Update(AnimationNames _name, float _deltaTime) {
	Rect r = Rect();
	//short s = m_animations[_name]->GetClipCurrent();
	//short posX = s % m_columns * m_clipSizeX;
	//short posY = s / m_columns * m_clipSizeY;
	//Rect r = Rect(posX, posY, posX + m_clipSizeX, posY + m_clipSizeY);

	//m_animations[_name]->Update(_name, _deltaTime, &r);
	
	Update(_name, _deltaTime, &r);

	return r;
}

void SpriteSheet::Update(AnimationNames _name, float _deltaTime, Rect* _rect) {
	short s = m_animations[_name]->GetClipCurrent();
	_rect->X1 = s % m_columns * m_clipSizeX;
	_rect->Y1 = s / m_columns * m_clipSizeY;
	_rect->X2 = _rect->X1 + m_clipSizeX;
	_rect->Y2 = _rect->Y1 + m_clipSizeY;

	m_animations[_name]->Update(_deltaTime);
}

void SpriteSheet::ResetCurrentClip(AnimationNames _name) {
	m_animations[_name]->Reset();
}

void SpriteSheet::Serialize(std::ostream& _stream) {
	_stream.write(reinterpret_cast<char*>(&m_rows), sizeof(m_rows));
	_stream.write(reinterpret_cast<char*>(&m_columns), sizeof(m_columns));
	_stream.write(reinterpret_cast<char*>(&m_clipSizeX), sizeof(m_clipSizeX));
	_stream.write(reinterpret_cast<char*>(&m_clipSizeY), sizeof(m_clipSizeY));
	int count = m_animations.size();
	_stream.write(reinterpret_cast<char*>(&count), sizeof(count));
	for (auto& a : m_animations) {
		AnimationNames index = a.first;
		_stream.write(reinterpret_cast<char*>(&index), sizeof(index));
		a.second->Serialize(_stream);
	}

	Texture::Serialize(_stream);
}

void SpriteSheet::Deserialize(std::istream& _stream)
{
	_stream.read(reinterpret_cast<char*>(&m_rows), sizeof(m_rows));
	_stream.read(reinterpret_cast<char*>(&m_columns), sizeof(m_columns));
	_stream.read(reinterpret_cast<char*>(&m_clipSizeX), sizeof(m_clipSizeX));
	_stream.read(reinterpret_cast<char*>(&m_clipSizeY), sizeof(m_clipSizeY));
	int count;
	_stream.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (int c = 0; c < count; c++) {
		AnimationNames index;
		_stream.read(reinterpret_cast<char*>(&index), sizeof(index));
		SpriteAnim* anim = SpriteAnim::Pool->GetResource();
		anim->Deserialize(_stream);
		m_animations[index] = anim;
	}

	Texture::Deserialize(_stream);
}

int SpriteSheet::GetCurrentClip(AnimationNames _name) {
	//Note: The below may need to be <= 0 rather than < 0.
	if (m_animations.count(_name) < 0) { //Checking if we have the right animation by using the dictionary of m_animations with the _name key.
		return 0; //may need to return -1.
	}
	return m_animations[_name]->GetClipCurrent();
}

void SpriteSheet::ToString() {
	cout << "SPRITE SHEETL ";
	cout << " Rows: " << (int)m_rows;
	cout << " Columns: " << (int)m_columns;
	cout << " ClipSizeX: " << (int)m_clipSizeX;
	cout << " ClipSizeY: " << (int)m_clipSizeY;
	Resource::ToString();
}