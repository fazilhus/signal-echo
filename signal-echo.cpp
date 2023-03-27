#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ucontext.h>
#include <pwd.h>

void handler(int num, siginfo_t* siginfo, void* context) {
    std::cout << "Received a SIGUSR1 signal from process " << siginfo->si_pid;
    std::cout << " executed by " << siginfo->si_uid << "." << std::endl; 
    ucontext_t* ucontext = static_cast<ucontext_t*>(context);
    std::cout << " State of the context: EIP = " << ucontext->uc_mcontext.gregs[REG_RIP];
    std::cout << ", EAX = " << ucontext->uc_mcontext.gregs[REG_RAX] << ", ";
    std::cout << " EBX = " << ucontext->uc_mcontext.gregs[REG_RBX] << "." << std::endl;

    return;
}

int main(int argc, char** argv) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = &handler;

    if (sigaction(SIGUSR1, &sa, NULL) < 0) {
        std::cerr << "Something went wrong: " << strerror(errno) << std::endl;
        exit(errno);
    }
    
    while(true) {
        sleep(1);
    }
    return 0;
}
