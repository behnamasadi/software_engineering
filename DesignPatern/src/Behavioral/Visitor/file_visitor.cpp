// Visitor — dispatch operations across a heterogeneous file collection.
// File subclasses (Archived/Split/Extracted) are stable; new operations are
// just new dispatchers (visitors).

#include <iostream>
#include <memory>
#include <vector>

class ArchivedFile;
class SplitFile;
class ExtractedFile;

class Dispatcher {
public:
    virtual ~Dispatcher() = default;
    virtual void dispatch(const ArchivedFile& file) = 0;
    virtual void dispatch(const SplitFile& file) = 0;
    virtual void dispatch(const ExtractedFile& file) = 0;
};

class File {
public:
    virtual ~File() = default;
    virtual void accept(Dispatcher& dispatcher) const = 0;
};

class ArchivedFile : public File {
public:
    void accept(Dispatcher& dispatcher) const override { dispatcher.dispatch(*this); }
};

class SplitFile : public File {
public:
    void accept(Dispatcher& dispatcher) const override { dispatcher.dispatch(*this); }
};

class ExtractedFile : public File {
public:
    void accept(Dispatcher& dispatcher) const override { dispatcher.dispatch(*this); }
};

class PrintDispatcher : public Dispatcher {
public:
    void dispatch(const ArchivedFile&)  override { std::cout << "dispatching ArchivedFile\n"; }
    void dispatch(const SplitFile&)     override { std::cout << "dispatching SplitFile\n"; }
    void dispatch(const ExtractedFile&) override { std::cout << "dispatching ExtractedFile\n"; }
};

int main() {
    std::vector<std::unique_ptr<File>> files;
    files.push_back(std::make_unique<ArchivedFile>());
    files.push_back(std::make_unique<SplitFile>());
    files.push_back(std::make_unique<ExtractedFile>());

    PrintDispatcher dispatcher;
    for (const auto& file : files) file->accept(dispatcher);
}
