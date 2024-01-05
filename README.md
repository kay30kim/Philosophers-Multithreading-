# Philsophers (Multithreading)
## Description
Implement a solution to the dining philosophers problem using threads and mutexes. Each philosopher is represented by a thread, and there is one fork between each pair of philosophers. Philosophers need two forks to eat, one on their left and one on their right. To prevent race conditions, mutexes are used to protect the state of forks. The program takes the number of philosophers, time to die, time to eat, and time to sleep as command-line arguments.

## Table of Contents
1. [General Idea]()
2. [Race Conditions & Mutex]()
3. [Step-by-Step Guide]()
   3-1. [Checking the Input]()
   3-2. [Creating the Structures]()
   3-3. [Initialization and Allocation]()
   3-4. [Structuring the Philo's Routine, the Supervisor, and the Monitor]()
   3-5. [Clearing the Memory]()
   3-6. [Utils Functions]()
   
## General Idea
The project solves the dining philosophers problem using multithreading. Each philosopher thinks, eats, and sleeps in a loop. Mutexes are used to avoid race conditions and ensure proper synchronization between the philosophers. A supervisor thread monitors the time since the last meal for each philosopher, and a monitor thread checks if all philosophers have eaten the required number of times.

## Race Conditions & Mutex
- **Race Conditions**: Situations where multiple threads try to access and modify the same variable simultaneously, leading to unexpected results.
- **Mutex (Mutual Exclusion)**: Locks used to prevent race conditions by allowing only one thread to access a critical section at a time.
  
## Step-by-Step Guide
1. **Checking the Input**
  - Validate and parse command-line arguments.
  - Ensure the input adheres to specified conditions.
2. **Creating the Structures**
   - Define structures for the general set of rules and individual philosophers.
   - Use pointers to link structures and pass data between threads.
3. **Initialization and Allocation**
   - Allocate memory for structures.
   - Initialize mutexes and start threads using pthread_create.
4. **Structuring the Philo's Routine, the Supervisor, and the Monitor**
  - Implement the philosopher's routine with actions such as thinking, eating, and sleeping.
   - Create a supervisor thread to monitor philosopher activity.
   - Implement a monitor thread for optional termination conditions.
5. **Clearing the Memory**
   - Join threads using pthread_join.
   - Destroy mutexes with pthread_mutex_destroy.
   - Free allocated memory using free.
6. **Utils Functions**
   - Utilize functions for error handling, time retrieval, and thread termination.
   - Implement clear_data, ft_exit, error, get_time, and ft_usleep functions.

## Utils Functions
 - *clear_data*: Clear allocated memory for structures.
 - *ft_exit*: Destroy mutexes and clear memory on program exit.
 - *error*: Handle errors and perform cleanup.
 - *get_time*: Retrieve the current time in milliseconds.
 - *ft_usleep*: A more precise implementation of the usleep function.
  
## Make
The project includes a Makefile with standard rules (`all`, `clean`, `fclean`, `re`).

## Example Usage
```./philo 5 800 200 200 7```
This command runs the philosopher program with 5 philosophers, a time to die of 800 ms, time to eat of 200 ms, time to sleep of 200 ms, and each philosopher must eat 7 times.
