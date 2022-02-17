#include <iostream>
#include <string.h>
#include <fstream>


/*
 *  This is my first C++ program!
 * */


// name of used wordlist (in same folder)
const std::string wordlist_name = "words.txt";
// Word input buffer
char wordin[50];
// Counter for wordlist length
int wl_length = 0;
//Variable that holds current working line
std::string line;



void print_help()
{
  std::cout << "usage: xkcdpwgen [-h] [-w WORDS] [-c CAPS] [-n NUMBERS] [-s SYMBOLS]\n";
  std::cout << "\nGenerate a secure, memorable password using the XKCD method\n";
  std::cout << "\noptional arguments:\n";
  std::cout << "    -h, --help            show this help message and exit\n";
  std::cout << "    -w WORDS, --words WORDS\n";
  std::cout << "                          include WORDS words in the password (default=4)\n";
  std::cout << "    -c CAPS, --caps CAPS  capitalize the first letter of CAPS random words\n";
  std::cout << "                          (default=0)\n";
  std::cout << "    -n NUMBERS, --numbers NUMBERS\n";
  std::cout << "                          insert NUMBERS random numbers in the password\n";
  std::cout << "                          (default=0)\n";
  std::cout << "    -s SYMBOLS, --symbols SYMBOLS\n";
  std::cout << "                          insert SYMBOLS random symbols in the password\n";
  std::cout << "                          (default=0)\n";
}

std::string* get_words(int num)
{

  std::string* chosen_words = new std::string[num];
  
  int chosen_index[num];
  int file_index = 0;
  srand(time(0));

  // get _num_ number of random lines
  for(int i = 0; i < num; i++)
  {
    chosen_index[i] = rand() % wl_length;
  }

  // Open wordlist as word_list
  std::fstream word_list;
  word_list.open(wordlist_name, std::ios::in);

  if(word_list)
  {
    while(getline(word_list, line))
    {
      
      line.erase(line.size() -1, 1); 
      for(int i = 0; i < num; i++)
       {
          if(file_index == chosen_index[i])
          {
            chosen_words[i] = line;
          }
       }
       file_index++;
    }
  }
  else
  {
    exit(1);
  }
  word_list.close();

  return chosen_words;
}

int main(int argc, char *argv[]) 
{

  //flag and corrosponding argument (default if unset)
  int wordf = 0;
  std::string word = "4";

  int capsf = 0;
  std::string caps = "";

  int numbersf = 0;
  std::string numbers = "";

  int symbolsf = 0;
  std::string symbols = "";

  // Set flags and args (or exit)
  if(argc > 1) 
  {
    for (int i = 0; i < argc; i++)
    {
      if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
      {
        print_help();
        exit(0);
      }

      if (!strcmp(argv[i], "-w") || !strcmp(argv[i], "--words"))
      {
        wordf = 1;
        if (i < argc) {
          word = argv[i+1];
        } else {
          print_help();
          exit(0);
        }
      }
      
      if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--caps"))
      {
        capsf = 1;
        if (i < argc) {
          caps = argv[i+1];
        } else {
          print_help();
          exit(0);
        }
      }

      if (!strcmp(argv[i], "-n") || !strcmp(argv[i], "--numbers"))
      {
        numbersf = 1;
        if (i < argc) {
          numbers = argv[i+1];
        } else {
          print_help();
          exit(0);
        }
      }

      if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--symbols"))
      {
        symbolsf = 1;
        if (i < argc) {
          symbols = argv[i+1];
        } 
        else 
        {
          print_help();
          exit(0);
        }
      }
    }
  } 
  // get length of word list
  // Open wordlist as infile
  std::fstream infile;
  infile.open(wordlist_name, std::ios::in);
  if(infile)
  {
    while(getline(infile, line))
    {
    wl_length++;
    }

    infile.close();
  }
  else
  {
    exit(1);
  }

  
  // output variable
  std::string outpass = "";
  
  // get given number of words
  std::string* words;
  words = get_words(std::stoi(word));

  //capitalize if needed
  if(capsf)
  {
    int words_to_caps[std::stoi(caps)];
    if(std::stoi(caps) > std::stoi(word)){
      caps = word;
    }
    //choose words
    for(int i = 0; i < std::stoi(caps); i++){
      if(std::stoi(word) == std::stoi(caps)){
        words_to_caps[i] = i;
      } else {
        words_to_caps[i] = rand() % std::stoi(word);
        for(int j = 0; j < std::stoi(caps); j++){
          if(j != i && words_to_caps[i] == words_to_caps[j]){
           i--;
          }
        }
      }
    }
    for(int i = 0; i < std::stoi(word); i++){
      for(int j = 0; j < std::stoi(caps); j++){
        if(j < std::stoi(word) && words_to_caps[j] == i){
          words[i] = char(std::toupper(words[i].front())) 
            + words[i].substr(1, words[i].size()-1);
        }
      }
    }
  }

  // insert numbers if needed
  if(numbersf){
    
    for(int i = 0; i < std::stoi(numbers); i++){
      //choose random number (0-9)
      //insert into words
      int chosen_index = rand() % (std::stoi(word) + 1);
      if(chosen_index != 0){
        words[chosen_index - 1] = words[chosen_index - 1] + std::to_string((rand() % 10)); 
      }
      else
      {
        words[0] = std::to_string((rand() % 10)) + words[0];
      }
    }
  }

  // insert symbols if needed
  if(symbolsf){
    
    char symbol_list[] = {'~', '!', '@', '#', '$', '%', '^', '&', '*', '.', ':', ';'};

    for(int i = 0; i < std::stoi(symbols); i++){
      //choose random symbol (0-11)
      //insert into words
      int chosen_index = rand() % (std::stoi(word) + 1);
      if(chosen_index != 0){
        words[chosen_index - 1] = words[chosen_index - 1] + symbol_list[(rand() % 12)]; 
      }
      else
      {
        words[0] = symbol_list[(rand() % 12)] + words[0];
      }
    }
  }

  for(int i = 0; i < std::stoi(word); i++){
    outpass += words[i];
  }
 
  std::cout << outpass << "\n";

  return 0;
}



