#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <cassert>

using namespace std;

class Domain {
    // разработайте класс домена
public:
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами
    Domain(const std::string& domain) : domain_(domain)
    {
        reverse(domain_.begin(), domain_.end());
        domain_.push_back('.');
    }

    // разработайте operator==
    bool operator==(const Domain& other)
    {
        return domain_ == other.domain_;
    }

    //   метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& other) const
    {
        if (domain_.size() < other.domain_.size()) 
        {
            return false;
        }
        for(size_t idx = 0; idx < other.domain_.size(); ++idx)
        {
            if(domain_[idx] != other.domain_[idx])
            {
                return false;
            }
        }
        return true;
    }
    
    friend bool operator<(const Domain& lhs, const Domain& rhs);
    friend bool operator==(const Domain& lhs, const Domain& rhs);

private:
    std::string domain_;
};

bool operator<(const Domain& lhs, const Domain& rhs)
{
    return std::lexicographical_compare(lhs.domain_.begin(), lhs.domain_.end(), rhs.domain_.begin(), rhs.domain_.end());
}

bool operator==(const Domain& lhs, const Domain& rhs)
{
    return lhs.domain_ == rhs.domain_;
}

class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template <typename Iterator>
    DomainChecker(Iterator forbidden_begin, Iterator forbidden_end) : fd_(forbidden_begin, forbidden_end)
    {
        std::sort(fd_.begin(), fd_.end());
        fd_.erase(std::unique(fd_.begin(), fd_.end(), [](const Domain& lhs, const Domain& rhs)
                                                    {
                                                        return rhs.IsSubdomain(lhs);
                                                    }), 
                                                    fd_.end());
    }

    DomainChecker() = delete;
    
    ~DomainChecker() = default;
    
    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& tested_domain)
    {
        auto it = std::upper_bound(fd_.begin(), fd_.end(), tested_domain);     
        if (it == fd_.begin())
        {
            return false;
        }
        else
        {
            return tested_domain.IsSubdomain(*std::prev(it));
        }
    }

    size_t GetSize() const
    {
        return fd_.size();
    }
private:
    std::vector<Domain> fd_;
};



template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
template <typename Number>
std::vector<Domain> ReadDomains(std::istream& input, Number num)
{
    std::vector<Domain> result;
    while(num)
    {
        std::string s;
        getline(input, s);
        result.emplace_back(s);
        num--;
    }
    return result;
}

void TestExample();

void TestIsSubDomain()
{
    Domain com("com");
    Domain subcom("sub.com"); 
    //sub.com is subdomain of com 
    assert(!com.IsSubdomain(subcom));
    assert(subcom.IsSubdomain(com));
}

void TestCheckerReduceSubdomain()
{
    Domain com("com");
    Domain subcom("sub.com"); 
    const std::vector<Domain> fd{com, subcom};
    DomainChecker checker(fd.begin(), fd.end());

    //sub.com is subdomain of com, size should be 1
    assert(checker.GetSize() == 1);
}

void RunTests()
{
    TestIsSubDomain();
    TestCheckerReduceSubdomain();
    TestExample();
}
int main() {
    RunTests();
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}

void TestExample()
{
    std::string test_1_in = {
    "4\n"
    "gdz.ru\n"
    "maps.me\n"
    "m.gdz.ru\n"
    "com\n"
    "7\n"
    "gdz.ru\n"
    "gdz.com\n"
    "m.maps.me\n"
    "alg.m.gdz.ru\n"
    "maps.com\n"
    "maps.ru\n"
    "gdz.ua \n"
    };

    std::vector<std::string> test_1_out = {
    "Bad\n",
    "Bad\n",
    "Bad\n",
    "Bad\n",
    "Bad\n",
    "Good\n",
    "Good\n"
    };

    std::stringstream ss(test_1_in);

    auto num = ReadNumberOnLine<size_t>(ss);
    const std::vector<Domain> forbidden_domains = ReadDomains(ss, num);
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());
    
    num = ReadNumberOnLine<size_t>(ss);
    const std::vector<Domain> test_domains = ReadDomains(ss, num);

    std::vector<std::string> result;
    for (const Domain& domain : test_domains) {
        std::stringstream out;
        // cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
        out << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;

        result.push_back(out.str());
    }
    
    assert(result == test_1_out);
}

