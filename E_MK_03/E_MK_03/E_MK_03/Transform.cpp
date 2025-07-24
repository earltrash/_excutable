#include "pch.h"
#include "Transform.h"

void D2DTM::Transform::SetPivotPreset(PivotPreset preset, const D2D1_SIZE_F& size)
{
	switch (preset)
	{
	case PivotPreset::TopLeft:
		m_pivot = { 0.0f, 0.0f };
		break;
	case PivotPreset::TopRight:
		m_pivot = { size.width, 0.0f };
		break;
	case PivotPreset::BottomLeft:
		m_pivot = { 0.0f, -size.height };
		break;
	case PivotPreset::BottomRight:
		m_pivot = { size.width, -size.height };
		break;
	case PivotPreset::Center:
		m_pivot = { size.width * 0.5f, -(size.height * 0.5f) };

		break;
	}
}


void  D2DTM::Transform::UpdateMatrices()
{
	//D2D1_MATRIX_3X2_F MakeRotationMatrix(FLOAT angle, D2D1_POINT_2F center /*= D2D1::Point2F()*/)
	//�ڵ� ����
	// D2D1::Matrix3x2F::Scale(m_scale.x, m_scale.y, m_pivot)
	//D2D1::Matrix3x2F::Rotation(m_rotation, m_pivot);
	// Ʈ�������� �����ϱ����� Ǯ�� �� �ڵ�
	/*const auto P = D2D1::Matrix3x2F::Translation(-m_pivot.x, -m_pivot.y);

	const auto S = D2D1::Matrix3x2F::Scale(m_scale.x, m_scale.y);

	const auto R = D2D1::Matrix3x2F::Rotation(m_rotation);

	const auto T1 = D2D1::Matrix3x2F::Translation(m_pivot.x, m_pivot.y);

	const auto T2 = D2D1::Matrix3x2F::Translation(m_position.x, m_position.y);

	m_matrixLocal = P * S * R * T1 * T2;*/

	// �ڵ� ȿ��ȭ

	m_matrixLocal =
		D2D1::Matrix3x2F::Scale(m_scale.x, m_scale.y, m_pivot) *
		D2D1::Matrix3x2F::Rotation(m_rotation, m_pivot) *
		D2D1::Matrix3x2F::Translation(m_position.x, m_position.y);

	std::cout << "������Ʈ ���� matrix x ��" << (m_position.x) << "������Ʈ ���� matrix y��" << m_position.y << std::endl;


	if (m_parent)
		m_matrixWorld = m_matrixLocal * m_parent->GetWorldMatrix();
	else
		m_matrixWorld = m_matrixLocal;

	m_dirty = false;
}