#pragma once

namespace M {
	inline void VectorTransformA(const Vector& in1, const matrix3x4_t& in2, Vector& out) {
		out.x = in1.x * in2[0][0] + in1.y * in2[0][1] + in1.z * in2[0][2] + in2[0][3];
		out.y = in1.x * in2[1][0] + in1.y * in2[1][1] + in1.z * in2[1][2] + in2[1][3];
		out.z = in1.x * in2[2][0] + in1.y * in2[2][1] + in1.z * in2[2][2] + in2[2][3];
	}
	inline float DistanceScreen(Vector2D vDstPos, Vector2D vSrcPos)
	{
		return (sqrt(pow(vSrcPos.x - vDstPos.x, 2) + pow(vSrcPos.y - vDstPos.y, 2)));
	}
	inline void MatrixPosition(const matrix3x4_t &matrix, Vector &position)
	{
		position[0] = matrix[0][3];
		position[1] = matrix[1][3];
		position[2] = matrix[2][3];
	}
	inline void SinCos(float radians, float* sine, float* cosine)
	{
		*sine = sin(radians);
		*cosine = cos(radians);
	}
	inline void VectorAngles(const Vector& forward, QAngle& angles)
	{
		if (forward[1] == 0.0f && forward[0] == 0.0f)
		{
			angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
			angles[1] = 0.0f; //yaw left/right
		}
		else
		{
			angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
			angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

			if (angles[1] > 90)
				angles[1] -= 180;
			else if (angles[1] < 90)
				angles[1] += 180;
			else if (angles[1] == 90)
				angles[1] = 0;
		}

		angles[2] = 0.0f;
	}
	inline QAngle CalcAngle(Vector src, Vector dst)
	{
		QAngle angles;
		Vector delta = src - dst;
		VectorAngles(delta, angles);
		delta.Normalize();
		return angles;
	}
	inline void AngleVectors(const QAngle& angles, Vector* forward)
	{
		float sp, sy, cp, cy;

		SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
		SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}
}