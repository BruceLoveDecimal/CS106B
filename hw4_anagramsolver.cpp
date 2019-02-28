#include <string>
#include "set.h"
#include "letterinventory.h"
#include "vector.h"

using namespace std;

void findAnagramsHelper(int max, LetterInventory& Li, const Set<string>& anagram, Vector<string>& chosen, int& num, int& remain);
void phraseToWords(Set<string>& anagram, const Set<string>& dictionary, LetterInventory& Li); // to generate all possible anagrams for a given phrase

int findAnagrams(const string& phrase, int max, const Set<string>& dict) {
    LetterInventory Li = LetterInventory(phrase); // to use this variable to store the unchosen part of the phrase, then construct it for the input
    Vector<string> chosen;
    Set<string> choices;
    int anagramNum = 0, remain = max;
    phraseToWords(choices, dict, Li);

    if(max != 0){
        findAnagramsHelper(max, Li, choices, chosen, anagramNum, remain);
    }
    else{
        findAnagramsHelper(phrase.size(), Li, choices, chosen, anagramNum, remain);// it means no limit on the number of anagram words
    }
    return anagramNum;
}

void phraseToWords(Set<string>& anagram, const Set<string>& dict, LetterInventory& Li){
    for(auto word : dict){
        if(Li.contains(word))
            anagram.add(word);
    }
}

void findAnagramsHelper(int max, LetterInventory& Li, const Set<string>& choices, Vector<string>& chosen, int& num, int& remain){
    // remain stands for how many words can it be choosed to avoid exceeding the maximum words required
    if(Li.isEmpty() && remain >= 0){
        cout << chosen << endl;
        num++;
    }
    else{
        // recursive case
        // choose
        for(string s : choices){
            if(Li.contains(s)){
                Li.subtract(s);
                // explore
                chosen.add(s);
                remain = max - chosen.size();
                findAnagramsHelper(max, Li, choices, chosen, num, remain);
                // un-choose
                chosen.remove(chosen.size()-1);
                Li.add(s);
            }
        }
    }
}
