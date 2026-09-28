#include <iostream>
#include <future>
#include <thread>
#include <functional>

using namespace std::placeholders;

class Test
{
public:
    void operator()(int x, int y)
    {
        std::cout << "Operator() X=" << x << " Y=" << y << std::endl;
    }

    void run(int x, int y)
    {
        std::cout << "Run() X=" << x << " Y=" << y << std::endl;
    }
};

int main()
{
    std::promise<int> i_promise;
    std::future<int> i_future;
    std::cout << "Not assigned future is " << (i_future.valid() ? "valid" : "invalid") << std::endl;
    i_future = i_promise.get_future();
    std::cout << "Future is now " << (i_future.valid() ? "valid" : "invalid") << std::endl;
    std::thread th1([&i_promise]()
                    {
        std::cout << "Thread th1 launched" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        i_promise.set_value(0); });

    i_future.wait(); // blocking call
    std::cout << "Future is ready and the retrieved value is " << i_future.get() << " and after get the shared state is now "
              << (i_future.valid() ? "valid" : "invalid") << std::endl;

    // i_future and i_promise are no longer usable
    try
    {
        i_promise.set_value(2);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception raised for promise set: " << e.what() << std::endl;
    }
    try
    {
        i_future.get();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception raised for future get: " << e.what() << std::endl;
    }
    th1.join();

    // future cannot be used to wait from many threads since it will cause an exception
    // we have to used shared future
    std::promise<int> v_promise;
    std::shared_future<int> vs_future1 = v_promise.get_future();

    // getting a second shared future like below will cause exception if
    // get is performed from the first shared_future
    // std::shared_future<void> vs_future2 = v_promise.get_future();

    // a copy of shared_future itself should be sone
    std::shared_future<int> vs_future2{vs_future1};

    std::thread th2([&vs_future1]()
                    {
        std::cout << "Th2 is launched" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Th2 finished " << vs_future1.valid() 
            << " value " << vs_future1.get() << std::endl; });
    std::thread th3([&vs_future2]()
                    {
        std::cout << "Th3 is launched" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Th3 finished " << vs_future2.valid() 
        << " value " << vs_future2.get() << std::endl; });
    std::cout << "Set promise for shared futures" << std::endl;
    v_promise.set_value(51);

    th2.join();
    th3.join();

    // example of synchronization using shared futures
    std::promise<void> pr1;
    std::promise<void> pr2;
    std::promise<void> pr3;

    std::shared_future<void> fut1 = pr1.get_future();
    std::future<void> fut2 = pr2.get_future();
    std::future<void> fut3 = pr3.get_future();

    std::thread th4([&, fut1]()
                    {
        pr2.set_value();
        fut1.wait();
        std::cout << "Th4 exited" << std::endl; });
    std::thread th5([&, fut1]()
                    {
        pr3.set_value();
        fut1.wait();
        std::cout << "Th5 exited" << std::endl; });

    std::cout << "Wait Th4 and Th5 to start" << std::endl;
    fut2.wait();
    fut3.wait();
    std::cout << "Allow threads to exit" << std::endl;
    pr1.set_value();
    th4.join();
    th5.join();

    // exception from the thread using promise and future
    std::promise<int> e_pr;
    std::future<int> e_ft = e_pr.get_future();

    std::thread eTh([&e_pr]() {
        try
        {
            // some processing that throw an exception
            throw std::runtime_error("This is an exception");
        }
        catch (...)
        {
            e_pr.set_exception(std::current_exception()); // std::exception_ptr
    } });

    try
    {
        e_ft.wait();
        int value = e_ft.get();
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception thrown from thread " << e.what() << std::endl;
    }
    eTh.join();
    std::cout << std::endl
              << "############### std::async #################" << std::endl;
    std::promise<void> launch_pr;
    std::future<void> launch_ft = launch_pr.get_future();
    std::future<int> async_ret_future = std::async([&launch_pr]()
                                                   {
        int x{0};
        launch_pr.set_value();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return x; });
    // wait thread to be launched (immediately)
    launch_ft.get();
    std::cout << "Thread is launched" << std::endl;
    std::cout << "Thread returned value " << async_ret_future.get() << std::endl;

    // same think to check how deferreed is working
    std::promise<void> launch_pr_d;
    std::future<void> launch_ft_d = launch_pr_d.get_future();
    std::future<int> async_ret_future_d = std::async(std::launch::deferred, [&launch_pr_d]()
                                                     {
        int x{10};
        launch_pr_d.set_value();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return x; });
    // wait thread to be launched, won't happen since result is not claimed
    std::cout << "Wait for deferred thread to be launched" << std::endl;
    std::future_status sts = launch_ft_d.wait_for(std::chrono::seconds(2));
    if (sts != std::future_status::ready)
    {
        std::cout << "Wait for deferred thread start, result is " << (sts == std::future_status::deferred ? " deferred" : " timed out") << std::endl;
    }
    // claim result to start thread
    int res = async_ret_future_d.get();
    sts = launch_ft_d.wait_for(std::chrono::seconds(1));
    if (sts == std::future_status::ready)
    {
        std::cout << "Deferred thread started" << std::endl;
    }
    std::cout << "Wait for deferred thread start, result is " << res << std::endl;

    auto lambda = []()
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cout << "Async Thread returned" << std::endl;
        return 1;
    };

    // using std::async will block during call or ~future returned by it as rvalue
    // if assigned to lvalue, it will run asynchronously
    /*auto ft = */ std::async(lambda);

    std::cout << "Async exited" << std::endl;

    std::cout << std::endl
              << "############### std::packaged_task #################" << std::endl;

    // using std::packaged_tas will block during call or ~future returned by it
    std::packaged_task<void(void)> ptsk(lambda);
    ptsk();
    std::packaged_task<int(void)> ptsk2(lambda);
    std::cout << "Packaged_task exited" << std::endl;
    auto ft2 = ptsk2.get_future();
    std::thread pkg_thread(std::move(ptsk2));
    std::cout << "Launched as thread" << std::endl;
    pkg_thread.join();
    std::cout << "Thread result is " << ft2.get() << std::endl;

    // std::bind will create an equivalend function by passing 2 as first parameter
    // it becomes here operator()(2, y)
    std::packaged_task<void(int)> ptsk3(std::bind(Test(), 2, _1));
    ptsk3(10);
    Test test;
    auto fn = std::mem_fn(&Test::run); // get a function pointer to run member function
    auto bound = std::bind(fn, &test, 3, _1);

    std::packaged_task<void(int)> ptsk4(bound);
    ptsk4(50);
    bound(50);
    return 0;
}