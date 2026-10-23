// Chapter 22 - Project 09: std::weak_ptr
// std::weak_ptr is a non-owning observer of a shared_ptr-managed resource.
// It does NOT contribute to the reference count.
//
// Primary use: break circular references between shared_ptrs.
//
// Key operations:
//   - lock()    - returns a shared_ptr if the resource still exists, else empty.
//   - expired() - returns true if the managed object has been deleted.
//   - use_count() - observation only (number of shared_ptrs, not weak_ptrs).

#include <iostream>
#include <memory>
#include <string>

// -----------------------------------------------------------------------
// Resource class
// -----------------------------------------------------------------------
class Resource
{
    std::string m_name;

public:
    explicit Resource(const std::string &name) : m_name{name}
    {
        std::cout << "  [Resource] \"" << m_name << "\" created\n";
    }
    ~Resource()
    {
        std::cout << "  [Resource] \"" << m_name << "\" destroyed\n";
    }
    const std::string &name() const { return m_name; }
};

// -----------------------------------------------------------------------
// 1. Basic weak_ptr usage
// -----------------------------------------------------------------------
void basicWeakPtr()
{
    std::cout << "=== 1. Basic weak_ptr ===\n";

    std::weak_ptr<Resource> weak;

    {
        auto shared = std::make_shared<Resource>("FileHandle");
        weak = shared; // weak_ptr observes - does NOT increase ref count

        std::cout << "  Inside scope:\n";
        std::cout << "    shared use_count = " << shared.use_count() << '\n';               // 1 (weak doesn't count)
        std::cout << "    weak expired?    = " << std::boolalpha << weak.expired() << '\n'; // false

        // To use the resource through weak_ptr, lock() it first
        if (auto locked = weak.lock())
        {
            std::cout << "    Locked: \"" << locked->name() << "\"\n";
            std::cout << "    use_count while locked = " << shared.use_count() << '\n'; // 2
        }
        // locked goes out of scope - count back to 1
    }
    // shared is destroyed here - Resource is deleted

    std::cout << "  Outside scope:\n";
    std::cout << "    weak expired? = " << weak.expired() << '\n'; // true

    // lock() returns an empty shared_ptr since the resource is gone
    if (auto locked = weak.lock())
        std::cout << "    Locked: \"" << locked->name() << "\"\n";
    else
        std::cout << "    lock() returned nullptr - resource is gone\n";
}

// -----------------------------------------------------------------------
// 2. weak_ptr as a cache / observer pattern
// -----------------------------------------------------------------------
class Cache
{
    std::weak_ptr<Resource> m_cached;

public:
    void store(std::shared_ptr<Resource> res)
    {
        m_cached = res;
        std::cout << "  [Cache] Stored weak reference to \"" << res->name() << "\"\n";
    }

    std::shared_ptr<Resource> get() const
    {
        return m_cached.lock(); // Returns shared_ptr or nullptr
    }

    bool hasValidEntry() const
    {
        return !m_cached.expired();
    }
};

void cacheDemo()
{
    std::cout << "\n=== 2. Cache / observer pattern ===\n";

    Cache cache;

    {
        auto res = std::make_shared<Resource>("Config");
        cache.store(res);

        // Cache can access the resource while it's alive
        if (auto cached = cache.get())
            std::cout << "  Cache hit: \"" << cached->name() << "\"\n";
    }
    // Resource destroyed - shared_ptr out of scope

    // Cache detects that the resource is gone
    if (cache.hasValidEntry())
        std::cout << "  Cache still valid\n";
    else
        std::cout << "  Cache entry expired - resource was destroyed\n";
}

// -----------------------------------------------------------------------
// 3. Dangling raw pointer vs safe weak_ptr
// -----------------------------------------------------------------------
void safetyComparison()
{
    std::cout << "\n=== 3. weak_ptr detects dangling (raw pointer can't) ===\n";

    // With raw pointer: DANGEROUS - no way to know if deleted
    // Resource* rawPtr = nullptr;
    // {
    //     auto res = std::make_shared<Resource>("X");
    //     rawPtr = res.get();
    // }
    // // rawPtr is now dangling! Using it = undefined behavior.

    // With weak_ptr: SAFE - expired() / lock() detect destruction
    std::weak_ptr<Resource> wp;
    {
        auto sp = std::make_shared<Resource>("SafeRef");
        wp = sp;
        std::cout << "  Alive: expired = " << std::boolalpha << wp.expired() << '\n';
    }
    std::cout << "  Dead:  expired = " << wp.expired() << '\n';
    std::cout << "  (No undefined behavior - weak_ptr knows the resource is gone)\n";
}

// -----------------------------------------------------------------------
int main()
{
    basicWeakPtr();
    cacheDemo();
    safetyComparison();

    std::cout << "\nDone.\n";
    return 0;
}
