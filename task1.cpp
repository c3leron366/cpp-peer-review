#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <set>
#include <iomanip>


class BookStorage
{
private:
    const int max_pages_;
    const int max_users_;
    int top_readed_pages;
    std::vector<int> id_to_pages; ///< Contains number of readed pages. User id is index to access it
    std::vector<int> pages_to_id; ///< Contains the number of users who have read this page. Index is number of pages
    std::set<int> user_ids; ///< Set of users

public:
    BookStorage(int max_pages, int max_users) : max_pages_(max_pages), max_users_(max_users)
    {
        id_to_pages.resize(max_users_ + 1);
        pages_to_id.resize(max_pages_ + 1);
    }

    BookStorage() = delete;
    ~BookStorage() = default;
    
    void AddReadedPages(int user_id, int pages)
    {
        if(user_id > max_users_ )
        {
            throw std::out_of_range("user_id exceed max_users");
        }
        if(pages > max_pages_ )
        {
            throw std::out_of_range("pages number exceed max_pages");
        }

        if(pages > top_readed_pages)
        {
            top_readed_pages = pages;
        }

        auto [_, is_inserted] = user_ids.insert(user_id);
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
        for(int i = 0; i < top_readed_pages + 1; i++)
        {
            if(i < pos)
            {
                up += pages_to_id[i];
            }
        }

        down = user_ids.size();
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


void Parse(std::istream& input, std::ostream& out, BookStorage& storage)
{
    out << std::setprecision(6);
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
        else if(s.find("CHEER") != std::string::npos)
        {
            int id;
            input >> id;
            out << storage.GetUserStat(id) << std::endl;
        }
        else
        {
            throw std::invalid_argument("unkown command");
        }
    }
}



int main (void)
{
    constexpr static int MAX_PAGES = 1000;
    constexpr static int MAX_USERS = 100000;
    BookStorage book1(MAX_PAGES, MAX_USERS);
    Parse(std::cin, std::cout, book1);

    return 0;
}
