#ifndef STOPPEDSTATE_H
#define STOPPEDSTATE_H

#include "musicPlayerState.hpp"

class StoppedState: public MusicPlayerState
{
public:
    void play(MusicPlayer *player);
    StoppedState();

};
#endif //STOPPEDSTATE_H
