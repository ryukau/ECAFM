#include "ElementaryCA.h"

#include <cmath>
#include <algorithm>
#include <random>

ElementaryCA::ElementaryCA()
    : rule(30)
{
    setSize(16);
    init(0);
}

ElementaryCA::~ElementaryCA()
{

}

size_t ElementaryCA::size()
{
    return cell.size();
}

void ElementaryCA::setSize(int n)
{
    cell.resize(n);
    backcell.resize(n);
}

void ElementaryCA::setRule(int r)
{
    rule = r;
}

void ElementaryCA::init(int seed)
{
    std::mt19937 mt(seed);
    std::uniform_int_distribution<short> dist(0, 1);

    for (auto &it : cell)
        it = dist(mt) == 0 ? false : true;
}

void ElementaryCA::next()
{
    std::copy(cell.begin(), cell.end(), backcell.begin());

    for (int n = 0; n < cell.size(); ++n)
    {
        int pattern = 4 * backcell.at(mmod(n - 1)) + 2 * backcell.at(n) + backcell.at(mmod(n + 1));
        cell[n] = ((rule / (int)pow(2, pattern)) % 2) == 0 ? false : true;
    }
}

bool ElementaryCA::at(int index)
{
    int i = index % cell.size();
    if (index < 0)
        i = static_cast<int>(cell.size()) - i;

    return cell[i];
}

int ElementaryCA::mmod(int i)
{
    if (i < 0)
        return static_cast<int>(cell.size()) + i;

    return i % cell.size();
}

