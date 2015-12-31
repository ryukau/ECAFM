#pragma once

#include <vector>

class ElementaryCA
{
public:
    ElementaryCA();
    ~ElementaryCA();

    size_t size();
    void setSize(int n);
    void setRule(int r);
    void setSmoothTime(float msec);

    void init(int seed);
    void next();
    bool at(int index);
    float gainAt(int index);
    int mmod(int i);

private:
    int rule;
    std::vector<bool> cell;
    std::vector<bool> backcell;

    float steepness;
    std::vector<float> gain;
};
