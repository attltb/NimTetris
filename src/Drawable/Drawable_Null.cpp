#include "Drawable_Null.hpp"
using namespace std;
Drawable Drawable::Null() {
	return shared_ptr<Drawable_>(new Drawable_Null());
}