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
    Progression(int start, int step, unsigned id) : 
        _value(start),
        _step(step),
        _id(id)
    {

    }
    
    int64_t Value()
    {
        return _value;
    }

    int64_t Step()
    {
        int64_t ret = _value;
        _value += _step;
        return ret;
    }

    unsigned ID()
    {
        return _id;
    }
};

class Proggressions
{
    std::map<unsigned int, Progression> _progressions;

public:
    //we don't need a constructor - default one should do

    void Add(int start, int step, int id)
    {
        _progressions.insert({id, Progression(start, step, id)});
        //we assume that ids won't repeat so that there is no need to check for that. If they repeat - there would happen an exception
    }

    void Remove(int id)
    {
        _progressions.erase(id);
        //Again, assume that the id is in the database - won't check. The exception would be thrown
    }

    int64_t Progress()
    {
        int64_t min_value = std::numeric_limits<int64_t>::max();
        std::unique_ptr<Progression> progression;
        for (auto& iter : _progressions)
        {
            if (iter.second.Value() < min_value)
            {
                progression.release();
                progression.reset(&iter.second);
                min_value = iter.second.Value();
            }
            else if (iter.second.Value() == min_value 
                    && progression.get())
            {
                if(progression->ID() > iter.first)
                {
                    progression.release();
                    progression.reset(&iter.second);
                }
            }
        }
        int64_t ret = progression->Step();
        progression.release();
        return ret;
    }
};

int main()
{
    Proggressions progressions_database;

    unsigned commands_count;
    std::cin >> commands_count;
    for(int index = 0; index < commands_count; ++index)
    {
        unsigned command;
        std::cin >> command;
        
        unsigned id;
        switch (command)
        {
        case 1:
            int start, step;
            std::cin >> start >> step >> id;

            progressions_database.Add(start, step, id); //assume all data correct and no repetative ids
            break;
        
        case 2:
            std::cin >> id;
            progressions_database.Remove(id); //assume we id to be correct
            break;

        case 3:
            int64_t value = progressions_database.Progress();
            std::cout << value << std::endl;
            break;
        }
    }
    return 0;
}