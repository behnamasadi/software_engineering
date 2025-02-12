#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <vector>

class Snapshot {
public:
    virtual std::string getState() = 0;
    virtual std::string getTimestamp() = 0;
    virtual std::string getName() = 0;
    virtual ~Snapshot() = default;
};

class TextSnapshot : public Snapshot {
private:
    std::string textState;
    std::string timestamp;

public:
    TextSnapshot(std::string state) : textState(state) {
        std::time_t now = std::time(nullptr);
        timestamp = std::ctime(&now);
        timestamp.pop_back(); // Remove newline added by ctime
    }

    std::string getState() override {
        return textState;
    }

    std::string getTimestamp() override {
        return timestamp;
    }

    std::string getName() override {
        return timestamp + " / " + textState;
    }
};

class Editor {
    std::string textContent;

public:
    Editor(std::string initialText) : textContent(initialText) {
        std::cout << "Editor: Initial content set to: \"" << textContent << "\"\n";
    }

    std::unique_ptr<Snapshot> save() {
        return std::make_unique<TextSnapshot>(textContent);
    }

    void restore(Snapshot* snapshot) {
        textContent = snapshot->getState();
        std::cout << "Editor: Restored content to: \"" << textContent << "\"\n";
    }

    void updateText(const std::string& newText) {
        textContent = newText;
        std::cout << "Editor: Updated content to: \"" << textContent << "\"\n";
    }
};

class HistoryManager {
    std::vector<std::unique_ptr<Snapshot>> history;
    Editor* editor;

public:
    HistoryManager(Editor* editor) : editor(editor) {}

    void saveState() {
        history.push_back(editor->save());
        std::cout << "HistoryManager: Saved current state.\n";
    }

    void undo() {
        if (history.empty()) {
            std::cout << "HistoryManager: No states to restore.\n";
            return;
        }

        std::unique_ptr<Snapshot> lastSnapshot = std::move(history.back());
        history.pop_back();
        std::cout << "HistoryManager: Restoring to: " << lastSnapshot->getName() << "\n";
        editor->restore(lastSnapshot.get());
    }
};

int main() {
    Editor editor("Initial Draft");
    HistoryManager historyManager(&editor);

    editor.updateText("First Edit");
    historyManager.saveState();

    editor.updateText("Second Edit");
    historyManager.saveState();

    historyManager.undo();

    editor.updateText("Final Edit");
    historyManager.saveState();

    historyManager.undo();
    historyManager.undo();
}
