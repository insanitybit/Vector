
NOTE
====
I'll be moving development of this to my DataStructures repo, I'm leaving this repo for the moment, but if you want to see my latest implementation of Vector, here's the link:
https://github.com/insanitybit/DataStructures


Vector
======

An implementation of the vector data structure. Uses C++11 smart pointers. Support for custom allocator coming at some point.

Should work as a drop in replacement for std::vector for most common functions, with the added benefit of specifying a custom growth rate.

Optimized with -O3 it appears to have a higher data cache hit rate than the STL. Don't ask me why, this was just a first go at it. I haven't
actually bothered to try to optimize it yet.
