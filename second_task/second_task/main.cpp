#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>

std::list<double> read_nums_from_file (const std::string& filename)
{
    std::list<double> numbers_from_file;
    {
        std::string line;
        std::ifstream myfile (filename);
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

                    numbers_from_file.push_back(val);
                    line.erase(0, sz);
                }
            }
        }
        else
            return {};
    }

    return numbers_from_file;
}

int task2_impl (const std::list<double>& nums)
{

    if (nums.empty() || (++nums.begin()) == nums.end())
        return 0;
    bool have_max = false;
    int cnt = 0;
    int i=0;
 int how_many_times =0;
    double max_val = *nums.begin();
    for (const double & number: nums)
    {
        i++;
        if (number>max_val )
        {
            if (!have_max)
            {
                ++cnt;

                max_val = number;
                have_max = true;
                how_many_times=0;
            }
            else
               { max_val = number;
                how_many_times=0;}

        }
        else
        {
           if (number<max_val)
           {
               if (!have_max)
               { if (how_many_times==0)
                  { ++cnt;

                   max_val = number;
                   have_max = true;
                   ++how_many_times;}
                   else {
                       ++how_many_times;
                       max_val = number;
                   }

               }
               else
               { max_val = number;
                       have_max =false;
                   ++how_many_times;}


                   }
           }

           }




        return cnt;
    }

int task2_impl_by_ma (const std::list<double>& nums)
{
    if (nums.empty() || (++nums.begin()) == nums.end())
        return 0;

    enum class trend_t
    {
        up,
        down,
        equal,
        invalid
    };

    trend_t prev_trend = trend_t::up;
    double prev_value = -DBL_MAX;
    int cnt = 0;
    size_t iteration = 0;
    bool has_real_max = false;
    for (const double& n : nums)
    {
        if (n > prev_value)
        {
            prev_trend = trend_t::up;
        }
        else if (std::fabs(n - prev_value) < std::numeric_limits<double>::epsilon())
        {
            if (iteration == 1 && prev_trend == trend_t::up)
                prev_trend = trend_t::equal;
        }
        else
        {
            if (prev_trend == trend_t::up || !has_real_max)
            {
                prev_trend = trend_t::down;
                ++cnt;
                has_real_max = true;
            }
        }
        prev_value = n;
        ++iteration;
    }

    if (prev_trend == trend_t::up || (!has_real_max && prev_trend != trend_t::equal))
        ++cnt;

    return cnt;
}

void test ();

int task2 (const std::string &filename)
{
    test ();
    std::list<double> numbers_from_file = read_nums_from_file (filename);
    return task2_impl(numbers_from_file);
}

void test ()
{
    std::vector<std::pair<std::list<double>, int>> test_data = {
        {{}, 0},
       {{1,1,1,1}, 0},
      {{1,2,1},1},
      {{1}, 0},
        {{1,2,3,4,5,6,7,8,9,123}, 1},
       {{123,9,8,7,6,5,4,3,2,1,0}, 1},
        {{1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,2,2,2,2,2,2,1}, 1},
      {{1,1,2,2,1,1,0,0,0,0,0,0,0,0,456,456,456,456,456,456,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1},2},
       {{2,2,2,2,2,2,2,1}, 1}
    };

    for (const auto& data : test_data)
    {
        int answ = task2_impl(data.first);
        if (answ == data.second)
            std::cout << "[OK]\n";
        else
            std::cout << "[FAIL] answ = " << answ << ", expected = " << data.second << "\n";
    }
}

int main (int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << '\t';

    std::cout << std::endl;

    if (argc == 2)
    {
        std::cout << '\n' << task2 (argv[1]) << '\n';
    }
    else
        std::cout << "Wrong number of arguments\n";

    return 0;
}
