// This program should return the position of each occurence of the a pattern in a text using KMP algorithm

#include <iostream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

int* computeLPS(string pattern);
vector<int> kmp(string text, string pattern);
void print_text_with_highlights(string text, vector<int> positions, int pattern_size);

int main(void){
    string text; string pattern;
    cout << "Enter the pattern: ";
    cin >> pattern;

    cout << "Enter the text: ";
    cin >> text;

    vector<int> positions = kmp(text, pattern);

    // Just a nice way to print the positions
    if (positions.size() == 0){
        cout << "The pattern does not occur in the text." << endl;
        return 0;
    } else if (positions.size() == 1){
        cout << "The pattern occurs at position ";
        cout << positions[0] << endl;
        return 0;
    }

    cout << "The pattern occurs at positions ";
    for(int i = 0; i < positions.size() - 1; i++){
        cout << positions[i] << " ";
    }
    cout << "and " << positions[positions.size() - 1] << "." << endl;
    
}


// This function computes the longest prefix suffix array for the pattern
int* computeLPS(string pattern){
    int m = pattern.length();
    int *lps = new int[m];
    lps[0] = 0;
    int i = 1; int j = 0;  // i is the index of the suffix and j is the index of the prefix
    while(i < m){  // we start from the second character of the pattern
        if(pattern[i] == pattern[j]){  // if the characters match, we increment both i and j
            j++;
            lps[i] = j;  // the value of lps[i] is the length of the longest prefix that is also a suffix of the substring pattern[0..i]
            i++;
        }
        else{  // if the characters don't match, we need to move j back to the last matching character
            if(j != 0){  // if j is not at the beginning of the pattern, we move it back to the last matching character
                j = lps[j-1];  // we don't increment i because we need to compare the current character of the pattern with the character at the index j
            }
            else{  // if j is at the beginning of the pattern, we increment i
                lps[i] = 0;  // the value of lps[i] is 0 because there is no prefix that is also a suffix of the substring pattern[0..i]
                i++;
            }
        }
    }
    return lps;
}


// This function returns the positions of the occurences of the pattern in the text
vector<int> kmp(string text, string pattern){
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    int i = 0; int j = 0;  // i is the index of text and j is the index of pattern
    int *lps = computeLPS(pattern);
    while(i < n){
        if(text[i] == pattern[j]){  // if the characters match, increment both i and j
            i++; j++;
        }
        if(j == m){  // if j reaches the end of the pattern, we have found a match
            positions.push_back(i-j);
            j = lps[j-1];
        }
        else if(i < n && text[i] != pattern[j]){  // if the characters don't match, we need to move j back to the last matching character
            if(j != 0){  // if j is not at the beginning of the pattern, we move it back to the last matching character
                j = lps[j-1];
            }
            else{  // if j is at the beginning of the pattern, we increment i
                i++;
            }
        }
    }
    delete [] lps;
    return positions;
}


// I hope it works
