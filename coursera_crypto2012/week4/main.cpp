//  CBC padding oracle attack demonstration
//
//
//  Spyros Seimenis
//  Computer Engineering and Informatics Department
//  14 April 2012
//
#include <stdint.h>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <iterator>

#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>

using namespace std;
using namespace CryptoPP;

std::string substring(std::string , const char* , const char* );
std::string xor_pad(std::string , uint8_t );
std::string xor_full(std::string , std::string );

int main(int argc, char **argv) {
    ifstream file("../proj4-log.txt");
    std::string cbc_iv;
    std::string oracles[4];
    std::string cbc_enc[5];
    std::string or_pad;

    //Handling of encrypted text
    getline(file, cbc_enc[0]);
    cbc_enc[0] = substring( cbc_enc[0], "/", " " );
    cbc_iv = cbc_enc[0].substr(0, 32);
    for(int i=1; i<4; i++) {
        cbc_enc[i] = cbc_enc[0].substr(i*32, 32);
    }

    //Handling of 404 requests
    std::string reg = "\" 404";
    uint8_t pad = 0x10;
    int i = 0;
    int counter = 0;
    while(!file.eof()) {
        getline(file, or_pad);
        if(or_pad.find(reg) != or_pad.npos) {
            or_pad = substring( or_pad, "/", " " );
            counter++;
            if(counter==16) {
                oracles[i] = or_pad.substr(0, 32);
                oracles[i++] = xor_pad(oracles[i],pad);
                counter = 0;
            }
        }
    }

    std::string plain = "";
    plain = xor_full(cbc_iv, oracles[1]);
    for(int i=1; i< 4; i++) {
        plain.append(xor_full(oracles[i+1], cbc_enc[i]));
    }
    cout << plain << endl;
}

std::string substring(std::string first, const char* init, const char* final) {
    size_t found;
    std::string data;

    data = first.substr(first.find(init)+1);
    data = data.substr(0,data.find(final));
    return data;
}

std::string xor_pad(std::string encoded, uint8_t pad) {
    std::string ret;
    std::string decoded;

    HexDecoder decoder;

    decoder.Attach( new StringSink( decoded ) );
    decoder.Put( (byte*)encoded.data(), encoded.size() );
    decoder.MessageEnd();

    for(int i=0; i < decoded.length(); i++)
        decoded[i] = decoded[i]^pad;

    HexEncoder encoder;

    encoder.Attach( new StringSink( ret ) );
    encoder.Put( (byte*)decoded.data(), decoded.size() );
    encoder.MessageEnd();

    return ret;
}

std::string xor_full(std::string encoded, std::string iv) {
    std::string ret;
    std::string decoded;
    std::string decoded_iv;

    HexDecoder decoder;

    decoder.Attach( new StringSink( decoded ) );
    decoder.Put( (byte*)encoded.data(), encoded.size() );
    decoder.MessageEnd();

    HexDecoder decoder_iv;

    decoder_iv.Attach( new StringSink( decoded_iv ) );
    decoder_iv.Put( (byte*)iv.data(), iv.size() );
    decoder_iv.MessageEnd();

    for(int i=0; i < decoded.length(); i++)
        decoded[i] = decoded[i]^decoded_iv[i];

    return decoded;
}

