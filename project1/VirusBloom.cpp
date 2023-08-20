#include "VirusBloom.h"

// Constructor
VirusBloom::VirusBloom(string virus, int bloom_size)
{
    this->virusName = virus;
    this->bf = new BloomFilter(bloom_size);
}

// Destructor
VirusBloom::~VirusBloom()
{
    delete this->bf;
}

// returning the name of the virus
string VirusBloom::get_virus_name(void) const
{
    return this->virusName;
}

// returning the bloom filter itself
BloomFilter* VirusBloom::get_bloom_filter(void) const
{
    return this->bf;
}