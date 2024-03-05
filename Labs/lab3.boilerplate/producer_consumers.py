import threading
import time

'''
This program simulates a producer-consumer problem using threads. The producer-consumer problem is a 
classic synchronization problem where there are two types of threads: producers and consumers. Producers produce 
data and put it into a shared buffer, while consumers consume data from the buffer. The problem is to make sure 
that the producers and consumers do not interfere with each other and that the consumers do not consume data that has not been produced yet.
'''


class SharedBuffer:
    def __init__(self, size):
        # Internal shared buffer
        self.buffer = []
        
        # Mutex to protect the buffer
        self.mutex = threading.Lock()
        
        # Semaphores to signal when the buffer is not empty
        self.notEmpty = threading.Semaphore(0)
        
        # Semaphores to signal when the buffer is not full
        self.notFull = threading.Semaphore(size)
        
        # Flag to signal that production is done
        self.doneProducing = False

    '''
    Add a message to the buffer. If the buffer is full, the producer will wait.
    '''

 

    def add_message(self, message):
        # Wait if buffer is full
        self.notFull.acquire()
        
        with self.mutex:
            self.buffer.append(message)
        
        # Signal that buffer is not empty
        self.notEmpty.release()


    '''
    Read a message from the buffer. If the buffer is empty, the consumer will wait.
    '''

    def read_message(self):
        message = None
        # TODO: wait if buffer is empty
        self.notEmpty.acquire()

        with self.mutex:
            # TODO: if production is done and buffer is empty, return None (check the buffer length)
            if len(self.buffer) == 0 and self.doneProducing:
                # TODO: release the requried semaphore to avoid deadlock
                self.notEmpty.release()

                # Return None if production is done and buffer is empty
                return None

            message = self.buffer.pop(0)
        
        # Signal that buffer is not full
        self.notFull.release()

        return message

    '''
    Mark that production is done. This will be used by the producers to signal that they are done producing.
    '''

    def mark_done_producing(self):
        with self.mutex:
            # Set the flag to signal that production is done
            self.doneProducing = True
            print("Current Buffer: " + str(self.buffer))
            # Release semaphore to ensure all consumers can exit
            for _ in range(len(self.buffer)):
                self.notEmpty.release()
                # self.notEmpty.release()
            if len(self.buffer) == 0:
                self.notEmpty.release()


    def check_done_producing(self):
        with self.mutex:
            if self.doneProducing and len(self.buffer) == 0:
                # Release the semaphore to wake up any waiting consumers
                self.notEmpty.release()
                return True
            return False


# Shared buffer
buffer = SharedBuffer(10)

'''
Producer and consumer functions. Each producer produces multiple messages and each consumer consumes messages until production is done.
'''


def producer(thread_id):
    # Each producer produces 5 messages
    for message_number in range(5):
        
        message = f"Message {message_number} from Producer {thread_id}\n"
        buffer.add_message(message)
        
        print(f"Producer {thread_id} produced: {message}")
        time.sleep(2)
        
    # After the last producer finishes, signal that production is done. Note that 4 is the number of producers
    if thread_id == 4 - 1:
        buffer.mark_done_producing()



'''
Consumer function. Each consumer consumes messages until production is done and the buffer is empty.
'''


def consumer(thread_id):
    while True:
        
        # Consume a message from the buffer
        message = buffer.read_message()
        
        if message is None:
            # Break the loop if production is done and buffer is empty
            if buffer.check_done_producing():
                break
            
        print(f"Consumer {thread_id} consumed: {message}")
        time.sleep(1)  # Simulate reading time


def main():
    producers = [threading.Thread(target=producer, args=(i,)) for i in range(4)]
    consumers = [threading.Thread(target=consumer, args=(i,)) for i in range(10)]

    for p in producers:
        p.start()

    for c in consumers:
        c.start()

    for p in producers:
        p.join()

    for c in consumers:
        c.join()

    print("All producers and consumers have finished.")


if __name__ == '__main__':
    main()