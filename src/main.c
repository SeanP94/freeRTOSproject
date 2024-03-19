#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"

#include "esp_event.h"
#include "driver/gpio.h"    


#define ON_BOARD_LED_BLINK_PIN GPIO_NUM_2
#define LED_BLINK_PIN GPIO_NUM_27

void toggleLED(void *parameter) {
    // Task flips a LED on and off.
    uint8_t switcher = 1;
    for (;;) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(LED_BLINK_PIN, switcher);
        switcher = 1 - switcher;
        printf("Task1\n");
    }
}

void toggleOnBoardLED(void *parameter) {
    // Task flips a LED on and off.
    uint8_t switcher = 0;
    for (;;) {
        printf("Task2\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(ON_BOARD_LED_BLINK_PIN, switcher);
        switcher = 1 - switcher;
    }
}


void app_main() {
    // Log the startup and get RTOS task variables.
    printf("Hello, Startup!\n");
    TaskHandle_t xHandler_LED = NULL;
    TaskHandle_t xHandler_ONBOARDLED = NULL;
    
    // Configure the GPIO LED Pin
    gpio_config_t ledGpioConfig = {
        .pin_bit_mask = (1ULL << LED_BLINK_PIN | 1ULL << ON_BOARD_LED_BLINK_PIN),
        .mode =  GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&ledGpioConfig));

    xTaskCreate(
        toggleLED,                 // Task
        "LED Toggle Task",         // Name task
        configMINIMAL_STACK_SIZE,  // this is the stack size in words.
        NULL,                      // No Parameters
        1,                         // Low priority
        &xHandler_LED              // Handler of the tasks
    );

    xTaskCreate(
        toggleOnBoardLED,           // Task
        "LED OnBoard ToggleTask",  // Name task
        configMINIMAL_STACK_SIZE,  // this is the stack size in words.
        NULL,                      // No Parameters
        2,                         // Low priority
        &xHandler_ONBOARDLED       // Handler of the tasks
    );

    printf("Buh-Bye!\n");
}