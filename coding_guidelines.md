# IGTK Coding Guidelines and Conventions

## Naming conventions

### File names

In general, all files must be `snake_case` conformant. E.g. `my_file.hpp`, `my_file.cpp`, `my_file.md`, etc.

For C++ and similar files, headers shall use the `.hxx` extension, 
inline definitions shall have the `.inl` extension, whereas source files shall use the `.cpp` extension.

### C++ essential naming conventions

* user defined types (classes, structures) shall use the `CamelCase` convention
* (member) variable names shall use the `snake_case` convention
* private member variables shall have a trailing `_` suffix, e.g. `int private_counter_{};`
* function and method names shall use the `snake_case` convention

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


