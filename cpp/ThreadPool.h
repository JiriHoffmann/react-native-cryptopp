#pragma once

#include <condition_variable>
#include <exception>
#include <mutex>
#include <queue>
#include <stdio.h>
#include <thread>
#include <vector>

class ThreadPool {
public:
  ThreadPool();
  ~ThreadPool();
  void queueWork(std::function<void(void)> task);

private:
  // This condition variable is used for the threads to wait until there is work
  // to do
  std::condition_variable_any workQueueConditionVariable;

  // We store the threads in a vector, so we can later stop them gracefully
  std::vector<std::thread> threads;

  // Mutex to protect workQueue
  std::mutex workQueueMutex;

  // Queue of requests waiting to be processed
  std::queue<std::function<void(void)>> workQueue;

  // This will be set to true when the thread pool is shutting down. This tells
  // the threads to stop looping and finish
  bool done;

  // Function used by the threads to grab work from the queue
  void doWork();
};
