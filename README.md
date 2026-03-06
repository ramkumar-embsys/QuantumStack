# 🚀 QuantumStack (QMS)

**QuantumStack** is a lightweight, deterministic, and dynamic stack implementation engineered for resource-constrained embedded environments. 

Most embedded stacks are "static"—they occupy a fixed chunk of RAM regardless of use. **QuantumStack** breaks this limitation by using **Qmalloc**, a custom Free-List memory allocator, allowing the stack to grow and shrink dynamically while maintaining the predictability required for real-time systems.

## 🌟 Unique Selling Propositions (USPs)

### 1. Zero Static Bloat
Traditional embedded development often requires pre-allocating large arrays (e.g., `int stack[1024]`). This wastes RAM if the stack isn't full. QuantumStack allocates memory only when `push` is called, maximizing available heap for other system tasks.

### 2. Powered by Qmalloc (Free-List Engine)
The stack is built on top of a hand-coded **Free-List Allocator**. 
* **Deterministic**: Designed for predictable timing, unlike the "black box" of standard `malloc`.
* **Fragmentation Aware**: Specifically tuned to handle the uniform block sizes common in stack operations.

### 3. "Plug-and-Play" Modular Design
Integration is seamless. An engineer only needs to include `QMS_Stack.c` and its header to begin. No complex OS dependencies or heavy standard libraries are required.

### 4. Safety & Robustness
By moving away from static buffers, QuantumStack avoids silent stack overflows. If memory is exhausted, the allocator returns a clear error code, allowing the firmware to enter a safe state rather than crashing.

---

## 🛠 Project Structure

```text
QuantumStack/
├── src/                # Core Stack logic (QMS_Stack.c)
├── include/            # Header definitions
├── lib/                # Dependency: QuantumMalloc (Qmalloc)
├── obj/                # Auto-generated object files
└── Makefile            # Advanced build system with dependency tracking

#include "QMS_Stack.h"

int main() {
    // 1. Initialize the stack
    QMS_Stack *myStack = QMS_Stack_Create();

    // 2. Push data dynamically
    QMS_Push(myStack, 0xDEADBEEF);

    // 3. Pop data
    uint32_t val = QMS_Pop(myStack);

    // 4. Clean up
    QMS_Stack_Destroy(myStack);
    return 0;
}
