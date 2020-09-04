//http://www.vishalchovatiya.com/double-dispatch-visitor-design-pattern-in-modern-cpp/
#include <string>
#include <vector>
#include <iostream>

class DocumentVisitor;
class Document
{
protected:
public:
    std::vector<std::string> content;

    virtual void addToList(std::string)=0;
    virtual void visit(DocumentVisitor* dv)=0;
};

/*
<ul>
  <li>item1</li>
  <li>item2</li>
  <li>item3</li>
</ul>
*/

class HTMLDocument:public Document
{
public:
    std::string start="<li>";
    std::string end="</li>";
    void addToList(std::string s)override
    {
        content.push_back(s);
    }
    void visit(DocumentVisitor* dv) override;
};

/*
* Item 1
* Item 2
  * Item 2a
  * Item 2b
*/

class MarkdownDocument:public Document
{
public:

    void visit(DocumentVisitor* dv) override ;
    std::string start="* ";
    void addToList(std::string s)override
    {
        content.push_back(s);
    }

};

class DocumentVisitor
{
public:
    void virtual visit(HTMLDocument*)=0;
    void virtual visit(MarkdownDocument*)=0;
};

class DocumentPrinter: public DocumentVisitor
{
public:
    void visit(MarkdownDocument * md) {
        for (auto &&item : md->content)
            std::cout << md->start << item << std::endl;
    }
    void visit(HTMLDocument* hd) {
        std::cout << "<ul>" << std::endl;
        for (auto &&item : hd->content)
            std::cout << "\t" << hd->start << item << hd->end << std::endl;
        std::cout << "</ul>" << std::endl;
    }
};

class DocumentRenderer: public DocumentVisitor{};

void HTMLDocument::visit(DocumentVisitor* dv) { dv->visit(this); }
void MarkdownDocument::visit(DocumentVisitor* dv)  { dv->visit(this); }



int main()
{
    {
        Document* d=new HTMLDocument;
        d->addToList("first");
        d->addToList("second");
        d->visit(new DocumentPrinter);
    }


    {
        Document* d=new MarkdownDocument;
        d->addToList("first");
        d->addToList("second");
        d->visit(new DocumentPrinter);
    }
}
