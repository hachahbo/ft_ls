# ft_ls

**Recoding the Unix `ls` command.**

This project is a major step in the C programming journey (42 School), requiring direct interaction with the operating system's file system API. The goal is to master file system access, data management, and algorithm optimization in C.

---

## 🗺️ ft_ls Learning Roadmap

This project focuses on three main areas: **File System I/O**, **Data Structures & Sorting**, and **Metadata Retrieval**.

### 1. File System Interaction (The Kernel Interface)
The most critical part of the project is understanding how to "look inside" a directory using the kernel interface.

| Concept | Explanation | Mandatory Functions |
| :--- | :--- | :--- |
| **Directory Access** | Opening a directory, reading entries one by one, and closing it. | `opendir`, `readdir`, `closedir` |
| **File Metadata** | Retrieving detailed info (permissions, size, owner, timestamps) for the `-l` flag. | `stat`, `lstat` |
| **User/Group Info** | Translating numeric UIDs and GIDs into readable names. | `getpwuid`, `getgrgid` |
| **Time Management** | Formatting raw timestamps into readable date strings. | `time`, `ctime` |
| **Symbolic Links** | Handling files that point to other files (`lstat` vs `stat`). | `readlink` |

### 2. Data Structures and Sorting
A key challenge of `ft_ls` is designing the code structure before writing it.

* **Design a File/Entry Structure:** You cannot simply print names as they are read. To support sorting (`-r`, `-t`) and recursion (`-R`), all directory entries must be read and stored in memory first.
* **Recommended Structure:** A **Linked List** is the most flexible choice.
    * *Struct Idea:* `t_file_info` containing the filename, `stat` data, and a pointer to the next node.
* **Sorting Algorithms:**
    * **Name:** Alphanumeric sort (Default).
    * **Reverse Name:** Reverse alphanumeric sort (`-r`).
    * **Time:** Sort by modification time (`-t`).

### 3. Libft and Utility Functions
The quality of the custom library (`libft`) significantly impacts the project workflow.

* **Memory Management:** `malloc`, `free`, and custom allocation for structures.
* **String Functions:** Essential for comparing and sorting file names.
* **List Management:** Adding, deleting, and iterating through file structures.
* **Error Handling:** Using `perror`, `strerror`, and `exit` for permission handling.
* **Formatted Output:** `ft_printf` is highly recommended for managing the spacing and padding required by the `-l` flag.

---

## 🏁 Implementation Stages

To ensure a robust architecture, the development followed this priority order:

### Phase 1: Basic Listing (`ls -a`)
* **Read and Store:** A function takes a directory path, uses `opendir` and `readdir`, and creates a linked list of all files (including hidden ones starting with `.`).
* **Simple Output:** Iterates the list and uses `write` to print names, effectively recreating basic `ls` behavior.

### Phase 2: Sorting (`ls -r`, `ls -t`)
* **Sorting Logic:** Implementation of a sorting algorithm (e.g., Merge Sort) applied to the linked list.
* **Stat Integration:** The structure was modified to use `lstat` during the reading phase, storing full metadata to allow for time-based sorting.

### Phase 3: Long Format (`ls -l`)
* **Formatting:** Logic to display detailed metadata: Permissions (`drwxr-xr-x`), link count, owner, group, size, and formatted time.

### Phase 4: Recursion (`ls -R`)
* **Recursive Logic:** When the program encounters a directory, it calls the main listing function on that new path. This was accounted for in the initial design to prevent massive refactoring.

---

## 📚 Resources
* **Man pages:** `man 3 opendir`, `man 2 stat`, `man 3 ctime`.