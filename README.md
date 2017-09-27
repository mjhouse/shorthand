# Shorthand.h

This is a small header-only library of simple data structures and utilities that are meant to be used in other C++ projects. All structures are contained in the **shorthand::** namespace Everything here is FOSS under the GNU General Public License v2.0.

### config.h
This is a tiny config-file parser.

### list.h
A templated single-linked-list data structure. Only has add, remove and count methods, although the add method can also insert a value into the middle of the list.

### queue.h
A templated queue with push, pop and count methods.

### stack.h
Basically another queue with the same methods, but used as a stack.

### tree.h
A tree for integer values only (not a template).

### utilities.h
This was meant to hold a lot of little useful functions, but they got removed or merged into other files. The only remaining function is a nifty little split function that turns a string into a vector on a delimeter.
