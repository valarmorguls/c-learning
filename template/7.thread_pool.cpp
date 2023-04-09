/*************************************************************************
	> File Name: 7.thread_pool.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 09 Apr 2023 08:51:10 PM CST
 ************************************************************************/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>
#include <condition_variable>

using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(thread_usage)

void func() {
    cout << "hello world" << endl;
    return ;
} 

void print(int a, int b) {
    cout << a << " " << b << endl;
    return ;
} 

int main() {
    thread t1(func);
    t1.join();
    thread t2(print, 3, 4);
    t2.join();
    return 0;
}

ENDS(thread_usage)

//5000w以内素数的统计
BEGINS(prime_count_test)

bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

//功能函数
int prime_count(int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; i++) {
        ans += is_prime(i);
    }
    return ans;
} 

//多线程执行的主函数
//多线程程序设计，功能函数和线程入口函数要分开
//高内聚，低耦合
void worker(int l, int r, int &ret) {
    cout << this_thread::get_id() << " begin" << endl;
    ret = prime_count(l, r);
    cout << this_thread::get_id() << " done" << endl;
    return ;
}

int main() {
    #define batch 5000000
    thread *t[10];
    int ret[10];
    for (int i = 0, j = 1; i < 10; i++, j += batch) {
        t[i] = new thread(worker, j, j + batch - 1, ref(ret[i]));
    }
    for (auto x : t) x->join();
    int ans = 0;
    for (auto x : ret) ans += x;
    for (auto x : t) delete x;
    cout << ans << endl;
    return 0;
}

ENDS(prime_count_test)

BEGINS(prime_count_test1)

int ans = 0;
std::mutex m_mutex; //互斥锁

bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

//功能函数
void prime_count(int l, int r) {
    cout << this_thread::get_id() << " begin" << endl;
    for (int i = l; i <= r; i++) {
        unique_lock<mutex> lock(m_mutex); //临界区
        ans += is_prime(i); //临界资源 （加锁的资源）
        lock.unlock();
    }
    cout << this_thread::get_id() << " end" << endl;
    return ;
} 

int main() {
    #define batch 5000000
    thread *t[10];
    int ret[10];
    for (int i = 0, j = 1; i < 10; i++, j += batch) {
        t[i] = new thread(prime_count, j, j + batch - 1);
    }
    for (auto x : t) x->join();
    for (auto x : t) delete x;
    cout << ans << endl;
    return 0;
}

ENDS(prime_count_test1)

BEGINS(prime_count_test2)

int ans = 0;
std::mutex m_mutex; //互斥锁

bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

//功能函数
void prime_count(int l, int r) {
    cout << this_thread::get_id() << " begin" << endl;
    for (int i = l; i <= r; i++) {
        int ret = is_prime(i); //临界资源 （加锁的资源）
        __sync_fetch_and_add(&ans, ret);
    }
    cout << this_thread::get_id() << " end" << endl;
    return ;
} 

int main() {
    #define batch 5000000
    thread *t[10];
    int ret[10];
    for (int i = 0, j = 1; i < 10; i++, j += batch) {
        t[i] = new thread(prime_count, j, j + batch - 1);
    }
    for (auto x : t) x->join();
    for (auto x : t) delete x;
    cout << ans << endl;
    return 0;
}

ENDS(prime_count_test2)

BEGINS(tast_test)

class Task {
public:
    template <typename FUNC_T, typename ...ARGS>
    Task(FUNC_T func, ARGS ...args) {
        this->func = bind(func, forward<ARGS>(args)...);
    }
    void run() {
        func();
        return ;
    }

private:
    function<void()> func;
};

void test() {
    cout << "hello world : function test" << endl;
    return ;
}

void func(int a, int b) {
    cout << "function " << a << " " << b << endl;
}

void add_one(int &n) {
    n += 1;
    return ;
}

int main() {
    Task t1(func, 3, 4); 
    t1.run();
    t1.run();
    Task t2(test);
    t2.run();

    int n = 1;
    cout << "n = " << n << endl;
    Task t3(add_one, ref(n));
    t3.run();
    t3.run();
    t3.run();
    t3.run();
    cout << "n = " << n << endl;
    return 0;
}

ENDS(task_test)

BEGINS(thread_pool_test)

class Task {
public:
    template <typename FUNC_T, typename ...ARGS>
    Task(FUNC_T func, ARGS ...args) {
        this->func = bind(func, forward<ARGS>(args)...);
    }
    void run() {
        func();
        return ;
    }

private:
    function<void()> func;
};

class ThreadPool {
public:
    ThreadPool(int n = 1) 
    : thread_size(n), threads(n), starting(false) {
        this->start();
        return ;
    }
    void worker() {
        auto id = this_thread::get_id();
        running[id] = true;
        while (running[id]) {
            // 取任务
            Task *t = get_task();
            // 执行任务
            t->run();
            delete t;
        }
        return ;
    }
    void start() {
        if (starting == true) return ;
        for (int i = 0; i < thread_size; i++) {
            threads[i] = new thread(&ThreadPool::worker, this);
        }
        starting = true;
        return ;

    }
    void stop() {
        if (starting == false) return ;
        for (int i = 0; i < threads.size(); i++) {
            this->add_task(&ThreadPool::stop_running, this);
        } 
        for (int i = 0; i < threads.size(); i++) {
            threads[i]->join();
        }
        for (int i = 0; i < threads.size(); i++) {
            delete threads[i];
            threads[i] = nullptr;
        }
        starting = false;
        return ;
    }
    template <typename FUNC_T, typename ...ARGS>
    void add_task(FUNC_T func, ARGS ...args) {
        unique_lock<mutex> lock(m_mutex);
        tasks.push(new Task(func, forward<ARGS>(args)...));
        m_cond.notify_one();
        return ;
    }
    ~ThreadPool() {
        this->stop();
        while (!tasks.empty()) {
            delete tasks.front();
            tasks.pop();
        }
        return ;
    }

private:
    Task *get_task() {
        unique_lock<mutex> lock(m_mutex);
        while (tasks.empty()) m_cond.wait(lock); 
        Task *t = tasks.front();
        tasks.pop();
        return t;
    }
    void stop_running() {
        auto id = this_thread::get_id();
        running[id] = false;
        return ;
    }
    bool starting;
    int thread_size;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    vector<thread *> threads;    
    unordered_map<decltype(this_thread::get_id()), bool> running;
    queue<Task *> tasks;
};

bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

//功能函数
int prime_count(int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; i++) {
        ans += is_prime(i);
    }
    return ans;
} 

//多线程执行的主函数
//多线程程序设计，功能函数和线程入口函数要分开
//高内聚，低耦合
void worker(int l, int r, int &ret) {
    cout << this_thread::get_id() << " begin" << endl;
    ret = prime_count(l, r);
    cout << this_thread::get_id() << " done" << endl;
    return ;
}

int main() {
    ThreadPool tp(5);
    int ret[10];
    for (int i = 0, j = 1; i < 10; i++, j += batch) {
        tp.add_task(worker, j, j + batch - 1, ref(ret[i]));
    }
    //等待线程池中所有任务结束
    tp.stop();
    int ans = 0;
    for (auto x : ret) ans += x;
    cout << ans << endl;
    return 0;
}

ENDS(thread_pool_test)

int main() {
    //thread_usage::main();    
    //prime_count_test::main();
    //prime_count_test1::main();
    //prime_count_test2::main();
    //task_test::main();
    thread_pool_test::main();
    return 0;
}
