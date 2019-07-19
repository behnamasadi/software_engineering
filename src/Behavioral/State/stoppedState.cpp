#include "stoppedState.hpp"
#include "playingState.hpp"


void StoppedState::play(MusicPlayer *player)
{
    player->setState(new PlayingState());
}

StoppedState::StoppedState():MusicPlayerState("STOP"){}
