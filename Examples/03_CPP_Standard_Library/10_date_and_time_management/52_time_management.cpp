#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

int main()
{
    ////// system_clock
    std::chrono::system_clock sys_clk;
    std::chrono::time_point<std::chrono::system_clock> now_sys_time = sys_clk.now();
    std::time_t time = std::chrono::system_clock::to_time_t(now_sys_time);
    std::cout << "System time now is " << std::ctime(&time) << std::endl;
    std::chrono::system_clock::duration d = now_sys_time.time_since_epoch();
    std::cout << "Years since epoch " << (std::chrono::duration_cast<std::chrono::hours>(d).count() / 24 / 365) << std::endl;

    /////// steady_clock
    std::chrono::steady_clock stdy_clock;
    std::chrono::time_point<std::chrono::steady_clock> tp1 = stdy_clock.now();
    std::this_thread::sleep_for(std::chrono::microseconds(200));
    std::chrono::time_point<std::chrono::steady_clock> tp2 = stdy_clock.now();
    std::cout << "Time spent " << std::chrono::duration_cast<std::chrono::microseconds>(tp2 - tp1).count() << std::endl;

    /////// steady_clock
    std::chrono::high_resolution_clock high_clock;
    std::chrono::time_point<std::chrono::high_resolution_clock> tph1 = high_clock.now();
    std::this_thread::sleep_for(std::chrono::microseconds(200));
    std::chrono::time_point<std::chrono::high_resolution_clock> tph2 = high_clock.now();
    std::cout << "Time spent " << std::chrono::duration_cast<std::chrono::microseconds>(tph2 - tph1).count() << std::endl;

    using namespace std::chrono_literals;
    using TP_HRC = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using DUS = std::chrono::duration<double, /* ratio*/ std::micro>;
    using DUS_DIRECT = std::chrono::microseconds;
    TP_HRC tp_static1 = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);
    TP_HRC tp_static2 = std::chrono::high_resolution_clock::now();
    DUS dr_double = tp_static2 - tp_static1; // high_resolution_clock type is double
    DUS_DIRECT dr_direct = std::chrono::duration_cast<std::chrono::microseconds>(tp_static2 - tp_static1);
    std::cout << "Compare results with casting " << dr_direct.count() << " vs. " << std::fixed << std::setprecision(9) 
                << dr_double.count() << std::endl;


    // duration literal operator
    std::chrono::hours day = 24h;
    std::chrono::minutes hour = 60min;
    std::chrono::seconds minute = 60s;
    std::chrono::milliseconds second = 1000ms;
    std::cout << "A day has " << day.count() << " hours, an hour has " << hour.count() << " seconds..." << std::endl;
    std::cout << "An hour and 20 min and 35 seconds has a total in seconds " << (1h + 20min + 35s).count() << std::endl;

    return 0;
}