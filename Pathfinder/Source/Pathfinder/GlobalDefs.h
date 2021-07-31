#pragma once
#ifndef __GLOBALDEFS__
#define __GLOBALDEFS__

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>

namespace RL
{
	typedef std::pair<int, int> Edge;
	typedef std::vector<Edge> ArrayEdge;

	typedef std::vector<int> ArrayInt;
	typedef std::vector<double> ArrayDouble;
	typedef std::vector<float> ArrayFloat;

	typedef std::vector<ArrayInt> MatrixInt;
	typedef std::vector<ArrayDouble> MatrixDouble;
	typedef std::vector<ArrayFloat> MatrixFloat;


	Edge createEdge(int from, int to) noexcept
	{
		return std::make_pair(from, to);
	}

	template<typename T>
	void printGenericMatrixDebug(const T& tMatrix, const std::string& matrixName = "", std::streamsize strSize = 5) noexcept
	{
		std::cout << std::endl << matrixName << std::endl;
		std::cout << "------------------------------------------------------" << std::endl;

		for (size_t i = 0; i < tMatrix.size(); ++i)
		{
			std::ostringstream ss;
			for (size_t j = 0; j < tMatrix.size(); ++j)
			{
				ss << std::setw(strSize) << tMatrix[i][j] << " ";
			}

			std::cout << ss.str() << std::endl;
		}

		std::cout << std::endl;
	}

	template<typename T>
	void printGenericGraphDebug(const T& tMatrix) noexcept
	{
		const size_t N = tMatrix.size();
		for (size_t i = 0; i < N; ++i)
		{
			std::ostringstream s;
			s << i << "-> ";

			int edgesCount = 0;
			for (size_t j = 0; j < N; ++j)
			{
				if (tMatrix[i][j] != 0)
				{
					s << j << " ";
					edgesCount++;
				}
			}

			if (edgesCount > 0)
			{
				std::cout << s.str() << std::endl;
			}
		}
	}

	template<typename T>
	void printGenericArrayDebug(const T& tArray, void* excludeVal, const std::string& arrayName = "", std::streamsize strSize = 1) noexcept
	{
		std::cout << std::endl << arrayName << std::endl;
		std::cout << "------------------------------------------------------" << std::endl;

		std::ostringstream ss;
		for (size_t i = 0; i < tArray.size(); ++i)
		{
			if (excludeVal != nullptr && *static_cast<int*>(excludeVal) == int(tArray[i]))
			{
				continue;
			}

			ss << std::setw(strSize) << tArray[i] << " ";
		}

		std::cout << ss.str() << std::endl;
	}
}

#endif // __GLOBALDEFS__