#include "../param.hpp"
#include "../util.hpp" 

void ParamSet::add(const std::string& key, const std::string& value) {
    attributes[key] = value;
}

bool ParamSet::count(const std::string& key) const {
    return attributes.find(key) != attributes.end();
}

std::string ParamSet::get_string(const std::string& key, const std::string& default_val) const {
    if (count(key)) return attributes.at(key);
    return default_val;
}

int ParamSet::get_int(const std::string& key, int default_val) const {
    if (count(key)) return Util::parse_int(attributes.at(key));
    return default_val;
}

float ParamSet::get_float(const std::string& key, float default_val) const {
    if (count(key)) return Util::parse_float(attributes.at(key));
    return default_val;
}

bool ParamSet::get_bool(const std::string& key, bool default_val) const {
    if (count(key)) return Util::parse_bool(attributes.at(key));
    return default_val;
}

Color ParamSet::get_color(const std::string& key, const Color& default_val) const {
    if (count(key)) return Util::parse_color(attributes.at(key));
    return default_val;
}

std::vector<float> ParamSet::get_floats(const std::string& key) const {
    if (count(key)) return Util::parse_floats(attributes.at(key));
    return std::vector<float>(); // Retorna lista vazia se não encontrar
}