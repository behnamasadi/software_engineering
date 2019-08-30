/*
Consider a class called XMLExporter. XMLExporter takes a Document object,
and exports it into a different file format for another application.



class XMLExporter {
private:
    URL _runSaveDialog();
    String _exportDocumentToXML(Document doc);
    void _showSuccessDialog();
public:
    void exportDocument(Document doc);
};

void XMLExporter::exportDocument(Document doc)
{
    String xmlFileContent = _exportDocumentToXML(doc);
    URL fileURL = _runSaveDialog();
    xmlFileContent.writeToURL(fileURL);
    _showSuccessDialog();
}


There are at least two reasons for change (a.k.a. responsibilities) in the XMLExporter class.
The class needs to be modified if the GUI changes — for example, if an options dialog is added.
Also, the class needs to be modified if the XML format changes, or the Document needs to be exported differently.


// XMLConverter
class XMLConverter {
public:
    String convertDocumentToXML(Document doc);
}

//  XMLExporter

class XMLExporter {
private:
    URL _runSaveDialog();
    void _showSuccessDialog();
public:
    void exportDocument(Document doc);
};

void XMLExporter::exportDocument(Document doc)
{
    XMLConverter converter;
    String xmlFileContent = converter.convertDocumentToXML(doc);
    URL fileURL = _runSaveDialog();
    xmlFileContent.writeToURL(fileURL);
    _showSuccessDialog();
}

*/

int main()
{

}
