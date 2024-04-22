

namespace maths
{
	/* A simple rect implementation that has a position (x, y) and a size (w, h). */
	template<typename _Ty> 
	struct Rect
	{
		_Ty x, y, w, h; 

		bool PointIsWithin(_Ty _x, _Ty _y)
		{
			if (_x > x && _y > y && _x < x + w && _y < y + h)
				return true;
			return false; 
		}
	};

	using IntRect = Rect<int>;
}