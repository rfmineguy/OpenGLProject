#include "Test.h"
#include "imgui/imgui.h"

namespace test {
	TestMenu::TestMenu(Test*& currentTestPtr)
		:m_CurrentActiveTest(currentTestPtr)
	{
	}
	TestMenu::~TestMenu()
	{
	}

	void TestMenu::OnImGuiRender()
	{
		ImGui::Text("Tests");
		for (auto& test : m_Tests) {
			if(ImGui::Button(test.first.c_str())) {
				m_CurrentActiveTest = test.second();
			}
		}
	}
};
