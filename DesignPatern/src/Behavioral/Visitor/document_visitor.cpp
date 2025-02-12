#include <string>
#include <vector>
#include <iostream>
#include <memory>

class DocumentVisitor;
class Document
{
protected:
    std::vector<std::string> content;

public:
    virtual void appendItem(const std::string&) = 0;
    virtual void accept(std::shared_ptr<DocumentVisitor> dv) = 0;
    virtual ~Document() = default;
    std::vector<std::string> getContent() const { return content; }
};

class HTMLDocument : public Document
{
public:
    const std::string tagStart = "<li>";
    const std::string tagEnd = "</li>";
    
    void appendItem(const std::string& item) override
    {
        content.push_back(item);
    }
    void accept(std::shared_ptr<DocumentVisitor> dv) override;
};

class MarkdownDocument : public Document
{
public:
    const std::string prefix = "- ";
    
    void appendItem(const std::string& item) override
    {
        content.push_back(item);
    }
    void accept(std::shared_ptr<DocumentVisitor> dv) override;
};

class DocumentVisitor
{
public:
    virtual void visit(std::shared_ptr<HTMLDocument>) = 0;
    virtual void visit(std::shared_ptr<MarkdownDocument>) = 0;
    virtual ~DocumentVisitor() = default;
};

class DocumentPrinter : public DocumentVisitor
{
public:
    void visit(std::shared_ptr<MarkdownDocument> md) override {
        for (const auto& item : md->getContent())
            std::cout << md->prefix << item << std::endl;
    }
    void visit(std::shared_ptr<HTMLDocument> hd) override {
        std::cout << "<ul>" << std::endl;
        for (const auto& item : hd->getContent())
            std::cout << "\t" << hd->tagStart << item << hd->tagEnd << std::endl;
        std::cout << "</ul>" << std::endl;
    }
};

class DocumentRenderer : public DocumentVisitor {};

void HTMLDocument::accept(std::shared_ptr<DocumentVisitor> dv) { dv->visit(std::make_shared<HTMLDocument>(*this)); }
void MarkdownDocument::accept(std::shared_ptr<DocumentVisitor> dv) { dv->visit(std::make_shared<MarkdownDocument>(*this)); }

int main()
{
    {
        auto d = std::make_shared<HTMLDocument>();
        d->appendItem("Item A");
        d->appendItem("Item B");
        d->accept(std::make_shared<DocumentPrinter>());
    }

    {
        auto d = std::make_shared<MarkdownDocument>();
        d->appendItem("Item A");
        d->appendItem("Item B");
        d->accept(std::make_shared<DocumentPrinter>());
    }
}
