#include "Interface.h"
#include <fstream>

//global variable for the size of the file
int skip_size;

// visiting a citizen to print
void visit_citizen(void *my_citizen)
{ 
    CitizenRecord *c = (CitizenRecord *) my_citizen;
    c->print();
}

// visiting an id from the citizen record given
void visit_id(void *cr)
{
    CitizenRecord* CR = (CitizenRecord*) cr; 
    string id = CR->get_id();
    cout << id << " ----> ";
}

// visiting a virus bloom filter to print
void visit_virus_bloom(void *my_virus_bloom)
{ 
    VirusBloom *vb = (VirusBloom *) my_virus_bloom;
    cout << vb->get_virus_name() << endl;
    vb->get_bloom_filter()->Print();
}

// visiting a virus bloom filter to print
void visit_virus_skip(void *my_virus_skip)
{ 
    VirusSkip *vs = (VirusSkip *) my_virus_skip;
    cout << vs->get_virusname() << endl;
    if(vs->get_vaccination_state() == true) cout << "Vaccinated People IDs:" << endl;
    else cout << "Not Vaccinated People IDs:" << endl;
    vs->get_skip_list()->Print(visit_id);
}

// comparing ids from the citizen records given
int compare_ids(void* c1, void* c2)
{
    CitizenRecord* cr1 = (CitizenRecord*) c1;
    CitizenRecord* cr2 = (CitizenRecord*) c2;
    string s1 = cr1->get_id();
    string s2 = cr2->get_id();
    return atoi(s1.c_str()) - atoi(s2.c_str());
}

int main(int argc, char* argv[])
{
    

    // examining the number of the arguments given
    if (argc != 5)
    {
        cout << "Not enough arguments have been given!" << endl;
        return -1;
    }

    string myText;
    // default values
    char filename[20];
    int bloom_size = 102400;

    // examining the order and the validity of the arguments given on the run command
    if(!strcmp(argv[3], "-c") && !strcmp(argv[1], "-b"))
    {
        strcpy(filename, argv[4]);
        bloom_size = atoi(argv[2]);
    }
    else if(!strcmp(argv[1], "-c") && !strcmp(argv[3], "-b"))
    {
        strcpy(filename, argv[2]);
        bloom_size = atoi(argv[4]);
    } 
    else
    {
        cout << "Wrong arguments have been given!" << endl;
        return -1;  
    }

    // getting the size of the file
    ifstream citizenRecordsFileSize(filename);
    int file_size = 0;
    while (getline(citizenRecordsFileSize, myText))
    {
        file_size++;
    }
    skip_size = (int) log2(file_size);

    // reading from the text file
    ifstream citizenRecordsFile(filename);
    string citizen_record[8];

    List* citizen_list;
    citizen_list = new List();

    List* virus_bloom_list;
    virus_bloom_list = new List();

    List* virus_skip_list;
    virus_skip_list = new List();

    

    // using a while loop together with the getline() function to read the file line by line
    while (getline(citizenRecordsFile, myText)) 
    {

        // initialize the array with the records
        for(int n = 0; n < 8; n++)
        {
            citizen_record[n] = ""; 
        }

        // converting the string to c_string in order to token it
        char* record;
        record = new char [myText.length()+1];
        strcpy(record, myText.c_str());
        
        // seperating each line according to spaces
        // spaces determine each member of the class CitizenRecord
        char* cs;
        cs = strtok(record, " ");

        if(cs == NULL)
        {
            continue;
        }
        int i = 0;
        while(1)
        {
            string temp(cs);
            citizen_record[i] = temp;
            cs = strtok(NULL, " ");
            if(cs == NULL)
            {
                break;
            }
            i++;       
        }
        
        int valid = is_valid(citizen_record, citizen_list);
        if(valid == 0) record_error(citizen_record);  
        else 
        {

            CitizenRecord* CR;

            // if this is a new record
            if(valid == 2)
            {
                // creating a record with the array
                CR = new CitizenRecord(citizen_record);

                // inserting the record on a list with citizens
                citizen_list->ListInsertLast(CR);
            }
            else if(valid == 1) 
            {
                // citizen's id exists
                CR = id_exists(citizen_record[0], citizen_list);
            }

            // creating a bloom filter for the virus independent of the citizen's vaccination
            if(virus_has_a_bloom_filter(citizen_record[5], virus_bloom_list) == NULL)
            {
                VirusBloom* vb = new VirusBloom(citizen_record[5], bloom_size);
                virus_bloom_list->ListInsertLast(vb);
            }

            // creating two skip lists for the virus (vaccinated and not vaccinated people)
            // independent of the citizen's vaccination
            if(virus_has_skip_lists(citizen_record[5], virus_skip_list) == false)
            {
                VirusSkip* vs1 = new VirusSkip(citizen_record[5], "YES", skip_size);
                virus_skip_list->ListInsertLast(vs1);
                VirusSkip* vs2 = new VirusSkip(citizen_record[5], "NO", skip_size);
                virus_skip_list->ListInsertLast(vs2);
            }

            // coverting the id to c_string
            string id = CR->get_id();
            char* c_id = new char[id.length() + 1];
            strcpy(c_id, id.c_str());

            // inserting the citizen id in the BloomFilter only if they are vaccinated
            if(citizen_is_vaccinated(citizen_record[5], CR) == true)
            {
                SkipList* sl = virus_has_a_skip_list(citizen_record[5], virus_skip_list, "YES");
                BloomFilter* bf = virus_has_a_bloom_filter(citizen_record[5], virus_bloom_list);
                sl->Insert(CR, compare_ids); 
                bf->Insert((unsigned char*) c_id);    

            }
            else
            {
                string id = CR->get_id();
                SkipList* sl = virus_has_a_skip_list(citizen_record[5], virus_skip_list, "NO");
                sl->Insert(CR, compare_ids);
            }

            delete[] c_id;   

        } 

        delete[] record;

    }

    cout << "Type: /<command> <arguments>" << endl;
    string input;
    getline(cin, input);
    while(input != "/exit")
    {
        input_manager(input, citizen_list, virus_bloom_list, virus_skip_list, bloom_size);
        getline(cin, input);

    }

    destroy_citizen_list(citizen_list);
    destroy_virus_bloom_list(virus_bloom_list);
    destroy_virus_skip_list(virus_skip_list);

    // closing the file
    citizenRecordsFile.close();
    return 0;
}