// SPDX-License-Identifier: GPL-3.0-or-later

#include "mem.h"
#include "types.h"

// Register state for a thread.
struct ThreadContext {
    u128 gprs[25]; // $at - $t9
    u128 gp, fp, sp, ra, hi, lo;
    u32  sa;
    u32  fprs[32]; // $f0 - $f31
    u32  fp_acc;
    u32  fp_ctrl;
};

// A thread.
struct Thread {
    // The thread's $gp register.
    u32   gp_reg;
    // Size of the thread's stack.
    i32   stack_size;
    // The top of the thread's stack, minus space for a ThreadContext.
    void* initial_stack;
    // The bottom of the thread's stack.
    void* stack_bottom;
    // The address to return to after the thread exits.
    void* return_address;
    // Thread arguments.
    char* args;
};

// The thread state. 
#define CURR_THREAD  0x00003000
#define THREAD_ARRAY 0x00001000
#define END_OF_RAM   0x02000000

struct Thread* threads = (struct Thread*)THREAD_ARRAY;
int* current_thread = (int*)CURR_THREAD;

// Initialise the main thread, setting up the stack.
void* ee_init_main_thread(u32 gp, void* stack_ptr, i32 stack_size, char* args, u32 return_address)
{
    // -1 is a magic term meaning "the end of RAM", more or less.
    // I don't think games care too much about the exact positioning, but we'll follow the BIOS.
    if ((i32)stack_ptr == -1) {
        // Specifically, -1 means "the end of RAM minus (stack_size plus 4KiB)".
        stack_ptr = (void*)(END_OF_RAM - (stack_size + 4096));
    }

    // Initialise a thread context within the 4KiB buffer zone.
    struct ThreadContext* ctx = (struct ThreadContext*)((u32)stack_ptr + stack_size - sizeof(struct ThreadContext) / 4);

    ctx->gp = gp;
    ctx->ra = return_address;
    ctx->fp = ctx->sp = (u32)ctx + sizeof(struct ThreadContext);

    // Zero the thread array.
    memset(threads, 0, 256 * sizeof(struct Thread));

    // Initialise the current thread.
    threads[*current_thread].gp_reg = gp;
    threads[*current_thread].stack_size = stack_size;
    threads[*current_thread].initial_stack = ctx;
    threads[*current_thread].stack_bottom = stack_ptr;
    threads[*current_thread].return_address = (void*)return_address;
    // TODO: setup argument buffer from args.

    // Return the ThreadContext object that represents this thread.
    return ctx;
}