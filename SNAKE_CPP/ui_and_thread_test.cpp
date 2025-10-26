//#include <iostream>
//#include <thread>
//#include <chrono>
//#include <atomic>
//int times1 = 0;
//int times2 = 0;
//void showGame() {
//	std::cout << "\nshow game for " << times1 << " times\n";
//	times1++;
//}
//
//void inputHandler(std::atomic<bool>& running) {
//	while (running) {
//		std::cout << "\nChecking keys..." << times2;
//		times2++;
//		std::this_thread::sleep_for(std::chrono::milliseconds(20)); 
//	}
//}

//int main() {
//	std::atomic<bool> running(true);
//
//	std::thread inputThread(inputHandler, std::ref(running));
//
//	for (int i = 0; i < 50; ++i) { 
//		showGame();
//		std::this_thread::sleep_for(std::chrono::milliseconds(250)); 
//	}
//
//	running = false;
//	inputThread.join();
//	std::cout << "Game ended.\n";
//	return 0;
//}