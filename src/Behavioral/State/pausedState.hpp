#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H
#include "musicPlayerState.hpp"



class PausedState: public MusicPlayerState
{
public:
    void play(MusicPlayer *player);
    PausedState();

};
#endif //PAUSEDSTATE_H

