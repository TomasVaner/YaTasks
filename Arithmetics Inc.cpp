#include <map>
#include <tuple>
#include <limits>
#include <memory>
#include <iostream>

class Progression
{
    int64_t _value; //int64_t because if we make too many steps we can get out of bound of int
    int _step;
    unsigned _id;

public:
    //just a simple constructor that stores the given values
    Progression(int start, int step, unsigned id) : 
        _value(start),
        _step(step),
        _id(id)
    {

    }
    
    //value getter
    int64_t Value()
    {
        return _value;
    }

    //progress the progression and return previous value
    int64_t DoStep()
    {
        return (_value += _step) - _step; //tidied it up just to make it one-liner. Shame there is no way to make += behave like post-increment
    }

    //ID getter
    unsigned ID()
    {
        return _id;
    }
};

class Proggressions
{
    std::map<unsigned, Progression> _progressions;

public:
    //we don't need a constructor - default one should do

    void Add(int start, int step, unsigned id)
    {
        _progressions.insert({id, Progression(start, step, id)});
        //we assume that ids won't repeat so that there is no need to check for that. If they repeat - there would happen an exception
        //errata: C++ does not throw exception, I worked with C# for too long, haha
    }

    void Remove(unsigned id)
    {
        _progressions.erase(id);
        //Again, assume that the id is in the database - won't check. The exception would be thrown
        //errata: C++ does not throw exception, I worked with C# for too long, haha
    }

    int64_t Progress()
    {
        int64_t min_value = std::numeric_limits<int64_t>::max();
        unsigned id = 0;
        for (auto& iter : _progressions)
        {
            if (iter.second.Value() < min_value)
            {
                //if progression has a lower value
                id = iter.first;
                min_value = iter.second.Value();
            }
            else if (iter.second.Value() == min_value)
            {
                if (id)
                {
                    //in case one of the progressions got its value int64_t.max. Just a precaution, though
                    id = iter.first;
                }
                else if(id > iter.first)
                {
                    //replace the pointer only if ID is less than the id of remembered progression
                    id = iter.first;
                }
            }
        }
        //used iterator and find because _progressions[id] would require default constructor for Progression which it does not have
        auto it = _progressions.find(id);
        return it != _progressions.end()
            ? it->second.DoStep()
            : 0;
    }
};

int main()
{
    Proggressions progressions_database; //the database that is gonna store and manage our progressions

    //reading the commands count and then iterate reading commands
    unsigned commands_count;
    std::cin >> commands_count; 
    for(unsigned index = 0; index < commands_count; ++index)
    {
        unsigned command;
        std::cin >> command;
        
        unsigned id;
        switch (command)
        {
        case 1:
            //just add the new progression to the database
            int start, step;
            std::cin >> start >> step >> id;

            progressions_database.Add(start, step, id); //assume all data correct and no repetative ids
            break;
        
        case 2:
            //remove a progression from the database by its id
            std::cin >> id;
            progressions_database.Remove(id); //assume the id to be correct
            break;

        case 3:
            //make an operation of getting minimum value and then advance the progression
            int64_t value = progressions_database.Progress();
            std::cout << value << std::endl;
            break;
        }
    }
    return 0;
}