# Exercice

Note: this topic appears twice in the source deck (non-consecutively); both occurrences are preserved below in their original order.

- Create a class named "Object" that allows
  - Creating all constructors
  - Containing attributes: `m_name` (string), `m_id` (int), `m_pNext` (Object*)
  - Initializes the attributes and suitable processing in different constructors

---

- Create a class `Point` that holds two integers which are x and y coordinates.
- Create a pure virtual class `Shape` that contains
  - Pure virtual `print` method that gets as input an `ostream` and returns it back
  - A pure virtual method that checks if a `Point` is in the shape outline
  - Overload of the stream operator
- Create a class `Circle` that inherits from `Shape` and has an attribute 'center' (`Point`) and radius value
- Perform necessary actions, knowing that the `Circle` is no longer inherited
- Overload the operator `+=` to be able to add `Point`(s) to the circle outline
- Write `Main` function to highlight the implemented code
  - (x - h)² + (y - k)² = r² where (h,k) are the center point coordinates, r is the radius and (x, y) are coordinates of a point in the circle outline
