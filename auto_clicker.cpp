#include <windows.h>
#include <iostream>
#include <thread>

bool running = true;
int click_count = 0;

// Function to get proportionate coordinates
void getProportionateCoordinates(int &x, int &y, int originalX, int originalY, int originalWidth, int originalHeight)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    x = (originalX * screenWidth) / originalWidth;
    y = (originalY * screenHeight) / originalHeight;
}

// Function to move the mouse to (x, y) and click
void click_at_position(int x, int y, int interval)
{
    while (running)
    {
        // Move the mouse
        SetCursorPos(x, y);

        // Click the mouse
        INPUT inputs[2] = {};
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

        SendInput(2, inputs, sizeof(INPUT));

        click_count++;
        std::cout << "\rClick count: " << click_count << std::flush;

        // Sleep in small intervals to check for ESC key more frequently
        for (int i = 0; i < interval * 10; ++i)
        {
            if (!running)
            {
                std::cout << "\nTerminating script." << std::endl;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void listen_for_esc()
{
    while (running)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            running = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    int originalWidth = 1920;
    int originalHeight = 1080;
    int originalX = 1550;
    int originalY = 800;
    int x, y;
    int interval = 1;

    getProportionateCoordinates(x, y, originalX, originalY, originalWidth, originalHeight);

    std::cout << "Press ESC to stop the script." << std::endl;

    std::thread esc_listener(listen_for_esc);
    click_at_position(x, y, interval);

    esc_listener.join();
    return 0;
}
