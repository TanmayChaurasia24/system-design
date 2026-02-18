#include <iostream>
#include <fstream>
using namespace std;

class DocumentElement {
public:
  virtual string render() = 0;
};

class TextElement : public DocumentElement {
private:
  string text;

public:
  TextElement(string t) { 
    this->text = t; 
  }

  string render() override {
    return text;
  }
};

class ImageElement : public DocumentElement {
  private:
    string path;
  public:
    ImageElement(string path) {
      this->path = path;
    }

    string render() override {
      return "Image: " + path;
    }
};

class NewLineElement : public DocumentElement {
  public:
    string render() override {
      return "\n";
    }
};

class TabSpaceElement : public DocumentElement {
  public:
    string render() override {
      return "\t";
    }
};

class Document{
  private:
    vector<DocumentElement*> elements;
  public:
    void addElement(DocumentElement* element) {
      elements.push_back(element);
    }

    string render() {
      string result = "";
      for(auto element : elements) {
        result += element->render();
      }

      return result;
    }
};

class Persistance {
  public:
    virtual void save(string data) = 0;
};

class FileStorage : public Persistance {
  public:
    void save(string data) override {
      ofstream outFile("data.txt");
      if(outFile) {
        outFile << data;
        outFile.close();
        cout << "File saved successfully" << endl;
      } else {
        cout << "Error saving file" << endl;
      }
    }
};

class DBstorage : public Persistance {
  public:
   void save(string data) override {
     cout << "Saving data to database" << endl;
     // TODO: Save data to database
   }
};

class DocumentEditor {
  private:
    Document* document;
    Persistance* storage;
    string renderdocument;
  public:
    DocumentEditor(Document* document, Persistance* persistance) {
      this->document = document;
      this->storage = persistance;
    }

    void addText(string text) {
      document->addElement(new TextElement(text));
    }

    void addImage(string path) {
      document->addElement(new ImageElement(path));
    }

    void addNewLine() {
      document->addElement(new NewLineElement());
    }

    void addTabSpace() {
      document->addElement(new TabSpaceElement());
    }

    string renderDocument() {
      renderdocument = document->render();
      return renderdocument;
    }

    string saveDocument() {
      storage->save(renderDocument());
      return "Document saved successfully";
    }
};

int main() {
    Document* document = new Document();
    Persistance* persistence = new FileStorage();

    DocumentEditor* editor = new DocumentEditor(document, persistence);

    editor->addText("Hello, world!");
    editor->addNewLine();
    editor->addText("This is a real-world document editor example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addNewLine();
    editor->addImage("picture.jpg");

    cout << editor->renderDocument() << endl;

    editor->saveDocument();

    return 0;
}