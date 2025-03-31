#ifndef TTFONT_H
#define TTFONT_H

#include "StandardIncludes.h"

class Renderer; //Does not contain a renderer variable pointer, so early declaration not REQUIRED, but it works.
//By including StandardIncludes, we already have a Renderer anyway, so early declaration may be redundant.
class TTFont
{
public:
	// Constructors/Destructors
	TTFont();
	virtual ~TTFont();

	//Methods
	void Initialize(int _pointSize); //_pointSize is font size
	//Write passes renderer, text, color, and position to the method
	void Write(SDL_Renderer* _renderer, const char* _text, SDL_Color _color, SDL_Point _pos);
	void Shutdown();

private:
	//Methods
	TTF_Font* m_font;
	SDL_Rect destRect; //This is where we want to render the texture on screen
};

#endif // TTFONT_H