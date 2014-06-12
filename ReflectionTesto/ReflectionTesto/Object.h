#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Method.h"
#include "Property.h"

using namespace std;

class ObjectBase
{
protected:

    string thisType;
    string baseType;

public:

    const string&   GetTypeName         (void)
    {
        return thisType;
    }
    const string&   GetBaseTypeName     (void)
    {
        return baseType;
    }

    vector<string>  GetInheritanceChain (void)
    {
        return vector<string>();
    }
};

template<class _thisType, class _baseType>
class Object : public ObjectBase
{
public:

    Object              (void)
    {
        // todo: check first in the DB if baseType is defined

        thisType = string(typeid(_thisType).name());
        baseType = string(typeid(_baseType).name());
    }

    vector<Property>    properties;
    vector<Method>      methods;

    Variant             GetValue    (_thisType* type, const wstring& name)
    {
        auto result = find_if(properties.begin(), properties.end(), [&](Property entry) -> bool
        {
            return entry.name == name;
        });

        if (result != properties.end())
        {
            return result->getter(type);
        }

        return Variant();
    }

    void                SetValue    (_thisType* type, const wstring& name, const Variant& value)
    {
        auto result = find_if(properties.begin(), properties.end(), [&](Property entry) -> bool
        {
            return entry.name == name;
        });

        if (result != properties.end())
        {
            if (value.GetType() != result->type)
                throw runtime_error("Types are incompatible!");

            result->setter(type, value);
        }
    }

    Variant             Invoke      (_thisType* type, const wstring& name, const vector<Variant>& parameters = vector<Variant>())
    {
        auto result = find_if(methods.begin(), methods.end(), [&](Method entry) -> bool
        {
            return entry.name == name;
        });

        if (result != methods.end())
        {
            return result->onInvoke(type, parameters);
        }

        return Variant();
    }

    Variant             Invoke      (_thisType* type, const wstring& name, const Variant& param1)
    {
        return Invoke(type, name, { param1 });
    }
    Variant             Invoke      (_thisType* type, const wstring& name, const Variant& param1, const Variant& param2)
    {
        return Invoke(type, name, { param1, param2 });
    }
    Variant             Invoke      (_thisType* type, const wstring& name, const Variant& param1, const Variant& param2, const Variant& param3)
    {
        return Invoke(type, name, { param1, param2, param3 });
    }
    Variant             Invoke      (_thisType* type, const wstring& name, const Variant& param1, const Variant& param2, const Variant& param3, const Variant& param4)
    {
        return Invoke(type, name, { param1, param2, param3, param4 });
    }
    Variant             Invoke      (_thisType* type, const wstring& name, const Variant& param1, const Variant& param2, const Variant& param3, const Variant& param4, const Variant& param5)
    {
        return Invoke(type, name, { param1, param2, param3, param4, param5 });
    }
};
