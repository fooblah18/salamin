#include "Object.h"

#define DEFINE_PROPERTY_SETTER(ClassType, Type, Name, Variable) static void     Set##Name(void* target, const Variant& type)    { ((ClassType*)target)->Variable = (Type)type; }
#define DEFINE_PROPERTY_GETTER(ClassType, Type, Name, Variable) static Variant  Get##Name(void* target)                         { return Variant(((ClassType*)target)->Variable); }

class BaseType
{
};

class SomeType
{
private:

    int value;

public:

    SomeType(void) : value(0)
    {

    }

    void DoSomething(void)
    {
        printf("Hello world!\nValue is: %d\n", value);
    }

    DEFINE_PROPERTY_SETTER(SomeType, int, Something, value);
    DEFINE_PROPERTY_GETTER(SomeType, int, Something, value);

    static Variant StaticDoSomething(void* target, const vector<Variant>& args)
    {
        ((SomeType*)target)->DoSomething();

        return Variant();
    }
};

int main(void)
{
    SomeType                    type;
    SomeType                    anotherType;
    Object<SomeType, BaseType>  someObject;

    someObject.properties.push_back(Property
    {
        L"name"                 ,
        Variant::Type::Integer  ,
        &SomeType::SetSomething ,
        &SomeType::GetSomething
    });

    someObject.methods.push_back(Method
    { 
        Variant::Type::Nothing          ,
        vector<Argument>()              ,
        L"DoSomething"                  ,
        &SomeType::StaticDoSomething
    });

    someObject.SetValue (&type,         L"name", 20);
    someObject.SetValue (&anotherType,  L"name", 40);
    
    someObject.Invoke   (&type,         L"DoSomething");
    someObject.Invoke   (&anotherType,  L"DoSomething");

    return 0;
}
