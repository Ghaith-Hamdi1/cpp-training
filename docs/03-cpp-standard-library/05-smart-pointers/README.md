# Smart Pointers

(Slides 29–36)

- Smart pointers are classes that wrap pointers, so allocation and deallocation of pointer is done respectively in constructor and destructor. This follows the RAII paradigm.
- Available smart pointers in standard library:
  - `std::unique_ptr<T>`: smart pointer with unique object ownership
  - `std::shared_ptr<T>`: smart pointer with shared object ownership
  - `std::weak_ptr<T>`: smart pointer that references an object managed by `std::shared_ptr`
  - `std::auto_ptr<T>`: smart pointer with strict object ownership (**deprecated**, not to be used)

