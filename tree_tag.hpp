template<typename T, typename Tag, typename = void>
struct has_tag : std::false_type {};

// Specialization for when a tag is found directly on the type
template<typename T, typename Tag>
struct has_tag<T, Tag, std::void_t<typename T::tag, std::enable_if_t<std::is_same_v<typename T::tag, Tag>>>> : std::is_same<typename T::tag, Tag> {};

// Recursive check up the inheritance chain
// This specialization is enabled only if T has a base class and T::tag is not the Tag we're looking for.
template<typename T, typename Tag>
struct has_tag<T, Tag, std::void_t<typename T::_TreeType, std::enable_if_t<!std::is_same_v<typename T::tag, Tag>>>>
    : has_tag<typename T::_TreeType, Tag> {};

// Helper variable template for easier usage
template<typename T, typename Tag>
inline constexpr bool has_tag_v = has_tag<T, Tag>::value;
