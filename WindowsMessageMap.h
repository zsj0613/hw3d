#pragma once
#include<unordered_map>
#include<string>
#include<Windows.h>
class WindowsMessageMap
{
public:
	WindowsMessageMap() noexcept;
	std::string operator()(DWORD msg, LPARAM lp, WPARAM wp) const noexcept;//重载（）
private:
	std::unordered_map<DWORD, std::string> map;//创建数据存储
};
