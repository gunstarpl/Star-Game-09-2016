#pragma once

//
// NonCopyable
//
//  Prevents an instance of derived class from being copied.
//
//  Example usage:
//      class Object : private NonCopyable
//      {
//          /* ... */
//      }
//

class NonCopyable
{
protected:
    // Default class constructor and destructor.
    NonCopyable() = default;
    ~NonCopyable() = default;

    // Delete copy constructor and operator.
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};
