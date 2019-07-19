#include "pausedState.hpp"
#include "playingState.hpp"

void PausedState::play(MusicPlayer *player)
{
    player->setState(new PlayingState());
}
PausedState::PausedState():MusicPlayerState("PAUSE"){}
