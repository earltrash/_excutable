#include "pch.h"
#include "Transform.h"

using Vec2 = MYHelper::Vector2F;


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
	// 코드 효율화

	m_matrixLocal =
		D2D1::Matrix3x2F::Scale(m_scale.x, m_scale.y, m_pivot) *
		D2D1::Matrix3x2F::Rotation(m_rotation, m_pivot) *
		D2D1::Matrix3x2F::Translation(m_position.x, m_position.y);

	std::cout << "오브젝트 로컬 matrix x 값" << (m_position.x) << "오브젝트 로컬 matrix y값" << m_position.y << std::endl;


	if (m_parent)
		m_matrixWorld = m_matrixLocal * m_parent->GetWorldMatrix();
	else
		m_matrixWorld = m_matrixLocal;

	m_dirty = false;
}


bool D2DTM::Transform::Contains(const Vec2& point) const
{
		D2D1_RECT_F rect = GetRect();
		return point.x >= rect.left && point.x <= rect.right &&
				point.y >= rect.top && point.y <= rect.bottom;
}

D2D1_RECT_F D2DTM::Transform::GetRect() const
{
		Vec2 worldPos = GetPosition();
		Vec2 scaledSize = Vec2(m_scale.x, m_scale.y);

		// 피벗을 기준으로 위치 계산
		Vec2 pivotOffset = Vec2(
				scaledSize.x * m_pivot.x,
				scaledSize.y * m_pivot.y
		);

		return D2D1::RectF(
				worldPos.x - pivotOffset.x,
				worldPos.y - pivotOffset.y,
				worldPos.x - pivotOffset.x + scaledSize.x,
				worldPos.y - pivotOffset.y + scaledSize.y
		);
}
