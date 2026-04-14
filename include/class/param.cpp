#include "../param.hpp"
#include "../util.hpp"

void ParamSet::add(const std::string &key, const std::string &value)
{
    attributes[key] = value;
}

bool ParamSet::count(const std::string &key) const
{
    return attributes.find(key) != attributes.end();
}

std::string ParamSet::get_string(const std::string &key, const std::string &default_val) const
{
    if (count(key))
        return attributes.at(key);
    return default_val;
}

int ParamSet::get_int(const std::string &key, int default_val) const
{
    if (count(key))
        return Util::parse_int(attributes.at(key));
    return default_val;
}

float ParamSet::get_float(const std::string &key, float default_val) const
{
    if (count(key))
        return Util::parse_float(attributes.at(key));
    return default_val;
}

bool ParamSet::get_bool(const std::string &key, bool default_val) const
{
    if (count(key))
        return Util::parse_bool(attributes.at(key));
    return default_val;
}

Color ParamSet::get_color(const std::string &key, const Color &default_val) const
{
    if (count(key))
        return Util::parse_color(attributes.at(key));
    return default_val;
}

Point3 ParamSet::get_point3(const std::string &key, const Point3 &default_val) const
{
    if (count(key))
    {
        std::vector<float> vals = get_floats(key);
        if (vals.size() == 3)
        {
            return Point3(vals[0], vals[1], vals[2]);
        }
    }
    return default_val;
}

Vector3 ParamSet::get_vector3(const std::string &key, const Vector3 &default_val) const
{
    if (count(key))
    {
        std::vector<float> vals = get_floats(key);
        if (vals.size() == 3)
        {
            return Vector3(vals[0], vals[1], vals[2]);
        }
    }
    return default_val;
}
std::vector<float> ParamSet::get_floats(const std::string &key) const
{
    if (count(key))
        return Util::parse_floats(attributes.at(key));
    return std::vector<float>(); // Retorna lista vazia se não encontrar
}