#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <random>
#include <atomic>

struct WorkerStats {
    int sleepCount = 0;
    int wakeCount = 0;
    bool isSleeping = false;
};

std::mutex mtx;
std::condition_variable cv;
std::queue<int> mainQueue;
bool finished = false;

std::vector<WorkerStats> stats(10);
std::queue<int> sleepingWorkers; 

void workerFunc(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]{ return !mainQueue.empty() || finished; });

        if (finished && mainQueue.empty()) break;

        int num = mainQueue.front();
        mainQueue.pop();
        lock.unlock();

        if (num == 7) {
            stats[id].sleepCount++;
            stats[id].isSleeping = true;
            std::unique_lock<std::mutex> sleepLock(mtx);
            sleepingWorkers.push(id);
            cv.wait(sleepLock, [&]{ return !stats[id].isSleeping; });
        } else if (num == 0) {
            if (!sleepingWorkers.empty()) {
                int wid = sleepingWorkers.front();
                sleepingWorkers.pop();
                stats[wid].wakeCount++;
                stats[wid].isSleeping = false;
                cv.notify_all();
            }
        } else if (num == 21) {
            while (!sleepingWorkers.empty()) {
                int wid = sleepingWorkers.front();
                sleepingWorkers.pop();
                stats[wid].wakeCount++;
                stats[wid].isSleeping = false;
            }
            cv.notify_all();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

int main() {
    int N;
    std::cout << "Enter quantity numbers: ";
    std::cin >> N;

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(-100, 100);

    std::vector<std::thread> workers;
    for (int i = 0; i < 10; i++) {
        workers.emplace_back(workerFunc, i);
    }

    for (int i = 0; i < N; i++) {
        int num = dist(gen);
        {
            std::lock_guard<std::mutex> lock(mtx);
            mainQueue.push(num);
        }
        cv.notify_all();
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv.notify_all();

    for (auto &w : workers) w.join();

    int sleepEndCount = 0;
    std::vector<int> sleepEndIds;
    for (int i = 0; i < 10; i++) {
        if (stats[i].isSleeping) {
            sleepEndCount++;
            sleepEndIds.push_back(i);
        }
    }

    std::cout << "Thread end sleep: " << sleepEndCount << "\n";
    std::cout << "ID sleep: ";
    for (int id : sleepEndIds) std::cout << id << " ";
    std::cout << "\n";
    for (int i = 0; i < 10; i++) {
        std::cout << "Worker " << i << ": sleep=" << stats[i].sleepCount << ", wake=" << stats[i].wakeCount << "\n";
    }
}
