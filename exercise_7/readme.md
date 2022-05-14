# Why do we use the keyword volatile?
The `volatile` modifier is used C programs to mark a variable to be used with more care as concerning compiler optimizations and runtime.
In the context of embedded systems, this modifier is for example required for variables when interrupts modify them. A foreseeable usage/processing of such a variable can't be guaranteed, as the interrupt can happen at any time.

# What are the problems with dynamic memory allocation in embedded systems?
If an embedded system doesn't use an OS which handles garbage collection, the memory tends to fragment as dynamic memory isn't allocated and deallocated in a consecutive manner (like the stack memory). The address from where new memory is allocated moves always forward when new memory is required and only moves backwards, when the last allocated memory is deallocated. Memory that is deallocated in the middle simply leaves most of the times an unusable hole. In the worst case, this fragmentation leads to crashs, as the memory that can allocated is not enough and reaches into the stack memory or other address spaces.
