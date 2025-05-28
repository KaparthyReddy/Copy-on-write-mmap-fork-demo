# Copy-on-Write Demo using mmap and fork 🧠💥

This project demonstrates the **Copy-on-Write (COW)** mechanism in Linux using:
- `mmap()` for memory allocation,
- `fork()` for process creation,
- and observation of shared memory behavior before and after modifications.

---

## 📚 Concept

Copy-on-Write allows a child process to share the parent's memory pages after a `fork()`, and **only duplicates** the memory page when a **write** operation occurs.

---

## 🛠 Features

- Allocates a memory page using `mmap()`
- Forks a child process
- Both processes read and print shared data
- Child modifies the shared memory (triggers COW)
- Parent modifies its own copy later
- All memory content and addresses are printed

---

## 📄 Files

- `cow_demo.c`: Main program demonstrating COW

---

## 🏃 How to Run

```bash
gcc -o cow_demo cow_demo.c
./cow_demo

🔍 Sample Output

Parent process (PID: 1234)
Parent before fork: Data at address 0x... contains: 'Initial data'

Child process (PID: 1235)
Child after fork: Data at address 0x... contains: 'Initial data'
Child now writes to the shared page (should trigger COW)
Child after write: Data at address 0x... contains: 'Modified by child'

Parent process again (PID: 1234)
Parent after child modification: Data at address 0x... contains: 'Initial data'
Parent modifies its copy of the page
Parent after write: Data at address 0x... contains: 'Modified by parent'

🧠 Learnings
How Linux handles shared memory after fork()

Copy-on-Write behavior and lazy memory duplication

Using mmap() for anonymous private memory pages

📄 License
MIT License
