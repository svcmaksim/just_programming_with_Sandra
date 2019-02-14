#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <cctype>
#include <string>
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
            else if (std::fabs (a - max_v) < std::numeric_limits<double>::epsilon())
                ++cnt;
        }
    }
    else
        return -1;

    return cnt;
}

int task1 (const std::string &filename)
{
    std::string line;
    std::ifstream myfile (filename);
    int cnt = 0;
    double max_val = -DBL_MAX;
    if (myfile.is_open())
    {
        while (std::getline (myfile, line))
        {
            while (!line.empty())
            {
                size_t sz = 0;
                double val = 0;
                bool ok = true;
                try {
                    val = std::stod (line, &sz);
                } catch (std::exception& ) {
                    ok = false;
                }

                if (!ok)
                    break;

                if (std::fabs(val - max_val) < std::numeric_limits<double>::epsilon())
                    ++cnt;
                else if (val > max_val)
                {
                    max_val = val;
                    cnt = 1;
                }

                line.erase (0, sz);
            }
        }
        return cnt;
    }

    return -1;
}

int main (int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << '\t';

    if (argc == 2)
    {
        std::cout << '\n' << task1 (argv[1]) << '\n';
     //   std::cout << task1_max (argv[1]) << '\n';
    }
    else
        std::cout << "Wrong number of arguments\n";

    return 0;
}
