#include <iostream>

using namespace std;

// Parent class
class Encryption
{
private:
    string raw;
    string encoded;

public:
    void setRaw(string r);
    string getEncoded()
    {
        return encoded;
    }
    void setEncoded(string e)
    {
        encoded = e;
    }

    Encryption();
    Encryption(string raw);

    virtual char transform(char x) = 0;
};

// Child class
class ASCIIEncryption : public Encryption
{
private:

public:
    ASCIIEncryption();
    ASCIIEncryption(string raw);

    // Adds 2 to ASCII char
    char transform(char x)
    {
        return x + 1;
    }
};

void Encryption::setRaw(string r)
{
    raw = r;
}


ASCIIEncryption::ASCIIEncryption(string raw)
{
    setRaw(raw);

    for (char x : raw)
    {
        char encodedChar = transform(x);
        setEncoded(getEncoded() + encodedChar);
    }
}


int main()
{
    ASCIIEncryption x("Hello");

    cout << x.getEncoded();

    return 0;
}