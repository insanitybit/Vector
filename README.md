Vector
======

An implementation of the vector data structure. Uses C++11 smart pointers. Support for custom allocator coming at some point.

Should work as a drop in replacement for std::vector for most common functions, with the added benefit of specifying a custom growth rate.

Optimized with -O3 it appears to have a higher data cache hit rate than the STL. Don't ask me why, this was just a first go at it. I haven't
actually bothered to try to optimize it yet.