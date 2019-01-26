#include <iostream>
#include <fstream>
#include <list>
#include <sstream>

int task1_max (const std::string &filename)
{
    double a = 0;
    double max_v = std::numeric_limits<double>::min ();
    int cnt = 0;
    std::ifstream myfile (filename);
    if (myfile.is_open())
    {
        while (myfile >> a)
        {
            if (a > max_v)
            {
                max_v = a;
                cnt = 1;
            }
            else if (a == max_v)
                ++cnt;
        }
    }
    else
        return -1;

    return cnt;
}

int task1 (const std::string &filename)
{
    std::list<double> a_lst;
    double a = 0;
    int count = 0;
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open())
        while (std::getline (myfile, line))
        {
            std::stringstream ss (line);
            while (ss >> a)
                a_lst.push_back(a);
        }
    else
        return -1;

    double max = std::numeric_limits<double>::min ();
    for (double v : a_lst)
    {
         if (v > max)
             max = v;
    }

    for (double v : a_lst)
    {
        if (v == max)
            count++;
    }

    std::cout << std::endl;

    return count;
}

int main (int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << std::endl;

    if (argc == 2)
    {
        std::cout << task1 (argv[1]) << '\n';
        std::cout << task1_max (argv[1]) << '\n';
    }
    else
        std::cout << "Wrong number of arguments\n";

    return 0;
}
