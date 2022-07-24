#include <iostream>
#include <cctype>
#include <set>
#include <map>
#include <string>
/*
The function to parse the string and form the result
input: parsed string
return: ordered number with most occurences
*/

std::set<int> parse_string(std::string input)
{
    std::map<int, unsigned int> occurances; //storage for the number and its occurances
    std::string number_buffer; //the buffer to store a number
    unsigned int most_occurances = 1; //we are promissed at least 1 number in the input

    //parse the string by iterating its symbols
    for (const unsigned char& symbol : input)
    {
        //if the symbol is a digit - add it to the buffer and go to the next sybmbol
        if (std::isdigit(symbol) || symbol == u'-')
        {
            number_buffer += static_cast<char>(symbol);
        }
        else if(number_buffer.length() > 0) //only if we already gathered the number into the buffer
        {
            int number = std::stoi(number_buffer); //convert string to a number
            number_buffer.clear(); //clear the buffer

            const auto& it = occurances.find(number); //find the number in the storage
            if (it == occurances.end()) //if it is not preset
                occurances.insert({number, 1u}); //initialize the record
            else
            {
                ++it->second; //else just increase currently stored occurences
                most_occurances = std::max(most_occurances, it->second); //update the max occurances value
            }
        }
    }
    //we don't need to parse the buffer as it will be always empty because the array is always closing by ']' un the end

    //go through the gathered data and form the result
    std::set<int> return_value;
    for (const auto& map_iter : occurances)
    {
        if (map_iter.second == most_occurances)
        {
            return_value.insert(map_iter.first);
        }
    }
    return return_value;
    
}

int main()
{
    std::string array_string;
    std::getline(std::cin, array_string); //we assume that there is no line breaks in the input
    auto most_occurred = parse_string(array_string);
    bool not_first_number = false;
    for (const auto& set_iter : most_occurred)
    {
        if (not_first_number)
            std::cout << ' ';
        std::cout << set_iter;
        not_first_number = true;
    }
    

    return 0;
}
