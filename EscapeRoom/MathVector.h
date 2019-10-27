#pragma once

namespace EscapeRoom
{
	struct MathVector
	{
	public:
		float x;
		float y;
		float z;
		float w;

		MathVector(
			const float x_ = 0.f,
			const float y_ = 0.f,
			const float z_ = 0.f,
			const float w_ = 1.f
		) :
		x(x_),
		y(y_),
		z(z_),
		w(w_)
		{
		}

		inline static float VecDistance(const MathVector& lhs_, const MathVector& rhs_)
		{
			return sqrt(
				(lhs_.x - rhs_.x) * (lhs_.x - rhs_.x) +
				(lhs_.y - rhs_.y) * (lhs_.y - rhs_.y) +
				(lhs_.z - rhs_.z) * (lhs_.z - rhs_.z)
			);
		}

		inline MathVector& operator+=(const MathVector& other_)
		{
			x += other_.x;
			y += other_.y;
			z += other_.z;
			
			return *this;
		}

		inline MathVector& operator-=(const MathVector& other_)
		{
			x -= other_.x;
			y -= other_.y;
			z -= other_.z;

			return *this;
		}

		inline MathVector GetNormalized() const
		{
			MathVector result;
			const float mag = GetMag();

			result.x = x / mag;
			result.y = y / mag;
			result.z = z / mag;

			return result;
		}

		inline float GetMag() const
		{
			return sqrt(
				x * x +
				y * y +
				z * z
			);
		}
	};

	inline MathVector operator*(const MathVector& lhs_, const float rhs_)
	{
		MathVector result;

		result.x = lhs_.x * rhs_;
		result.y = lhs_.y * rhs_;
		result.z = lhs_.z * rhs_;

		return result;
	}

	inline MathVector operator*(const MathVector& lhs_, const MathVector& rhs_)
	{
		MathVector result;

		result.x = lhs_.x * rhs_.x;
		result.y = lhs_.y * rhs_.y;
		result.z = lhs_.z * rhs_.z;

		return result;
	}

	inline MathVector operator+(const MathVector& lhs_, const MathVector& rhs_)
	{
		MathVector result;

		result.x = lhs_.x + rhs_.x;
		result.y = lhs_.y + rhs_.y;
		result.z = lhs_.z + rhs_.z;

		return result;
	}

	inline MathVector operator-(const MathVector& lhs_, const MathVector& rhs_)
	{
		MathVector result;

		result.x = lhs_.x - rhs_.x;
		result.y = lhs_.y - rhs_.y;
		result.z = lhs_.z - rhs_.z;

		return result;
	}
}