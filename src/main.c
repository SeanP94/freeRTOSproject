#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_event.h"
#include "driver/gpio.h"    

#define LED_BLINK_PIN GPIO_NUM_2


void toggleLED(void *parameter) {
    const char *taskName = pcTaskGetName(NULL);
    uint8_t switcher = 1;
    // ESP_LOGI(taskName, "LED Pin light up is a go!\n");
    for (;;) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(LED_BLINK_PIN, switcher);
        switcher = 1 - switcher;
    }
}


void app_main() {
    // Log the startup and get variables.
    char *firstTask = pcTaskGetName(NULL);
    ESP_LOGI(firstTask, "Hello, Startup!");
    TaskHandle_t xHandler = NULL;
    BaseType_t xLEDTask;
    
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
        1024,               // this is the stack size in words.
        NULL,               // No Parameters
        1,                  // Low priority
        &xHandler           // Handler of the tasks
    );
    configASSERT(xHandler);
    
    // Run so the other function can run forever.
    for (;;) {}

    // Cleanup
    if (xHandler != NULL)
        vTaskDelete(xHandler);
    ESP_LOGI(firstTask, "Buh-Bye!");
}