#pragma once

namespace EscapeRoom
{
	using Points = std::vector<MathVector>;

	struct Rect
	{
		MathVector p1;
		MathVector p2;
		MathVector p3;
		MathVector p4;

		Rect(const MathVector& p1_, const MathVector& p2_, const MathVector& p3_, const MathVector& p4_) :
			p1(p1_),
			p2(p2_),
			p3(p3_),
			p4(p4_)
		{
		}

		Rect(const MathVector& centre_, const float width_, const float height_) :
			p1(centre_.x - width_ * .5f, centre_.y + height_ * .5f),
			p2(centre_.x + width_ * .5f, centre_.y + height_ * .5f),
			p3(centre_.x + width_ * .5f, centre_.y - height_ * .5f),
			p4(centre_.x - width_ * .5f, centre_.y - height_ * .5f)
		{
		}

		Rect(const Points& points_) :
			p1(points_.at(0)),
			p2(points_.at(1)),
			p3(points_.at(2)),
			p4(points_.at(3))
		{
		}

		inline float GetWidth() const
		{
			return abs(p2.x - p1.x);
		}

		inline float GetHeight() const
		{
			return abs(p1.y - p4.y);
		}

		inline MathVector GetCentre() const
		{
			MathVector result;
			result.x = p1.x + GetWidth() / 2.f;
			result.y = p4.y + GetHeight() / 2.f;

			return result;
		}

		inline Points GetPoints() const
		{
			Points result;
			result.emplace_back(p1);
			result.emplace_back(p2);
			result.emplace_back(p3);
			result.emplace_back(p4);

			return result;
		}
	};

	struct Line
	{
		MathVector start, end;

		Line(const MathVector& start_, const MathVector& end_) :
			start(start_),
			end(end_)
		{
		}
	};

	using LinePack = std::vector<Line>;

	class LinePackFactory
	{
	public:
		inline static LinePack MakePolygon(const Points& points_)
		{
			LinePack result;
			
			for (size_t i = 0; i < points_.size(); i++)
			{
				MathVector end_point;
				if (i + 1 == points_.size())
				{
					end_point = points_.at(0);
				}
				else
				{
					end_point = points_.at(i + 1);
				}

				result.emplace_back(Line(points_.at(i), end_point));
			}

			return result;
		}
		
		inline static LinePack MakeRect(Rect& rect_)
		{
			LinePack result;

			result.emplace_back(Line(rect_.p1, rect_.p2 ));
			result.emplace_back(Line(rect_.p2, rect_.p3 ));
			result.emplace_back(Line(rect_.p3, rect_.p4 ));
			result.emplace_back(Line(rect_.p4, rect_.p1 ));

			return result;
		}

		inline static LinePack MakeStar4C()
		{
			LinePack result;

			result.emplace_back(Line(MathVector(-0.5, 0), MathVector(-0.18, -0.18)));
			result.emplace_back(Line(MathVector(-0.18, -0.18), MathVector(0, -0.5)));
			result.emplace_back(Line(MathVector(0, -0.5), MathVector(0.18, -0.18)));
			result.emplace_back(Line(MathVector(0.18, -0.18), MathVector(0.5, 0)));
			result.emplace_back(Line(MathVector(0.5, 0), MathVector(0.18, 0.18)));
			result.emplace_back(Line(MathVector(0.18, 0.18), MathVector(0, 0.5)));
			result.emplace_back(Line(MathVector(0, 0.5), MathVector(-0.18, 0.18)));
			result.emplace_back(Line(MathVector(-0.18, 0.18), MathVector(-0.5, 0)));

			return result;
		}
	};
	
}
