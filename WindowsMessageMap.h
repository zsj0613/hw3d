#pragma once
#include<unordered_map>
#include<string>
#include<Windows.h>
class WindowsMessageMap
{
public:
	WindowsMessageMap() noexcept;
	std::string operator()(DWORD msg, LPARAM lp, WPARAM wp) const noexcept;//���أ���
private:
	std::unordered_map<DWORD, std::string> map;//�������ݴ洢
};
