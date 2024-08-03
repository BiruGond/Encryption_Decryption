#include<bits/stdc++.h>
using namespace std;

void rearrangeDecryptedText(string &str) {

    int magicNumber = 10;

    for(int i=0; i<str.length(); i++) {
        if(int(str[i] - magicNumber) < 32) {
            str[i] = 127 - (32 - (str[i] - magicNumber));
        }
        else {
            str[i] = str[i] - magicNumber;
        }
    }

    for(int i=0; i<str.length()-1; i+=2) {
        if(i+1 < str.length()) {
            swap(str[i],str[i+1]);
        }
    }

    reverse(str.begin(),str.end());

}

void rearrangeMessage(string &str) {

    reverse(str.begin(),str.end());

    for(int i=0; i<str.length()-1; i+=2) {
        if(i+1 < str.length()) {
            swap(str[i],str[i+1]);
        }
    }

    int magicNumber = 10;

    for(int i=0; i<str.length(); i++) {
        if(int(str[i]) >= 117) {
            str[i] = ((str[i]+ magicNumber)%127 + 32);
        }
        else {
            str[i] = (str[i] + magicNumber);
        }
    }
}

void rearrangeKey(vector<int> &key) {

    reverse(key.begin(), key.end());

    for(int i=0; i<key.size()-1; i+=2) {
        if(i+1 < key.size()) {
            swap(key[i],key[i+1]);
        }
    }
}

vector<int> keyGeneration(int messageLength) {
    
    vector<int> key(2*messageLength);
    
    srand((unsigned) time(NULL));

    for(int i=0; i<2*messageLength; i++) {
        int x = 32 + (rand()%(126-32+1));
        key[i] = x;
    }

    return key;
}

int characterShift(int front, int back) {
    int frontDigitProduct = 1, backDigitProduct = 1;
    
    while(front) {
        int lastDigit = front%10;
        frontDigitProduct *= lastDigit;
        front /= 10;
    }

    while(back) {
        int lastDigit = back%10;
        backDigitProduct *= lastDigit;
        back /= 10;
    }

    return (frontDigitProduct + backDigitProduct);
}

void encode(string &message, vector<int> key) {

    rearrangeMessage(message);
    rearrangeKey(key);

    cout<<"\nMessage after rearranging : "<<message<<"\n";
    cout<<"final key : ";
    for(auto x : key) {
        cout<<x<<" ";
    }


    int front = 0;
    int back = key.size()-1;

    while(front < back) {

        int shift = characterShift(key[front],key[back]);
        
        if(shift > 95) {
            shift = shift%95 + 32;
        }

        if(message[front] + shift >= 127) {
            message[front] = (message[front] + shift)%127 + 32;
        }    
        else {
            message[front] = (message[front] + shift);
        }

        front++;
        back--;
    }

}

void decode(string encryptedText, vector<int> key) {

    rearrangeKey(key);

    int front = 0;
    int back = key.size()-1;

    string decryptedText;

    while(front < back) {
        int shift = characterShift(key[front],key[back]);

        if(shift > 95) {
            shift = shift%95 + 32;
        }

        if(encryptedText[front] - shift < 32) {
            decryptedText.push_back(127 - (32 - (encryptedText[front] - shift)));
        }
        else {
            decryptedText.push_back((encryptedText[front] - shift));
        }

        front++;
        back--;
    }

    cout<<"\nBefore rearranging decrypted text : "<<decryptedText;

    rearrangeDecryptedText(decryptedText);

    cout<<"\nPlain text should be : "<<decryptedText;
}

int main() {

    string message;
    getline(cin,message);
    vector<int> v = keyGeneration(message.length());

    cout<<"\nThis is the plain text : "<<message;

    encode(message,v);

    cout<<"\nEncrypted text ye aaya : "<<message;

    decode(message,v);

    return 0;
}