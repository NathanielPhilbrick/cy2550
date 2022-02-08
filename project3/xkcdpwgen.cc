#include <iostream>
#include <string.h>

using namespace std;



void print_help()
{
  cout << "usage: xkcdpwgen [-h] [-w WORDS] [-c CAPS] [-n NUMBERS] [-s SYMBOLS]\n";
  cout << "\nGenerate a secure, memorable password using the XKCD method\n";
  cout << "\noptional arguments:\n";
  cout << "    -h, --help            show this help message and exit\n";
  cout << "    -w WORDS, --words WORDS\n";
  cout << "                          include WORDS words in the password (default=4)\n";
  cout << "    -c CAPS, --caps CAPS  capitalize the first letter of CAPS random words\n";
  cout << "                          (default=0)\n";
  cout << "    -n NUMBERS, --numbers NUMBERS\n";
  cout << "                          insert NUMBERS random numbers in the password\n";
  cout << "                          (default=0)\n";
  cout << "    -s SYMBOLS, --symbols SYMBOLS\n";
  cout << "                          insert SYMBOLS random symbols in the password\n";
  cout << "                          (default=0)\n";
}

int main(int argc, char *argv[]) 
{

  //flag and corrosponding argument (0 or "" if unset)
  int wordf = 0;
  string word = "";

  int capsf = 0;
  string caps = "";

  int numbersf = 0;
  string numbers = "";

  int symbolsf = 0;
  string symbols = "";

  if(argc == 1) 
  {
    print_help();
    exit(0);
  } else 
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
        } else {
          print_help();
          exit(0);
        }
      }


 

    }
  }



  return 0;
}
