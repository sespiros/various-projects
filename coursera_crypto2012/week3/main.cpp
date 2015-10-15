//  Collision Detection Algorithm for 50 lsb of SHA256
//
//
//  Spyros Seimenis
//  Computer Engineering and Informatics Department
//  12 April 2012
//
#include <stdint.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>

#include <cryptopp/sha.h>

class hash
{
public:
    uint8_t lsb[8];

    operator uint64_t() const {
        return *(uint64_t*)lsb;
    }

    hash(uint8_t full_hash[])
    {
        for (size_t s=CryptoPP::SHA256::DIGESTSIZE-1,d=0; d<7; d++,s--)
            lsb[d]=full_hash[s];

        // 8:8:8:8:8:8:2:0 // 50 bits!
        lsb[6]&=0x03;
        lsb[7]=0;
    }
};

void sha256(std::string , uint8_t* );
std::string random_string(size_t );

int main(int argc, char *argv[])
{
    std::map<hash,std::string> hashes;

    bool done=false;
    uint64_t rounds=0;
    uint8_t full_hash[CryptoPP::SHA256::DIGESTSIZE];

    while (!done)
    {
        rounds++;

        std::string this_random_string=random_string(10);

        sha256(this_random_string, full_hash);
        hash this_short_hash(full_hash);

        if (hashes.find(this_short_hash)!=hashes.end())
        {
            if (hashes[this_short_hash]!=this_random_string)
            {
                done=true;
                std::cout << this_random_string << " and " << hashes[this_short_hash]
                          << " have hash " << std::hex << (uint64_t)this_short_hash
                          << std::endl;
            }
        }
        else
            hashes[this_short_hash]=this_random_string;
    }
    std::cout << std::dec << "found after " << rounds << " rounds" << std::endl;
}

std::string random_string(size_t len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string s;
    for (size_t i=0; i<len; i++)
        s.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);

    return s;
}

void sha256(std::string plain, uint8_t digest[CryptoPP::SHA256::DIGESTSIZE])
{
    CryptoPP::SHA256 hash;
    hash.CalculateDigest ( digest, ( byte * ) plain.c_str(), plain.length() );
}
