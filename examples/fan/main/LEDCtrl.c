#include "LEDCtrl.h"
#include <driver/ledc.h>
#include <esp_log.h>
#include <math.h>

static const char *TAG = "HAP_LEDCTRL";

static ledc_channel_config_t _ledCfg;
static ledc_timer_config_t _ledTmrCfg;

/**
 * @brief Initialize LED controller
 * @param freq - PWM frequency
 * @return none
 */
void ledCtrlInit(int freq) 
{
  // timer config
  _ledTmrCfg.duty_resolution = LEDC_TIMER_10_BIT;
  _ledTmrCfg.freq_hz = freq;
  _ledTmrCfg.speed_mode = LEDC_HIGH_SPEED_MODE;
  _ledTmrCfg.timer_num = LEDC_TIMER_0;
  ledc_timer_config(&_ledTmrCfg);
  ESP_LOGI(TAG, "LED Controller Timer configured");

  _ledCfg.channel = LEDC_CHANNEL_0;
  _ledCfg.duty = 0;
  _ledCfg.gpio_num = IO_LED_PIN;
  _ledCfg.speed_mode = LEDC_HIGH_SPEED_MODE;
  _ledCfg.hpoint = 0;
  _ledCfg.intr_type = LEDC_INTR_DISABLE;
  _ledCfg.timer_sel = LEDC_TIMER_0;
  ledc_channel_config(&_ledCfg);
  ledc_fade_func_install(0);

  ESP_LOGI(TAG, "LED Controller channel initialized, fade function installed");
}

/**
 * @brief Set LED brightness (percent)
 * @param percent - brightness
 * @return none
 */
void ledCtrlSetVal(float percent)
{
  int pwmVal = rintf(1023.0 * percent * 0.01f);
  ledc_set_fade_with_time(_ledCfg.speed_mode, _ledCfg.channel, pwmVal, 200);
  ledc_fade_start(_ledCfg.speed_mode, _ledCfg.channel, LEDC_FADE_NO_WAIT);
}
