// Memento — capture an object's state so it can be restored later, without
// exposing its internals.
//
// Roles:
//   Originator (Editor)    : creates and consumes mementos
//   Memento    (Snapshot)  : opaque state holder; only Editor can read it
//   Caretaker  (History)   : keeps mementos but never inspects them

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Editor {
public:
    // Snapshot is opaque to outside code: state_ is private and Editor is friend.
    class Snapshot {
        friend class Editor;
        explicit Snapshot(std::string text) : text_(std::move(text)) {}
        std::string text_;
    };

    void type(const std::string& text) {
        text_ = text;
        std::cout << "[Editor] now: \"" << text_ << "\"\n";
    }

    std::unique_ptr<Snapshot> save() const {
        return std::unique_ptr<Snapshot>(new Snapshot(text_));
    }

    void restore(const Snapshot& snap) {
        text_ = snap.text_;
        std::cout << "[Editor] restored: \"" << text_ << "\"\n";
    }

private:
    std::string text_;
};

class History {
public:
    void push(std::unique_ptr<Editor::Snapshot> snap) { stack_.push_back(std::move(snap)); }

    std::unique_ptr<Editor::Snapshot> pop() {
        if (stack_.empty()) return nullptr;
        auto snap = std::move(stack_.back());
        stack_.pop_back();
        return snap;
    }

private:
    std::vector<std::unique_ptr<Editor::Snapshot>> stack_;
};

int main() {
    Editor editor;
    History history;

    editor.type("Hello");
    history.push(editor.save());

    editor.type("Hello, world");
    history.push(editor.save());

    editor.type("oops");

    if (auto snap = history.pop()) editor.restore(*snap);  // back to "Hello, world"
    if (auto snap = history.pop()) editor.restore(*snap);  // back to "Hello"
}
