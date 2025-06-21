#include <bits/stdc++.h>
using namespace std;

void inputFromFiles() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL);
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-result"
    #ifndef ONLINE_JUDGE
        freopen("/home/bhumika0077/bhumi/input.in", "r", stdin);
        freopen("/home/bhumika0077/bhumi/output.out", "w", stdout);
    #endif
    #pragma GCC diagnostic pop
}

// Abstract class for document elements
class DocumentElement {
public:
    virtual string render() = 0;
    virtual ~DocumentElement() {}
};

// Text element
class TextElement : public DocumentElement {
private:
    string text;
public:
    TextElement(string text) : text(text) {}
    string render() override {
        return text;
    }
};

// Image element
class ImageElement : public DocumentElement {
private:
    string imagePath;
public:
    ImageElement(string imagePath) : imagePath(imagePath) {}
    string render() override {
        return "[ image: " + imagePath + "]";
    }
};

// New line element
class NewLineElement : public DocumentElement {
public:
    string render() override {
        return "\n";
    }
};

// Tab space element
class TabSpace : public DocumentElement {
public:
    string render() override {
        return "\t";
    }
};

// Document class
class Document {
private:
    vector<DocumentElement*> documentElements;
public:
    void addElement(DocumentElement* element) {
        documentElements.push_back(element);
    }

    string render() {
        string result;
        for (auto element : documentElements) {
            result += element->render();
        }
        return result;
    }

    ~Document() {
        for (auto element : documentElements) {
            delete element;
        }
    }
};

// Persistence interface
class Persistence {
public:
    virtual void save(string data) = 0;
    virtual ~Persistence() {}
};

// File storage class
class FileStorage : public Persistence {
public:
    void save(string data) override {
        ofstream outfile("document.txt");
        if (outfile) {
            outfile << data;
            outfile.close();
            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: unable to open file for writing" << endl;
        }
    }
};

// Placeholder for DB storage
class DBStorage : public Persistence {
public:
    void save(string data) override {
        // Simulate DB storage
        cout << "Document saved to database (simulated)" << endl;
    }
};

// Document editor class
class DocumentEditor {
private:
    Document* doc;
    Persistence* storage;
    string renderedDocument;
public:
    DocumentEditor(Document* doc, Persistence* storage) : doc(doc), storage(storage) {}

    void addText(string text) {
        doc->addElement(new TextElement(text));
    }

    void addImage(string imagePath) {
        doc->addElement(new ImageElement(imagePath));
    }

    void addNewLine() {
        doc->addElement(new NewLineElement());
    }

    void addTabSpace() {
        doc->addElement(new TabSpace());
    }

    string renderDocument() {
        if (renderedDocument.empty()) {
            renderedDocument = doc->render();
        }
        return renderedDocument;
    }

    void saveDocument() {
        storage->save(renderDocument());
    }
};

// Client usage example
int main() {
    inputFromFiles();

    Document* myDoc = new Document();
    Persistence* storage = new FileStorage();
    DocumentEditor editor(myDoc, storage);

    // Sample document content
    editor.addText("Hello, Bhumika!");
    editor.addNewLine();
    editor.addText("Here is an image:");
    editor.addNewLine();
    editor.addImage("images/flower.png");
    editor.addNewLine();
    editor.addTabSpace();
    editor.addText("This text is indented.");
    editor.addNewLine();

    // Save to file
    editor.saveDocument();

    // Clean up memory
    delete myDoc;
    delete storage;

    return 0;
}