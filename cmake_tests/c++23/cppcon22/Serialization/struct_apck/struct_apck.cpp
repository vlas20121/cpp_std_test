#include <string>

struct UniversalType {
	template <typename T> operator T();
};

template <typename T, typename... Args> 
consteval auto member_count() {
	// must be aggregate type.
	static_assert(std::is_aggregate_v<std::remove_cvref_t<T>>);
	// Utilize c++20 concepts to detect arguments count of an aggregate object.
	if constexpr (requires { T{{Args{}}..., {UniversalType{}}}; } == false) {
		return sizeof...(Args);
	} else {
		return member_count<T, Args..., UniversalType>();
	}
}

// reflect all fields of dummy.
visit_members(t, [](auto &&...items){});

decltype(auto) visit_members(auto &&object, auto &&visitor) {
	using type = std::remove_cvref_t<decltype(object)>;
	constexpr auto Count = member_count<type>();
	if constexpr (Count == 0) {
		return visitor();
	} else if constexpr (Count == 1) {
		auto &&[a1] = object;
		return visitor(a1);
	} else if constexpr (Count == 2) {
		auto &&[a1, a2] = object;
		return visitor(a1, a2);
	} else if constexpr (Count == 3) {
		auto &&[a1, a2, a3] = object;
		return visitor(a1, a2, a3);
	}
// ...
}

struct dummy {
	int id;
	float number;
	std::string str;
};

void serialize(dummy t) {
	// reflect all fields of dummy into items…
	visit_members(t, [](auto &&...items){
		// serialize each item.
		serialize_many(items...);
	});
}
//=========serialize

//serialize type
template <typename T>
void serialize(T &&t) {
	// generate hash code of t.
	constexpr uint32_t types_code =
		get_types_code<decltype(get_types(std::forward<T>(t)))>();
	// serialize the hash code for deserialization type checking
	std::memcpy(data_ + pos_, &types_code, sizeof(uint32_t));
	pos_ += sizeof(uint32_t);

	// serialize t
	serialize_one(t);
}

//Optimize performance
struct dummy {
	int32_t a;
	int32_t b;
	int32_t c;
	int32_t d;
	double e;
	char f;
};

void serialize(dummy t) {
	pack_int(t.a);
	pack_int(t.b);
	pack_int(t.c);
	pack_int(t.d);
	pack_double(t.e);
	pack_char(t.f);
}
//
void serialize_one(auto &&item) {
	using type = std::remove_cvref_t<decltype(item)>;
	if constexpr (std::is_trivially_copyable_v<type>) {
		std::memcpy(data_ + pos_, &item, sizeof(type));
		pos_ += sizeof(type);
	}
}
//Classic serialize
void classic_serialize(const std::vector<rect> &rects) { 
	for(auto &r : rects) { 
		classic_serialize(r); 
	} 
}

void classic_serialize(const rect &r) { 
	pack_int_type(); 
	pack_int_value(r.x); 
	pack_int_type(); 
	pack_int_value(r.y); 
	pack_int_type(); 
	pack_int_value(r.width); 
	pack_int_type(); 
	pack_int_value(r.height); 
}
//packed
template <typename T>
void reflection_based_serialize(const T &rects) {
	if constexpr (continuous_container<T>) {
		pack_size(rects.size());
		auto size = rects.size() * sizeof(T);
		std::memcpy(data_ + pos_, &rects[0], size);
	}
}
//=========
//Complex Object 
enum Color : uint8_t { Red, Green, Blue };
struct Vec3 { float x; float y; float z;};
struct Weapon { std::string name; int16_t damage;};
struct Monster {
	Vec3 pos;
	int16_t mana;
	int16_t hp;
	std::string name;
	std::vector<uint8_t> inventory;
	Color color;
	std::vector<Weapon> weapons;
	Weapon equipped;
	std::vector<Vec3> path;
};
