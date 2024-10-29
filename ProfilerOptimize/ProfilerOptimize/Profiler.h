#pragma once
#include <string>
#include <chrono>
#include <list>
/**********************/
// �����
// �����ϰ��� �ϴ� ���� ó���� DEBUG_PROFILER_START(__FUNCTION_NAME__);
// ���� DEBUG_PROFILER_END;
// 
// ����
// �޸� ���� ������ ���� ��������
// DEBUG_PROFILER_DUMP;
// DEBUG_PROFILER_DELETE;
// �������
//
// main.cpp�� �������� �÷�����
/**********************/
namespace MyProfiler
{
	class Block
	{
		std::string name;
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;

		std::list<Block*> children;
		Block* parent;

	public:
		Block(const std::string& name_, Block* parent_ = nullptr);
		~Block();

		void End();

		double GetSeconds() const;
		Block* GetParent() const { return parent; }
		std::string GetName();

		Block* AddChild(const std::string& name_);

		void Dump(int n = 0) const;
	};

	class Profiler
	{
		static Profiler* ptr;
		Profiler() = default;
		Profiler(const Profiler&) = default;
		~Profiler();
		Profiler& operator=(const Profiler&) = default;

		Block* current = nullptr;	

		std::list<Block*> FullyFinishedBlocks;

	public:
		void StartBlock(std::string name_);
		void End();
		void Dump();

		void Clear();

		static Profiler* GetPtr();
		static void DeletePtr();
	};
}

#ifdef _DEBUG

#define DEBUG_PROFILER_START(x) MyProfiler::Profiler::GetPtr()->StartBlock(x);
#define DEBUG_PROFILER_END MyProfiler::Profiler::GetPtr()->End();
#define DEBUG_PROFILER_DUMP MyProfiler::Profiler::GetPtr()->Dump();
#define DEBUG_PROFILER_DELETE MyProfiler::Profiler::GetPtr()->DeletePtr();

#else

#define DEBUG_PROFILER_START(x) 
#define DEBUG_PROFILER_END 
#define DEBUG_PROFILER_DUMP 
#define DEBUG_PROFILER_DELETE 

#endif // _DEBUG

#ifndef  __FUNCTION_NAME__
#ifdef WIN32
#define __FUNCTION_NAME__	__FUNCTION__
#else
#define __FUNCTION_NAME__  __func__

#endif // WIN32

#endif // ! FUNCTION_NAME
