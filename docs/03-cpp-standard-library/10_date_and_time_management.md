# Date and time management

(Slides 59–60)

- For C++, the standard library provides the `chrono` library that allows manipulating date and time in source code
- The `chrono` library contains three main types of utilities:
  - clocks
  - time points
  - durations
- Clocks: a clock consists of a starting timepoint named "epoch"
  - `std::chrono::system_clock`: represents system clock, non-monotonic clock (can be modified at any time) and can be mapped to C-style time
  - `std::chrono::steady_clock`: monotonic clock (that can never be modified), and it is most suitable for measuring intervals (like time since last reboot, ...)
  - `std::chrono::high_resolution_clock`: a clock with smallest tick period, used for precision time measurement
  - Refer to example for details on how to use clocks

```cpp
// Trimmed excerpt — full runnable example: examples/03-cpp-standard-library/10-date-and-time-management/52_time_management.cpp
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    ////// system_clock: non-monotonic, can be mapped to C-style time
    std::chrono::system_clock sys_clk;
    std::chrono::time_point<std::chrono::system_clock> now_sys_time = sys_clk.now();
    std::time_t time = std::chrono::system_clock::to_time_t(now_sys_time);
    std::cout << "System time now is " << std::ctime(&time) << std::endl;
    std::chrono::system_clock::duration d = now_sys_time.time_since_epoch();
    std::cout << "Years since epoch " << (std::chrono::duration_cast<std::chrono::hours>(d).count() / 24 / 365) << std::endl;

    /////// steady_clock: monotonic, suited for measuring intervals
    std::chrono::steady_clock stdy_clock;
    std::chrono::time_point<std::chrono::steady_clock> tp1 = stdy_clock.now();
    std::this_thread::sleep_for(std::chrono::microseconds(200));
    std::chrono::time_point<std::chrono::steady_clock> tp2 = stdy_clock.now();
    std::cout << "Time spent " << std::chrono::duration_cast<std::chrono::microseconds>(tp2 - tp1).count() << std::endl;

    /////// high_resolution_clock: smallest tick period, for precision measurement
    std::chrono::high_resolution_clock high_clock;
    std::chrono::time_point<std::chrono::high_resolution_clock> tph1 = high_clock.now();
    std::this_thread::sleep_for(std::chrono::microseconds(200));
    std::chrono::time_point<std::chrono::high_resolution_clock> tph2 = high_clock.now();
    std::cout << "Time spent " << std::chrono::duration_cast<std::chrono::microseconds>(tph2 - tph1).count() << std::endl;

    // duration literal operator
    using namespace std::chrono_literals;
    std::chrono::hours day = 24h;
    std::chrono::minutes hour = 60min;
    std::cout << "A day has " << day.count() << " hours, an hour has " << hour.count() << " minutes" << std::endl;

    return 0;
}
```

---

