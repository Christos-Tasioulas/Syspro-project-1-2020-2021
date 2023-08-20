#ifndef VIRUSBLOOM
#define VIRUSBLOOM
#include "BloomFilter.h"

class VirusBloom
{
private:
    string virusName;
    BloomFilter* bf;
public:
    // Constructor
    VirusBloom(string virus, int bloom_size);
    // Destructor
    ~VirusBloom();
    // returning the name of the virus
    string get_virus_name(void) const;
    // returning the bloom filter itself
    BloomFilter* get_bloom_filter(void) const;
};

#endif