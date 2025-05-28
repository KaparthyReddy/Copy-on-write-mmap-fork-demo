#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

#define PAGE_SIZE 4096

void print_memory_info(char *label, void *addr, char *data) {
    printf("%s: Data at address %p contains: '%s'\n", label, addr, data);
}

int main() {
    char *shared_page = mmap(NULL, PAGE_SIZE,
                             PROT_READ | PROT_WRITE,
                             MAP_ANONYMOUS | MAP_PRIVATE,
                             -1, 0);

    if (shared_page == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    strcpy(shared_page, "Initial data");

    printf("Parent process (PID: %d)\n", getpid());
    print_memory_info("Parent before fork", shared_page, shared_page);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("\nChild process (PID: %d)\n", getpid());
        print_memory_info("Child after fork", shared_page, shared_page);

        printf("\nChild reads shared data (no copy made yet)\n");

        printf("\nChild now writes to the shared page (should trigger COW)\n");
        strcpy(shared_page, "Modified by child");
        print_memory_info("Child after write", shared_page, shared_page);

        exit(0);
    } else {
        usleep(10000);

        printf("\nParent process again (PID: %d)\n", getpid());
        print_memory_info("Parent after child modification", shared_page, shared_page);

        printf("\nParent modifies its copy of the page\n");
        strcpy(shared_page, "Modified by parent");
        print_memory_info("Parent after write", shared_page, shared_page);

        wait(NULL);
    }

    munmap(shared_page, PAGE_SIZE);

    return 0;
}
