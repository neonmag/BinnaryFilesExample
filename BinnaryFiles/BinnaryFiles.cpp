#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    const string filename = "example.bin";

    int number = 42;
    double pi = 3.14159;
    string message = "Hello, binary file!";

    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error while openning file.\n";
        return 1;
    }

    outFile.write(reinterpret_cast<const char*>(&number), sizeof(number));
    outFile.write(reinterpret_cast<const char*>(&pi), sizeof(pi));

    size_t messageSize = message.size();
    outFile.write(reinterpret_cast<const char*>(&messageSize), sizeof(messageSize));
    outFile.write(message.c_str(), messageSize);

    outFile.close();
    cout << "Info successfully.\n";

    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error while readding.\n";
        return 1;
    }

    int readNumber;
    double readPi;
    size_t readMessageSize;
    string readMessage;

    inFile.read(reinterpret_cast<char*>(&readNumber), sizeof(readNumber));
    inFile.read(reinterpret_cast<char*>(&readPi), sizeof(readPi));

    inFile.read(reinterpret_cast<char*>(&readMessageSize), sizeof(readMessageSize));
    readMessage.resize(readMessageSize);
    inFile.read(&readMessage[0], readMessageSize);

    inFile.close();

    cout << "Info from file:\n";
    cout << "Number: " << readNumber << "\n";
    cout << "Number Pi: " << readPi << "\n";
    cout << "Message: " << readMessage << "\n";

    return 0;
}
