// Created by Jose Lugo

#include <iostream>
#include <string>
using namespace std;

// The partition method returns the middle index of an array, which can be used in the implementation of the quickSort method.
int partition(string **arr, int low, int high)
{
    // The pivot of the partition will be set to the highest element of the array.
    string pivot = *arr[high];
    int i = (low - 1);
    for(int j = low; j <= high - 1; j++)
    {
        if(*arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    // Once the function is complete, the index of the middle of the array is given which will help sort the data.
    return (i + 1);
}

// The quickSort method will sort an array of string pointers by calling to the partition method and applying quickSort recursively.
void quickSort(string** arr, int low, int high)
{
    if(low < high)
    {
        // The integer mid is calculated by calling the partition method, which will give us the middle index of the array.
        int mid = partition(arr, low, high);
        quickSort(arr, low, mid - 1);
        quickSort(arr, mid + 1, high);
    }
}

int main(int argc, char* argv[])
{
    // The variable sort will take in either the word "insertion" or "quick" from a command line input. This will determine the sorting algorithm used in the program.
    string sort = argv[1];

    // The variable input will be obtained from stdin which will be a text file given in the command line.
    string input;

    // The integer exit will be used to help with exiting the ode when the end of the file ha been reached.
    int exit;

    // A while loop will take each line of the input variable until the end of the file has been reached.
    while(!cin.eof())
    {
        getline(cin, input);

        // If the new line captured is a LF or newline, it will skip to the next line until it reaches text once again.
        while(input.empty())
        {
            // If the next line captured is the end of the file, then it will break out of the while loop, and set exit to 1.
            if(cin.eof())
            {
                exit = 1;
                break;
            }
            cout << endl;
            getline(cin, input);
        }

        // If exit is equal to 1, then it will break out of the while loop and end the program.
        if(exit == 1)
        {
            break;
        }

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

        // An array of pointer will point to all of the strings lexicals created.
        string* ptr[input.length()];
        for(int i = 0; i < input.length(); i++)
        {
            ptr[i] = &lexicals[i];
        }

        // From the input received from the command line, the ptr array will sort by pointer so that the strings they point to are sorted by increasing ASCII number.
        // When the word "insertion" is inputted, the array will be sorted via insertion sort.
        if(sort == "insertion")
        {
            for(int i = 1; i < input.length(); i++)
            {
                // The value of j is decreased by one so that any element j with a lower value than (j - 1) will be swapped until it is in the right spot.
                for(int j = i; j > 0; j--)
                {
                    // The element at index j is compared to the previous one to see if they need to be swapped.
                    if(*ptr[j] < *ptr[j - 1])
                    {
                        swap(ptr[j], ptr[j - 1]);
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
            quickSort(ptr, 0, input.length() - 1);
        }

       // for(int i = 0; i < input.length(); i++)
        //{
         //   cout << *ptr[i] << endl;
        //}

        // The integer index will find the index in the ptr array which contain the original string that was read from stdin.
        int index = 0;
        for(int i = 0; i < input.length(); i++)
        {
            if(*ptr[i] == input)
            {
                index = i;
                break;
            }
        }

        // The index of the original string is printed.
        cout << index << endl;

        // The string named last is created and will contain the last character of each row from the lexicals array.
        string last;
        string letter;
        for(int i = 0; i < input.length(); i++)
        {
            letter = *ptr[i];
            last += letter[input.length() - 1];
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
            // If we have reached the end of the encoded message, the program will print endl so that we can avoid excess whitespace.
            if(i == (input.length() - 1))
            {
                cout << last[i] << endl;
            }
            else
            {
                cout << last[i] << " ";
            }
            amount = 1;
        }
    }

    return 0;
}
