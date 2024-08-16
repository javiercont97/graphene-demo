#include <Graphene.h>
#include <mbed.h>

#include <chrono>

void splashScreen(GrapheneDrivers::STM32F769I_Canvas &screenDriver,
				  rtos::Kernel::Clock::duration_u32 timeout = 2000ms) {
	screenDriver.clear(Graphene::NAVY);
	screenDriver.drawString(
		screenDriver.getBounds(), "STM32F769I-DISCO", Graphene::WHITE,
		Graphene::NAVY, Graphene::SYSTEM::getSystemFont("ubuntu_light_35px"),
		Graphene::TextAlignment::CENTER);

	Graphene::Rect grapheneRect = screenDriver.getBounds();
	grapheneRect.setY(50);
	grapheneRect.setHeight(grapheneRect.getHeight() - 50);

	screenDriver.drawString(
		grapheneRect, "Graphene", Graphene::WHITE, Graphene::NAVY,
		Graphene::SYSTEM::getSystemFont("ubuntu_light_23px"),
		Graphene::TextAlignment::CENTER);

	screenDriver.drawLine({0, 0},
						  {screenDriver.getWidth(), screenDriver.getHeight()},
						  Graphene::WHITE);

	ThisThread::sleep_for(timeout);
}

void shapes(GrapheneDrivers::STM32F769I_Canvas &screenDriver,
			rtos::Kernel::Clock::duration_u32 timeout = 5000ms) {
	screenDriver.clear(Graphene::NAVY);

	screenDriver.drawRectangle({10, 10}, 100, 100, Graphene::WHITE);
	screenDriver.drawCircle({200, 200}, 50, Graphene::RED);
	screenDriver.drawLine({0, 0},
						  {screenDriver.getWidth(), screenDriver.getHeight()},
						  Graphene::GREEN);
	screenDriver.drawPolygon({{150, 100}, {200, 130}, {120, 150}},
							 Graphene::PINK);

	screenDriver.fillRectangle({400, 80}, 100, 100, Graphene::LIME_GREEN);
	screenDriver.fillCircle({500, 300}, 50, Graphene::AQUA);
	screenDriver.fillPolygon({{450, 200}, {500, 230}, {420, 250}},
							 Graphene::YELLOW);

	ThisThread::sleep_for(timeout);
}

void uiThread() {
	GrapheneDrivers::STM32F769I_Canvas screenDriver;
	GrapheneDrivers::STM32F769I_Touch touchScreenDriver;
	splashScreen(screenDriver);
	shapes(screenDriver);

	// PagesView mainView(screenDriver.getBounds());
	// Graphene::GrapheneApp app(&screenDriver, &touchScreenDriver, &mainView);

	screenDriver.clear(Graphene::DARK_GRAY);

	while(true) {
		// app.eventLoop();
		ThisThread::sleep_for((rtos::Kernel::Clock::duration_u32)33ms);
	}
}

int main() {
	Thread uiThreadHandle(osPriorityNormal, 4096, nullptr, "uiThread");
	uiThreadHandle.start(uiThread);

	while (true) {
		ThisThread::yield();
	}
}