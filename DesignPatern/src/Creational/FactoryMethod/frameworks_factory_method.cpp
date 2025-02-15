#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

/* Abstract base class declared by framework */
class Document {
public:
    explicit Document(const string& fn) : name(fn) {}
    virtual ~Document() = default;
    virtual void Open() = 0;
    virtual void Close() = 0;
    string GetName() const { return name; }

private:
    string name;
};

/* Concrete derived class defined by client */
class MyDocument : public Document {
public:
    explicit MyDocument(const string& fn) : Document(fn) {}
    void Open() override {
        cout << "   MyDocument: Open()" << endl;
    }
    void Close() override {
        cout << "   MyDocument: Close()" << endl;
    }
};

/* Framework declaration */
class Application {
public:
    Application() { cout << "Application: ctor" << endl; }
    
    void NewDocument(const string& name) {
        cout << "Application: NewDocument()" << endl;
        auto doc = CreateDocument(name);
        doc->Open();
        _docs.push_back(move(doc));
    }
    
    void ReportDocs() {
        cout << "Application: ReportDocs()" << endl;
        for (const auto& doc : _docs) {
            cout << "   " << doc->GetName() << endl;
        }
    }

protected:
    virtual unique_ptr<Document> CreateDocument(const string&) = 0;

private:
    vector<unique_ptr<Document>> _docs;
};

/* Customization of framework defined by client */
class MyApplication : public Application {
public:
    MyApplication() { cout << "MyApplication: ctor" << endl; }
    
protected:
    unique_ptr<Document> CreateDocument(const string& fn) override {
        cout << "   MyApplication: CreateDocument()" << endl;
        return make_unique<MyDocument>(fn);
    }
};

int main() {
    MyApplication myApp;
    myApp.NewDocument("foo");
    myApp.NewDocument("bar");
    myApp.ReportDocs();
    return 0;
}
