import threading
import time

'''def activity(tag):
    for i in range(5):
        thread_id = threading.current_thread().ident
        print('Hello from',tag,"i = " ,i,"thread_id = ",thread_id)
        time.sleep(1)


def worker1():
    activity("worker1")

def worker2():
    activity("worker2")

def main():
    thread1 = threading.Thread(target=worker1)
    thread2 = threading.Thread(target=worker2)
    thread1.start()
    thread2.start()'''
counter = 0

def watcher():
    global counter
    for i in range(10):
        print('counter in watcher ',counter)
        time.sleep(0.2)

def update(lock):
    name = threading.current_thread().name
    global counter
    #for i in range(5):
    with lock:
        #while True:
        for i in range(10):
            counter += 1
            time.sleep(0.1)
        print(name, "i value" ,i,"counter value",counter)

def main():
    threads = []
    lock = threading.RLock()
    for i in range(5):
        thread = threading.Thread(target=update,args=(lock,),name="worker"+str(i))
        threads.append(thread)
        thread.start()
    #thread1 = threading.Thread(target=update,name="worker1")
    #thread2 = threading.Thread(target=update,name="worker1")
    thread3 = threading.Thread(target=watcher,name="worker1")
    #thread1.start()
    #thread2.start()
    thread3.start()
    #thread1.join()
    #thread2.join()
    thread3.join()

    print('final value of counter is',counter)

if __name__ == "__main__":
    main()
