# IGTK Coding Guidelines and Conventions

## Naming conventions

### File names

In general, all files must be `snake_case` conformant. E.g. `my_file.hpp`, `my_file.cpp`, `my_file.md`, etc.

#### C++ files

* headers: `header_file.hpp`
* inline header fragments: `inline_file.inl`
* source files: `source_file.cpp`


### C++ essential naming conventions

The core intent of having a naming convention reference is to ensure consistency across the codebase. 
Since C++ is not really regulated in this sense (e.g. for Python there is the popular PEP8 reference, while for C# Microsoft has established a coding and naming
style), we cannot select a style that would be compatible with all possible C++ libraries (e.g. Boost and Google are popular options for writing style references, 
but typically every major vendor has their own variation). Therefore, without a sound reason to settle for a particular one, we will nevertheless adopt a style 
very similar to the one proposed here http://geosoft.no/development/cppstyle.html.

**NOTE:** It is thus very important to ensure consistency. The proposed style was simply selected due to the fact that it combines some of the more popular 
choices the authors of this repository have been exposed to throughout their careers.

**WARNING:** When integrating an external library with its own style, any code that explicitly extends or makes direct use (e.g. not through a wrapper or any 
other abstraction layer) of that API should, preferably, abide by the external style. One typical example is when working with Qt code. If you create a custom 
extension, it is preferable to adhere to the Qt naming conventions to enhance aesthetics (the code looks uniformly written and thus more readable).

#### List of C++ relevant naming conventions

1. type names use PascalCase, e.g. `ConcreteClass`, `DataUnion`, `DataStruct`
  i. type aliases should use the `T` suffix, e.g. `VectorT`, `InternalT`
  ii. template typenames should use the `T` prefix, e.g. `T`, `TBuffer`, `TNumeric`, etc.
  
2. variables use lower camelCase, e.g. `value`, `minValue`
3. functions and methods use lower camelCase, e.g. `analyzeResults`, `computeWeightedAverage`, `getInventoryList`
4. 

## Best practices

### Variables and parameters
* `const` qualify all possible variables and functions unless explicitly required otherwise.
* use `constexpr` wherever possible, but avoid abuse (this requires clarification)
* when passing parameters, reason about passing by value+move and const reference and their potential implications. Almost never pass by value
data that can incur the copying of large memory blocks. Small, POD-like values can and often should be passed by value
* if you want your types to be non-copyable, always remember to instruct the compiler to omit the implementation of that specific constructor. The same goes for
all special functions part of the rule-of-5 set

### Pointers and references
* avoid using raw pointer semantics unless it is part of a specific mechanism
* avoid passing pointers to types instead of const references
* use dedicated containers or STL equivalents instead of managing your data on the heap (i.e. you almost never need to create your vector types, smart pointers etc.)


