#include <map>
#include <tuple>
#include <limits>
#include <memory>

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
    
    int Value()
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
                progression.reset();
            }
            else if (iter.second.Value() == min_value 
                    && progression.get())
            {
                if(progression->ID() > iter.first)
                {
                    progression.reset(&iter.second);
                }
            }
        }
        return progression->Value();
    }
};

void main()
{
    Proggressions progressions_database;

    
}