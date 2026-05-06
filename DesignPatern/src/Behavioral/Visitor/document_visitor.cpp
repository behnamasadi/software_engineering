// Visitor — render different document types through a single visitor.
// HTMLDocument and MarkdownDocument both expose accept(Visitor&); a Printer
// handles each format.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class HTMLDocument;
class MarkdownDocument;

class DocumentVisitor {
public:
    virtual ~DocumentVisitor() = default;
    virtual void visit(const HTMLDocument& doc) = 0;
    virtual void visit(const MarkdownDocument& doc) = 0;
};

class Document {
public:
    virtual ~Document() = default;

    void appendItem(std::string item) { content_.push_back(std::move(item)); }
    const std::vector<std::string>& content() const { return content_; }

    virtual void accept(DocumentVisitor& visitor) const = 0;

private:
    std::vector<std::string> content_;
};

class HTMLDocument : public Document {
public:
    void accept(DocumentVisitor& visitor) const override { visitor.visit(*this); }
};

class MarkdownDocument : public Document {
public:
    void accept(DocumentVisitor& visitor) const override { visitor.visit(*this); }
};

class DocumentPrinter : public DocumentVisitor {
public:
    void visit(const HTMLDocument& doc) override {
        std::cout << "<ul>\n";
        for (const auto& item : doc.content()) std::cout << "\t<li>" << item << "</li>\n";
        std::cout << "</ul>\n";
    }
    void visit(const MarkdownDocument& doc) override {
        for (const auto& item : doc.content()) std::cout << "- " << item << '\n';
    }
};

int main() {
    HTMLDocument html;
    html.appendItem("Item A");
    html.appendItem("Item B");

    MarkdownDocument md;
    md.appendItem("Item A");
    md.appendItem("Item B");

    DocumentPrinter printer;
    html.accept(printer);
    md.accept(printer);
}
