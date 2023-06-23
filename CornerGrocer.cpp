// Author - Ghana Phuyel
// CS-210

#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class CornerGrocer {
    private:
        ifstream inputFile;
        string inputFileName;
        map<string, int> productFrequency;

        // opens up the input file for read
        bool openFile() {
            try {
                inputFile.open(inputFileName);
            } catch (ios_base::failure& e) {
                cout << "ERROR : Could not open the file !!" << endl;
            }

            return inputFile.is_open();
        }

        // creates a back up file by copying input file product and its frequency
        void createBackUp() {
            
            ofstream output("frequency.dat");
            string product;
            if (!openFile()) {
                cout << "Unable to open the input file." <<  endl;
            }
            if (!output.is_open()) {
                cout << "Failed to open the onput file." << endl;
            }

            while(inputFile >> product) {
                ++productFrequency[product]; // increment the frequency value using product as a key
            }

            // iterates through the productFrequency and write both key and value to the output file 
            for (auto& pair : productFrequency) {
                output << pair.first << ", " << pair.second << endl;
            }

            inputFile.close();
        }

    public:
        // constructor
        CornerGrocer(string fileName){
            inputFileName = fileName;
            createBackUp();
        }

        // display menu
        void displayMenu() {
            cout << "1. Input a word/item to check its frequency." << endl;
            cout << "2. Print the list of items/word and its frequency." << endl;
            cout << "3. Print the histogram of item/word and its frequency" << endl;
            cout << "4. Exit" << endl;
            cout << endl;
        }

        // prompt user for a word and find the frequency of that word in the map
        void printWordFrequency() {
            string word;
            cout << "Enter a word: ";
            cin >> word;
            cout << endl;
            map<string, int>::iterator it = productFrequency.find(word); // using maps `find` function to get the iterator and extract its name and value pair. 
            if (it != productFrequency.end()) {
                cout << it->second << endl;
            } else {
                cout << "Word is not found in the file" << endl;
            }
        }

        // print key/value from the map seperated by comma
        void printWordFrequencyList() {
            for (auto& pair : productFrequency) {
                cout << pair.first << ", " << pair.second << endl;
            }
        }

        // print the histogram of the map
        void printWordFrequencyHistogram() {
            bool is_open = openFile();
            if(is_open) {
                for (auto& product : productFrequency) {
                    int frequency = product.second;
                    cout << product.first << " ";
                    for (int i = 0; i < frequency; i++) {
                        cout << "*";
                    }
                    cout << endl;
                }
            }
        }
};

int main() {

    CornerGrocer grocer("CS210_Project_Three_Input_File.txt");
    int userChoice;
    grocer.displayMenu();
    try {
        cout << "Select an option: ";
        cin >> userChoice;
        cout << endl;
        switch (userChoice)
        {
        case 1:
            grocer.printWordFrequency();
            break;
        case 2:
            grocer.printWordFrequencyList();
            break;
        case 3: 
            grocer.printWordFrequencyHistogram();
            break;
        default:
            break;
        }
    } catch (ios_base::failure& e) {
        cout << "Error: Incorrect user input !!" << endl;
    }
}