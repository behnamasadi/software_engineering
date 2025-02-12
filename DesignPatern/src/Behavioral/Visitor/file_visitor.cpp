#include <iostream>
#include <memory>
#include <vector>

class AbstractDispatcher;  // Forward declare AbstractDispatcher

class File {  // Parent class for the elements (ArchivedFile, SplitFile, ExtractedFile)
 public:
  virtual ~File() = default;

  // This function accepts an object of any class derived from AbstractDispatcher
  virtual void Accept(const std::shared_ptr<AbstractDispatcher>& dispatcher) = 0;
};

// Forward declare specific elements (files) to be dispatched
class ArchivedFile;
class SplitFile;
class ExtractedFile;

class AbstractDispatcher {  // Declares the interface for the dispatcher
 public:
  virtual ~AbstractDispatcher() = default;

  // Declare overloads for each kind of file to dispatch
  virtual void Dispatch(const std::shared_ptr<ArchivedFile>& file) = 0;
  virtual void Dispatch(const std::shared_ptr<SplitFile>& file) = 0;
  virtual void Dispatch(const std::shared_ptr<ExtractedFile>& file) = 0;
};

class ArchivedFile : public File, public std::enable_shared_from_this<ArchivedFile> {
 public:
  void Accept(const std::shared_ptr<AbstractDispatcher>& dispatcher) override {
    dispatcher->Dispatch(shared_from_this());
  }
};

class SplitFile : public File, public std::enable_shared_from_this<SplitFile> {
 public:
  void Accept(const std::shared_ptr<AbstractDispatcher>& dispatcher) override {
    dispatcher->Dispatch(shared_from_this());
  }
};

class ExtractedFile : public File, public std::enable_shared_from_this<ExtractedFile> {
 public:
  void Accept(const std::shared_ptr<AbstractDispatcher>& dispatcher) override {
    dispatcher->Dispatch(shared_from_this());
  }
};

class Dispatcher : public AbstractDispatcher {
 public:
  void Dispatch(const std::shared_ptr<ArchivedFile>&) override {
    std::cout << "dispatching ArchivedFile" << std::endl;
  }

  void Dispatch(const std::shared_ptr<SplitFile>&) override {
    std::cout << "dispatching SplitFile" << std::endl;
  }

  void Dispatch(const std::shared_ptr<ExtractedFile>&) override {
    std::cout << "dispatching ExtractedFile" << std::endl;
  }
};

class FileCollection {
 private:
  std::vector<std::shared_ptr<File>> files;

 public:
  void addFile(const std::shared_ptr<File>& file) {
    files.push_back(file);
  }

  void processFiles(const std::shared_ptr<AbstractDispatcher>& dispatcher) {
    for (const auto& file : files) {
      file->Accept(dispatcher);
    }
  }
};

int main() {
  auto archived_file = std::make_shared<ArchivedFile>();
  auto split_file = std::make_shared<SplitFile>();
  auto extracted_file = std::make_shared<ExtractedFile>();

  FileCollection file_collection;
  file_collection.addFile(archived_file);
  file_collection.addFile(split_file);
  file_collection.addFile(extracted_file);

  auto dispatcher = std::make_shared<Dispatcher>();
  file_collection.processFiles(dispatcher);

  return 0;
}