// State — music player.
// The player delegates play/pause/stop to its current state object. Each state
// allows only the valid transitions; all others fall through to a default
// implementation that rejects the request.

#include <iostream>
#include <memory>
#include <string>
#include <utility>

class AudioPlayer;

class PlayerState {
public:
    virtual ~PlayerState() = default;

    // Default: reject the transition. Concrete states override what they allow.
    virtual void play(AudioPlayer& player);
    virtual void pause(AudioPlayer& player);
    virtual void stop(AudioPlayer& player);

    const std::string& name() const { return name_; }

protected:
    explicit PlayerState(std::string name) : name_(std::move(name)) {}

private:
    std::string name_;
};

class AudioPlayer {
public:
    AudioPlayer();

    void setState(std::unique_ptr<PlayerState> next);
    void play()  { state_->play(*this); }
    void pause() { state_->pause(*this); }
    void stop()  { state_->stop(*this); }

    const std::string& currentState() const { return state_->name(); }

private:
    std::unique_ptr<PlayerState> state_;
};

class StopMode : public PlayerState {
public:
    StopMode() : PlayerState("STOPPED") {}
    void play(AudioPlayer& player) override;
};

class PlayMode : public PlayerState {
public:
    PlayMode() : PlayerState("PLAYING") {}
    void pause(AudioPlayer& player) override;
    void stop(AudioPlayer& player) override;
};

class PauseMode : public PlayerState {
public:
    PauseMode() : PlayerState("PAUSED") {}
    void play(AudioPlayer& player) override;
};

void PlayerState::play(AudioPlayer&) {
    std::cout << "Invalid transition from " << name_ << " to PLAY\n";
}
void PlayerState::pause(AudioPlayer&) {
    std::cout << "Invalid transition from " << name_ << " to PAUSE\n";
}
void PlayerState::stop(AudioPlayer&) {
    std::cout << "Invalid transition from " << name_ << " to STOP\n";
}

AudioPlayer::AudioPlayer() : state_(std::make_unique<StopMode>()) {
    std::cout << "AudioPlayer starts in " << state_->name() << '\n';
}

void AudioPlayer::setState(std::unique_ptr<PlayerState> next) {
    std::cout << "  " << state_->name() << " -> " << next->name() << '\n';
    state_ = std::move(next);
}

void StopMode::play(AudioPlayer& player)   { player.setState(std::make_unique<PlayMode>()); }
void PlayMode::pause(AudioPlayer& player)  { player.setState(std::make_unique<PauseMode>()); }
void PlayMode::stop(AudioPlayer& player)   { player.setState(std::make_unique<StopMode>()); }
void PauseMode::play(AudioPlayer& player)  { player.setState(std::make_unique<PlayMode>()); }

int main() {
    AudioPlayer player;
    player.play();
    player.play();    // invalid: PLAYING -> PLAY
    player.pause();
    player.play();
    player.stop();
    player.pause();   // invalid: STOPPED -> PAUSE
}
