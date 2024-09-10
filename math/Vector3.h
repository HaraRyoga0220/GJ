#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
	// * 演算子のオーバーロード
	Vector3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
	
	// - 演算子のオーバーロード
	Vector3 operator-(const Vector3& other) const {
		return {x - other.x, y - other.y, z - other.z};
	}

	// + 演算子のオーバーロード
	Vector3 operator+(const Vector3& other) const {
		return {x + other.x, y + other.y, z + other.z};
	}

};