#include <iostream>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

string target;

string removeChars( string s, int pos, bool f( char c ) )
{
   if ( pos >= s.size() ) return s;                                  // safety if starts beyond end of string
   string::iterator end = remove_if( s.begin() + pos, s.end(), f );  // 'removed' chars still in s; end points to them or end of string
   return s.substr( 0, end - s.begin() );                            // just return the non-removed characters
}

bool isIn( char c ) { return target.find( toupper( c ) ) != string::npos; }

bool notAlpha( char c ) { return !isalpha( c ); }

string soundex( string word )
{
   map<char,char> cmap = { {'B','1'}, {'F','1'}, {'P','1'}, {'V','1'},
                           {'C','2'}, {'G','2'}, {'J','2'}, {'K','2'}, {'Q','2'}, {'S','2'}, {'X','2'}, {'Z','2'},
                           {'D','3'}, {'T','3'},
                           {'L','4'},
                           {'M','5'}, {'N','5'},
                           {'R','6'} };


   // Remove non-alphabetic characters
   string result = removeChars( word, 0, notAlpha );

   // Put in upper case
   for ( char &c : result ) c = toupper( c );

   // Store first character
   char firstLetter = result[0];

   // Remove all occurrences of H and W except first letter
   target = "HW";   result = removeChars( result, 1, isIn );

   // Map consonants to digits
   for ( char &c : result ) { if ( cmap.count( c ) ) c = cmap[c]; }

   // Replace all adjacent same digits with one digit
   for ( int i = 1; i < result.size(); i++ ) if ( result[i] == result[i-1] ) result[i-1] = '*';
   target = "*";   result = removeChars( result, 1, isIn );

   // Remove all occurrences of AEIOUY except first letter
   target = "AEIOUY";   result = removeChars( result, 1, isIn );

   // Replace first letter
   result[0] = firstLetter;

   // Get correct length and return
   result += "000";
   return result.substr( 0, 4 );
}


int main()
{
   string word;
   while ( true )
   {
      cout << "Enter a word (empty to end): ";   getline( cin, word );
      if ( word == "" ) exit( 0 );
      cout << "Soundex representation is " << soundex( word ) << endl;
   }
}
