#include "WavDraw.h"
#include "AssetController.h"
#include "Renderer.h"


WavDraw::WavDraw() {
	m_header = { };
	m_data = nullptr;
	m_wSize = { };
	m_stepSize = 0;
	m_wavData = nullptr;
	m_xPos = 0;
	m_prevLeft = { };
	m_prevRight = { };
}

WavDraw::~WavDraw() {
}

//this function will likely work for any file type.
bool WavDraw::CompareFileExt(string _source, string _ext) { //_source is the file name, while _ext is .WAV
	//NOTE: In the below, we are using a lambda function, to set the return value as an unsigned char array, returning to itself std::tolower(c). This means that it could have actually been its own function as well.
	std::transform(_source.begin(), _source.end(), _source.begin(), [](unsigned char c)
		{return std::tolower(c); });//transforming the entire _source string to become lower case (storing each character one by one into _source).

	if (_source.length() >= _ext.length()) { //extension CANNOT be longer than the source file name.
		return (0 == _source.compare(_source.length() - _ext.length(), _ext.length(), _ext)); //returning the length of the filename - extension
	}
	else {
		return false;
	}
}

//this function will only work for .WAV
void WavDraw::IntegrityChecks(Asset* _rawWav) { //integrity check specifically for .WAV.
	//Check if we have any wave data
	M_ASSERT(_rawWav->GetDataSize() > 44, "Not a valid WAV file");//checking if the size is 44 bytes.
	memcpy(&m_header, _rawWav->GetData(), sizeof(WAVHeader));

	//Check if the format is supported
	string guid = _rawWav->GetGUID(); //grabbing the GUID of the asset
	M_ASSERT((CompareFileExt(guid, ".wav") == true), "Not a valid WAV file."); //checking if it ends with .WAV
	int r = strcmp("RIFF", m_header.RIFFHeader);
	M_ASSERT(string(m_header.RIFFHeader, 4) == "RIFF", "Not a valid WAV file.");
	M_ASSERT(string(m_header.FMTHeader, 3) == "fmt", "Not a valid WAV file") //this one
		M_ASSERT(string(m_header.DataHeader, 4) == "data", "Not a valid WAV file.");
	M_ASSERT((m_header.AudioFormat == 1), "Only supports PCM format");
	M_ASSERT((m_header.NumChannels == 2), "Can only display 2 channels");
	M_ASSERT((m_header.BitDepth == 16), "Can only display 16bps");
}

void WavDraw::DrawWave(Asset* _rawWav, Renderer* _renderer, float _yZoom) {
	IntegrityChecks(_rawWav); //doing the integrity checks

	//if the integrity checks passed,
	//Render the axes
	m_wSize = _renderer->GetWindowSize(); //getting the window size as a member variable.
	_renderer->SetDrawColor(Color(128, 128, 128, 255)); //draw background as grey
	_renderer->RenderLine(Rect(0, m_wSize.Y / 4, m_wSize.X, m_wSize.Y / 4)); //creating a line from 0 to 1920
	_renderer->RenderLine(Rect(0, m_wSize.Y * 3 / 4, m_wSize.X, m_wSize.Y * 3 / 4)); //creating a line from 


	//Render the WAV
	m_stepSize = m_header.DataBytes / m_header.SampleAlignment / m_wSize.X * 2; //size of each step means X length of each line
	m_wavData = (short*)(_rawWav->GetData() + 44); //wav data starts at stack data entry + 44 bytes
	m_xPos = 0; //x pos starts at position 0
	//1920 samples
	for (int count = 0; count < m_header.DataBytes; count += m_stepSize) {
		int leftYPos = *(m_wavData + count); //Left channel sample, which is EVEN
		leftYPos = (int)(((m_wSize.Y / 4) + (float)leftYPos / m_wSize.Y * -1 * _yZoom));
		int rightYPos = *(m_wavData + count + 1); //Right channel sample, which is ODD
		rightYPos = (int)(((m_wSize.Y * 3 / 4) + (float)rightYPos / m_wSize.Y * -1 * _yZoom));
		if (count > 0) {
			_renderer->SetDrawColor(Color(255, 0, 0, 255));
			_renderer->RenderLine(Rect(m_xPos, leftYPos, m_prevLeft.X, m_prevLeft.Y)); //drawing a line between the first and second sample
			_renderer->SetDrawColor(Color(0, 0, 255, 255));
			_renderer->RenderLine(Rect(m_xPos, rightYPos, m_prevRight.X, m_prevRight.Y));
		}
		m_prevLeft = Point(m_xPos, leftYPos);
		m_prevRight = Point(m_xPos, rightYPos);
		m_xPos++;

		if (m_xPos > (int)m_wSize.X) break;
	}
}