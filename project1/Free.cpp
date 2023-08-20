// C++ file to destroy complicated data structures
#include "Interface.h"

// destroying everything the given citizen list includes
void destroy_citizen_list(List* citizen_list)
{
    // searching in the list for each record in order to delete it
    ListNode* node;
    node = citizen_list->get_first();
    while(node != NULL)
    {
        // deleting the virus list for each citizen before the record itself
        CitizenRecord* CR; 
        CR = (CitizenRecord*) node->get_value();

        // searching the viruses in each citizen's list in order to delete them
        List* cvl; 
        cvl = CR->get_virus_list();
        ListNode* temp;
        temp = cvl->get_first();
        while(temp != NULL)
        {
            // deleting each virus
            CitizenVirus* CV;
            CV = (CitizenVirus*) temp->get_value();
            delete CV;
            temp = temp->get_next();
        }

        // deleting the record itself
        delete CR;
        node = node->get_next();

    }

    // deleting the citizen itself
    delete citizen_list;
}

// destroying everything the given virus-bloom filter list includes
void destroy_virus_bloom_list(List* virus_bloom_list)
{
    ListNode* node;
    node = virus_bloom_list->get_first();
    while(node != NULL)
    {
        VirusBloom* VB;
        VB = (VirusBloom*) node->get_value();
        delete VB;
        node = node->get_next();
    }
    delete virus_bloom_list;
}

// destroying everything the given virus-skip list list includes
void destroy_virus_skip_list(List* virus_skip_list)
{
    ListNode* node;
    node = virus_skip_list->get_first();
    while(node != NULL)
    {
        VirusSkip* VS;
        VS = (VirusSkip*) node->get_value();
        delete VS;
        node = node->get_next();
    }
    delete virus_skip_list;
}

// destroying everything the given countries list list includes
void list_destroy_countries(List* countries)
{
    ListNode* node;
    node = countries->get_first();
    while(node != NULL)
    {
        string* country;
        country = (string*) node->get_value();
        delete country;
        node = node->get_next();
    }
    delete countries;
}