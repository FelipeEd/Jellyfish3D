#pragma once

// Light types
// enum ltype
// {
//     directional,
//     point
// };

class Light : public Object
{
private:
    //ltype type;
    glm::vec3 m_color;

public:
    Light(std::string name, glm::vec3 color, glm::vec3 pos);
    glm::vec3 getColor() { return m_color; }
};
