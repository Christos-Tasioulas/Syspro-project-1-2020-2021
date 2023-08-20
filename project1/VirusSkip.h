#ifndef VIRUSSKIP
#define VIRUSSKIP
#include "SkipList.h"

using namespace std;

class VirusSkip
{
private:
    string virusName;
    bool are_vaccinated;
    SkipList* sl;
public:
    // Constructor
    VirusSkip(string virus, string yesno, int levels);
    // Destructor
    ~VirusSkip();
    // returning the name of the virus
    string get_virusname() const;
    // returning whether the skip list is about vaccinated people or not 
    bool get_vaccination_state() const;
    // returning the skip list iself
    SkipList* get_skip_list() const;
};



#endif