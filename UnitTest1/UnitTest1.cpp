#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab12.12(1)/lab12.12(1).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestPrintPersonInfo)
		{
			Node* head = nullptr;
			Note note = { "Doe", "John", "123456789", {1, 4, 1990} };
			addNode(head, note);

			std::stringstream buffer;
			std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

			printPersonInfo(head, "Doe");

			std::cout.rdbuf(oldCout);

			std::string expectedOutput = "Last Name: Doe\nFirst Name: John\nPhone Number: 123456789\nBirth Date: 1/4/1990\n";
			Assert::AreEqual(expectedOutput, buffer.str());
		}

		TEST_METHOD(TestSortList)
		{
			Node* head = nullptr;
			Note note1 = { "Doe", "John", "223456789", {1, 4, 1990} };
			Note note2 = { "Smith", "Alice", "123456789", {15, 8, 1985} };
			Note note3 = { "Brown", "Charlie", "987654321", {12, 3, 1992} };

			addNode(head, note1);
			addNode(head, note2);
			addNode(head, note3);

			sortList(head);

			Assert::IsNotNull(head);
			Assert::AreEqual(std::string("Smith"), head->data.lastName);
			Assert::IsNotNull(head->next);
			Assert::AreEqual(std::string("Doe"), head->next->data.lastName);
			Assert::IsNotNull(head->next->next);
			Assert::AreEqual(std::string("Brown"), head->next->next->data.lastName);
		}

		TEST_METHOD(TestLoadFromFile)
		{
			Node* head = nullptr;

			std::ofstream outFile("testfile.txt");
			outFile << "Doe\nJohn\n123456789\n1 4 1990\n";
			outFile << "Smith\nAlice\n987654321\n15 8 1985\n";
			outFile.close();

			loadFromFile(head, "testfile.txt");

			Assert::IsNotNull(head);
			Assert::AreEqual(std::string("Doe"), head->data.lastName);
			Assert::IsNotNull(head->next);
			Assert::AreEqual(std::string("Smith"), head->next->data.lastName);
		}
	};
}