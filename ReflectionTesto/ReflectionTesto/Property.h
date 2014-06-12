#pragma once

#include "Variant.h"

#include <string>
#include <functional>

using namespace std;

class Property
{
public:

    wstring                                 name;
    Variant::Type                           type;

    function<void(void*, const Variant&)>   setter;
    function<Variant(void*)>                getter;

    Property(const wstring&                                 name    ,
             Variant::Type                                  type    ,
             const function<void(void*, const Variant&)>&   setter  ,
             const function<Variant(void*)>&                getter  ) :

             name           (name)          ,
             type           (type)          ,

             setter         (setter)        ,
             getter         (getter)

    {

    }
};
