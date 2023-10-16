#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <set>
#include <iomanip>


struct BookStorage
{
    constexpr static int MAX_USERS = 1001;
    constexpr static int MAX_PAGES = 100001;
    BookStorage()
    {
        pages_to_id.reserve(MAX_USERS);
        id_to_pages.reserve(MAX_PAGES);
    }
    std::vector<int> id_to_pages;
    std::vector<int> pages_to_id;
    std::set<int> user_ids;

    void AddReadedPages(int user_id, int pages)
    {
        auto [a, is_inserted] = user_ids.insert(user_id);
        if(!is_inserted)
        {
            pages_to_id[id_to_pages[user_id]] -= 1;
        }
        
        id_to_pages[user_id] = pages;
        pages_to_id[pages] += 1;
    }

    double GetUserStat(int user_id)
    {
        auto pos = id_to_pages[user_id];

        double up = 0.0;
        double down = 0.0;
        for(int i = 0; i < pages_to_id.capacity(); i++)
        {
            if(i < pos)
            {
                up += pages_to_id[i];
            }
            down += pages_to_id[i];
        }

        if(down == 1)
        {
            if(pages_to_id[pos] == 1)
            {
                up = 1;
            }
                
        }
        else if(down < 1)
        {
            down = 1;
        }
        else
        {
            //if user exists, remove it
            if(id_to_pages[user_id] > 0)
            {
                down -= 1;
            }
        }

        return up / down;
    }
};


void parse(std::istream& input, BookStorage& storage)
{
    int q;
    input >> q;
    for(int idx = 0; idx < q; ++idx)
    {
        std::string s;
        input >> s;
        if(s.find("READ") != std::string::npos)
        {
            int id;
            int pages;
            input >> id;
            input >> pages;
            storage.AddReadedPages(id, pages);            
        }
        if(s.find("CHEER") != std::string::npos)
        {
            int id;
            input >> id;

            std::cout << std::setprecision(6) << storage.GetUserStat(id) << std::endl;
        }
    }
}



std::string test_input = 
{
    "12\n"
    "CHEER 5\n"
    "READ 1 10\n"
    "CHEER 1\n"
    "READ 2 5\n"
    "READ 3 7\n"
    "CHEER 2\n"
    "CHEER 3\n"
    "READ 3 10\n"
    "CHEER 3\n"
    "READ 3 11\n"
    "CHEER 3\n"
    "CHEER 1\n"
};


int main (void)
{
    BookStorage users;
    
    // std::stringstream ss;
    // ss << test_input;
    // parse(ss, users);
    parse(std::cin, users);

    return 0;
}
