#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <list>
#include <cstring>
#include <algorithm>
using namespace std;

// function prototypes
int convertRomanToArabic(string);
string convertArabicToRoman(int);

// Number struct
struct Number
{
   char roman[16];
   char arabic[5];
};

// main function
int main()
{
   // open the file to read
   fstream file;
   file.open("numbers1.txt", ios::in);

   // exit from the program if the input file does not exist
   if (file.fail())
   {
       cout << "The input file could not be opened!" << endl;
       exit(1);
   }

   // declare the required variables
   list<Number> lst;
   Number num;
   string readLine;
   int count = 0;

   // read data from the file
   file.seekg(0); // go to the first line
    while (getline(file, readLine))
   {
        
       if (readLine[0] == ' ')
       {
            string str = readLine.substr(16, 4);
           strcpy(num.arabic, str.c_str());
           string rom = convertArabicToRoman(atoi(str.c_str()));
           strcpy(num.roman, rom.c_str());
       }

       else
       {
            string str = readLine.substr(0, 15);
           strcpy(num.roman, str.c_str());
           
           int arab = convertRomanToArabic(str);
           stringstream ss;
           ss << arab;
           string s = ss.str();

           strcpy(num.arabic, s.c_str());
       }

       lst.push_back(num);

       count++;
   }

   // close the file
   file.close();

   // open the file to write
   file.open("numbers.txt", ios::out);

   //write data to the file
   auto itr = lst.crbegin();
   while (itr != lst.crend())
   {
       file << left << setw(15) << (*itr).roman << " " << setw(4) << (*itr).arabic << endl;
       itr++;
   }
   

   // close the file
   file.close();


   return 0;
} // end of main function

// convertRomanToArabic function implementation
int value(char roman)
{
    int results = 0;
    switch(roman)
    {
        case 'I':results = 1;
            break;
        case 'V':results = 5;
            break;
        case 'X':results = 10;
            break;
        case 'L':results = 50;
            break;
        case 'C':results = 100;
            break;
        case 'D':results = 500;
            break;
        case 'M':results = 1000;
            break;
    }
    return results;
}

//Function to convert Roman Numerals to Integer
int convertRomanToArabic(string str)
{
    int arabic=0, p=0;
    long n , i;
    n = str.length()-1;

    for( i=n; i>=0; i--)
    {
        if( value(str[i]) >= p)
            arabic = arabic + value(str[i]);
        else
            arabic = arabic - value(str[i]);

    p = value(str[i]);
    }
       return arabic;
} // end of convertRomanToArabic function

// convertArabicToRoman function implementation
string convertArabicToRoman(int arabic)
{
   string roman;
   int curr;

   if (arabic >= 1000)
    {
       curr = arabic / 1000;
       for (int i = 0; i < curr; i++)
       {
           roman += 'M';
       }

       arabic = arabic % 1000;
    }

   if (arabic >= 100)
    {
       curr = arabic / 100;

       if (curr == 9)
       {
           roman += "CM";
       }
       else if (curr >= 5)
       {
           roman += 'D';
           for (int i = 0; i < curr - 5; i++)
           {
               roman += 'C';
           }
       }
       else if (curr == 4)
       {
           roman += "CD";
       }
       else if (curr >= 1)
       {
           for (int i = 0; i < curr; i++)
           {
               roman += 'C';
           }
       }

       arabic = arabic % 100;
    }

   if (arabic >= 10)
   {
       curr = arabic / 10;
       if (curr == 9)
       {
           roman += "XC";
       }
       else if (curr >= 5)
       {
           roman += 'L';
           for (int i = 0; i < curr - 5; i++)
           {
               roman += 'X';
           }
       }
       else if (curr == 4)
       {
           roman += "XL";
       }
       else if (curr >= 1)
       {
           for (int i = 0; i < curr; i++)
           {
               roman += 'X';
           }
       }

       arabic = arabic % 10;
   }

   if (arabic >= 1)
   {
       curr = arabic;
       if (curr == 9)
       {
           roman += "IX";
       }
       else if (curr >= 5)
       {
           roman += 'V';
           for (int i = 0; i < curr - 5; i++)
           {
               roman += 'I';
           }
       }
       else if (curr == 4)
       {
           roman += "IV";
       }
       else if (curr >= 1)
       {
           for (int i = 0; i < curr; i++)
           {
               roman += 'I';
           }
       }
   }

   return roman;
}
