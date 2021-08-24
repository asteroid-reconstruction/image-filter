#include "JSONParser.h"
#include <sstream>

std::string ar::util::JSONParser::parse(const std::vector<FilterOutput>& foVec)
{
    char lbra = '[', rbra = ']';
    char comma = ',';

    std::stringstream json;

    json << lbra;

    for (std::vector<FilterOutput>::size_type i = 0; i < foVec.size(); ++i) {
        json << foVec[i].toJSON();
        if (i != foVec.size() - 1) json << comma;
    }

    json << rbra;

    return json.str();
}
