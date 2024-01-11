#include <iostream>
#include <array>
#include <cassert>
using namespace std;

namespace Geom
{
	template<class T,size_t N>
	using vec=std::array<T,N>;

	template<class T,size_t N>
	void dump(const vec<T,N>& v)
	{
		cout << "vec" << N << "(";
		for(int i=0;i<N;i++)
		{
			cout << v[i];
			if(i<N-1)
				cout << ",";
		}
		cout << ")\n";
	}
    template<class VEC, class T = VEC::value_type>
    inline VEC operator*(const VEC& a, T scalar)
    {
        VEC ret = a;
        for (auto& el : ret)
            el *= scalar;
        return ret;
    }
    template<class VEC, class T = VEC::value_type>
    inline VEC operator/(const VEC& a, T scalar)
    {
        bool not0 = std::abs(scalar) > std::numeric_limits<T>::epsilon();
        if (!not0)
        {
            int brk = 0;
        }
        assert(not0);
        return a * (1. / scalar);
    }
    template<class VEC>
    inline VEC operator+(const VEC& a, const VEC& b)
    {
        VEC ret{ 0 };
        for (int i = 0; i < a.size(); i++)
            ret[i] = a[i] + b[i];
        return ret;
    }
    template<class VEC>
    inline VEC operator-(const VEC& a, const VEC& b)
    {
        VEC ret{ 0 };
        for (int i = 0; i < a.size(); i++)
            ret[i] = a[i] - b[i];
        return ret;
    }
    template<class VEC>
    inline VEC operator-(const VEC& a)
    {
        VEC ret;
        for (int i = 0; i < a.size(); i++)
            ret[i] = -a[i];
        return ret;
    }
    /// @brief dot product: https://billcookmath.com/papers/2012-09_nD_pythag_talk.pdf 
    template<class VEC, class T = VEC::value_type>
    inline T dot(const VEC& a, const VEC& b)
    {
        T ret = T();
        for (int i = 0; i < a.size(); i++)
            ret += a[i] * b[i];
        return ret;
    }
    /// @brief cross product: https://billcookmath.com/papers/2012-09_nD_pythag_talk.pdf
    /// @param a 
    /// @param b 
    /// @return 
    template<class VEC, class T = VEC::value_type>
    inline VEC cross3(const VEC& v, const VEC& w)
    {
        //3d: (v x w={v2w3 - 3w2, -(v1w3 - v3w1), v1w2 - v2w1}
        assert(v.size() == 3);
        VEC ret{
            v[1] * w[2] - v[2] * w[1],
            -(v[0] * w[2] - v[2] * w[0]),
            v[0] * w[1] - v[1] * w[0]
        };
        return ret;
    }
    template<class VEC, class T = VEC::value_type>
    inline VEC cross2(const VEC& v)
    {
        //2: (x v={v2, -v1}
        assert(v.size() == 2);
        VEC ret{v[1],-v[0]};
        return ret;
    }
    template<class VEC, class T = VEC::value_type>
    inline T length(const VEC& a)
    {
        return sqrt(dot(a, a));
    }
    template<class VEC, class T = VEC::value_type>
    inline VEC normalize(const VEC& a)
    {
        T l = length(a);
        return a / l;
    }
    template<class VEC, class T = VEC::value_type>
    inline VEC lerp(const VEC& a, const VEC& b, T t)
    {
        return a + (b - a) * t;
    }
    template<class VEC>
    inline VEC MulComp(const VEC& a, const VEC& b)
    {
        VEC ret;
        for (int i = 0; i < a.size(); i++)
            ret[i] = a[i] * b[i];
        return ret;
    }
    template<class VEC>
    inline VEC DivComp(const VEC& a, const VEC& b)
    {
        VEC ret;
        for (int i = 0; i < a.size(); i++)
            ret[i] = a[i] / b[i];
        return ret;
    }
}

template<class T>
void dump(const T& v)
{
}

using namespace Geom;

void geom_test()
{
    cout << "geom_test()\n";
    using vec2d = Geom::vec<double, 2>;
    using vec3d = Geom::vec<double, 3>;
    vec2d v={0};
	dump(vec2d{ 0, 0 });
    dump(vec2d{ 1, 1 });
    dump(vec2d{ 1, 1 } + vec2d{ 2, 2 });

    dump(vec3d{ 0, 0, 0 });
    dump(vec3d{ 1, 2, 3 }*3.);
    cout << "cross2(vec2d{ 1, 2})=";dump(cross2(vec2d{ 1, 2}));
    cout << "cross3(vec3d{ 1, 0, 0 },vec3d{ 0, 0, 1})=";dump(cross3(vec3d{ 1, 0, 0 },vec3d{ 0, 0, 1}));
}

