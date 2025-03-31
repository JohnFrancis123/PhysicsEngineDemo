#include "TTFont.h"
#include "Renderer.h"

TTFont::TTFont() { //initialize member variables so no garbage values
	m_font = nullptr;
	destRect = { };
}

TTFont::~TTFont() {
	Shutdown();
}

void TTFont::Initialize(int _pointSize) { //Initializes font library
	M_ASSERT((TTF_Init() >= 0), "Unable to initialize SDL TTF."); //if greater than or equal zero, success
	//open font with specific font size as shown below
	//when we need same font with multiple sizes, we create multiple instances of TTFont.
	M_ASSERT((m_font = TTF_OpenFont("../Assets/Fonts/arial.ttf", _pointSize)) != nullptr, "Failed to load font."); //open arial.ttf font
}
//NOTE: SOME FONTS ARE COPYRIGHTED
void TTFont::Shutdown() {
	TTF_Quit(); //we may need to call Shutdown() from the destructor.
}
//NOTE: We use SDL color instead of our own here.
void TTFont::Write(SDL_Renderer* _renderer, const char* _text, SDL_Color _color, SDL_Point _pos) {
	if (strlen(_text) == 0) return; //to avoid working with empty strings

	//NOTE: This method may not be efficient for larger games. Just for demonstrative purposes.
	SDL_Surface* surface;
	surface = TTF_RenderUTF8_Blended(m_font, _text, _color);

	SDL_Texture* texture;
	texture = SDL_CreateTextureFromSurface(_renderer, surface); //create a texture from the surface to put in the vram
	//NOTE: When we render anything onto the screen, it must be in VRAM
	//SDL_FLIP_NONE means the TGA is not flipped, so should not be flipped.
	SDL_Rect destRect{ _pos.x, _pos.y, surface->w, surface->h };
	M_ASSERT(((SDL_RenderCopyEx(_renderer, texture, nullptr, &destRect, 0,
		nullptr, SDL_FLIP_NONE)) >= 0), "Could not render texture");

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
} //we have a course on OpenGL later on.