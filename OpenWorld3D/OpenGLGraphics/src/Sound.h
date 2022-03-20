#pragma once 

#include <irrKlang/irrKlang.h>

using namespace irrklang;

class Sound 
{
private:

	ISoundEngine* engine = createIrrKlangDevice();
	const char* filepath;
	bool isPlaying;
	float x, y, z;
    float time;

public:
	Sound();
	Sound(const char* filepath);
	~Sound();
	
	inline void testSound(){
		this->filepath = "res/music/intro.mp3";
		engine->play2D(filepath, true);
		engine->setSoundVolume(0.2f);
		this->isPlaying = true;
	};
	
	inline bool isPlayed() {
		if (isPlaying) {
			return true;
		}
		else 
		{
			return false;
		}
	}
	void setPlaying(bool isPlaying) {
		isPlaying = isPlaying;
	}

	void playSound() const;
	void stopSound() const;
	void playSound3D()const;
	void stopSound3D() const;

	void playSoundWithTime(float time);

	void setPositon();
	void getPosition();
};