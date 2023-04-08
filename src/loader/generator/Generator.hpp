#pragma once
#include "Main.hpp"
#include "Tree.hpp"

class Generator {
	private:
		inline static Generator* _instance = nullptr;

		Generator();

	public:
		Generator(Generator& other) = delete;
		void operator=(const Generator&) = delete;

		/**
		 * @brief Get the Instance object (singleton)
		 *
		 * @return Generator*
		 */
		static Generator* getInstance();

		Main generate(const Tree&);

};