#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"

#include "esp_event.h"
#include "driver/gpio.h"    

#define LED_BLINK_PIN GPIO_NUM_2


void toggleLED(void *parameter) {
    uint8_t switcher = 1;
    for (;;) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(LED_BLINK_PIN, switcher);
        switcher = 1 - switcher;
    }
}

void printUpdates(void *parameter) {
    
    for(;;) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        printf("Hello from the 2nd task!\n");
    }
}


void app_main() {
    // Log the startup and get variables.
    printf("Hello, Startup!\n");
    TaskHandle_t xHandler = NULL;
    BaseType_t xLEDTask;
    BaseType_t xPrintTask;
    
    // Create the GPIO LED Pin
    /*
        Not sure why this isnt working... for now use the 2 lines below.
        gpio_config_t ledGpioConfig = {
            .pin_bit_mask = LED_BLINK_PIN,
            .mode =  GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };
        ESP_ERROR_CHECK(gpio_config(&ledGpioConfig));
    */
    esp_rom_gpio_pad_select_gpio(LED_BLINK_PIN);
    gpio_set_direction(LED_BLINK_PIN, GPIO_MODE_OUTPUT);


    xLEDTask = xTaskCreate(
        toggleLED,          // Task
        "LED Toggle Task",  // Name task
        1000,               // this is the stack size in words.
        NULL,               // No Parameters
        2,                  // Low priority
        &xHandler           // Handler of the tasks
    );

    xPrintTask = xTaskCreate(
        printUpdates,          // Task
        "Print Task",  // Name task
        1000,               // this is the stack size in words.
        NULL,               // No Parameters
        1,                  // Low priority
        &xHandler           // Handler of the tasks
    );

    configASSERT(xHandler);
    
    // Run so the other function can run forever.
    for (;;) {

        // Use this to stop the watchdog from failing and rebooting.
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    // Cleanup
    if (xHandler != NULL)
        vTaskDelete(xHandler); 
    printf("Buh-Bye!\n");
}