//https://boost-experimental.github.io/di/cpp-london-2017/#/2/34
#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>


/*
(+) God object - does too much!
(-) Tightly coupled (hard to extend/maintain)
(-) Hard to test (TDD/BDD)

*/

namespace simple
{
    class App
    {
        public:
        void run()
        {
            auto value = 0;
            {
                std::ifstream file{"input.txt"};
                assert(file.good());
                file >> value;
            }
            std::cout << value << '\n';
        }
    };
}



/*
(+/-) We can somewhat test it in isolation (can't test the App)
(-) Reader/Printer tightly coupled to the App
(-) Reader/Printer are still tightly coupled to the App
(-) Can't have different Readers/Printers
(-) Can't test factories easily


*/

namespace abstract
{
class Reader
{
    static constexpr auto path = "input.txt";
    std::ifstream file{path};
public:
    auto read()
    {
        auto value = 0;
        file >> value;
        return value;
    }
};

class Printer
{
    public:
    void print(int value)
    {
        std::cout << value << '\n';
    }
};


class App
{

public:
    Reader reader;
    Printer printer;

    void run()
    {
        printer.print(reader.read());
    }
};

}


/*
Object oriented design with dynamic polymorphism

*/
//namespace dependencyInjection
//{
//class IReader
//{
//public:
//    virtual ~IReader() noexcept = default;
//    virtual int read() = 0;
//};

//class FileReader final : public IReader
//{
//    std::shared_ptr<std::istream> input;

//public:
//    explicit FileReader(std::shared_ptr<std::istream> istreamPtr) // NOTE -> it's not a path!
//    {
//        input=istreamPtr;
//    }
//    int read() override;
//    ~FileReader(){}
//    //explicit FileReader(std::istream& istream):input(istream){}

//};

//class IPrinter
//{
//public:
//    virtual ~IPrinter() noexcept = default;
//    virtual void print(int) = 0;
//};

//class ConsolePrinter final : public IPrinter
//{
//    std::ostream& output;

//public:
//    explicit ConsolePrinter(std::ostream&);  // NOTE -> ostream
//    void print(int) override;                //         injection!
//    ~ConsolePrinter();


//};

//class App
//{
//    IReader& reader;
//    IPrinter& printer;

//public:
//    App(IReader& reader, IPrinter& printer): reader(reader), printer(printer) {}

//    void run()
//    {
//        printer.print(reader.read());
//    }
//};



//}



int main()
{

    simple::App{}.run();

    abstract::App{}.run();


    std::shared_ptr<std::fstream> filePtr;
    filePtr.reset( new std::fstream{"input.txt"}  );
    //auto reader = dependencyInjection::FileReader{filePtr};
//    auto& out = std::cout;
//    auto printer = dependencyInjection::ConsolePrinter{out};
//    dependencyInjection::App{reader, printer}.run();


}
