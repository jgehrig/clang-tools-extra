.. title:: clang-tidy - microsoft-uniform-initialization

microsoft-uniform-initialization
================================

Prefer uniform initialization whenever possible, especially for integral data
types. Uniform initialization helps catch narrowing bugs at compile time.

**Bad:**
.. code-block:: C++
// The compile will allow this:
int foo = 1.25; // foo == 1
..

**Good:**
.. code-block:: C++
// The compiler will not allow this:
int foo { 1.25 }; // Error narrowing conversion!
..

**TODO:** Some types do not require {} if the default constructor is well
designed. EX) ``std::string foo;``
an em

See http://www.stroustrup.com/C++11FAQ.html#narrowing and
http://www.stroustrup.com/C++11FAQ.html#init-list for more details
