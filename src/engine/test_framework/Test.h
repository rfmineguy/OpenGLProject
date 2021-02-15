#pragma once

#include "glad/glad.h"
#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}
	
		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void OnResize(int width, int height) {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPtr);
		~TestMenu();

		void OnImGuiRender();
		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering test: " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		Test*& m_CurrentActiveTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}