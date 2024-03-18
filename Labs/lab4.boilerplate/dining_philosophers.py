import threading
import time
import random

# Define the number of philosophers / forks
PHILOSOPHERS_COUNT = 5
thinking_time = 1
eating_time = 5

# Initialize locks for each fork
forks = [threading.Lock() for _ in range(PHILOSOPHERS_COUNT)]

mutex = threading.Semaphore(1)


def philosopher(id):

    while True:
        # Think
        print(f"Philosopher {id} is thinking.")
        # Simulate thinking time
        time.sleep(random.randint(1, thinking_time))

        # TODO: You should protect the critical section before executing the code below
        mutex.acquire()

        left_fork = id
        right_fork = (id + 1) % PHILOSOPHERS_COUNT

        # Pick up forks
        print(f"Philosopher {id} is hungry.")

        forks[left_fork].acquire()
        print(f"Philosopher {id} picked up left fork.")

        forks[right_fork].acquire()
        print(f"Philosopher {id} picked up right fork.")

        # Release the lock
        mutex.release()
        
        # Eat
        # Simulate eating time
        print(f"Philosopher {id} is eating.")
        time.sleep(random.randint(1, eating_time))

        # Put down forks
        forks[left_fork].release()
        forks[right_fork].release()


        print(f"Philosopher {id} finished eating and put down forks.")


if __name__ == "__main__":
    # Create and start philosopher threads
    philosophers = [threading.Thread(
        target=philosopher, args=(i,)) for i in range(PHILOSOPHERS_COUNT)]
    for p in philosophers:
        p.start()

    # Wait for all threads to finish
    for p in philosophers:
        p.join()
