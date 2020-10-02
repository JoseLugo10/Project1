// Created by Jose Lugo

#include <iostream>
#include <string>
using namespace std;

// The partition method returns the middle index of an array, which can be used in the implementation of the quickSort method.
int partition(char arr[], int low, int high)
{
    // The pivot of the partition will be set to the highest element of the array.
    char pivot = arr[high];
    int i = (low - 1);
    for(int j = low; j <= high - 1; j++)
    {
        if(arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    // Once the function is complete, the index of the middle of the array is given which will help sort the data.
    return (i + 1);
}

// The quickSort method will sort an array of character pointers by calling to the partition method and applying quickSort recursively.
void quickSort(char arr[], int low, int high)
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
    // sort will take in a parameter from command line which will equate to either "insertion", or "quick".
    string sort = argv[1];

    // Variables input, and number will represent the encoded message, and the index of the original message respectively.
    string input;
    string number;

    // exit variable will be used in assisting to exit the while loop.
    int exit = 0;

    // The file will be read from command line until the end of it has been reached.
    while(!cin.eof())
    {
        // The index of the original message is captured.
        getline(cin, number);

        // If the new line captured is a LF or newline, it will skip to the next line until it reaches text once again.
        while(number.empty())
        {
            // If the next line captured is the end of the file, then it will break out of the while loop, and set exit to 1.
            if(cin.eof())
            {
                exit = 1;
                break;
            }
            cout << endl;
            getline(cin, number);
        }

        // If exit is equal to 1, then it will break out of the while loop and end the program.
        if(exit == 1)
        {
            break;
        }

        // The encoded message is captured and set to input.
        getline(cin, input);

        // last will contain the clusters of letters from the input, nums will be used to capture a cluster amount, and amount is an int variable that will convert the clusters into an integer.
        string last;
        string nums;
        int amount;

        for(int i = 0; i < input.length(); i += 2)
        {
            // val captures the amount of times a letter is repeated in a cluster
            int val = (int)input[i] - 48;
            nums += to_string(val);

            // If the amount for a single letter is more than one digit, this if statement will help in finding the second digit of the amount of clusters.
            if(((int)input[i + 1] - 48) == 0 || ((int)input[i + 1] - 48) == 1 || ((int)input[i + 1] - 48) == 2 || ((int)input[i + 1] - 48) == 3 || ((int)input[i + 1] - 48) == 4 || ((int)input[i + 1] - 48) == 5 || ((int)input[i + 1] - 48) == 6 || ((int)input[i + 1] - 48) == 7 || ((int)input[i + 1] - 48) == 8 ||((int)input[i + 1] - 48) == 9)
            {
                val = (int)input[i + 1] - 48;
                nums += to_string(val);
                i++;
            }

            // amount is finally set to a string to int conversion of nums.
            amount = stoi(nums);
            i += 2;

            // The letter in the encoded message is found and is repeated by the amount of times it is seen in the cluster.
            char letter = input[i];
            for(int j = 0; j < amount; j++)
            {
                last += letter;
            }
            nums = "";
            amount = 0;
        }

        // An array of characters is created which will contain all of the letters from last.
        char letters[last.length()];
        for(int i = 0; i < last.length(); i++)
        {
            letters[i] = last[i];
        }

        // If the word "insertion" is inputted in command line, the letters will be lexicographically ordered via insertion sort.
        if(sort == "insertion")
        {
            for(int i = 1; i < last.length(); i++)
            {
                // The value of j is decreased by one so that any element j with a lower value than (j - 1) will be swapped until it is in the right spot.
                for(int j = i; j > 0; j--)
                {
                    // The element at index j is compared to the previous one to see if they need to be swapped.
                    if(letters[j] < letters[j - 1])
                    {
                        swap(letters[j], letters[j - 1]);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        // If the word "quick" is inputted in command line, the letters will be lexicographically ordered via quicksort.
        if(sort == "quick")
        {
            quickSort(letters, 0, last.length() - 1);
        }

        // The integer arrays next and used will contain the next index that is needed to be traversed to, and a binary representation of whether or not a letter has been used respectively.
        int next[last.length()];
        int used[last.length()];
        for(int i = 0; i < last.length(); i++)
        {
            used[i] = 0;
        }

        // The nested for loops will determine the values for next, and skip letters if they have been used already by using the used array.
        char pick;
        for(int i = 0; i < last.length(); i++) {
            pick = letters[i];
            for (int j = 0; j < last.length(); j++) {
                if (last[j] == pick && used[j] == 0) {
                    next[i] = j;
                    used[j] = 1;
                    break;
                }
            }
        }

        // The index found earlier from getline is converted into an integer, and will be used to start the decoded message from the index.
        int index = stoi(number);
        char decoded[last.length()];

        // Initial letter is set to the first letter from the index.
        decoded[0] = letters[index];
        int limit = 0;
        int k = 1;

        // The while loop will help in calculating the decoded message by traversing through the next index in the letters array.
        while(limit < last.length())
        {
            index = next[index];
            decoded[k] = letters[index];
            k++;
            limit++;
        }

        // The decoded message is printed.
        for(int i = 0; i < last.length(); i++)
        {
            cout << decoded[i];
        }
        cout << endl;
    }

    return 0;
}
