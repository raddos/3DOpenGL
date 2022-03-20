#include "Sound.h"


Sound::Sound() {
	
}

Sound::Sound(const char* filepath) :filepath(filepath)
{
	if (engine == nullptr) {
		engine->drop();
	};

	engine->play2D(filepath, true);
}

Sound::~Sound(){
	engine->drop();
}

void Sound::playSound() const
{

}

void Sound::stopSound() const 
{
	engine->stopAllSounds();
}

void Sound:: playSound3D()const
{
	engine->play2D(filepath);

}

void Sound::stopSound3D() const 
{
	engine->stopAllSounds();
}

void Sound::playSoundWithTime(float time)
{
	this->time=time;

} 

void Sound::setPositon()
{

}

void Sound::getPosition()
{

}