#include <iostream>
#include <vector>

class AbstractDispatcher;  // Forward declare AbstractDispatcher

class File
{  // Parent class for the elements (ArchivedFile, SplitFile and
              // ExtractedFile)
 public:
  // This function accepts an object of any class derived from
  // AbstractDispatcher and must be implemented in all derived classes
  virtual void Accept(AbstractDispatcher& dispatcher) = 0;
};

// Forward declare specific elements (files) to be dispatched
class ArchivedFile;
class SplitFile;
class ExtractedFile;

class AbstractDispatcher
{  // Declares the interface for the dispatcher
 public:
  // Declare overloads for each kind of a file to dispatch
  virtual void Dispatch(ArchivedFile& file) = 0;
  virtual void Dispatch(SplitFile& file) = 0;
  virtual void Dispatch(ExtractedFile& file) = 0;
};

class ArchivedFile : public File {  // Specific element class #1
 public:
  // Resolved at runtime, it calls the dispatcher's overloaded function,
  // corresponding to ArchivedFile.
  void Accept(AbstractDispatcher& dispatcher) override {
    dispatcher.Dispatch(*this);
  }
};

class SplitFile : public File {  // Specific element class #2
 public:
  // Resolved at runtime, it calls the dispatcher's overloaded function,
  // corresponding to SplitFile.
  void Accept(AbstractDispatcher& dispatcher) override {
    dispatcher.Dispatch(*this);
  }
};

class ExtractedFile : public File {  // Specific element class #3
 public:
  // Resolved at runtime, it calls the dispatcher's overloaded function,
  // corresponding to ExtractedFile.
  void Accept(AbstractDispatcher& dispatcher) override {
    dispatcher.Dispatch(*this);
  }
};

class Dispatcher : public AbstractDispatcher
{  // Implements dispatching of all
                                                // kind of elements (files)
 public:
  void Dispatch(ArchivedFile&) override {
    std::cout << "dispatching ArchivedFile" << std::endl;
  }

  void Dispatch(SplitFile&) override {
    std::cout << "dispatching SplitFile" << std::endl;
  }

  void Dispatch(ExtractedFile&) override {
    std::cout << "dispatching ExtractedFile" << std::endl;
  }
};

int main()
{
  ArchivedFile archived_file;
  SplitFile split_file;
  ExtractedFile extracted_file;

  std::vector<File*> files = {
      &archived_file,
      &split_file,
      &extracted_file,
  };

  Dispatcher dispatcher;
  for (File* file : files) {
    file->Accept(dispatcher);
  }
}
