#include "math/linalg.h"

#include <array>
#include <unordered_map>
#include <vector>

namespace igtk
{
namespace geometry
{
namespace queries 
{

struct QuadCell
{
	linalg::aliases::float2 center;
	float size;
	size_t first_child_index{0};
};

struct Element
{
	linalg::aliases::float3 position;
	linalg::aliases::float3 normal;
};



class QuadTree
{

public:
	QuadTree() = default;
	void build(const std::vector<Element>& elements);

	size_t get_cell_index_for_element(const Element& element);
private:
	size_t split_cell(const size_t parent_cell_index);
	
	std::vector<QuadCell> cells_;
	std::unordered_map<size_t,std::vector<Element>> leaf_data_;
};

}
}
}