#pragma once
#include <unordered_map>
#include <functional>

class IMazeGenerator;
class IPathFinder;

using GeneratorPtr = std::unique_ptr<IMazeGenerator>;
using PathfinderPtr = std::unique_ptr<IPathFinder>;

using AlgorithmNames = std::vector<std::string>;

class AlgorithmFactory {
private:
	using CreateGeneratorFunc = std::function<GeneratorPtr()>;
	using CreatePathFinderFunc = std::function<PathfinderPtr()>;
public:
	AlgorithmFactory();
	~AlgorithmFactory() = default;
public:
	const AlgorithmNames& getGeneratorNames() const;
	GeneratorPtr getGenerator(const std::string& name) const;

	const AlgorithmNames& getPathFinderNames() const;
	PathfinderPtr getPathfinder(const std::string& name) const;
private:
	std::unordered_map<std::string, CreateGeneratorFunc> m_generatorMap;
	std::unordered_map<std::string, CreatePathFinderFunc> m_pathfindingMap;

	AlgorithmNames m_generatorNames;
	AlgorithmNames m_pathfinderNames;
};