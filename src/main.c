#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define LED_BLINK_PIN GPIO


void toggleLED(void *parameter) {
    vTaskDelay(500 / portTICK_PERIOD_MS);
    
    vTaskDelay(500 / portTICK_PERIOD_MS);
}


void app_main() {
    char *firstTask = pcTaskGetName(NULL);
    ESP_LOGI(firstTask, "Hello, Startup!");

    for (;;) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}