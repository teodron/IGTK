#include "quad_tree/quad_tree.hh"

namespace igtk::geometry::queries
{

	using namespace linalg::aliases;

	bool are_elements_similar(const Element& element_a, const Element& element_b)
	{
		constexpr float delta_z_m = 0.01f;
		constexpr float delta_theta_rad = 0.5f * 3.1415f/180.0f;
		static const float min_cos = cosf(delta_theta_rad);

		return (std::fabs(element_a.position.z - element_b.position.z) <= delta_z_m)&&(dot(element_a.normal, element_b,normal) >= min_cos);
	}

	bool is_element_inside_cell(const Element& element, const QuadCell& cell)
	{
		float dx = (-cell.center.x + elements.position.x) + 0.5f*cell.size;
		float dy = (-cell.center.y + elements.position.y) + 0.5f*cell.size;
		if (dx >= 0.f && dx < cell.size && dy >=0.f && dy < cell.size)
		{
			return true;
		}
		return false;
	}

	size_t QuadTree::get_cell_index_for_element(const Element& element)
	{
		size_t owner_cell_index = 0;
		bool found = false;
		while (!found)
		{
			const auto& owner_cell = cells_[owner_cell_index];
			if (owner_cell.first_child_index == 0)
			{
				found = true;
			}
			else 
			{
				for (const auto child_cell_index = owner_cell.first_child_index; child_cell_index < owner_cell.first_child_index + 4; ++child_cell_index)
				{
					const auot& child_cell = cells_[child_cell_index];
					float dx = (-child_cell.center.x + elements.position.x) + 0.5f*child_cell.size;
					float dy = (-child_cell.center.y + elements.position.y) + 0.5f*child_cell.size;
					if (dx >= 0.f && dx < child_cell.size && dy >=0.f && dy < child_cell.size)
					{
						owner_cell_index = child_cell_index;
						break;
					}
				}
			}
		}
		return owner_cell_index; // this function will not work for all edge cases - fixme: find edge cases
	}

	size_t QuadTree::split_cell(const size_t parent_cell_index)
	{
		std::vector<Element> original_elements{std::move(leaf_data_[parent_cell_index])};
		size_t first_child_index = cells_.size();
		const float child_cell_size = cells_[parent_cell_index].size / 2.f;
		const auto& parent_cell_center = cells_[parent_cell_index].center;
		QuadCell bottom_left_cell{};
		QuadCell bottom_right_cell{};
		QuadCell top_right_cell{};
		QuadCell top_left_cell{};

		bottom_right_cell.center = parent_cell_center;
		bottom_left_cell.center = parent_cell_center;
		top_left_cell.center = parent_cell_center;
		top_right_cell.center = parent_cell_center;

		bottom_left_cell.center.x -= child_cell_size/2.0f;
		bottom_left_cell.center.y -= child_cell_size/2.0f;
		bottom_right_cell.center.x += child_cell_size/2.0f;
		bottom_right_cell.center.y -= child_cell_size/2.0f;
		top_right_cell.center.x += child_cell_size/2.0f;
		top_right_cell.center.y += child_cell_size/2.0f;
		top_left_cell.center.x -= child_cell_size/2.0f;
		top_left_cell.center.y += child_cell_size/2.0f;
		bottom_right_cell.size = child_cell_size;
		bottom_left_cell.size = child_cell_size;
		top_left_cell.size = child_cell_size;
		top_right_cell.size = child_cell_size;

		cells_.emplace_back(bottom_left_cell);
		cells_.emplace_back(bottom_right_cell);
		cells_.emplace_back(top_right_cell);
		cells_.emplace_back(top_left_cell);
		cells_[parent_cell_index].first_child_index = first_child_index;

		for (const auto& element: original_elements)
		{
			for (size_t child_index = first_child_index; child_index < first_child_index + 4; ++child_index)
			{
				if (is_element_inside_cell(element, cells_[child_index]))
				{
					leaf_data_[child_index].emplace_back(element);
				}
			}
		}
	}

	void QuadTree::build(const std::vector<Element>& elements)
	{
		cells_.clear();
		leaf_data_.clear();
		// compute bounding box
		float2 min_xy{1000.f,1000.f}; //fixme: hardcoded min float here
		float2 max_xy = -min_xy;
		for (const auto& element: elements)
		{
			min_xy.x = std::min(min_xy.x, element.position.x);
			min_xy.y = std::min(min_xy.y, element.position.y);
			max_xy.x = std::max(max_xy.x, element.position.x);
			max_xy.y = std::max(max_xy.y, element.position.y);
		}
		// create root cell
		const float2 wh_xy = max_xy - min_xy;
		QuadCell root_cell;
		root_cell.center = min_xy + 0.5f*wh_xy;;
		root_cell.size = std::max(wh_xy.x, wh_xy.y)+0.1f; // fixme: hardcoded epsilon here
		cells_.emplace_back(root_cell);
		leaf_data[0] = {};
		// 
		for (const auto& element: elements)
		{
			size_t owner_cell_index = get_cell_index_for_element(element);
			bool must_split_cell = false;
			for (const auto& existing_element : leaf_data_[owner_cell_index])
			{
				if (!are_elements_similar(element, existing_element))
				{
					must_split_cell = true;
					break;
				}
			}
			if (must_split_cell)
			{
				size_t first_child_index = split_cell(owner_cell_index);
			}
			else
			{
				
			}
		}
	}
}