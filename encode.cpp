// Created by Jose Lugo

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    // The variable sort will take in either the word "insertion" or "quick" from a command line input. This will determine the sorting algorithm used in the program.
    string sort = argv[1];

    // The variable input will be obtained from stdin which will be a text file given in the command line.
    string input;

    // A while loop will take each line of the input variable until the end of the file has been reached.
    while(!cin.eof())
    {
        getline(cin, input);

        // A 2D character array called shifts is allocated so that we can put in the input with cyclic shifts.
        char** shifts;
        shifts = new char * [input.length()];
        for(int i = 0; i < input.length(); i++)
        {
            shifts[i] = new char[input.length()];
        }

        // A character variable called temp will allow us to keep the first index of our input so that when we do the cyclic shift, we can move the character at index 0 to the end of the array.
        char temp;

        // This nested for loop will create the cyclic shifted input and put that onto the 2D array called shifts.
        for(int i = 0; i < input.length(); i++)
        {
            for(int j = 0; j < input.length(); j++)
            {
                shifts[i][j] = input[j];
            }

            // Since we want to keep the first element of our input, we set temp to the first index of the input.
            temp = input[0];

            // The cyclic shift is conducted by using a for loop and setting each element to the one ahead of it.
            for(int k = 0; k < input.length() - 1; k++)
            {
                input[k] = input[k + 1];
            }

            // The last element of the cyclic shifted string is set to our temp variable, which contains the first element of the input before we had shifted it.
            input[input.length() - 1] = temp;
        }

        // An array of strings called lexicals is created to hold all of the cyclic shifted character arrays.
        string lexicals[input.length()];
        for(int i = 0; i < input.length(); i++)
        {
            for(int j = 0; j < input.length(); j++)
            {
                lexicals[i] += shifts[i][j];
            }
        }

        // The allocated memory we created when making or 2D character array called shifts is deleted as we no longer need the array.
        delete shifts;

        // From the input received from the command line, the lexicals array will be sorted in order according to their ASCII values.
        // When the word "insertion" is inputted, the array will be sorted via insertion sort.
        if(sort == "insertion")
        {
            for(int i = 1; i < input.length(); i++)
            {
                // The value of j is decreased by one so that any element j with a lower value than (j - 1) will be swapped until it is in the right spot.
                for(int j = i; j > 0; j--)
                {
                    // The element at index j is compared to the previous one to see if they need to be swapped.
                    if(lexicals[j] < lexicals[j - 1])
                    {
                        swap(lexicals[j], lexicals[j - 1]);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        // When the word "quick" is inputted, the array will be sorted via quicksort.
        if(sort == "quick")
        {
            // Coming soon :)
        }

        // The integer index will find the index in the lexicals array which contain the original string that was read from stdin.
        int index = 0;
        for(int i = 0; i < input.length(); i++)
        {
            if(lexicals[i] == input)
            {
                index = i;
                break;
            }
        }

        // The index of the original string is printed.
        cout << index << endl;

        // The string named last is created and will contain the last character of each row from the lexicals array.
        string last;
        for(int i = 0; i < input.length(); i++)
        {
            last += lexicals[i][input.length() - 1];
        }

        // The variable amount will keep track of any clusters of characters.
        int amount = 1;
        for(int i = 0; i < input.length(); i++)
        {
            // If there are back to back instances of the same character, a while loop will activate until there is a different character in the string.
            while(last[i] == last[i + 1])
            {
                amount++;
                i++;
            }
            // The encoded message is printed.
            cout << amount << " ";
            cout << last[i] << " ";
            amount = 1;
        }
        cout << "" << endl;
    }
    return 0;
}
