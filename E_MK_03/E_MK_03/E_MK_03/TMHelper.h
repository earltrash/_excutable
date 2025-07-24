#pragma once
#include "pch.h"
#include "SimpleMathHelper.h"

namespace MYTM
{
	/// �������� ���� �⺻ ��ȯ
	D2D1_MATRIX_3X2_F MakeTranslationMatrix(D2D1_SIZE_F size);		// �̵�
	D2D1_MATRIX_3X2_F MakeRotationMatrix_Origin(FLOAT angle);		// ���������� ȸ��, ������
	D2D1_MATRIX_3X2_F MakeScaleMatrix_Origin(D2D1_SIZE_F size);

	// Ư�� ���� �������� �� ȸ��
	D2D1_MATRIX_3X2_F MakeRotationMatrix(FLOAT angle, D2D1_POINT_2F center = D2D1::Point2F());

	// Ư�� ���� �������� �� ũ�� ��ȯ
	D2D1_MATRIX_3X2_F MakeScaleMatrix(D2D1_SIZE_F size, D2D1_POINT_2F center = D2D1::Point2F());

	D2D1::Matrix3x2F MakeRenderMatrix(bool bUnityCoords = false, bool bMirror = false, float offsetX = 0, float offsetY = 0);


	// ����� ����� ���� TM ���ڿ�

	static void MakeMatrixToString(
		const D2D1_MATRIX_3X2_F& matrix,
		__out_ecount(bufSize) wchar_t* buffer,
		size_t bufSize
	);
	

	void DecomposeMatrix3x2
	(const D2D1::Matrix3x2F& M, MYHelper::Vector2F& outTranslation, float& outRotation, MYHelper::Vector2F& outScale);

	D2D1::Matrix3x2F RemovePivot(const D2D1::Matrix3x2F& M_local, const D2D1_POINT_2F& pivot);

	/// �簢�� rect �ȿ� point �� ���ԵǾ� ������ true ��ȯ
	/// (��� ���� �˻�)
	bool IsPointInRect(const D2D1_POINT_2F& point, const D2D1_RECT_F& rect) noexcept;
};
