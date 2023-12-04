#include <iostream>
#include <windows.h>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>
#include <thread>

auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
std::mutex m;

void setCursor(const int& x, const int& y)
{
	SetConsoleCursorPosition(handle, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
}

void backgound_color(bool black)
{
	(black) ? SetConsoleTextAttribute(handle, 0 << 4 | 7) : SetConsoleTextAttribute(handle, 7 << 4 | 7);
}

void progress_bar_thread(int progress_bar_length, int pb_y)
{
	std::unique_lock ul(m);
	setCursor(0, pb_y + 3);
	backgound_color(true);
	std::cout << pb_y;
	setCursor(8, pb_y + 3);
	std::cout << std::this_thread::get_id();
	ul.unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < progress_bar_length; ++i)
	{
		ul.lock();
		backgound_color(false);
		setCursor(16 + i, pb_y + 3);
		std::cout << '#';
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		ul.unlock();
	}
	std::chrono::duration<double> res = std::chrono::steady_clock::now() - start;
	ul.lock();
	backgound_color(true);
	setCursor(40, pb_y + 3);
	std::cout << res.count();
}

int main()
{
	int threads_count{ 0 };
	int progress_bar_length{ 0 };

	std::cout << "Enter numbers of threads (no more 16): ";
	std::cin >> threads_count;
	if(threads_count < 1 || threads_count > 16)
	{
		std::cout << "Incorrect numbers of threads!" << std::endl;
		return 33;
	}
	
	std::cout << "Enter progress bar length (no more 20): ";
	std::cin >> progress_bar_length;
	if (progress_bar_length < 1 || progress_bar_length > 20)
	{
		std::cout << "Incorrect progress bar length!" << std::endl;
		return 42;
	}

	std::cout << "#" << '\t' << "id" << '\t' << "Progress bar" << '\t' << '\t' << "Time" << std::endl;

	std::vector<std::thread> vt;

	for(int i=0; i<threads_count; ++i)
	{
		vt.push_back(std::thread(progress_bar_thread, progress_bar_length, i));
	}
	for (auto& t : vt)
	{
		t.join();
	}
	return 0;
}
