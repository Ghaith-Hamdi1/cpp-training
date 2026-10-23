# Objects relationships

- To have a well structured program, it must be composed by many objects and these objects have to interact between each others
- Relationships can be described by words (even before programming during the conception phase)
  - Car "is-a" vehicle
  - Car "has-a" door and "has-a" list of wheels
  - Programmer "uses-a" keyboard
  - Computer "Depends-on" electricity
  - Employee "member-of" employees list
- Composition: "has-a" relationship: object is composed by smaller objects. Create simpler classes to simplify complex classes
  - The smaller object must be part of the global object
  - The smaller object belongs to one object at a time
  - The smaller object existence is managed by global object (it won't exist if global object no longer exists)
  - The smaller object doesn't know about the global object existence
- Aggregation: "has-a" relationship as well: it is similar to composition, but
  - The smaller object must be part of the global object
  - The smaller object can belong to many objects at a time
  - The smaller object existence is not managed by global object: its existence doesn't depend on global object existence
  - The smaller object doesn't know about the global object existence
- Aggregation:
  - When global object is destructed, it is not responsible for aggregated objects destruction
- Association: "Uses-a" relationship
  - The associated object is not related to the object
  - The associated object can belong to more than one object
  - The associated object existence is not managed by the object
  - The associated object may or may not know about object existence
  - Unlike composition and aggregation, association may be bidirectional (objects are aware of each other)
- Association: implementation
  - [Code screenshot slide — no matching numbered file found in `examples/` and no text extractable beyond the heading; see Conversion notes.]
- Summary:

| Property | Composition | Aggregation | Association |
|---|---|---|---|
| Relationship type | Whole/part | Whole/part | Otherwise unrelated |
| Members can belong to multiple classes | No | Yes | Yes |
| Members' existence managed by class | Yes | No | No |
| Directionality | Unidirectional | Unidirectional | Unidirectional or bidirectional |
| Relationship verb | Part-of | Has-a | Uses-a |

- Dependency: "Depends-on" relationship, occurs when one object invokes another object's functionality in order to accomplish some specific task.
  - This is a weaker relationship than an association, but still, any change to object being depended upon may break functionality in the (dependent) caller.
  - A dependency is always a unidirectional relationship.
