#pragma once

#include <cmath>

#define MAT4_SIZE 4

namespace EscapeRoom
{
	class MathMatrix4x4
	{
	private:
		friend class MathMatrix;
		friend inline MathMatrix4x4 operator*(const MathMatrix4x4& lhs_, const MathMatrix4x4& rhs_);
		
		float mat[MAT4_SIZE][MAT4_SIZE];
		
	public:
		MathMatrix4x4()
		{
			std::fill((float*)mat, (float*)mat + sizeof(mat) / sizeof(float), 0.f);

			// Set ID mat
			mat[0][0] = 1.f;
			mat[1][1] = 1.f;
			mat[2][2] = 1.f;
			mat[3][3] = 1.f;
		}

		MathVector operator*(const MathVector& vec_)
		{
			MathVector result;

			result.x = mat[0][0] * vec_.x + mat[0][1] * vec_.y + mat[0][2] * vec_.z + mat[0][3] * vec_.w;
			result.y = mat[1][0] * vec_.x + mat[1][1] * vec_.y + mat[1][2] * vec_.z + mat[1][3] * vec_.w;
			result.z = mat[2][0] * vec_.x + mat[2][1] * vec_.y + mat[2][2] * vec_.z + mat[2][3] * vec_.w;
			result.w = mat[3][0] * vec_.x + mat[3][1] * vec_.y + mat[3][2] * vec_.z + mat[3][3] * vec_.w;

			return result;
		}
	};

	class MathMatrix
	{
	public:
		inline static MathMatrix4x4 Translate(MathVector& vector_)
		{
			MathMatrix4x4 mat_;
			mat_.mat[0][3] += vector_.x;
			mat_.mat[1][3] += vector_.y;
			mat_.mat[2][3] += vector_.z;

			return mat_;
		}

		inline static MathMatrix4x4 Rotate(MathVector& vector_, float angle_)
		{
			const float cos_angle = cos(angle_);
			const float sin_angle = sin(angle_);
			
			MathMatrix4x4 result;
			result.mat[0][0] = cos_angle + (vector_.x * vector_.x) * (1 - cos_angle);
			result.mat[0][1] = vector_.x * vector_.y * (1 - cos_angle) - vector_.z * sin_angle;
			result.mat[0][2] = vector_.x * vector_.z * (1 - cos_angle) + vector_.y * sin_angle;

			result.mat[1][0] = vector_.y * vector_.x * (1 - cos_angle) + vector_.z * sin_angle;
			result.mat[1][1] = cos_angle + (vector_.y * vector_.y) * (1 - cos_angle);
			result.mat[1][2] = vector_.y * vector_.z * (1 - cos_angle) - vector_.x * sin_angle;

			result.mat[2][0] = vector_.z * vector_.x * (1 - cos_angle) - vector_.y * sin_angle;
			result.mat[2][1] = vector_.z * vector_.y * (1 - cos_angle) + vector_.x * sin_angle;
			result.mat[2][2] = cos_angle + (vector_.z * vector_.z) * (1 - cos_angle);

			return result;
		}

		inline static MathMatrix4x4 Scale(MathVector& vector_)
		{
			MathMatrix4x4 result;
			result.mat[0][0] = vector_.x;
			result.mat[1][1] = vector_.y;
			result.mat[2][2] = vector_.z;

			return result;
		}
	};

	inline MathMatrix4x4 operator*(const MathMatrix4x4& lhs_, const MathMatrix4x4& rhs_)
	{
		MathMatrix4x4 result;

		for (size_t i = 0; i < MAT4_SIZE; i++) // lhs rows
		{
			for (size_t j = 0; j < MAT4_SIZE; j++) // lhs row i * rhs col j
			{
				float c_result = 0.f;
				for (size_t k = 0; k < MAT4_SIZE; k++) // each element of both matrices
				{
					c_result += lhs_.mat[i][k] * rhs_.mat[k][j];
				}

				result.mat[i][j] = c_result; // insert result
			}
		}

		return result;
	}

}