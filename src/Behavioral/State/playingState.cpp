#include "playingState.hpp"
#include "pausedState.hpp"
#include "stoppedState.hpp"

void  PlayingState::pause(MusicPlayer *player)
{
    player->setState(new PausedState());
}

void PlayingState::stop(MusicPlayer *player)
{
    player->setState(new StoppedState());
}

PlayingState::PlayingState():MusicPlayerState("PLAYING")
{
    //this->status=new StoppedState();

}

PlayingState::~PlayingState()
{

}
