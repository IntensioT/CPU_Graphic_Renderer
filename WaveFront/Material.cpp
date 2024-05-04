#include "Material.h"

CoordinateStruct getMaterialProperties(MaterialType type)
{
	CoordinateStruct material;
	switch (type) {
	case MaterialType::Default:
		material = { 0.04f, 0.04f, 0.04f };
		break;
	case MaterialType::Water:
		material = { 0.02f, 0.02f, 0.02f };
		break;
	case MaterialType::PlasticLow:
		material = { 0.03f, 0.03f, 0.03f };
		break;
	case MaterialType::PlasticHigh:
		material = { 0.05f, 0.05f, 0.05f };
		break;
	case MaterialType::GlassHigh:
		material = { 0.08f, 0.08f, 0.08f };
		break;
	case MaterialType::Ruby:
		material = { 0.08f, 0.08f, 0.08f };
		break;
	case MaterialType::Diamond:
		material = { 0.17f, 0.17f, 0.17f };
		break;
	case MaterialType::Iron:
		material = { 0.56f, 0.57f, 0.58f };
		break;
	case MaterialType::Copper:
		material = { 0.95f, 0.64f, 0.54f };
		break;
	case MaterialType::Gold:
		material = { 1.00f, 0.71f, 0.29f };
		break;
	case MaterialType::Aluminium:
		material = { 0.91f, 0.92f, 0.92f };
		break;
	case MaterialType::Silver:
		material = { 0.95f, 0.93f, 0.88f };
		break;
	}
	return material;
}
