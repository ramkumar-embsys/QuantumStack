🚀 QuantumStack
QuantumStack (QMS) is a lightweight, dynamic stack implementation specifically engineered for resource-constrained embedded systems. Unlike traditional embedded stacks that rely on fixed-size static arrays, QuantumStack leverages Qmalloc, a custom-built, deterministic free-list allocator, to provide dynamic scaling without the bloat of standard libraries.

🌟 Why QuantumStack? (USPs)
1. Zero Static Overhead
Traditional embedded implementations often force you to pre-allocate MAX_SIZE arrays, wasting precious RAM. QuantumStack allocates memory only when needed using the Qmalloc engine. This "just-in-time" approach maximizes available memory for other critical system tasks.

2. Powered by Qmalloc (Free List Engine)
The stack is built on top of a custom-implemented Free List allocator.

Deterministic: Designed to provide predictable allocation times, which is crucial for real-time systems.

Fragmentation Aware: Efficiently manages small memory blocks, a common requirement for stack-based operations.

3. "Plug-and-Play" Integration
Engineered for simplicity. To integrate QuantumStack into your firmware, an engineer only needs to include QMS_Stack.h (and the source files). There are no complex configuration files or heavy dependencies.

4. Safety-First Design
By moving away from static memory, QuantumStack helps mitigate common stack-overflow risks that occur when a static buffer is exceeded. Since it is backed by Qmalloc, it can return clear "Out of Memory" (OOM) status codes, allowing your system to fail gracefully rather than crashing silently.

QuantumStack/
├── src/                # Implementation files (.c)
├── include/            # Public headers (.h)
├── obj/                # Object files (Intermediate build artifacts)
├── bin/                # Final executable binaries
└── Makefile            # Advanced GNU Make build script
