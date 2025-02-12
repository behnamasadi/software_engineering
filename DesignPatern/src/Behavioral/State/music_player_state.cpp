#include <iostream>
#include <memory>
#include <string>

// Forward Declarations
class PlayerState;
class AudioPlayer;
class PauseMode;
class PlayMode;
class StopMode;

class PlayerState {
protected:
    std::string stateName;
public:
    virtual ~PlayerState() = default;
    virtual void play(AudioPlayer *player);
    virtual void pause(AudioPlayer *player);
    virtual void stop(AudioPlayer *player);
    std::string getName() { return stateName; }
protected:
    PlayerState(std::string name) : stateName(std::move(name)) {}
};

// AudioPlayer
class AudioPlayer {
private:
    std::shared_ptr<PlayerState> state;
public:
    AudioPlayer();
    void setState(std::shared_ptr<PlayerState> newState);
    void play();
    void pause();
    void stop();
    std::string currentState();
};

// Concrete States
class StopMode : public PlayerState {
public:
    StopMode() : PlayerState("STOPPED") {}
    void play(AudioPlayer *player) override;
};

class PlayMode : public PlayerState {
public:
    PlayMode() : PlayerState("PLAYING") {}
    void pause(AudioPlayer *player) override;
    void stop(AudioPlayer *player) override;
};

class PauseMode : public PlayerState {
public:
    PauseMode() : PlayerState("PAUSED") {}
    void play(AudioPlayer *player) override;
};

// State Method Implementations
void PlayerState::play(AudioPlayer *player) {
    std::cout << "Invalid transition from " << stateName << " to PLAY\n";
}

void PlayerState::pause(AudioPlayer *player) {
    std::cout << "Invalid transition from " << stateName << " to PAUSE\n";
}

void PlayerState::stop(AudioPlayer *player) {
    std::cout << "Invalid transition from " << stateName << " to STOP\n";
}

// AudioPlayer Implementation
AudioPlayer::AudioPlayer() : state(std::make_shared<StopMode>()) {
    std::cout << "AudioPlayer initialized in state: " << state->getName() << "\n";
}

void AudioPlayer::setState(std::shared_ptr<PlayerState> newState) {
    std::cout << "Transition: " << state->getName() << " -> " << newState->getName() << "\n";
    state = std::move(newState);
}

void AudioPlayer::play() {
    state->play(this);
}

void AudioPlayer::pause() {
    state->pause(this);
}

void AudioPlayer::stop() {
    state->stop(this);
}

std::string AudioPlayer::currentState() {
    return state->getName();
}

// StopMode Implementation
void StopMode::play(AudioPlayer *player) {
    player->setState(std::make_shared<PlayMode>());
}

// PlayMode Implementation
void PlayMode::pause(AudioPlayer *player) {
    player->setState(std::make_shared<PauseMode>());
}

void PlayMode::stop(AudioPlayer *player) {
    player->setState(std::make_shared<StopMode>());
}

// PauseMode Implementation
void PauseMode::play(AudioPlayer *player) {
    player->setState(std::make_shared<PlayMode>());
}

// Main Function
int main() {
    AudioPlayer player;
    player.play();
    player.play();  // Invalid transition
    player.pause();
    player.play();
    player.stop();
    player.pause(); // Invalid transition
}
