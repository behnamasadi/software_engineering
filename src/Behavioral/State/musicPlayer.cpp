#include "musicPlayer.hpp"
#include "stoppedState.hpp"
#include <iostream>

void MusicPlayer::play()
{
    status->play(this);
}
void MusicPlayer::pause()
{
    status->pause(this);
}
void MusicPlayer::stop()
{
    status->stop(this);
}

MusicPlayer::MusicPlayer()
{
    this->status=new StoppedState();
}
void MusicPlayer::setState(MusicPlayerState *state)
{
    std::cout << "changing from " << this->status->getName() << " to "<<state->getName()<<std::endl;
	this->status=state;
}
MusicPlayer::~MusicPlayer()
{
	delete status;
}
