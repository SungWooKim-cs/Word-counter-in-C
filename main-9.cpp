#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <stdlib.h>

vector <string> data;

//----------------------------------------------
string FixWord(string word)
//----------------------------------------------
{
    // Loop over characters to fix word
    string result = "";
    for (int i=0; i<(int)word.length(); i++)
    {
        // Save special character
        if (word[i] == '\'')
            result += word[i];
        
        // Save lower case letters
        else if ((word[i] >= 'a') && (word[i] <= 'z'))
            result += word[i];
        
        // Save upper case letters as lower case letters
        else if ((word[i] >= 'A') && (word[i] <= 'Z'))
            result += word[i] - 'A' + 'a';
    }
    return result;
}

//----------------------------------------------
void ReadWords(string filename)
//----------------------------------------------
{
    // Open input file
    ifstream din;
    din.open(filename.c_str());
    if (din.fail())
    {
        cout << "Error: Could not open " << filename << endl;
        return;
    }
    
    // Read words 
    string str = "";
    while (din >> str)
    {
        // Convert str to lower case
        str = FixWord(str);
        
        if(str != "")
            data.push_back(str);
    }
    
    for (int i; i<data.size(); i++)
        cout << data[i] << endl;
    din.close();
}

//--------------------------------------------------------
void merge_sort(vector <string>&data, int low, int high)
//--------------------------------------------------------
{
   // Check terminating condition
  int range = high - low + 1;
  if (range > 1)
  {
      // Divide the array and sort both halves
      int mid = (low + high) / 2;
      merge_sort(data, low, mid);
      merge_sort(data, mid + 1, high);

       // Create temporary array for merged data
      string *copy = new string[range];

       // Initialize array indices
      int index1 = low;
      int index2 = mid + 1;
      int index = 0;

       // Merge smallest data elements into copy array
      while (index1 <= mid && index2 <= high)
      {
	 if (data[index1] < data[index2])
	    copy[index++] = data[index1++];
	 else
	    copy[index++] = data[index2++];
      }

      // Copy any remaining entries from the first half
       while (index1 <= mid)
 	    copy[index++] = data[index1++];

       // Copy any remaining entries from the second half
       while (index2 <= high)
 	    copy[index++] = data[index2++];

      // Copy data back from the temporary array
      for (index = 0; index < range; index++)
	    data[low + index] = copy[index];
      delete[]copy;
  }
}

//--------------------------------------------------------
void hybrid_sort(vector<string> &words)
//--------------------------------------------------------
{
   // Creating an array of 26 vectors of strings
   vector <string> sorted [26];
   
   // Copying words into 26 vectors based on the first letter of the word
   for (int i=0; i < words.size(); i++)
   {
       string temp = words[i];
       char first_char = temp[0];
       int position = first_char - 'a';
       sorted[position].push_back(temp);
   }
   
   // Sorting all of the 26 vectors using an O(NlogN) sort algorithm
   for (int i=0; i<26; i++)
   {
       merge_sort(sorted[i], 0, sorted[i].size() - 1);
   }
   
   words.clear();
   
   // Copying words from 26 sorted vectors into original word vector
   for (int i=0; i<26; i++)
   {
       for (int j=0; j<sorted[i].size(); j++)
       {
           words.push_back(sorted[i][j]);
       }
   }
   
      int count = 1;
      
   // Outputting text file 
    ofstream dout;
    dout.open("book.count");
    
   // Calculating word frequencies
   for (int i=0; i<words.size()-1; i++)
   {
       string temp1 = words[i];
       string temp2 = words[i+1];
       
       if (temp1 == temp2)
            count++;
       else
       {
            dout << count << " " << temp1 << endl;
            count = 1;
       }
   }
   
   
}

int main()
{
  
  string filename;
   
  cout << "Project 5 \n" << "Enter the filename \n";
  cin >> filename;
  ReadWords(filename);
  hybrid_sort(data);
    
    return 0;
}