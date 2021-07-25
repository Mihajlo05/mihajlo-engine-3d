#pragma once

#include <string>
#include "Nodes/Node.h"
#include "Nodes/PointLights/PointLight.h" //untill better lighting sysyem is developed
#include <memory>

std::unique_ptr<Node> LoadModel(Graphics& gfx, const std::string& filename, const PointLight* pLight);
