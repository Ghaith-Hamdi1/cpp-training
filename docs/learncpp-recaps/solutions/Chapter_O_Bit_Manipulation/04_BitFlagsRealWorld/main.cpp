// Chapter O - Project 4: Real-World Bit Flags (Function Options)
//
// Key concept: Bit flags are especially useful when a function needs to accept
// many on/off options. Instead of a long list of bool parameters (which are
// error-prone and hard to read), you pass a single flags value.
//
// This pattern is widely used in real APIs (e.g., Win32 CreateWindow flags,
// OpenGL state flags, SDL initialization flags).

#include <cstdint>
#include <iostream>
#include <string>
#include <bitset>

// -----------------------------------------------------------------------
// 1. Define option flags as named constants
// -----------------------------------------------------------------------
// Using a namespace keeps the flag names organized and avoids polluting
// the global namespace.
namespace RenderOption
{
    constexpr std::uint16_t none{0};
    constexpr std::uint16_t wireframe{1 << 0};    // bit 0
    constexpr std::uint16_t antialiasing{1 << 1}; // bit 1
    constexpr std::uint16_t shadows{1 << 2};      // bit 2
    constexpr std::uint16_t reflections{1 << 3};  // bit 3
    constexpr std::uint16_t bloom{1 << 4};        // bit 4
    constexpr std::uint16_t hdr{1 << 5};          // bit 5
    constexpr std::uint16_t vsync{1 << 6};        // bit 6
    constexpr std::uint16_t fullscreen{1 << 7};   // bit 7

    // Convenience combo: a common "high quality" preset
    constexpr std::uint16_t highQuality{
        antialiasing | shadows | reflections | bloom | hdr};
}

// -----------------------------------------------------------------------
// 2. A function that accepts combined flags
// -----------------------------------------------------------------------
// The caller passes a single uint16_t built by OR-ing together any
// combination of RenderOption flags.
void initRenderer(std::uint16_t options)
{
    std::cout << "Initializing renderer with options: "
              << std::bitset<8>(options) << '\n';

    if (options & RenderOption::wireframe)
        std::cout << "  [x] Wireframe mode\n";
    if (options & RenderOption::antialiasing)
        std::cout << "  [x] Anti-aliasing\n";
    if (options & RenderOption::shadows)
        std::cout << "  [x] Shadows\n";
    if (options & RenderOption::reflections)
        std::cout << "  [x] Reflections\n";
    if (options & RenderOption::bloom)
        std::cout << "  [x] Bloom\n";
    if (options & RenderOption::hdr)
        std::cout << "  [x] HDR\n";
    if (options & RenderOption::vsync)
        std::cout << "  [x] VSync\n";
    if (options & RenderOption::fullscreen)
        std::cout << "  [x] Fullscreen\n";

    if (options == RenderOption::none)
        std::cout << "  (no options selected)\n";
}

// -----------------------------------------------------------------------
// 3. Demonstrate the pattern
// -----------------------------------------------------------------------
int main()
{
    // Call with no options:
    std::cout << "=== Default ===\n";
    initRenderer(RenderOption::none);

    // Call with a few individual options combined via |:
    std::cout << "\n=== Custom ===\n";
    initRenderer(RenderOption::antialiasing | RenderOption::shadows | RenderOption::vsync);

    // Call with the preset:
    std::cout << "\n=== High Quality Preset ===\n";
    initRenderer(RenderOption::highQuality);

    // Start from preset and add/remove options:
    std::cout << "\n=== High Quality + Fullscreen, minus Bloom ===\n";
    std::uint16_t myOptions{RenderOption::highQuality};
    myOptions |= RenderOption::fullscreen; // add fullscreen
    myOptions &= ~RenderOption::bloom;     // remove bloom
    initRenderer(myOptions);

    // -----------------------------------------------------------------------
    // 4. Advantage over bool parameters
    // -----------------------------------------------------------------------
    // Compare the readability:
    //
    //   initRenderer(false, true, true, false, false, true, true, false);
    //     → Which parameter is which? Very error-prone!
    //
    //   initRenderer(RenderOption::antialiasing | RenderOption::shadows | RenderOption::vsync);
    //     → Self-documenting and impossible to mix up.

    return 0;
}
