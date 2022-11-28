#include "AlgorithmFactory.h"
#include "Generation/RecursiveBacktracker.h"
#include "Generation/RecursiveDivision.h"
#include "Pathfinding/Wavefront.h"


AlgorithmFactory::AlgorithmFactory() {
    m_generatorMap["Recursive backtracker"] = []() { return std::make_unique<RecursiveBacktracker>(); };
    m_generatorMap["Recursive division"] = []() { return std::make_unique<RecursiveDivision>(); };

    m_pathfindingMap["Wavefront"] = []() { return std::make_unique<Wavefront>(); };

    for (auto& [name, func] : m_generatorMap)
        m_generatorNames.push_back(name);

    for (auto& [name, func] : m_pathfindingMap)
        m_pathfinderNames.push_back(name);
}

const AlgorithmNames& AlgorithmFactory::getGeneratorNames() const {
    return m_generatorNames;
}

GeneratorPtr AlgorithmFactory::getGenerator(const std::string& name) const {
    return m_generatorMap.at(name)();
}

const AlgorithmNames& AlgorithmFactory::getPathFinderNames() const {
    return m_pathfinderNames;
}

PathfinderPtr AlgorithmFactory::getPathfinder(const std::string& name) const {
    return m_pathfindingMap.at(name)();
}
