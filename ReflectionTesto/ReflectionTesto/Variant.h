#pragma once

#include <string>

using namespace std;

class Variant
{
public:

    enum class Type
    {
        Nothing ,

        Float   ,
        Bool    ,
        Integer ,
        String  ,
        Pointer
    };

private:

    struct String
    {
        char*   data;
        size_t  size;
    };

    struct Pointer
    {
        void*   data;
        size_t  size;
    };

    union
    {
        float       floatValue;
        bool        boolValue;
        int         intValue;

        String*     stringValue;

        Pointer*    pointerValue;
    };

    Type            type;

public:

    Variant         (void)                          : intValue(0)                               , type(Type::Nothing)
    {

    }

    Variant         (const float&   data)           : floatValue(data)                          , type(Type::Float)
    {

    }
    Variant         (const bool&    data)           : boolValue(data)                           , type(Type::Bool)
    {

    }
    Variant         (const int&     data)           : intValue(data)                            , type(Type::Integer)
    {

    }

    Variant         (char*          data, size_t size)  : stringValue(new String { data, size })    , type(Type::String)
    {

    }
    Variant         (void*          data, size_t size)  : pointerValue(new Pointer{ data, size })   , type(Type::Pointer)
    {

    }

    Variant         (Variant&& other)
    {
        switch (other.type)
        {
        case Type::Bool:    boolValue       = other.boolValue;              other.boolValue     = false;
            break;
        case Type::Float:   floatValue      = other.floatValue;             other.floatValue    = 0.0f;
            break;
        case Type::Integer: intValue        = other.intValue;               other.intValue      = 0;
            break;
        case Type::Pointer: pointerValue    = move(other.pointerValue);     other.pointerValue  = nullptr;
            break;
        case Type::String:  stringValue     = move(other.stringValue);      other.stringValue   = nullptr;
            break;
        }

        other.type = Type::Nothing;
    }

    ~Variant        (void)
    {
        if (type == Type::Pointer)
        {
            delete pointerValue;
        }

        if (type == Type::String)
        {
            delete stringValue;
        }
    }

    const char*     AsString        (void) const
    {
        switch (type)
        {
        case Variant::Type::Nothing:    return "Nothing"    ;
        case Variant::Type::Float:      return "Float"      ;
        case Variant::Type::Bool:       return "Bool"       ;
        case Variant::Type::Integer:    return "Integer"    ;
        case Variant::Type::String:     return "String"     ;
        case Variant::Type::Pointer:    return "Pointer"    ;
        }
    }

    Type            GetType         (void) const
    {
        return type;
    }

    // --------------------------------------------------------------------------------------------

    bool            operator ==     (const Variant& rhs)
    {
        if (rhs.type != type)
        {
            return false;
        }

        switch (type)
        {
        case Variant::Type::Float:      return floatValue   == rhs.floatValue;
        case Variant::Type::Bool:       return boolValue    == rhs.boolValue;
        case Variant::Type::Integer:    return intValue     == rhs.intValue;
        case Variant::Type::String:
        {
            if (stringValue->size != rhs.stringValue->size)
            {
                return false;
            }

            return strcmp(stringValue->data, rhs.stringValue->data) == 0;
        }
        case Variant::Type::Pointer:

            return pointerValue->data == rhs.pointerValue->data;
        }
    }

    Variant&        operator =      (Variant&& other)
    {
        switch (other.type)
        {
        case Type::Bool:    boolValue       = other.boolValue;              other.boolValue     = false;
            break;
        case Type::Float:   floatValue      = other.floatValue;             other.floatValue    = 0.0f;
            break;
        case Type::Integer: intValue        = other.intValue;               other.intValue      = 0;
            break;
        case Type::Pointer: pointerValue    = move(other.pointerValue);     other.pointerValue  = nullptr;
            break;
        case Type::String:  stringValue     = move(other.stringValue);      other.stringValue   = nullptr;
            break;
        }

        other.type = Type::Nothing;

        return *this;
    }

    // --------------------------------------------------------------------------------------------

    operator int                    (void) const
    {
        if (type != Type::Integer)
            throw runtime_error("Types are incompatible!");

        return intValue;
    }
    operator bool                   (void) const
    {
        if (type != Type::Bool)
            throw runtime_error("Types are incompatible!");

        return boolValue;
    }
    operator float                  (void) const
    {
        if (type != Type::Float)
            throw runtime_error("Types are incompatible!");

        return floatValue;
    }
    operator const char*            (void) const
    {
        if (type != Type::String)
            throw runtime_error("Types are incompatible!");

        return stringValue->data;
    }
    operator void*                  (void) const
    {
        if (type != Type::Pointer)
            throw runtime_error("Types are incompatible!");

        return pointerValue->data;
    }
};
