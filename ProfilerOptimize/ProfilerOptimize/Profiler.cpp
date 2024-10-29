#include "Profiler.h"
#include <iostream>

MyProfiler::Block::Block(const std::string& name_, Block* parent_) : name(name_), parent(parent_)
{
	start = std::chrono::steady_clock::now();
}

MyProfiler::Block::~Block()
{
	//delete all the children
	for (auto it : children)
		delete it;

	children.clear();
}

void MyProfiler::Block::End()
{
	end = std::chrono::steady_clock::now();
}

double MyProfiler::Block::GetSeconds() const
{
	return std::chrono::duration<double>(end - start).count();
}


std::string MyProfiler::Block::GetName()
{
	return name;
}

MyProfiler::Block* MyProfiler::Block::AddChild(const std::string& name_)
{
	Block* nBlock = new Block(name_, this);
	children.push_back(nBlock);
	return nBlock;
}

void MyProfiler::Block::Dump(int n) const
{
	//Print correct ammount of tabs
	for (int i = 0; i < n; i++)
	{
		std::cout << "\t";
	}
	//Print name and seconds
	std::cout << name << "	 in  " << GetSeconds() << "  seconds" << std::endl;
	//Print children
	for (const auto* c : children)
	{
		c->Dump(n + 1);
	}
}

MyProfiler::Profiler* MyProfiler::Profiler::ptr = nullptr;

MyProfiler::Profiler::~Profiler()
{
	Clear();
}

void MyProfiler::Profiler::StartBlock(std::string name_)
{
	if (!current)
	{
		current = new Block(name_);
	}
	else
		current = current->AddChild(name_);
}

void MyProfiler::Profiler::End()
{
	//stop counting time on current block
	current->End();
	//go 1 step back
	Block* parent = current->GetParent();
	//if no parent. push current to fullyfinished
	if (!parent)
	{
		FullyFinishedBlocks.push_back(current);
	}
	current = parent;
}

void MyProfiler::Profiler::Dump()
{
	for (const auto it : FullyFinishedBlocks)
	{
		it->Dump();
	}
}

void MyProfiler::Profiler::Clear()
{
	//iterate end() until current in nullptr
	while (current)
		End();
	//delete all the finished nodes
	for (auto it : FullyFinishedBlocks)
		delete it;
	FullyFinishedBlocks.clear();
}

MyProfiler::Profiler* MyProfiler::Profiler::GetPtr()
{
	if (!ptr)
	{
		ptr = new Profiler;
	}
	return ptr;
}

void MyProfiler::Profiler::DeletePtr()
{
	if(ptr)
		delete ptr;
}
