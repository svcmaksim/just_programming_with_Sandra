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
    std::string line;
    std::ifstream myfile (filename);
    int cnt = 0;
    double max_val = -DBL_MAX;
    if (myfile.is_open())
    {
        while (std::getline (myfile, line))
        {
            size_t begin_ind = 0, end_ind = 0;
            bool is_inside_num = false; ///< 134a21345 8935e9858u 12.5
            for (size_t i = 0; i < line.length(); i++)
                if (std::isdigit (line[i]) && i != (line.length () - 1))
                {
                    if (!is_inside_num)
                    {
                        is_inside_num = true;
                        begin_ind = i;
                    }
                }
                else
                {
                    if (!std::isspace(line[i]) && !std::isdigit (line[i]))
                        return -2;

                    if (is_inside_num)
                    {
                        is_inside_num = false;
                        end_ind = i + ((std::isdigit (line[i])) ? 1 : 0);
                        size_t sz = 0;
                        std::string num_str (line, begin_ind, end_ind - begin_ind);
                        double val = std::stod (num_str, &sz);
                        if (sz > 0)
                        {
                            if (std::fabs(val - max_val) < std::numeric_limits<double>::epsilon())
                                ++cnt;
                            else if (val > max_val)
                            {
                                max_val = val;
                                cnt = 1;
                            }
                        }
                    }
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
