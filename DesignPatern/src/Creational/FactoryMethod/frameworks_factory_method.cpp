// Factory Method — framework hook variant.
//
// The framework (Application) defines the workflow but delegates *which*
// concrete Document to create to its subclass via createDocument(). Clients
// customize behavior by subclassing Application, not by editing it.

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Document {
public:
    explicit Document(std::string name) : name_(std::move(name)) {}
    virtual ~Document() = default;

    virtual void open()  = 0;
    virtual void close() = 0;

    const std::string& name() const { return name_; }

private:
    std::string name_;
};

class MyDocument : public Document {
public:
    using Document::Document;
    void open()  override { std::cout << "  MyDocument: open()\n"; }
    void close() override { std::cout << "  MyDocument: close()\n"; }
};

class Application {
public:
    Application() { std::cout << "Application: ctor\n"; }
    virtual ~Application() = default;

    void newDocument(const std::string& name) {
        std::cout << "Application: newDocument(" << name << ")\n";
        auto doc = createDocument(name);  // hook into subclass
        doc->open();
        docs_.push_back(std::move(doc));
    }

    void reportDocs() const {
        std::cout << "Application: docs:\n";
        for (const auto& doc : docs_) std::cout << "  " << doc->name() << '\n';
    }

protected:
    // Factory Method — subclasses decide the concrete type.
    virtual std::unique_ptr<Document> createDocument(const std::string& name) = 0;

private:
    std::vector<std::unique_ptr<Document>> docs_;
};

class MyApplication : public Application {
public:
    MyApplication() { std::cout << "MyApplication: ctor\n"; }

protected:
    std::unique_ptr<Document> createDocument(const std::string& name) override {
        std::cout << "  MyApplication: createDocument()\n";
        return std::make_unique<MyDocument>(name);
    }
};

int main() {
    MyApplication app;
    app.newDocument("foo");
    app.newDocument("bar");
    app.reportDocs();
}
