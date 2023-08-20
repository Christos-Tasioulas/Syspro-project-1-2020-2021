#ifndef INTERFACE
#define INTERFACE
#include "CitizenRecord.h"
#include "VirusBloom.h"
#include "VirusSkip.h"
#include <cstring>
// header file for function prototypes that will be used outside of classes 

// IsValid.cpp

// confirming the record is invalid
void record_error(string* record_array);

// checking whether the given potential record attributes
// are valid according to a given list of citizen records
// returns: 
// >2 if the record is new, 
// >1 if the record already eixsts but not the virus
// >0 if the record is invalid
int is_valid(string* record_array, List* citizen_list);

// checks whether the date given is valid
bool date_valid(string date);

// compares two dates
int compare_dates(string date1, string date2);

// examining whether the virus given has a bloom filter in the list given
// returns the bloomfilter itself if it exists
BloomFilter* virus_has_a_bloom_filter(string virus, List* virus_bloom_list);

// examining whether the virus given has skip lists in the list given
bool virus_has_skip_lists(string virus, List* virus_skip_list);

// examining whether the virus given has a skip list in the list given
// returns the skiplist depending the yesno argument itself if it exists
// if yesno == yes returns the skip list for the vaccinated people
// otherwise returns the skip list for the non vaccinated people
SkipList* virus_has_a_skip_list(string virus, List* virus_skip_list, string yesno);

// testing whether the citizen id given exists in the list given
CitizenRecord* id_exists(string id, List* citizen_list);

// testing whether the citizen has been recorded with the virus given
CitizenVirus* virus_exists(string virus, CitizenRecord* CR);

// returns whether the citizen has been vaccinated or not
bool citizen_is_vaccinated(string virus, CitizenRecord* CR);

// Free.cpp

// destroying everything the given citizen list includes
void destroy_citizen_list(List* citizen_list);

// destroying everything the given virus-bloom filter list includes
void destroy_virus_bloom_list(List* virus_bloom_list);

// destroying everything the given virus-skip list list includes
void destroy_virus_skip_list(List* virus_skip_list);

// destroying everything the given countries list list includes
void list_destroy_countries(List* countries);

// InputManager.cpp

// managing the input given from the user
// the lists as arguments are the ones to check the existence and the 
// validity of the arguments given
void input_manager(string input, List* citizen_list, List* virus_bloom_list, List* virus_skip_list, int bloom_size);

#endif