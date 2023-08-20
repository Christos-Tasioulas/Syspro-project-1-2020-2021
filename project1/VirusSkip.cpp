#include "VirusSkip.h"

// Constructor
VirusSkip::VirusSkip(string virus, string yesno, int levels)
{
    this->virusName = virus;
    if(yesno == "YES")
    {
        this->are_vaccinated = true;
    }
    else this->are_vaccinated = false;
    this->sl = new SkipList(levels);
}

// Destructor
VirusSkip::~VirusSkip()
{
    delete this->sl;
}

// returning the name of the virus
string VirusSkip::get_virusname() const
{
    return this->virusName;
}

// returning whether the skip list is about vaccinated people or not 
bool VirusSkip::get_vaccination_state() const
{
    return this->are_vaccinated;
}

// returning the skip list iself
SkipList* VirusSkip::get_skip_list() const
{
    return this->sl;
}