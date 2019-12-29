/*
https://www.tomdalling.com/blog/software-design/solid-class-design-the-open-closed-principle/
You should be able to extend a classes behavior, without modifying it.


//XMLConverter
class XMLConverter {
public:
    String convertDocumentToXML(Document doc);
}


//BinaryConverter
class BinaryConverter {
public:
    Data convertDocumentToBinary(Document doc);
}


//DocumentExporter

enum ConverterType {
    XMLConverterType,
    BinaryConverterType
};

class DocumentExporter {
private:
    URL _runSaveDialog();
    void _showSuccessDialog;
    ConverterType _converterType;
public:
    void setConverterType(ConverterType converterType);
    void exportDocument(Document doc);
};

void DocumentExporter::exportDocument(Document doc)
{
    URL fileURL = _runSaveDialog();

    switch(_converterType){
        case XMLConverterType:{
            XMLConverter xmlConverter;
            String xmlFileContent = xmlConverter.convertDocumentToXML(doc);
            xmlFileContent.writeToURL(fileURL);
            break;
        }

        case BinaryConverterType:{
            BinaryConverter binaryConverter;
            Data binaryFileContent = binaryConverter.convertDocumentToBinary(doc);
            binaryFileContent.writeToURL(fileURL);
            break;
        }

        default:
            LogError("Unrecognised converter type");
            return;
    }

    _showSuccessDialog();
}


The DocumentExporter class is not closed to change. Every time a new export format must be supported, the DocumentExporter class must be modified.
"𝙀𝙣𝙪𝙢𝙨 𝙖𝙣𝙙 𝙨𝙬𝙞𝙩𝙘𝙝 𝙨𝙩𝙖𝙩𝙚𝙢𝙚𝙣𝙩𝙨" are strong indicators that a class is not closed to changes.


he way to close DocumentExporter to changes, in this case, is to make an abstract base class for all the converters. Then, the converter can be supplied
to DocumentExporter via a technique called dependency injection. The solution is as follows:



class Converter {
public:
    virtual Data convertDocumentToData(Document doc) = 0;
};

//XMLConverter

class XMLConverter : public Converter {
public:
    Data convertDocumentToData(Document doc);
};

Data XMLConverter::convertDocumentToData(Document doc)
{
    //convert to xml here
}

//BinaryConverter

class BinaryConverter : public Converter {
public:
    Data convertDocumentToData(Document doc);
};

Data BinaryConverter::convertDocumentToData(Document doc)
{
    //convert to binary here
}

//DocumentExporter

class DocumentExporter {
private:
    URL _runSaveDialog();
    void _showSuccessDialog;
    Converter* _converter;
public:
    void setConverter(Converter* converter); //Here is the dependency injection function
    void exportDocument(Document doc);
};

void DocumentExporter::exportDocument(Document doc)
{
    URL fileURL = _runSaveDialog();
    Data fileContent = _converter.convertDocumentToData(doc);
    fileContent.writeToURL(fileURL);
    _showSuccessDialog();
}



*/

int main()
{

}
