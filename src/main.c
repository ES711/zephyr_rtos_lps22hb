#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>

const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(lps22));

int main(void)
{
	int rc;

	if (!device_is_ready(dev)) {
		printf("Device %s is not ready\n", dev->name);
		return 0;
	}

	while (true) {
		struct sensor_value temp, press;
		rc = sensor_sample_fetch(dev);

		/*get temp & pressure*/
		if (rc == 0) {
			rc = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		}
		if (rc == 0) {
			rc = sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
		}
		/*get temp & pressure*/

		/*error handle*/
		if (rc != 0) {
			printf("Device %s error, code: %d", dev->name, rc);
			break;
		}

		printf("Temperature: %.1f °C\n", sensor_value_to_double(&temp));
		printf("Pressure: %1.f kPa\n", sensor_value_to_double(&press));

		k_msleep(2000);
	}
}