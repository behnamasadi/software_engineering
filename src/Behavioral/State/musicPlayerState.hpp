#ifndef MUSICPLAYERSTATE_H
#define MUSICPLAYERSTATE_H

#include <string>
#include "musicPlayer.hpp"


class MusicPlayer;
class MusicPlayerState
{
    std::string statuseName;
    public:
    virtual void play(MusicPlayer *player);

    virtual void pause(MusicPlayer *player);

    virtual void stop(MusicPlayer *player);

    MusicPlayerState(std::string statuseName);

    std::string getName();

    virtual ~MusicPlayerState();


};
#endif //MUSICPLAYERSTATE_H

