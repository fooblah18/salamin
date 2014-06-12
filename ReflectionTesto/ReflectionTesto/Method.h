#pragma once

#include <vector>
#include <functional>

#include "Argument.h"

using namespace std;

class Method
{
public:

    Variant::Type                                       returnType;
    vector<Argument>                                    arguments;

    wstring                                             name;

    function<Variant(void*, const vector<Variant>&)>    onInvoke;
};
